#include "vscp_ble_a2.h"
#include <openssl/evp.h>
#include <string.h>
static void be16(uint8_t *p,uint16_t x){p[0]=(uint8_t)(x>>8);p[1]=(uint8_t)x;}
static void be32(uint8_t *p,uint32_t x){p[0]=(uint8_t)(x>>24);p[1]=(uint8_t)(x>>16);p[2]=(uint8_t)(x>>8);p[3]=(uint8_t)x;}
static uint16_t rd16(const uint8_t *p){return ((uint16_t)p[0]<<8)|p[1];}
static uint32_t rd32(const uint8_t *p){return ((uint32_t)p[0]<<24)|((uint32_t)p[1]<<16)|((uint32_t)p[2]<<8)|p[3];}
static void nonce(uint8_t out[13],const uint8_t prefix[5],uint32_t epoch,uint32_t seq){
    memcpy(out,prefix,5);be32(out+5,epoch);be32(out+9,seq);
}
static void aad(uint8_t out[49],const uint8_t *frame){
    memcpy(out,"VSCP-BLE-A2",11);memcpy(out+11,frame+2,38);
}
size_t vscp_a2_encode(uint8_t out[256],const vscp_a2_sender *s,
                      uint16_t head,uint16_t cls,uint16_t type,
                      const uint8_t *plaintext,size_t n){
    if(!out||!s||n>200||(n&&!plaintext)||!s->key_id) return 0;
    uint8_t any=0;for(size_t i=0;i<16;i++)any|=s->guid[i];if(!any)return 0;
    out[0]=(uint8_t)(55+n);out[1]=0xff;
    out[2]=(uint8_t)s->company;out[3]=(uint8_t)(s->company>>8);
    out[4]=2;out[5]=1;be16(out+6,s->key_id);
    be32(out+8,s->epoch);be32(out+12,s->sequence);
    memcpy(out+16,s->guid,16);be16(out+32,head);
    be16(out+34,cls);be16(out+36,type);be16(out+38,(uint16_t)n);
    uint8_t iv[13],ad[49];nonce(iv,s->prefix,s->epoch,s->sequence);aad(ad,out);
    EVP_CIPHER_CTX *ctx=EVP_CIPHER_CTX_new();int k=0,ok=0;
    if(!ctx)return 0;
    if(EVP_EncryptInit_ex(ctx,EVP_aes_128_ccm(),NULL,NULL,NULL)!=1)goto end;
    if(EVP_CIPHER_CTX_ctrl(ctx,EVP_CTRL_AEAD_SET_IVLEN,13,NULL)!=1)goto end;
    if(EVP_CIPHER_CTX_ctrl(ctx,EVP_CTRL_AEAD_SET_TAG,16,NULL)!=1)goto end;
    if(EVP_EncryptInit_ex(ctx,NULL,NULL,s->key,iv)!=1)goto end;
    if(EVP_EncryptUpdate(ctx,NULL,&k,NULL,(int)n)!=1)goto end;
    if(EVP_EncryptUpdate(ctx,NULL,&k,ad,49)!=1)goto end;
    if(EVP_EncryptUpdate(ctx,out+40,&k,n?plaintext:(const uint8_t *)"",(int)n)!=1)goto end;
    if(EVP_EncryptFinal_ex(ctx,out+40+n,&k)!=1)goto end;
    if(EVP_CIPHER_CTX_ctrl(ctx,EVP_CTRL_AEAD_GET_TAG,16,out+40+n)!=1)goto end;
    ok=1;
end: EVP_CIPHER_CTX_free(ctx);return ok?56+n:0;
}
int vscp_a2_decode(const uint8_t *f,size_t len,vscp_a2_receiver *r,
                   uint8_t plaintext[200],size_t *n,
                   uint16_t *head,uint16_t *cls,uint16_t *type){
    if(!f||!r||!plaintext||!n||!head||!cls||!type||len<56||len>256||
       f[0]!=len-1||f[1]!=0xff||f[4]!=2||f[5]!=1||
       f[2]!=(uint8_t)r->company||f[3]!=(uint8_t)(r->company>>8)||
       rd16(f+6)!=r->key_id||memcmp(f+16,r->guid,16)!=0)return 0;
    uint8_t any=0;for(size_t i=0;i<16;i++)any|=f[16+i];if(!any)return 0;
    size_t sz=rd16(f+38);if(sz>200||len!=56+sz)return 0;
    uint32_t ep=rd32(f+8),seq=rd32(f+12);
    if(r->initialized&&(ep<r->highest_epoch||
       (ep==r->highest_epoch&&seq<=r->highest_sequence)))return 0;
    uint8_t iv[13],ad[49],tmp[200]={0};nonce(iv,r->prefix,ep,seq);aad(ad,f);
    EVP_CIPHER_CTX *ctx=EVP_CIPHER_CTX_new();int k=0,ok=0;
    if(!ctx)return 0;
    if(EVP_DecryptInit_ex(ctx,EVP_aes_128_ccm(),NULL,NULL,NULL)!=1)goto end;
    if(EVP_CIPHER_CTX_ctrl(ctx,EVP_CTRL_AEAD_SET_IVLEN,13,NULL)!=1)goto end;
    if(EVP_CIPHER_CTX_ctrl(ctx,EVP_CTRL_AEAD_SET_TAG,16,(void*)(f+40+sz))!=1)goto end;
    if(EVP_DecryptInit_ex(ctx,NULL,NULL,r->key,iv)!=1)goto end;
    if(EVP_DecryptUpdate(ctx,NULL,&k,NULL,(int)sz)!=1)goto end;
    if(EVP_DecryptUpdate(ctx,NULL,&k,ad,49)!=1)goto end;
    /* CCM verifies tag as part of the ciphertext update. */
    if(EVP_DecryptUpdate(ctx,tmp,&k,f+40,(int)sz)!=1)goto end;
    memcpy(plaintext,tmp,sz);*n=sz;
    *head=rd16(f+32);*cls=rd16(f+34);*type=rd16(f+36);
    r->highest_epoch=ep;r->highest_sequence=seq;r->initialized=1;
    ok=1;
end: EVP_CIPHER_CTX_free(ctx);OPENSSL_cleanse(tmp,sizeof(tmp));return ok;
}

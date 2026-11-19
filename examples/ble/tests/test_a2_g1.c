#include <assert.h>
#include <stdint.h>
#include <string.h>
#include "vscp_ble_a2.h"
#include "vscp_ble_g1.h"
int main(void){
    vscp_a2_sender s={0};s.company=0xffff;s.key_id=1;s.epoch=1;s.sequence=2;
    for(int i=0;i<16;i++){s.guid[i]=(uint8_t)i;s.key[i]=(uint8_t)i;}
    for(int i=0;i<5;i++)s.prefix[i]=(uint8_t)(0xa0+i);
    uint8_t pt[]={0x11,0x22,0x33},ad[256],plain[200]={0};
    size_t len=vscp_a2_encode(ad,&s,0,10,6,pt,3);
    assert(len==59);
    const uint8_t expected[]={0x3c,0x45,0x32,0x03,0x97,0x88,0xb4,0x4a,0x4a,
        0xd3,0x21,0xc6,0x49,0x37,0x48,0xc0,0xf6,0xc4,0xd1};
    assert(!memcmp(ad+40,expected,sizeof(expected)));
    vscp_a2_receiver r={0};r.company=s.company;r.key_id=s.key_id;
    memcpy(r.guid,s.guid,16);memcpy(r.key,s.key,16);memcpy(r.prefix,s.prefix,5);
    size_t n=0;uint16_t head=0,cls=0,type=0;
    assert(vscp_a2_decode(ad,len,&r,plain,&n,&head,&cls,&type));
    assert(n==3&&!memcmp(pt,plain,3)&&cls==10&&type==6);
    assert(!vscp_a2_decode(ad,len,&r,plain,&n,&head,&cls,&type)); /* replay */
    r.initialized=0;ad[40]^=1;
    assert(!vscp_a2_decode(ad,len,&r,plain,&n,&head,&cls,&type));
    ad[40]^=1;ad[34]^=1;
    assert(!vscp_a2_decode(ad,len,&r,plain,&n,&head,&cls,&type));
    uint8_t rec[521],frag[64];uint8_t guid[16];
    memcpy(guid,s.guid,16);
    uint8_t data[100];for(int i=0;i<100;i++)data[i]=(uint8_t)i;
    size_t total=vscp_g1_encode(rec,sizeof(rec),42,guid,0,10,6,data,100);
    assert(total==134);
    vscp_g1_reassembly state={0};size_t off=0;
    while(off<total){
        size_t flen=vscp_g1_fragment(frag,sizeof(frag),rec,total,off,23);
        assert(flen>=9);
        int result=vscp_g1_feed(&state,frag,flen,1000,521);
        off+=flen-8;
        assert(result==(off==total?1:0));
    }
    assert(!memcmp(state.record,rec,total));
    vscp_g1_reset(&state);
    size_t flen=vscp_g1_fragment(frag,sizeof(frag),rec,total,0,23);
    assert(vscp_g1_feed(&state,frag,flen,1000,521)==0);
    assert(vscp_g1_feed(&state,frag,flen,1001,521)==-1); /* overlap */
    vscp_g1_reset(&state);
    assert(vscp_g1_feed(&state,frag,flen,1000,521)==0);
    assert(vscp_g1_feed(&state,frag,flen,7001,521)==-1); /* timeout */
    return 0;
}

#ifndef VSCP_BLE_E1_H
#define VSCP_BLE_E1_H
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define VSCP_E1_MAX_DATA 222u
#define VSCP_E1_AD_TYPE 0xffu
#define VSCP_E1_VERSION 1u

/* Output includes AD Length, AD Type and little-endian Company Identifier.
   Return 0 on invalid arguments/size; otherwise the complete AD length. */
static inline size_t vscp_e1_encode(uint8_t *out, size_t cap, uint16_t company,
                                    uint32_t seq, const uint8_t guid[16],
                                    uint16_t head, uint16_t cls, uint16_t type,
                                    const uint8_t *data, size_t n)
{
    if (!out || !guid || n > VSCP_E1_MAX_DATA || cap < 34u+n ||
        (n && !data)) return 0;
    uint8_t any = 0;
    for (size_t i=0; i<16; ++i) any |= guid[i];
    if (!any) return 0;
    out[0]=(uint8_t)(33u+n); out[1]=VSCP_E1_AD_TYPE;
    out[2]=(uint8_t)company; out[3]=(uint8_t)(company>>8);
    out[4]=VSCP_E1_VERSION; out[5]=0;
    out[6]=(uint8_t)(seq>>24); out[7]=(uint8_t)(seq>>16);
    out[8]=(uint8_t)(seq>>8); out[9]=(uint8_t)seq;
    memcpy(out+10,guid,16);
    out[26]=(uint8_t)(head>>8); out[27]=(uint8_t)head;
    out[28]=(uint8_t)(cls>>8); out[29]=(uint8_t)cls;
    out[30]=(uint8_t)(type>>8); out[31]=(uint8_t)type;
    out[32]=(uint8_t)(n>>8); out[33]=(uint8_t)n;
    if(n) memcpy(out+34,data,n);
    return 34u+n;
}

typedef struct {
    uint32_t seq;
    uint8_t guid[16];
    uint16_t head, cls, type;
    const uint8_t *data; /* points inside input buffer */
    size_t size;
} vscp_e1_event;

/* Caller must supply one complete AD structure, not a whole AD data set.
   Returns 1 for valid E1, otherwise 0. Security: E1 is untrusted S0 only. */
static inline int vscp_e1_decode(const uint8_t *ad, size_t len,
                                  uint16_t expected_company, vscp_e1_event *ev)
{
    if(!ad || !ev || len<34 || len>256 || ad[0] != len-1 ||
       ad[1]!=0xff || ad[2]!=(uint8_t)expected_company ||
       ad[3]!=(uint8_t)(expected_company>>8) ||
       ad[4]!=1 || ad[5]!=0) return 0;
    size_t n=((size_t)ad[32]<<8)|ad[33];
    if(n>222 || len!=34+n) return 0;
    uint8_t any=0;
    for(size_t i=10;i<26;i++) any|=ad[i];
    if(!any) return 0;
    ev->seq=((uint32_t)ad[6]<<24)|((uint32_t)ad[7]<<16)|
            ((uint32_t)ad[8]<<8)|ad[9];
    memcpy(ev->guid,ad+10,16);
    ev->head=((uint16_t)ad[26]<<8)|ad[27];
    ev->cls=((uint16_t)ad[28]<<8)|ad[29];
    ev->type=((uint16_t)ad[30]<<8)|ad[31];
    ev->data=ad+34; ev->size=n;
    return 1;
}
#endif

#include "vscp_ble_g1.h"
#include <string.h>
static void wr16(uint8_t *p,uint16_t v){p[0]=v>>8;p[1]=v;}
static void wr32(uint8_t *p,uint32_t v){p[0]=v>>24;p[1]=v>>16;p[2]=v>>8;p[3]=v;}
static uint16_t rd16(const uint8_t *p){return ((uint16_t)p[0]<<8)|p[1];}
static uint32_t rd32(const uint8_t *p){return ((uint32_t)p[0]<<24)|((uint32_t)p[1]<<16)|((uint32_t)p[2]<<8)|p[3];}
void vscp_g1_reset(vscp_g1_reassembly *r){if(r)memset(r,0,sizeof(*r));}
size_t vscp_g1_encode(uint8_t *o,size_t cap,uint32_t id,const uint8_t guid[16],
                      uint16_t head,uint16_t cls,uint16_t type,
                      const uint8_t *data,size_t n){
    if(!o||!guid||!id||n>487||cap<34+n||(n&&!data))return 0;
    uint8_t any=0;for(int i=0;i<16;i++)any|=guid[i];if(!any)return 0;
    o[0]=1;o[1]=1;o[2]=0;o[3]=0;wr32(o+4,id);wr16(o+8,(uint16_t)(22+n));
    memcpy(o+10,guid,16);wr16(o+26,head);wr16(o+28,cls);
    wr16(o+30,type);wr16(o+32,(uint16_t)n);
    if(n)memcpy(o+34,data,n);
    return 34+n;
}
size_t vscp_g1_fragment(uint8_t *o,size_t cap,const uint8_t *record,
                        size_t record_len,size_t off,size_t mtu){
    if(!o||!record||record_len<34||record_len>521||off>=record_len||
       mtu<23||cap<9||record[0]!=1||record[1]!=1||!rd32(record+4))return 0;
    size_t max=mtu-11;
    if(max>cap-8)max=cap-8;
    size_t n=record_len-off;if(n>max)n=max;
    if(!n||(off==0&&n<10))return 0;
    o[0]=1;o[1]=(uint8_t)((off==0?1:0)|(off+n==record_len?2:0));
    wr32(o+2,rd32(record+4));wr16(o+6,(uint16_t)off);
    memcpy(o+8,record+off,n);return 8+n;
}
int vscp_g1_feed(vscp_g1_reassembly *r,const uint8_t *f,size_t len,
                 uint64_t now,size_t max_record){
    if(!r)return -1;
    if(!f||len<9||f[0]!=1||(f[1]&~3u)||!rd32(f+2)||
       max_record<34||max_record>521){vscp_g1_reset(r);return -1;}
    if(r->active&&((now<r->started_ms)||(now-r->started_ms>5000))){
        vscp_g1_reset(r);return -1;
    }
    size_t off=rd16(f+6),chunk=len-8;uint32_t id=rd32(f+2);
    if(off==0){
        if(!(f[1]&1)||chunk<10||r->active||f[8]!=1||f[9]!=1||
           f[10]!=0||f[11]!=0||rd32(f+12)!=id){vscp_g1_reset(r);return -1;}
        size_t total=12u+rd16(f+16);
        if(total<34||total>max_record||total>521||chunk>total){vscp_g1_reset(r);return -1;}
        vscp_g1_reset(r);r->active=1;r->transaction=id;
        r->expected=total;r->started_ms=now;
    } else if(!r->active||(f[1]&1)||r->transaction!=id){vscp_g1_reset(r);return -1;}
    if(off!=r->received||chunk>r->expected-off){vscp_g1_reset(r);return -1;}
    memcpy(r->record+off,f+8,chunk);r->received+=chunk;
    r->started_ms=now;
    if(r->received==r->expected){
        if(!(f[1]&2)||r->record[0]!=1||r->record[1]!=1||
           r->record[2]!=0||r->record[3]!=0||
           rd32(r->record+4)!=id||
           rd16(r->record+8)!=r->expected-12||
           rd16(r->record+32)!=r->expected-34){
            vscp_g1_reset(r);return -1;
        }
        uint8_t any=0;for(int i=10;i<26;i++)any|=r->record[i];
        if(!any){vscp_g1_reset(r);return -1;}
        r->active=0;return 1;
    }
    if(f[1]&2){vscp_g1_reset(r);return -1;}
    return 0;
}

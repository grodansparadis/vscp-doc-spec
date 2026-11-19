#include <assert.h>
#include <stdint.h>
#include <string.h>
#include "vscp_ble_e1.h"
int main(void) {
    uint8_t guid[16], frame[256];
    for(unsigned i=0;i<16;i++) guid[i]=(uint8_t)i;
    const uint8_t payload[]={0x11,0x22};
    const uint8_t expected[]={
        0x23,0xff,0xff,0xff,0x01,0,0,0,0,1,
        0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
        0,0,0,10,0,6,0,2,0x11,0x22
    };
    size_t n=vscp_e1_encode(frame,sizeof(frame),0xffff,1,guid,0,10,6,payload,2);
    assert(n==sizeof(expected) && !memcmp(frame,expected,n));
    vscp_e1_event ev;
    assert(vscp_e1_decode(frame,n,0xffff,&ev));
    assert(ev.seq==1 && ev.cls==10 && ev.type==6 && ev.size==2);
    frame[5]=0x80; assert(!vscp_e1_decode(frame,n,0xffff,&ev)); frame[5]=0;
    frame[0]--; assert(!vscp_e1_decode(frame,n,0xffff,&ev)); frame[0]++;
    frame[33]=3; assert(!vscp_e1_decode(frame,n,0xffff,&ev)); frame[33]=2;
    assert(!vscp_e1_decode(frame,n-1,0xffff,&ev));
    uint8_t maxdata[222]={0};
    assert(vscp_e1_encode(frame,sizeof(frame),0xffff,2,guid,0,10,6,maxdata,222)==256);
    assert(vscp_e1_decode(frame,256,0xffff,&ev));
    assert(vscp_e1_encode(frame,sizeof(frame),0xffff,2,guid,0,10,6,maxdata,223)==0);
    return 0;
}

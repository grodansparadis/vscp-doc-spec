#ifndef VSCP_BLE_G1_H
#define VSCP_BLE_G1_H
#include <stddef.h>
#include <stdint.h>
#define VSCP_G1_MAX_DATA 487u
#define VSCP_G1_MAX_RECORD 521u
/* Platform-neutral record/fragment layer for either GATT role.
 * The host stack must provide authenticated ATT permissions, CCCDs, HELLO,
 * control indications, authorization and transaction scheduling. */
typedef struct {
    uint8_t record[VSCP_G1_MAX_RECORD];
    uint8_t active;
    uint32_t transaction;
    size_t expected,received;
    uint64_t started_ms;
} vscp_g1_reassembly;
size_t vscp_g1_encode(uint8_t *out,size_t cap,uint32_t txid,
                      const uint8_t guid[16],uint16_t head,uint16_t cls,
                      uint16_t type,const uint8_t *data,size_t n);
size_t vscp_g1_fragment(uint8_t *out,size_t cap,const uint8_t *record,
                        size_t record_len,size_t offset,size_t att_mtu);
/* Returns -1 invalid, 0 incomplete, 1 complete; 5-second deadline.
 * On complete, r->record holds the validated complete record.
 * A caller MUST authorize the event before delivery. */
int vscp_g1_feed(vscp_g1_reassembly *r,const uint8_t *fragment,
                 size_t len,uint64_t now_ms,size_t max_record);
void vscp_g1_reset(vscp_g1_reassembly *r);
#endif

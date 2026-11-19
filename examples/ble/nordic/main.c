/* nRF5 SDK + SoftDevice example: requires an SDK project configured with
   SoftDevice extended advertising support. Not nRF Connect SDK (use Zephyr).
   This file supplies the advertising initialization/start routine; invoke it
   after normal SoftDevice initialization and LF clock configuration. */
#include <stdint.h>
#include <string.h>
#include "ble_gap.h"
#include "nrf_sdh_ble.h"
#include "../common/vscp_ble_e1.h"

static uint8_t adv_data[256];
static uint8_t handle=BLE_GAP_ADV_SET_HANDLE_NOT_SET;
static const uint8_t guid[16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

uint32_t vscp_e1_nordic_start(void)
{
    const uint8_t sample[]={0x11,0x22};
    size_t n=vscp_e1_encode(adv_data,sizeof(adv_data),0xffff,1,
                            guid,0,10,6,sample,sizeof(sample));
    if(!n) return NRF_ERROR_INVALID_PARAM;
    ble_gap_adv_data_t data={0};
    data.adv_data.p_data=adv_data;
    data.adv_data.len=(uint16_t)n;
    ble_gap_adv_params_t p={0};
    p.properties.type=BLE_GAP_ADV_TYPE_EXTENDED_NONCONNECTABLE_NONSCANNABLE_UNDIRECTED;
    p.primary_phy=BLE_GAP_PHY_1MBPS;
    p.secondary_phy=BLE_GAP_PHY_1MBPS;
    p.interval=160;
    p.duration=0;
    uint32_t rc=sd_ble_gap_adv_set_configure(&handle,&data,&p);
    if(rc!=NRF_SUCCESS) return rc;
    return sd_ble_gap_adv_start(handle,APP_BLE_CONN_CFG_TAG);
}

#include <stdio.h>
#include <string.h>
#include "esp_err.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "nimble/nimble_port.h"
#include "host/ble_hs.h"
#include "host/ble_gap.h"
#include "host/util/util.h"
#include "vscp_ble_e1.h"

/* ESP-IDF NimBLE extended-advertising API; requires supported controller and
   CONFIG_BT_NIMBLE_EXT_ADV. Test-only GUID/company; no privileged events. */
static const char *TAG="VSCP_E1";
static const uint8_t guid[16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
static uint8_t ad[256];
static void on_sync(void)
{
    struct ble_gap_ext_adv_params p={0};
    p.connectable=0;
    p.scannable=0;
    p.legacy_pdu=0;
    p.primary_phy=BLE_HCI_LE_PHY_1M;
    p.secondary_phy=BLE_HCI_LE_PHY_1M;
    p.itvl_min=160;
    p.itvl_max=200;
    int rc=ble_gap_ext_adv_configure(0,&p,NULL,NULL,NULL);
    if(rc){ESP_LOGE(TAG,"extended advertising unavailable: %d",rc);return;}
    const uint8_t data[]={0x11,0x22};
    size_t n=vscp_e1_encode(ad,sizeof(ad),0xffff,1,guid,0,10,6,data,sizeof(data));
    if(!n){ESP_LOGE(TAG,"encode failed");return;}
    struct os_mbuf *m=os_msys_get_pkthdr(n,0);
    if(!m){ESP_LOGE(TAG,"mbuf allocation failed");return;}
    /* NimBLE extended-advertising API accepts full AD structure bytes. */
    if(os_mbuf_append(m,ad,n)){os_mbuf_free_chain(m);return;}
    rc=ble_gap_ext_adv_set_data(0,m); /* ownership transferred by API */
    if(rc){ESP_LOGE(TAG,"set data failed: %d",rc);return;}
    rc=ble_gap_ext_adv_start(0,0,0);
    if(rc)ESP_LOGE(TAG,"start failed: %d",rc);
    else ESP_LOGI(TAG,"E1 S0 advertising started (test company ID)");
}
void app_main(void)
{
    esp_err_t err=nvs_flash_init();
    if(err!=ESP_OK){ESP_LOGE(TAG,"NVS init: %s",esp_err_to_name(err));return;}
    nimble_port_init();
    ble_hs_cfg.sync_cb=on_sync;
    nimble_port_run();
}

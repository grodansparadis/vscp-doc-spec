#include <zephyr/kernel.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/sys/printk.h>
#include "../../common/vscp_ble_e1.h"

/* Demo GUID: provision a real stable GUID before deployment. */
static const uint8_t guid[16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
static uint8_t ad[256];
static struct bt_le_ext_adv *adv;

int main(void)
{
    int err=bt_enable(NULL);
    if(err){printk("Bluetooth init failed %d\n",err);return 0;}
    const struct bt_le_adv_param p={
        .id=BT_ID_DEFAULT,
        .sid=0,
        .secondary_max_skip=0,
        .options=BT_LE_ADV_OPT_EXT_ADV,
        .interval_min=BT_GAP_ADV_FAST_INT_MIN_2,
        .interval_max=BT_GAP_ADV_FAST_INT_MAX_2
    };
    err=bt_le_ext_adv_create(&p,NULL,&adv);
    if(err){printk("Extended advertising unavailable %d\n",err);return 0;}
    uint8_t sample[]={0x11,0x22};
    size_t len=vscp_e1_encode(ad,sizeof(ad),0xffff,1,guid,0,10,6,sample,sizeof(sample));
    if(!len){printk("E1 encoding failed\n");return 0;}
    /* Zephyr bt_data takes AD Data only (company + VSCP), not Length/Type. */
    const struct bt_data data[]={BT_DATA(BT_DATA_MANUFACTURER_DATA,ad+2,len-2)};
    err=bt_le_ext_adv_set_data(adv,data,ARRAY_SIZE(data),NULL,0);
    if(err){printk("Set advertising data failed %d\n",err);return 0;}
    err=bt_le_ext_adv_start(adv,BT_LE_EXT_ADV_START_DEFAULT);
    if(err){printk("Start extended advertising failed %d\n",err);return 0;}
    printk("VSCP E1 S0 extended advertiser running (test company ID)\n");
    for(;;) k_sleep(K_SECONDS(60));
}

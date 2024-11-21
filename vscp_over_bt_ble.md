# VSCP over BLE

The general BLE frame format is as follows

![VSCP Bluetooth](https://developerhelp.microchip.com/xwiki/bin/download/applications/ble/introduction/bluetooth-architecture/bluetooth-controller-layer/bluetooth-link-layer/Packet-Types/WebHome/packet-format-top-level.png?width=600&height=210&rev=1.1)

## Advertising format

The general BLE advertising format is as follows

![BLE Advertising](https://developerhelp.microchip.com/xwiki/bin/download/applications/ble/introduction/bluetooth-architecture/bluetooth-controller-layer/bluetooth-link-layer/Packet-Types/WebHome/adv-channel-pdu.png?width=450&height=183&rev=1.1)


The VSCP advertising payload format is as follows


| Description | Size | Note |    
| --- | --- | --- |
| head | 8-bit | |
| timestamp | 32 bit | Microsecond timestamp
| vscp-class | 32-bits | VSCP class |
| vscp-type | 32 bits | VSCP type |
| data | max =  37 - 13 = 24 | VSCP data |
   
  * GUID is constructed from BLE MAC, prefix _FF:FF:FF:FF:FF:FF:FF:F8:YY:YY:YY:YY:YY:YY:XX:XX_ where _YY:YY:YY:YY:YY:YY_ is the BLE MAC and _XX:XX_ is the nodeid. 
  * obid is set by receiver, zero if not used.
  * time is set by receiver


[filename](./bottom_copyright.md ':include')
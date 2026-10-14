# Globally Unique Identifiers

To classify as a node in a VSCP net, a node must be uniquely identified by a globally unique 16-byte (yes, that is 16-byte (128 bits), not 16-bit) identifier. This number uniquely identifies all devices around the world and can be used as a means to obtain device descriptions as well as drivers for a specific platform and for a specific device. 

The manufacturer of the device can also use the number as a serial number to track manufactured devices. In many other environments and protocols there is a high cost in getting a globally unique number for your equipment. This is not the case with VSCP. If you own an Ethernet card you also have what is needed to create your own GUIDs. 

The GUID address is not normally used during communication with a node. Instead an 8-bit address is used. This gives a low protocol overhead. A segment can have a maximum of 127 nodes even if the address gives the possibility for 256 nodes. The 8-bit address is received from a master node called the segment controller. The short address is also called the node's nickname-ID or nickname address.

Besides the GUID it is recommended that all nodes have a node description string in the firmware that points to a URL that can give full information about the node and its family of devices. As well as providing information about the node, this address can point at drivers for various operating systems or segment controller environments.

A general discussion of UUIDs/GUIDs can be found [here](https://en.wikipedia.org/wiki/Universally_unique_identifier).

There are different types of GUIDs available

| Type | Description |
| :---: | ----------- |
| 0 | Standard GUID (recommended) |
| 1 | IPv6 address |
| 2 | RFC 4122 Version 1 |
| 3 | RFC 4122 Version 4 |
| 4 | Random number (not recommended) |

GUIDs are written in hexadecimal form with the most significant byte first. For example

    FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:01

Hex characters can be written in upper or lower case. The above GUID can also be written as

    ff:ff:ff:ff:ff:ff:ff:ff:ff:ff:ff:ff:ff:ff:ff:01

As FF is very common, a GUID with FF in the most significant bytes can be written as

    *:1

This is the same as above. The * is a shortcut notation for FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF and '-' is a shorthand for 00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00

You can also group GUIDs in other ways

    ::0102:03aa:44:01:30

this is equal to 

    00:00:00:00:00:00:00:00:00:01:02:03:AA:44:01:30

while 

    *:0102:03aa:44:01:30

is equal to

    FF:FF:FF:FF:FF:FF:FF:FF:FF:01:02:03:AA:44:01:30

You can use the standard form for GUIDs

    {FFFFFFFF-FFFF-FFFF-0102-03AABB440130}

which can also be written as

    FFFFFFFF-FFFF-FFFF-0102-03AABB440130

or you can place the dashes anywhere you like, 

e.g.

    FF-FF-FF-FF-FFFF-FFFF-0102-03AABB-440130

and

    FFFFFFFF-FFFF-FFFF-0102-03-AA-BB-440130

are OK and all are equal to

    FF:FF:FF:FF:FF:FF:FF:FF:01:02:03:AA:BB:44:01:30
    

A GUID with all bytes set to FF is called a broadcast GUID and is used for broadcasting events to all nodes in the segment. You can write it as

    *

or

    FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF

A GUID with all bytes set to zero can be written as

    - 

or as

    ::

i.e.

    00000000-0000-0000-0000-000000000000

This GUID has a special meaning on its way through VSCP interfaces. The first interface the event passes through should fill in its interface GUID with the two lowest bytes set to zero. This is used for tracking the path of the event through the system.

Actually you can group the GUID in any way you like as long as you keep the most significant byte first and the least significant byte last. The grouping is just for readability and it's up to you how you want to group it.

Just as with ::1, for GUIDs starting with zeros you can write

    -:1,2,3

giving

    00:00:00:00:00:00:00:00:00:00:00:00:00:01:02:03

The wildcards '-', '*' and '::' can only be used once.

## Some examples of valid GUIDs

| Shorthand | Full GUID | Note |
| --------- | --------- | ---- |
| 00:11:22:33:44:55:66:77:88:99:AA:BB:CC:DD:EE:FF  | 00:11:22:33:44:55:66:77:88:99:AA:BB:CC:DD:EE:FF | Legacy form |
| 00112233445566778899AABBCCDDEEFF  | 00:11:22:33:44:55:66:77:88:99:AA:BB:CC:DD:EE:FF | Compact form |
| - | 00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00 | Shorthand for all zeros. If received, set to interface GUID. |
| :: | 00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00 | Same as above. |
| * | FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF | |
| *:0102:03aa:44:01:30 | FF:FF:FF:FF:FF:FF:FF:FF:FF:01:02:03:AA:44:01:30 | |
| -:0102:03aa:44:01:30 | 00:00:00:00:00:00:00:00:00:01:02:03:AA:44:01:30 | |
| -:1,2,3 | 00:00:00:00:00:00:00:00:00:00:00:00:00:01:02:03 | |
| 01:02:02:-04 | 01:02:02:00:00:00:00:00:00:00:00:00:00:00:00:04 | Dash in the middle adds zeros at that position |
| 01:02:03::04 | 01:02:03:00:00:00:00:00:00:00:00:00:00:00:00:04 | Double colon adds zeros in the middle |
| 01:02:03:*:45 | 01:02:03:FF:FF:FF:FF:FF:FF:FF:FF:FF:45 | Asterisk in the middle adds FF's at that position |
| 01:- | 01:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00 | Dash at end adds zeros at end |
| 01:: | 01:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00 | Same as above |
| 01 | 01:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00 | Same as above |
| 01* | 01:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF | Asterisk at end adds FF's at end |
| 01:* | 01:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF | Same as above |
| 001122 | 00:11:22:00:00:00:00:00:00:00:00:00:00:00:00:00 | Compact form with implicit trailing zeros |
| {FFFFFFFF-FFFF-FFFF-0102-03AABB440130} | FF:FF:FF:FF:FF:FF:FF:FF:01:02:03:AA:BB:44:01:30 | Standard form with braces. |
| FFFFFFFF-FFFF-FFFF-0102-03AABB440130 | FF:FF:FF:FF:FF:FF:FF:FF:01:02:03:AA:BB:44:01:30 | Standard form without braces. |
| {FFFFFFFFFFFFFFFE-010203AABB44-0130} | FF:FF:FF:FF:FF:FF:FF:FE:01:02:03:AA:BB:44:01:30 | Form suitable for predefined GUIDs as described below. |


## Predefined VSCP GUIDs

It is possible to create your own GUID without requesting a series and still get a valid VSCP GUID.


 | Assigned Global Unique IDs | IDs Series Reserved to/for | 
 | :-------------------------- | -------------------------- | 
 | <pre>FF:FF:FF:FF:FF:FF:FF:FF:YY:YY:YY:YY:YY:YY:YY:YY</pre> | Dallas Semiconductor GUIDs. This is the 1-wire/iButton 64-bit ID. The device code is in the MSB byte and CRC in the LSB byte. | 
 | <pre>FF:FF:FF:FF:FF:FF:FF:FE:YY:YY:YY:YY:YY:YY:XX:XX</pre>  | Ethernet Device GUIDs. The holder of the address can freely use the two least significant bytes of the GUID. MAC address in MSB - LSB order. Also called MAC-48 or EUI-48 by IEEE | 
 | <pre>FF:FF:FF:FF:FF:FF:FF:FD:YY:YY:YY:YY:XX:XX:XX:XX</pre> | Internet version 4 GUIDs. This is a 32-bit ID so the holder of the address can freely use the four least significant bytes of the GUID. IPv4 address in MSB - LSB order. | 
 | <pre>FF:FF:FF:FF:FF:FF:FF:FC:XX:XX:XX:XX:XX:XX:XX:XX</pre> | Private. Use for in-house local use. The GUID should never appear outside your local segments. | 
 | <pre>FF:FF:FF:FF:FF:FF:FF:FB:YY:YY:YY:XX:XX:XX:XX:XX</pre> | ISO ID. This is a three byte ID so the holder of the ISO ID can freely use the five least significant bytes of the GUID. | 
 | <pre>FF:FF:FF:FF:FF:FF:FF:FA:YY:YY:YY:YY:XX:XX:XX:XX</pre> | CiA (CAN in Automation) vendor ID. This is a 32-bit ID so the holder of the vendor ID can freely use the four least significant bytes of the GUID. | 
 | <pre>FF:FF:FF:FF:FF:FF:FF:F9:YY:YY:YY:XX:XX:XX:XX:XX</pre> | ZigBee 802.15.4 OID. This is a 24-bit ID so the holder of the OID can freely use the five least significant bytes of the GUID. | 
 | <pre>FF:FF:FF:FF:FF:FF:FF:F8:YY:YY:YY:YY:YY:YY:XX:XX</pre>  | Bluetooth MAC. This is a 48-bit ID so the holder of the address can freely use the two least significant bytes of the GUID. | 
 | <pre>FF:FF:FF:FF:FF:FF:FF:F7:YY:YY:YY:YY:YY:YY:YY:YY</pre> | IEEE EUI-64. This is a 64-bit ID. The upper three bytes are purchased from IEEE by the company that releases the product. The lower five bytes are assigned by the device and must be unique. | 
 | <pre>FF:FF:FF:FF:FF:FF:FF:F6:00:YY:YY:YY:YY:YY:YY:YY</pre> | Reserved for RAMTRON MRAM (and compatible), seven byte IDs. | 
 | <pre>FF:FF:FF:FF:FF:FF:FF:F6:01:YY:YY:YY:YY:YY:YY:YY - </pre><pre>FF:FF:FF:FF:FF:FF:FF:F6:FF:YY:YY:YY:YY:YY:YY:YY</pre> | Reserved for other future seven byte IDs (memory devices) that may have an ID, such as PRAM etc. | 
 | <pre>FF:FF:FF:FF:FF:FF:FF:F5:XX:XX:XX:XX:XX:XX:XX:XX</pre> | Reserved for VSCP & Friends demo and example usage. | 
 | <pre>FF:FF:FF:FF:FF:FF:FF:F4:XX:XX:XX:XX:XX:XX:YY:YY</pre> | Reserved for VSCP grouping where YY defines the group ID. XX is not currently used. | 
 | <pre>FF:FF:FF:FF:FF:FF:FF:F3:XX:XX:XX:XX:YY:YY:ZZ:ZZ</pre> | Reserved for VSCP interfaces where YY:YY defines the interface and ZZ:ZZ the node ID for a node on that interface. XX:XX:XX:XX can be used as the user likes, typically host ID (IPv4 address for example) | 
 | <pre>FF:FF:FF:FF:FF:FF:FF:F2:XX:XX:ZZ:ZZ:ZZ:ZZ:ZZ:ZZ</pre> | Reserved for LoRa 2 byte MAC address |
 | <pre>FF:FF:FF:FF:FF:FF:FF:F1:XX:XX:XX:XX:ZZ:ZZ:ZZ:ZZ</pre> | Reserved for LoRa 4 byte MAC address |
 | <pre>FF:FF:FF:FF:FF:FF:FF:F0:XX:XX:XX:XX:XX:XX:ZZ:ZZ</pre> | Reserved for LoRa 6 byte MAC address |
 | <pre>FF:FF:FF:FF:FF:FF:FF:00:00:00:00:00:00:00:00:00 - </pre><pre>FF:FF:FF:FF:FF:FF:FF:EF:FF:FF:FF:FF:FF:FF:FF:FF</pre> | Reserved  |
 | <pre>00:00:00:00:00:00:00:00:00:00:00:00:xx:xx:xx:xx</pre> | Lab usage. You can use this range for your own development or for in-house local use. The GUID should never appear outside your local segments. | 
 | <pre>FE:YY:YY:YY:YY:YY:YY:YY:YY:YY:YY:YY:YY:YY:YY:YY</pre> | Reserved for a generated 128-bit GUID where the most significant byte is replaced by FE. Only use for Level II and on internal nets. [https://hegel.ittc.ku.edu/topics/internet/internet-drafts/draft-l/draft-leach-uuids-guids-01.txt](https://hegel.ittc.ku.edu/topics/internet/internet-drafts/draft-l/draft-leach-uuids-guids-01.txt) | 
 | <pre>FD:AA:BB:YY:YY:YY:YY:YY:YY:YY:YY:YY:YY:YY:YY:YY</pre> | Reserved for MCU internal IDs provided by some manufacturers. AA:BB is the manufacturer code. There is room for a 13-byte ID. If the particular CPU has an ID that is shorter, put the used bits to the right and set unused MSB bytes to zero. See information below. | 

## MCU stored GUIDs

As explained above, GUIDs with 0xFD in the most significant byte are reserved for MCUs with an on-chip stored ID. If your manufacturer is not in the list below please let us know and we will add it (or you can add it yourself). Thus new MCUs will be added as they are needed by someone.

### Manufacturer code

 | Code | Description                         |
 | :----: | :-----------                      |
 | 0    | Microchip                           |
 | 1    | Atmel                               |
 | 2    | ST                                  |
 | 3    | NXP                                 |
 | 4    | Freescale                           |
 | 5    | Renesas                             |
 | 6    | Gecko                               |
 | 7    | Texas Instruments (+ Luminary Micro) |
 | 8    | GigaDevice Semiconductor |
 | 9    | Raspberry Pi |
 | 10   | Espressif |
 | 255   | Undefined/Unknown manufacturer (for compatibility) |
 | 0xffff | Undefined/Unknown manufacturer |

### Family codes

**!!!Family codes are deprecated as of 1.20.0.**


[Grodans Paradis AB](https://www.grodansparadis.com) controls the rest of the addresses and will allocate addresses to individuals or companies that send a request to [guid_request@vscp.org](mailto:guid_request@vscp.org). You can request a 32-bit series, making it possible for you to manufacture 4294967296 nodes. If you need more (**!!**) you can ask for another series. There is no cost for reserving a series. 

[This page](./assigned_guids.md) contains a list of currently assigned GUIDs.


[filename](./bottom_copyright.md ':include')

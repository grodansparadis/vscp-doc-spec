# Globally Unique Identifiers

To classify as a node in a VSCP net all nodes must be uniquely identified by a globally unique 16-byte (yes that is 16-byte (128 bits) not 16-bit) identifier. This number uniquely identifies all devices around the world and can be used as a means to obtain device descriptions as well as drivers for a specific platform and for a specific device. 

The manufacturer of the device can also use the number as a serial number to track manufactured devices. In many other environments and protocols there is a high cost in getting a globally unique number for your equipment. This is not the case with VSCP. If you own an Ethernet card you also have what is needed to create your own GUID's. 

The GUID address is not normally used during communication with a node. Instead an 8-bit address is used. This gives a low protocol overhead. A segment can have a maximum of 127 nodes even if the address gives the possibility for 256 nodes. The 8-bit address is received from a master node called the segment controller. The short address is also called the nodes nickname-ID or nickname address.

Besides the GUID it is recommended that all nodes should have a node description string in the firmware that points to a URL that can give full information about the node and its family of devices. As well as providing information about the node, this address can point at drivers for various operating systems or segment controller environments. Reserved GUID's 

A general discussion of UUID's/GUID's is [here](https///en.wikipedia.org/wiki/Universally_unique_identifier).

Some GUID's are reserved and unavailable for assignment. [This page](http://www.vscp.org/docs/vscpspec/doku.php?id=appendix_a) list these and also assigned IDs.

[Grodans Paradis AB](http://www.grodansparadis.com) controls the rest of the addresses and will allocate addresses to individuals or companies by them sending a request to [guid_request@vscp.org](guid_request@vscp.org) or filling in [this form](https///docs.google.com/forms/d/1PwH-8E5z3oiFcoxUvDqIDhSqVXBIhAMt-92MNnvgEBM/viewform). You can request a series of 32-bits making it possible for you to manufacture 4294967295 nodes. If you need more (!**!!**) you can ask for another series. There is no cost for reserving a series. 

[This page](http://www.vscp.org/docs/vscpspec/doku.php?id=appendix_a) contains a list of currently assigned guid's.

## Predefined VSCP GUID's

It is possible to create your own GUID without requesting a series and still get a valid VSCP GUID.


 | Assigned Global Unique IDs                                                                          | IDs Series Reserved to/for                                                                                                                                                                                                                                                                                                            | 
 | --------------------------                                                                          | --------------------------                                                                                                                                                                                                                                                                                                            | 
 | FF:FF:FF:FF:FF:FF:FF:FF:YY:YY:YY:YY:YY:YY:YY:YY                                                     | Dallas Semiconductor GUID's. This is the 1-wire/iButton 64-bit ID. The device code is in the MSB byte and CRC in the LSB byte.                                                                                                                                                                                                        | 
 | FF:FF:FF:FF:FF:FF:FF:FE:YY:YY:YY:YY:YY:YY:XX:XX                                                     | Ethernet Device GUID's. The holder of the address can freely use the two least significant bytes of the GUID. MAC address in MSB - LSB order. Also called MAC-48 or EUI-48 by IEEE                                                                                                                                                    | 
 | FF:FF:FF:FF:FF:FF:FF:FD:YY:YY:YY:YY:XX:XX:XX:XX                                                     | Internet version 4 GUID's. This is a 32-bit ID so the holder of the address can freely use the four least significant bytes of the GUID. IP V4 address in MSB - LSB order.                                                                                                                                                            | 
 | FF:FF:FF:FF:FF:FF:FF:FC:XX:XX:XX:XX:XX:XX:XX:XX                                                     | Private. Use for in-house local use. The GUID should never appear outside your local segments.                                                                                                                                                                                                                                        | 
 | FF:FF:FF:FF:FF:FF:FF:FB:YY:YY:YY:XX:XX:XX:XX:XX                                                     | ISO ID. This is a three byte ID so the holder of the ISO ID can freely use the five least significant bytes of the GUID.                                                                                                                                                                                                              | 
 | FF:FF:FF:FF:FF:FF:FF:FA:YY:YY:YY:YY:XX:XX:XX:XX                                                     | CiA (CAN in Automation) vendor ID. This is a 32-bit ID so the holder of the vendor ID can freely use the four least significant bytes of the GUID.                                                                                                                                                                                    | 
 | FF:FF:FF:FF:FF:FF:FF:F9:YY:YY:YY:XX:XX:XX:XX:XX                                                     | ZigBee 802.15.4 OID. This is a 24-bit ID so the holder of the OID can freely use the five least significant bytes of the GUID.                                                                                                                                                                                                        | 
 | FF:FF:FF:FF:FF:FF:FF:F8:YY:YY:YY:YY:YY:YY:XX:XX                                                     | Bluetooth MAC. This is a 48-bit ID so the holder of the OID can freely use the two least significant bytes of the GUID.                                                                                                                                                                                                               | 
 | FF:FF:FF:FF:FF:FF:FF:F7:YY:YY:YY:YY:YY:YY:YY:YY                                                     | IEEE EUI-64. This is a 64-bit ID. The upper three bytes are purchased from IEEE by the company that releases the product. The lower five bytes are assigned by the device and must be unique.                                                                                                                                         | 
 | FF:FF:FF:FF:FF:FF:FF:F6:00:YY:YY:YY:YY:YY:YY:YY                                                     | Reserved for RAMTRON MRAM (and compatible), seven byte IDs.                                                                                                                                                                                                                                                                           | 
 | FF:FF:FF:FF:FF:FF:FF:F6:01:YY:YY:YY:YY:YY:YY:YY- \\ FF:FF:FF:FF:FF:FF:FF:F6:FF:YY:YY:YY:YY:YY:YY:YY | Reserved for other future seven bit ID (memory devices) that may have ID, such as PRAM etc.                                                                                                                                                                                                                                           | 
 | FF:FF:FF:FF:FF:FF:FF:F5:XX:XX:XX:XX:XX:XX:XX:XX                                                     | Reserved for VSCP & Friends demo and example usage.                                                                                                                                                                                                                                                                                   | 
 | FF:FF:FF:FF:FF:FF:FF:F4:XX:XX:XX:XX:XX:XX:YY:YY                                                     | Reserved for VSCP grouping where YY defines the group id. XX is not currently used.                                                                                                                                                                                                                                                   | 
 | FF:FF:FF:FF:FF:FF:FF:00:00:00:00:00:00:00:00:00- \\ FF:FF:FF:FF:FF:FF:FF:F3:FF:FF:FF:FF:FF:FF:FF:FF | Reserved                                                                                                                                                                                                                                                                                                                              | 
 | 00:00:00:00:00:00:00:00:00:00:00:00:xx:xx:xx:xx                                                     | Lab usage. You can use this range for your own development or for in-house local use. The GUID should never appear outside your local segments.                                                                                                                                                                                       | 
 | FE:YY:YY:YY:YY:YY:YY:YY:YY:YY:YY:YY:YY:YY:YY:YY                                                     | Reserved for a generated 128 bit GUID where the most significant byte is replaced by FE Only use for Level II and on internal net. [http://hegel.ittc.ku.edu/topics/internet/internet-drafts/draft-l/draft-leach-uuids-guids-01.txt](http://hegel.ittc.ku.edu/topics/internet/internet-drafts/draft-l/draft-leach-uuids-guids-01.txt) | 
 | FD:AA:BB:YY:YY:YY:YY:YY:YY:YY:YY:YY:YY:YY:YY:YY                                                     | Reserved for MCU internal id's provided by some manufacturers. AA is manufacturer id. BB is circuit family. There is room for a 13-byte id. If the particular CPU have a an id that is shorter than put used bits to the right and set unused MSB bytes to zero. See information below.                                               | 

## MCU stored GUID's

As explained above GUID's with 0xFD in the most significant byte is reserved for MCU's with an on-ship stored id. If your MCU is not in the list below please let us know and we will add it (or you can add it yourself). Thus new MCU's will be added as they are needed by someone.

### Manufacturer code

 | Code | Description                         | 
 | ---- | -----------                         | 
 | 0    | Microchip                           | 
 | 1    | Atmel                               | 
 | 2    | ST                                  | 
 | 3    | NXP                                 | 
 | 4    | Freescale                           | 
 | 5    | Renesas                             | 
 | 6    | Gecko                               | 
 | 7    | Texas Instrument (+ Luminary Micro) | 

### Family codes

#### Microchip

*tbd*

#### Atmel

 | Code  | Description                                                                                                                                                                                                                                        | 
 | ----  | -----------                                                                                                                                                                                                                                        | 
 | 0     | Xmega Family, use [DEVID2:1][LOTNUM5:4:3:2:1:0]:[WAFNUM]:[COORDX1:0][COORDY1:0] as bytes 13::0 of the GUID. DEVID0 not used because it is always a constant. DEVIDx is from *"MCU Control registers"*, rest from *"Production Signature Row"*. | 
 | 1-255 | t.b.d                                                                                                                                                                                                                                              | 
Notes on other families:

*  No serial number: ATiny, AtMega, AT91SAM, SAM7 S/SE/X/XC, SAM9 XE n/M/N/CN/R/G/X, complete 8051 architecture

*  AT32 UC3 = 120 Bit

*  SAM C/D/E/G/L/S/V = 128 Bit

*  SAM3 A/N/S/U/X have 128 Bit

*  SAM4 L = 120 Bit, SAM4E/S/N = 128 Bit

*  SAMA5 = 128 Bit

####  ST Microelectronics

 | Code | Description                                                                                                                                                                                      | 
 | ---- | -----------                                                                                                                                                                                      | 
 | 0    | STM8 AL/L/S/T but not STM8AF, use the *"MCU device ID"* (which is 12 bit) as byte 13:12 (bits 7::4 of byte 13=0) and the *"Unique device ID"* (96 Bit = 12 Byte) as bytes 11::0 of the GUID. | 
 | 1    | STM32 F/L/T/W, use the *"MCU device ID"* (which is 12 bit) as byte 13:12 (bits 7::4 of byte 13=0) and the *"Unique device ID"* (96 Bit = 12 Byte) as bytes 11::0 of the GUID.                | 

Notes on other families:

*  STR75xFxx have no UID


#### NXP

*tbd (LPCxxxx all have 128Bit ID (without description)*

#### Freescale

*tbd*



## Shorthand GUID's

Note that there is a convenient shorthand notation :: used for IPV6 that can be used as a place holder for zeros. For example

    ::1 

really means 

    00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:01

and 

    FF:21::22:32 

is the same as

    FF:21:00:00:00:00:00:00:00:00:00:00:00:00:22:32

we use *: in the same way for FFs so that

	

	  *:1 


really means 

    FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:01

These short cut notations makes it much easier to write GUID's. 


\\ 
----
{{  ::copyright.png?400  |}}

`<HTML>``<p style="color:red;text-align:center;">``<a href="http://www.paradiseofthefrog.com">`Paradise of the Frog AB`</a>``</p>``</HTML>`

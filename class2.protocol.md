# Class=1024 (0x0400) - Level II Protocol Functionality

    CLASS2.PROTOCOL

## Description

For Level I events class=0 defines protocol control functionality. All events of this class are repeated at class=512 for use on Level II networks. The only difference is that the GUID is used instead of the Level I nickname.

This class defines protocol functionality for Level II. To simplify the handling of level II events, the data portion of the VSCP event can be considered as being made up of two parts. An 8-byte code portion (size of long integer) followed by a data portion if required. This is simply done to make processing level II events a little easier. The following events have been added to the level II control events to support configuration management. 

## Type=0 (0x00) - General event :id=type0
```
VSCP2_TYPE_PROTOCOL_GENERAL
```
General Event.
----

## Type=1 (0x01) - Read Register :id=type1
```
VSCP2_TYPE_PROTOCOL_READ_REGISTER
```
Read a Level II register from the 32-bit register space

 | Byte       | Description                                      | 
 | ----       | -----------                                      | 
 | Byte 0-15  | Contains the GUID of the target node (MSB->LSB). | 
 | Byte 16-19 | Register to read (or start index), (MSB->LSB).   | 
 | Byte 20-21 | Number of registers to read (max 508).           | 



----

## Type=2 (0x02) - Write Register :id=type2
```
VSCP2_TYPE_PROTOCOL_WRITE_REGISTER
```
 Write a Level II register to the 32.bit register space
 
 | Byte       | Description                                      | 
 | ----       | -----------                                      | 
 | Byte 0-15  | Contains the GUID of the target node (MSB->LSB). | 
 | Byte 16-19 | Register to write (or start index), (MSB->LSB).  | 
 | Byte 20…   | Data to write to register(s) (max 512-16-4 bytes).  | 



----

## Type=3 (0x03) - Read Write Response :id=type3
```
VSCP2_TYPE_PROTOCOL_READ_WRITE_RESPONSE
```
This is the response from a read or a write. Note that the data is returned in both cases and can be checked for validity. 

 | Byte      | Description                               | 
 | ----      | -----------                               | 
 | Byte 0-3  | Start register for register read/written. | 
 | Byte 4…   | Data read/written.                        | 
 
 Data read/written can be a maximum of 512-4 = 508 bytes for read and 512-16-4 = 492 bytes for a write response.

----

## Type=20 (0x14) - High end server/service capabilities :id=type20
```
VSCP2_TYPE_PROTOCOL_HIGH_END_SERVER_CAPS
```
Recommended to be implemented by all Level II devices and be sent out at least once every 60 second.

 | Data byte | Description                                 |
 | :----: |-----------                                     |
 | 0         | VSCP server 64-bit capability code MSB      |
 | 1         | VSCP server 64-bit capability code          |
 | 2         | VSCP server 64-bit capability code          |
 | 3         | VSCP server 64-bit capability code          |
 | 4         | VSCP server 64-bit capability code          |
 | 5         | VSCP server 64-bit capability code          |
 | 6         | VSCP server 64-bit capability code          |
 | 7         | VSCP server 64-bit capability code LSB      |
 | 8-23      | GUID for server                             |
 | 24-39     | For IPv4 or IPv6 IP address or other transport id identifier (MSB first). Note that this info is often already part of the GUID. |
 | 40-103    | 64 byte max zero terminated utf8 encoded name for this server. Blank if no name set. |
 | 104..     | Non standard port info for services. Not needed if the standard port is used.        |

### Capability code

Description of bit-usage for VSCP server 64-bit **capability code**. A bit should be set only if the service is active.

 | Bit       | Usage                   |
 | :----:       | -----                |
 | 63 | Node supports VSCP remote variables. |
 | 62 | Node have a standard decision matrix. |
 | 61 | Node is a multi interface node (tcp/ip 'interface' command list interfaces). |
 | Bit 16-60 | Reserved.               |
 | Bit 15    | Have VSCP TCP server with VCSP link interface.  |
 | Bit 14    | Have VSCP UDP server.   |
 | Bit 13    | Have VSCP Multicast announce interface. |
 | Bit 12    | Have VSCP raw Ethernet. |
 | Bit 11    | Have Web server.        |
 | Bit 10    | Have VSCP Websocket interface . |
 | Bit 9     | Have VSCP REST interface. |
 | Bit 8     | Have VSCP Multicast channel support. |
 | Bit 7     | Reserved.                 |
 | Bit 6     | IP6 support.              |
 | Bit 5     | IP4 support.              |
 | Bit 4     | SSL support.              |
 | Bit 3     | Accepts two or more simultaneous connections on TCP/IP interface. A limited device may only accept one connection.   |
 | Bit 2     | Support AES256 encryption. |
 | Bit 1     | Support AES192 encryption. |
 | Bit 0     | Support AES128 encryption. |

**For programmers:** Bits are defined in vscp.h.

### Non standard ports

Non standard port definitions. Each consist of three bytes.
 | Byte | Description                                                                                                     |
 | :----: | -----------                                                                                                   |
 | 0    | 0-63 Identify the service from the bit number (see bit usage). Offset zero. Bit 7 is set if encryption is used. |
 | 1    | Port MSB byte                                                                                                   |
 | 2    | Port LSB byte                                                                                                   |

### Example

**Example:** The standard TCP/IP server is on port **9598** if it has been moved to port **32000** the three bytes will be

 | Byte | Description                                       |
 | :----: | -----------                                     |
 | 0    | 15 for bit 15 which is the TCP/IP server          |
 | 1    | 0xD4 which is the most significant byte of 32000  |
 | 3    | 0x00 which is the least significant byte of 32000 |

----

## Type=32 (0x20) - Level II who is there response :id=type32
```
VSCP2_TYPE_PROTOCOL_WHO_IS_THERE_RESPONSE
```
This defines the response from a Level II node for a [CLASS1.PROTOCOL, Type=32, Who is there?](./class1.protocol.md#type31) event.

 | Byte  | Description                                       |
 | :----:  | -----------                                     |
 | 0-15  | GUID for node                                     |
 | 16-47 | MDF of node                                       |


----

## Type=34 (0x22) - Level II get DM info response :id=type34
```
VSCP2_TYPE_PROTOCOL_GET_MATRIX_INFO_RESPONSE
```
This defines the response from a Level II node for a [CLASS1.PROTOCOL, Type=33, VSCP_TYPE_PROTOCOL_GET_MATRIX_INFO](./class1.protocol.md#type34) event.

 | Byte   | Description    |
 | :----: | -----------    |
 | 0-15   | GUID for node  |
 | 16     | DM row size    |
 | 17     | DM number of rows |
 | 18-21  | Register start for DM |

 
----

## Type=36 (0x24) - Level II get embedded MDF response :id=type36
```
VSCP2_TYPE_PROTOCOL_GET_EMBEDDED_MDF_RESPONSE
```
Get embedded MDF of device. This defines the response from a Level II node for a [CLASS1.PROTOCOL, Type=35, VSCP_TYPE_PROTOCOL_GET_EMBEDDED_MDF](./class1.protocol.md#type35) event.

 | Byte   | Description  |
 | :----: | -----------  |
 | 0,1    | Index        |
 | 2,3    | Total number of frames |
 | 4-...  | MDF data     |

 Each packet can hold a maximum of 508 bytes. The first byte is the index of the MDF. The second byte is the total number of rows. The following bytes are the MDF data.


----

## Type=41 (0x29) - Level II events of interest response :id=type41
```
VSCP2_TYPE_PROTOCOL_GET_EVENT_INTEREST_RESPONSE
```
Get events of interest. This defines the response from a Level II node for a [CLASS1.PROTOCOL, Type=40, VSCP2_TYPE_PROTOCOL_GET_EVENT_INTEREST](./class1.protocol.md#type40) event.

 | Byte     | Description  |
 | :----:   | -----------  |
 | 0,1      | class 1      |
 | 2,3      | type 1       |
 | 4,5      | class 2      |
 | 6,7      | type 2       |
 | ....     | ....         |
 | 508,509  | class n      |
 | 510,511  | type n       |

 The response is a packet with class/type pairs. One frame can hold a maximum of 256 pairs. If more is needed send multiple frames. Type can be set to zero to indicate ALL types of that class.

 A node that is interested in everything just send a [CLASS2.PROTOCOL, Type=41 (Get event interest response)](./class2.protocol.md#type41) with no data if asked to provide that information.
----

[filename](./bottom_copyright.md ':include')
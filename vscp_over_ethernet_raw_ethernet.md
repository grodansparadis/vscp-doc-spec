# VSCP over Ethernet (raw Ethernet)

VSCP can use Ethernet directly making it possible to construct very low end nodes that use readily available Ethernet hardware. There is no need for nickname schema's etc as a VSCP GUID can be constructed from an Ethernet MAC. The payload is a standard VSCP level II frame with some specific Ethernet stuff in it- There are currently two types of frames

##  Version 1 frame (current) 

*This frame has been changed in format so it is consistent with the UDP and Multicast frames. Previous definition is below.*

 | Content                               | Size        | Description                                                            | 
 | -------                               | ----        | -----------                                                            | 
 | Preamble                              | 62 bits     | Standard Ethernet preamble. (Part of Ethernet)                         | 
 | SOF (Start of Frame)                  | 2 bits      | Standard Ethernet SOF. (Part of Ethernet)                              | 
 | **Destination MAC address**           | 6 bytes     | Always set to FF:FF:FF:FF:FF:FF (Part of Ethernet)                     | 
 | **Source MAC address**                | 6 bytes     | Source address. Part of GUID see information below. (Part of Ethernet) | 
 | **Ethernet Type**                     | 2 bytes     | Frame type: Always set to 0x257E (decimal 9598) (Part of Ethernet)     | 
 | **Version**                           | 1 byte      | 1                                                                      | 
 | **Packet type & encryption settings** | 1           | Se table below. Never encrypted.                                       | 
 | **VSCP Level II Head**                | 2           | The 16-bit VSCP header                                                 | 
 | **Timestamp**                         | 4           | VSCP relative timestamp in microseconds.                               | 
 | **Year**                              | 2           | UTC year                                                               | 
 | **Month**                             | 1           | UTC month of year (1-12)                                               | 
 | **Day**                               | 1           | UTC day of month (1-31)                                                | 
 | **Hour**                              | 1           | UTC hour of day (0-23)                                                 | 
 | **Minute**                            | 1           | UTC minute of hour (0-59)                                              | 
 | **Second**                            | 1           | UTC second of minute (0-59)                                            | 
 | **VSCP class**                        | 2           | VSCP class                                                             | 
 | **VSCP type**                         | 2           | VSCP Type                                                              | 
 | **Originating GUID**                  | 16          | GUID for sending node                                                  | 
 | **Data Size**                         | 2           | Size for payload (0-487) (VSCP data)                                   | 
 | **Payload**                           | 0-487 bytes | The VSCP data part. As usual 512-25 bytes.                             | 
 | **crc**                               | 2           | CRC (Calculated on HEAD + CLASS + TYPE + ADDRESS + SIZE + DATA…)     | 
 | **iv (optional)**                     | (16)        | Optional encryption data such as a 16-byte IV for AES follow here      | 
 | CRC                                   | 4-bytes     | 32 bit CRC checksum (Part of Ethernet)                                 | 

Time should always be UTC time. If the time block is set to all zero the current time will be set by interface (VSCP Server for example).

##### Definition of type

 | Bits    | Description                  | 
 | ----    | -----------                  | 
 | 7,6,5,4 | Packet type. Currently zero. | 
 | 3,2,1,0 | Encryption.                  | 

##### Encryption types

 | Code | Description                                                  | 
 | ---- | -----------                                                  | 
 | 0    | No encryption                                                | 
 | 1    | AES128 CBC encryption. 16-byte IV is appended to each frame. | 
 | 2    | AES192 CBC encryption. 16-byte IV is appended to each frame. | 
 | 3    | AES256 CBC encryption. 16-byte IV is appended to each frame. | 
 | 4-15 | Reserved                                                     | 

For encryption/decryption code using OpenSSL see [this link](https://wiki.openssl.org/index.php/EVP_Authenticated_Encryption_and_Decryption). Note that byte 0 of the frame is never encrypted. The encryption/decryption is instead carried out over byte 1 to the CRC.

On the VSCP Server the md5 of the [vscptoken](https://www.vscp.org/docs/vscpd/doku.php?id=configuring_the_vscp_daemon#security) is used as the key for AES128.

##### Definition of head

See [vscp.h](https://github.com/grodansparadis/vscp/blob/master/src/vscp/common/vscp.h)

 | Bits  | Description                                                         | 
 | ----  | -----------                                                         | 
 | 15    | GUID is IP v.6 address.                                             | 
 | 14    | Dumb node. No MDF. No registers.                                    | 
 | 13-8  | Reserved (**Set to zero!**).                                        | 
 | 7,6,5 | Priority.                                                           | 
 | 4     | Hard-coded.                                                         | 
 | 3     | Don't calculate CRC if bit set. CRC should be set to 0xAA55 if set. | 
 | 2,1,0 | Rolling index.                                                      | 

## Version 0 frame (old)

 | Content                     | Size         | Description                                                                                                                                                               | 
 | -------                     | ----         | -----------                                                                                                                                                               | 
 | Preamble                    | 62 bits      | Standard Ethernet preamble. (Part of Ethernet)                                                                                                                            | 
 | SOF (Start of Frame)        | 2 bits       | Standard Ethernet SOF. (Part of Ethernet)                                                                                                                                 | 
 | **Destination MAC address** | 6 bytes      | Always set to FF:FF:FF:FF:FF:FF (Part of Ethernet)                                                                                                                        | 
 | **Source MAC address**      | 6 bytes      | Source address. Part of GUID see information below. (Part of Ethernet)                                                                                                    | 
 | **Ethernet Type**           | 2 bytes      | Frame type: Always set to 0x257E (decimal 9598) (Part of Ethernet)                                                                                                        | 
 | **Version**                 | 1 byte       | 0                                                                                                                                                                         | 
 | **VSCP head**               | 4 bytes      | VSCP Header                                                                                                                                                               | 
 | **VSCP sub source address** | 2 bytes      | Identifies one subunit of an Ethernet device. Last two bytes of the GUID.                                                                                                 | 
 | **Timestamp**               | 4 bytes      | Timestamp in microseconds. Module relative value.                                                                                                                         | 
 | **obid**                    | 4 bytes      | For use by modules and drivers.                                                                                                                                           | 
 | **VSCP class**              | 2 bytes      | 16-bit VSCP class                                                                                                                                                         | 
 | **VSCP type**               | 2 bytes      | 16-bit VSCP type                                                                                                                                                          | 
 | **DataSize**                | 2 bytes      | Size of data part. Needed because Ethernet frames must have a minimum length of 64 bytes so payload may be padded so we cannot deduce real data size from payload length. | 
 | **Payload**                 | 0- 487 bytes | The VSCP data part. As usual 512-25 bytes.                                                                                                                                | 
 | CRC                         | 4-bytes      | 32 bit CRC checksum (Part of Ethernet)                                                                                                                                    | 

Type in bold is usually what is seen on the software level.

The VSCP GUID for Ethernet is defined as

    FF:FF:FF:FF:FF:FF:FF:FE:YY:YY:YY:YY:YY:YY:XX:XX

where **FF:FF:FF:FF:FF:FF:FF:FE** say this is an Ethernet GUID and **YY:YY:YY:YY:YY:YY** is the MAC address and **XX:XX** is the ID for a specific VSCP device. Each node can thus appear as 65535 - 2 nodes which is perfect for a gateway or similar device that have VSCP devices connected on one or many other buses such as CAN, RF and the like. Two IDs are reserved. 0x0000 which is the Ethernet node itself and 0xFFFF which is all nodes on the interface. If a node consist just of itself then it can ignore the VSCP sub address but it is recommended that it use 0x0000 for its transmitted frames.

The header (32-bits) is defined as follows

 | Content                                      | Size    | Description                                                                  | 
 | -------                                      | ----    | -----------                                                                  | 
 | Priority (Bit 31,30,29)                      | 3 bits  | Standard VSCP priority.                                                      | 
 | Cryptographic algorithm (Bit 28, 27, 26, 25) | 4 bits  | Cryptographic algorithm used to encrypt payloads. This is yet to be defined. | 
 | Reserved                                     | 25 bits |                                                                              | 

Cryptographic encoding is done after type up to and including the last data byte thus the VSCP head is never encoded.

### Powering Ethernet nodes

The unused pairs can be used to power nodes and that way making them lower cost. In a perfect world a standard compliant Power over Ethernet schema could have been used. Regrettably the technique is to expensive. At least at the moment. Instead a +9-48V DC injector is used. If in doubt use +48V DC. The IEEE 802.3af standard POE pin out is as follows:

 | Pin | Description | 
 | --- | ----------- | 
 | 1   |             | 
 | 2   |             | 
 | 3   |             | 
 | 4   | +9V - +28V  | 
 | 5   | +9V - +28V  | 
 | 6   |             | 
 | 7   | GND         | 
 | 8   | GND         | 

Maximum power usage depends on the cabling but for AWG-24 it is 0.5A for each pair but never more then 13 watts. There is a description of how different manufacturers implement this here [https://pinouts.ru/Net/poe_pinout.shtml]. A calculator for losses can be found here [https://www.demarctech.com/techsupport/poecalculate.htm||Power calculator].



[filename](./bottom_copyright.md ':include')

# VSCP over UDP

UDP be used to send and receive VSCP frames, non encrypted or encrypted and with or with out a frame acknowledge.

**Default Port:** 33333

### The packet format

## Packet format

 | Byte  | Description                                                            | Encrypted           | 
 | ----  | -----------                                                            | ---------           | 
 | 0     | Packet type & encryption settings.                                     | **Never encrypted** | 
 | 1     | VSCP Level II Head MSB                                                 | Yes                 | 
 | 2     | VSCP Level II Head LSB                                                 | Yes                 | 
 | 3     | Timestamp microseconds MSB                                             | Yes                 | 
 | 4     | Timestamp microseconds                                                 | Yes                 | 
 | 5     | Timestamp microseconds                                                 | Yes                 | 
 | 6     | Timestamp microseconds LSB                                             | Yes                 | 
 | 7     | Year MSB                                                               | Yes                 | 
 | 9     | Year LSB                                                               | Yes                 | 
 | 9     | Month                                                                  | Yes                 | 
 | 10    | Day                                                                    | Yes                 | 
 | 11    | Hour                                                                   | Yes                 | 
 | 12    | Minute                                                                 | Yes                 | 
 | 13    | Second                                                                 | Yes                 | 
 | 14    | CLASS MSB                                                              | Yes                 | 
 | 15    | CLASS LSB                                                              | Yes                 | 
 | 16    | TYPE MSB                                                               | Yes                 | 
 | 17    | TYPE LSB                                                               | Yes                 | 
 | 18-33 | ORIGINATING GUID                                                       | Yes                 | 
 | 34    | DATA SIZE MSB                                                          | Yes                 | 
 | 35    | DATA SIZE LSB                                                          | Yes                 | 
 | 36-n  | data ... limited to max 512-25 = 487 bytes                             | Yes                 | 
 | len-2 | CRC MSB (Calculated on HEAD + CLASS + TYPE + ADDRESS + SIZE + DATA…) | Yes                 | 
 | len-1 | CRC LSB                                                                | yes                 | 
 | opt   | Optional encryption data such as a 16-byte IV for AES follow here      | No                  | 

The number above is the offset in the package. Len is the total datagram size.

Time should always be UTC time. If the time block is set to all zero the current time will be set by interface (VSCP Server for example).

##### Definition of type

 | Bits    | Description                         | 
 | ----    | -----------                         | 
 | 7,6,5,4 | Packet type. Currently always zero. | 
 | 3,2,1,0 | Encryption.                         | 

##### Encryption types

 | Code | Description                                                  | 
 | ---- | -----------                                                  | 
 | 0    | No encryption                                                | 
 | 1    | AES128 CBC encryption. 16-byte IV is appended to each frame. | 
 | 2    | AES192 CBC encryption. 16-byte IV is appended to each frame. | 
 | 3    | AES256 CBC encryption. 16-byte IV is appended to each frame. | 
 | 4-15 | Reserved                                                     | 

For encryption/decryption code using OpenSSL see [this link](https///wiki.openssl.org/index.php/EVP_Authenticated_Encryption_and_Decryption). Note that byte 0 of the frame is never encrypted. The encryption/decryption is instead carried out over byte 1 to the CRC.

On the VSCP Server the md5 of the [vscptoken](http://www.vscp.org/docs/vscpd/doku.php?id=configuring_the_vscp_daemon#security) is used as the key for AES128.

##### Definition of head

See [vscp.h](https///github.com/grodansparadis/vscp/blob/master/src/vscp/common/vscp.h)

 | Bits  | Description                                                         | 
 | ----  | -----------                                                         | 
 | 15    | GUID is IP v.6 address.                                             | 
 | 14    | Dumb node. No MDF. No registers.                                    | 
 | 13-8  | Reserved (**Set to zero!**).                                        | 
 | 7,6,5 | Priority.                                                           | 
 | 4     | Hard-coded.                                                         | 
 | 3     | Don't calculate CRC if bit set. CRC should be set to 0xAA55 if set. | 
 | 2,1,0 | Rolling index.                                                      | 

Note also that the MSB is sent before the LSB (network byte order, Big Endian). So, for little endian machines such as a typical PC the byte order needs to be reversed for multi-byte types.

There is a 24-byte overhead to send one byte of data so this is not a protocol which should be used where an efficient protocol for data intensive applications is required and where data is sent in small packets.

The CRC used is the 16-bit CCITT type and it should be calculated across all bytes except for the CRC itself.

As indicated, the Class is 16-bits allowing for 65535 classes. Class 0000000x xxxxxxxx is reserved for the Level I classes. A low-end device should ignore all packages with a class > 511.

A packet traveling from a Level I device out to the Level II world should have an address translation done by the master so that a full address will be visible on the level II segment. A packet traveling from a Level II segment to a Level I segment must have a class with a value that is less then 512 in order for it to be recognized. If it has it is aimed for the Level I segment. Classes 512-1023 are reserved for packets that should stay in the Level II segment but in all other aspects (the lower nine bits + type) are defined in the same manner as for the low-end net.

The Level II register abstraction level also has more registers (32-bit address is used) and all registers are 32–bits wide. Registers 0-255 are byte wide and are the same as for level 1. If these registers are read at level 2 they still is read as 32-bit but have the unused bits set to zero. 

VSCP daemon implementation described [here](https://www.vscp.org/docs/vscpd/doku.php?id=daemon_udp_protocol_description_general).



{% include "./bottom_copyright.md" %}
 

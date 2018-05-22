# VSCP Multicast

For VSCP multicast the address

    224.0.23.158 VSCP

should be used.Please see the following:

[https://www.iana.org/assignments/multicast-addresses](https://www.iana.org/assignments/multicast-addresses) and [https://www.tldp.org/HOWTO/Multicast-HOWTO.html](https://www.tldp.org/HOWTO/Multicast-HOWTO.html) 

Currently the multicast interface is used for heart beats and announcements of available services and to set up multicast groups that share events. For this port **9698** is always used.

General multicast information can be found [here](https://www.juniper.net/techpubs/en_US/junos12.1x46/topics/concept/multicast-ip-overview.html).

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

On the VSCP Server the md5 of the [vscptoken](https://www.vscp.org/docs/vscpd/doku.php?id=configuring_the_vscp_daemon#security) is used as the key for AES128.

##### Definition of head

 | Bits  | Description                                                         | 
 | ----  | -----------                                                         | 
 | 15    | GUID is IP v.6 address.                                             | 
 | 14-8  | Reserved (**Set to zero!**).                                        | 
 | 7,6,5 | Priority.                                                           | 
 | 4     | Hard-coded.                                                         | 
 | 3     | Don't calculate CRC if bit set. CRC should be set to 0xAA55 if set. | 
 | 2,1,0 | reserved (**Set to zero!**).                                        | 

Note also that the MSB is sent before the LSB (network byte order, Big Endian). So, for little endian machines such as a typical PC the byte order needs to be reversed for multi-byte types.

There is a 24-byte overhead to send one byte of data so this is not a protocol which should be used where an efficient protocol for data intensive applications is required and where data is sent in small packets.

The CRC used is the 16-bit CCITT type and it should be calculated across all bytes except for the CRC itself.
## Announcement

Announcements are done on the default VSCP port 9598.

Announcements is an important part of the traffic on the multicast channel.  There are a few different types.


*  VSCP daemon announcements. Announce the availability of a VSCP daemon (or other server with exported interfaces) and tell its capabilities.

*  High end device announce. Announce the availability of the device and its capability. All Level II nodes should have this functionality. At the bottom line they just look to the system as a VSCP daemon with less capabilities.

*  Heart beats: Heart beats come in the form of heartbeats from VSCP daemons and from high end nodes. Both send them out each minute. Also heartbeats are available form devices connected to a daemon or through a high end node. 

## Events

It's up to the implementer to decide what events should be available on a multicast channel by setting the receive/transmit filters/masks for the channel. Several channels can be set up on different ports forming different subnets. Normally just a filtered number of events is transmitted. A typical example of such a segment is a group of nodes on Ethernet.

{% include "./bottom_copyright.md" %}


# VSCP Level I over RS-485/RS-422

This is a description of a low level protocol for RS-485. The protocol is a server based protocol and is low speed but very cheap to implement. At a very low additional cost a CAN network with full VSCP functionality and server less functionality can be constructed and this is recommended for the majority of systems.

**Baudrate:** 115200 (or any other suitable Baudrate) 
**Format:** 8N1 for packages. 9N1 for address.

### Addressing

Addressing is done with nine bit addressing. Address 0 is reserved for the server and the rest of the addresses are free to use for clients. Addresses are hard-coded within devices and each device should have its own unique address. Nine bit addressing is described here [http://electronicdesign.com/embedded/use-pcs-uart-9-bit-protocols](http://electronicdesign.com/embedded/use-pcs-uart-9-bit-protocols)

### Packet format

If a node has a event to send it sends it directly after the poll event. The node should respond within one maximum packet time (14 * 8 * 104uS = 10 ms. Note that the event may be addressed to another node on the segment not only to the host.

If the node has no events to send it can either not reply to the poll or reply with “No Events to send” which is the preferable way.

The events is standard VSCP Level I events in every other aspect.

A master on a RS-485 segment must check for new nodes on regular intervals. With 127 possible nodes this process could take 1.3 seconds to perform. Instead of doing all this at once it may be better to spread it over the standard polling range. That is to do a full polling of all active nodes and then try to discover a new node on an unused address etc etc. 

##### Frame format

 | Byte | Content                                              | 
 | :----: | :-------                                              | 
 | 0    | Nine bit destination address                         | 
 | 1    | Originating address (master=0)                       | 
 | 2    | Operation (see below)                                | 
 | 3    | Flags + bit nine of the class ( see below)           | 
 | 4    | VSCP Class (Lower 8 bits).                           | 
 | 5    | VSCP Type                                            | 
 | 6    | Data byte 0                                          | 
 | 7    | Data byte 1                                          | 
 | 8    | Data byte 2                                          | 
 | 9    | Data byte 3                                          | 
 | 10   | Data byte 4                                          | 
 | 11   | Data byte 5                                          | 
 | 12   | Data byte 6                                          | 
 | 13   | Data byte 7                                          | 
 | 14   | Packet CRC (counted from address (low 8-bits of it). | 

The DOW checksum is used. [https://www.vscp.org/wiki/doku.php?id=vscp_specification_crc_polynoms.](https://www.vscp.org/wiki/doku.php?id=vscp_specification_crc_polynoms.)

##### Operations

 | Operation code | Description                                            | 
 | :--------------: | :-----------                                            | 
 | 0              | No operation                                           | 
 | 1              | Level I event to/from node.                            | 
 | 2              | Poll for event. (No data content follows, just CRC).   | 
 | 3              | No events to send (No data content follows, just CRC). | 

##### Flags

 | Bit | Description                      | 
 | :---: | :-----------                   | 
 | 0-3 | Number of data-bytes             | 
 | 4   | Bit nine of Class.               | 
 | 5-7 | reserved and should be set to 0. | 



[filename](./bottom_copyright.md ':include')


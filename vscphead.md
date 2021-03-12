# VSCP Head

Depending on the transport which carries a VSCP event the VSCP frame head can be eight bytes or 16-bytes. It can even have other formats. For VSCP over CAN it is just represented by the hardcoded bit and the priority. For a transport that does not implement the full header definition the unused bits should normally be interpreted as if they where set to zero.

The full header is defined in [vscp.h](https://github.com/grodansparadis/vscp/blob/master/src/vscp/common/vscp.h) which is the main source (most valid) for information.

The full definition is

## Header

| Bits  | Description                                                         | 
 | ----  | -----------                                                         | 
 | 15    | Set if this is a dumb node. No MDF, register, nothing.              | 
 | 14    | GUID type                                                           |
 | 13    | GUID type                                                           | 
 | 12    | GUID type                                                           |  
 | 11-8  | Reserved (**Set to zero!**).                                        | 
 | 7,6,5 | Priority.                                                           | 
 | 4     | Hard-coded.                                                         | 
 | 3     | Don't calculate CRC if bit set. CRC should be set to 0xAA55 if set. | 
 | 2,1,0 | Rolling index.                                                      | 

## Bit 15 - Dumb node
If set the event comes from a dumb node. That is a node that does not have a MDF, register or behave as a good VSCP device should. Typically the node is a node that just send events.

## Bits 14,13,12 - GUID type
This tells hoq the GUIS of the VSCP fram should be interpreted.

| Value | Description |
| ----- | ----------- |
| 0 | GUID is a standard VSCP GUID |
| 1 | GUID is a Ipv6 address |
| 2-7 | Reserved |

## Bits 11-8 - Reserved
Bits that currently is unused. Set to zero and ignore.

## Bits 7,6,5 - Priority
This is the priority for the VSCP frame. Note that the priority is highest when all bits are set to zero.

## Bit 4 - Hard coded
This bit is set for a device that has a hard coded address. That is it can't be changed and will not be changed. 

## Bit 3 - Don't calculate CRC
This bit is used for transports that need it's own CRC frame check. Normally this is handled by the transport.

## Bits 2,1,0 - Rolling index
This is a rolling index whish is updated by one for each frame sent. It can be used on the reviving side to detect missed frames.





[filename](./bottom_copyright.md ':include')
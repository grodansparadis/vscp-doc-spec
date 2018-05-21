# VSCP over a serial channel (RS-232)

A byte stuffing binary interface is used to talk to the module through the serial interface.

The protocol is created for VSCP Level I events but can be used for other purposes also, as the 16 byte data content indicates. In this case the class and type bytes can be used freely by the implementer. 

Protocol defines are in [vscp_serial.h](https///github.com/grodansparadis/vscp_software/blob/master/src/vscp/common/vscp_serial.h)

### General frame format

The crc (X8 + X2 + X + 1) is calculated from, and including, frame type up to the last data-byte. For DLE in data which is sent as DLE DLE the crc is is calculated over just one of them.

The channel byte can be used to logically separate different channels on the same physical line. Typically this can also be a serial line with many nodes which are polled for data.

The sequence number byte marks a number for a sequence of a special frame. For instance four frame are sent after each other and they will get different counter numbers. The NACKs/ACKs that are responded from the node use the same counter values to separate the frames from others. Can, for example, be used to implement a sliding window protocol.

As noted there can be two types of ACKs/NACKs one (251/252) is a general ACK/NACK that is the response when a frame is received and put in a buffer. This is generally all that is needed. The other version (249/250) can optionally be sent when the frame is actually sent on the interface. 

### Frame format

 | Byte  | Content          | Description                                                                          | 
 | ----  | -------          | -----------                                                                          | 
 | 0     | [DLE]            | Escape character                                                                     | 
 | 1     | [STX]            | Start of frame                                                                       | 
 | 2     | Frame type       | (See table below )                                                                   | 
 | 3     | Channel          | The channel is used to separate messages from different units on a multi device bus. | 
 | 4     | Sequence number  | The sequence number is increased by one for each new message sent by a node.         | 
 | 5/6   | Size of payload  | Size of payload MSB/LSB                                                              | 
 | 7..n  | Payload          | This is the payload of the frame.                                                    | 
 | len-3 | Frame check sum. | CRC (X8 + X2 + X + 1).                                                               | 
 | len-2 | [DLE]            | Escape character                                                                     | 
 | len-1 | [ETX]            | End of frame                                                                         | 


### Frame types

 | Type   | Description                                                                                                                               | 
 | ----   | -----------                                                                                                                               | 
 | 0      | No operation(NOOP).                                                                                                                       | 
 | 1      | VSCP event to/from node.                                                                                                                  | 
 | 2      | CANAL message to/from node.                                                                                                               | 
 | 3      | Configure - Can be used to configure a transmitting/receiving device. Actual data is device dependent.                                    | 
 | 4      | Poll for event. A data frame is received if data is available and an operation=4 (no events to send) is returned if no data is available. | 
 | 5      | No events to send.                                                                                                                        | 
 | 6      | Multi frame CANAL message to/from node.                                                                                                   | 
 | 7      | Multi frame VSCP event to/from node.                                                                                                      | 
 | 8      | Capabilities request.                                                                                                                     | 
 | 9      | Capabilities response.                                                                                                                    | 
 | 10     | VSCP event to/from node WITH timestamp.                                                                                                   | 
 | 11     | CANAL message to/from node WITH timestamp.                                                                                                | 
 | 12     | Multi frame VSCP event to/from node WITH timestamp.                                                                                       | 
 | 13     | Multi frame CANAL message to/from node WITH timestamp.                                                                                    | 
 | 14-15  | Reserved.                                                                                                                                 | 
 | 16     | Unused/reserved and __will never be used__ (DLE).                                                                                         | 
 | 17-248 | Reserved.                                                                                                                                 | 
 | 249    | Sent ACK.                                                                                                                                 | 
 | 250    | Sent NACK.                                                                                                                                | 
 | 251    | ACK.                                                                                                                                      | 
 | 252    | NACK.                                                                                                                                     | 
 | 253    | Error.                                                                                                                                    | 
 | 254    | Command Reply.                                                                                                                            | 
 | 255    | Command.                                                                                                                                  | 

### Description of frames

#### Frame type=0 - NOOP

No data bytes.

#### Frame type=1 - VSCP Event

 | Data byte | Description                                    | 
 | --------- | -----------                                    | 
 | 0         | VSCP head MSB                                  | 
 | 1         | VSCP head LSB                                  | 
 | 2         | MSB of VSCP class                              | 
 | 3         | LSB of VSCP class                              | 
 | 4         | MSB of VSCP type                               | 
 | 5         | LSB of VSCP type                               | 
 | 6-21      | GUID (MSB first)                               | 
 | 22-n      | VSCP data (0-487 bytes/Max 8 byte for Level I) | 

#### Frame type=2 - CANAL message

 | Data byte | Description                | 
 | --------- | -----------                | 
 | 0         | CAN id (MSB)               | 
 | 1         | CAN id                     | 
 | 2         | CAN id                     | 
 | 3         | CAN id (LSB)               | 
 | 4         | dlc (0-8). Length of data. | 
 | 5-n       | CAN data (0-8 bytes)       | 

#### Frame type=3 - Configure

Format for data bytes defined by the maker of the device

#### Frame type=4 - Poll

No data bytes.

#### Frame type=5 - No events

No data bytes.

#### Frame type=6 - Multi frame CANAL

To make sending and receiving more efficient it is possible to send multiple CANAL frames as payload in one serial frame. Each frame is sent as 

 | Data byte | Description                | 
 | --------- | -----------                | 
 | 0         | id MSB                     | 
 | 1         | id                         | 
 | 2         | id                         | 
 | 3         | id LSB                     | 
 | 4         | datacount                  | 
 | 5-n       | data                       | 
 | n+1       | Start of next CANAL frame. | 

and can therefore have a maximum size of 13 bytes each.

#### Frame type=7 - Multi frame VSCP

To make sending and receiving more efficient it is possible to send multiple VSCP frames as payload in one serial frame. Each frame is sent as 

 | Data byte | Description                                    | 
 | --------- | -----------                                    | 
 | 0         | VSCP head MSB                                  | 
 | 1         | VSCP head LSB                                  | 
 | 2         | MSB of VSCP class                              | 
 | 3         | LSB of VSCP class                              | 
 | 4         | MSB of VSCP type                               | 
 | 5         | LSB of VSCP type                               | 
 | 6-21      | GUID (MSB first)                               | 
 | 22        | data count MSB                                 | 
 | 23        | data count LSB                                 | 
 | 24-n      | VSCP data (0-487 bytes/Max 8 byte for Level I) | 
 | n+1       | start of next VSCP frame                       | 

#### Frame type=8 - Request capabilities

Request capabilities of a device. A device will respond with a Request capabilities reply that shows what the devices can do. The sent payload is the capabilities of the requesting device.

The default value is what a device should suppose is true if no capabilities request reply has been received from a host. It can of course itself send the capabilities request.

Do not make expectations of the length of this frame as it will most certainly grow in the future.

 | Data byte | Description                                                                      | 
 | --------- | -----------                                                                      | 
 | 0         | Max number of VSCP frames this devices can receive in a multi frame (default=1)  | 
 | 1         | Max number of CANAL frames this devices can receive in a multi frame (default=1) | 

#### Frame type=9 - Request capabilities reply

Answer to request for capabilities of device. The default value is what a driver should suppose is true if no capabilities request reply has been received from the device.

Do not make expectations of the length of this frame as it will most certainly grow in the future.

 | Data byte | Description                                                                      | 
 | --------- | -----------                                                                      | 
 | 0         | Max number of VSCP frames this devices can receive in a multi frame (default=1)  | 
 | 1         | Max number of CANAL frames this devices can receive in a multi frame (default=1) | 

#### Frame type=10 - VSCP Event with timestamp

 | Data byte | Description                                    | 
 | --------- | -----------                                    | 
 | 0         | VSCP head MSB                                  | 
 | 1         | VSCP head LSB                                  | 
 | 2         | Timestamp MSB Microsconds                      | 
 | 3         | Timestamp                                      | 
 | 4         | Timestamp                                      | 
 | 5         | Timestamp LSB                                  | 
 | 6         | MSB of VSCP class                              | 
 | 7         | LSB of VSCP class                              | 
 | 8         | MSB of VSCP type                               | 
 | 9         | LSB of VSCP type                               | 
 | 10-25     | GUID (MSB first)                               | 
 | 26-n      | VSCP data (0-487 bytes/Max 8 byte for Level I) | 

#### Frame type=11 - CANAL message with timestamp

 | Data byte | Description                | 
 | --------- | -----------                | 
 | 0         | CAN id (MSB)               | 
 | 1         | CAN id                     | 
 | 2         | CAN id                     | 
 | 3         | CAN id (LSB)               | 
 | 4         | Timestamp MSB Microsconds  | 
 | 5         | Timestamp                  | 
 | 6         | Timestamp                  | 
 | 7         | Timestamp LSB              | 
 | 8         | dlc (0-8). Length of data. | 
 | 9-n       | CAN data (0-8 bytes)       | 

#### Frame type=12 - Multi frame CANAL with timestamp

To make sending and receiving more efficient it is possible to send multiple CANAL frames as payload in one serial frame. Each frame is sent as 

 | Data byte | Description                | 
 | --------- | -----------                | 
 | 0         | id MSB                     | 
 | 1         | id                         | 
 | 2         | id                         | 
 | 3         | id LSB                     | 
 | 4         | Timestamp MSB Microsconds  | 
 | 5         | Timestamp                  | 
 | 6         | Timestamp                  | 
 | 7         | Timestamp LSB              | 
 | 8         | datacount                  | 
 | 9         | dlc (0-8). Length of data. | 
 | 10-n      | data                       | 
 | n+1       | Start of next CANAL frame. | 

and can therefore have a maximum size of 13 bytes each.

#### Frame type=13 - Multi frame VSCP with timestamp

To make sending and receiving more efficient it is possible to send multiple VSCP frames as payload in one serial frame. Each frame is sent as 

 | Data byte | Description                                    | 
 | --------- | -----------                                    | 
 | 0         | VSCP head MSB                                  | 
 | 1         | VSCP head LSB                                  | 
 | 2         | Timestamp MSB Microsconds                      | 
 | 3         | Timestamp                                      | 
 | 4         | Timestamp                                      | 
 | 5         | Timestamp LSB                                  | 
 | 6         | MSB of VSCP class                              | 
 | 7         | LSB of VSCP class                              | 
 | 8         | MSB of VSCP type                               | 
 | 9         | LSB of VSCP type                               | 
 | 10-25     | GUID (MSB first)                               | 
 | 26        | data count MSB                                 | 
 | 27        | data count LSB                                 | 
 | 28-n      | VSCP data (0-487 bytes/Max 8 byte for Level I) | 
 | n+1       | start of next VSCP frame                       | 

#### Frame type=249 - Sent ACK

No data bytes.

#### Frame type=250 - Sent NACK

No data bytes.

#### Frame type=251 - ACK

No data bytes.

#### Frame type=252 - NACK

No data bytes.

#### Frame type=253 - Error

 | Data byte | Description                | 
 | --------- | -----------                | 
 | 0         | Error code                 | 
 | 1-255     | Possible real text message | 

#### Frame type=254 - Command reply

 | Data byte | Description                                                   | 
 | --------- | -----------                                                   | 
 | 0         | Reply code (0 is OK other code is application specific error) | 
 | 1         | Command code                                                  | 

#### Frame type=255 - Command

 | Data byte | Description                      | 
 | --------- | -----------                      | 
 | 0         | Command code                     | 
 | 1-n       | Command parameters (0-256 bytes) | 

### Special characters

As [DLE] is used as escape character the [DLE] itself is sent as [DLE][DLE]. The ASCII values for the reserved characters are

 | Character | ASCII code | 
 | --------- | ---------- | 
 | [DLE]     | 0x10       | 
 | [NUL]     | 0x00       | 
 | [STX]     | 0x02       | 
 | [ETX]     | 0x03       | 

### Command codes

Command codes and data format is decided by the device implementer. 

### Response codes

Response codes and data format is decided by the device implementer. 

### Error codes

Error codes and data format is decided by the device implementer. 




{% include "./bottom_copyright.md" %}

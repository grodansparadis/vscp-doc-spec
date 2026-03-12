# VSCP general binary protocol (VSCP-GPB)

The VSCP binary protocol is designed to be used on different types of transports such as TCP, UDP, serial, etc. The protocol is designed to be simple and efficient for sending VSCP events and commands between devices. 

Encryption is available, but optional. When used it can be AES-128, AES-192 or AES-256 in CBC mode. The encryption is applied to the entire packet except for the first byte which contains the packet type and encryption settings. The encryption key is a common key with length of 128/192/256 bits that is secret and shared between the devices. Encryption gives confidentiality but not integrity. The integrity is instead provided by the CRC which is calculated on the encrypted data. The encryption settings are defined in the first byte of the packet and indicate if encryption is used and if so which encryption method is used. Overhead for encryption is 16 bytes for all encryption types as AES has a fixed block size of 128 bits, regardless of key length.

Encrypting frames has the advantage over TLS that it can be used on any transport and that it can be used in a peer-to-peer manner without the need for a client-server architecture. It also allows for end-to-end encryption between devices without the need for a secure tunnel between them. The disadvantage is that it does not provide integrity protection and that it requires a shared secret key which can be difficult to manage in large deployments. The main advantage is the simplicity and flexibility of the protocol which allows it to be used in a wide range of applications and scenarios and abovove all no need to update certificates on devices.


### The packet format 0

 | Byte  | Description | Encrypted | 
 | :----:  | ----------- | :---------: | 
 | 0     | Packet type & encryption settings. | _Never encrypted_ | 
 | 1     | VSCP Level II Head MSB             | Yes | 
 | 2     | VSCP Level II Head LSB             | Yes | 
 | 3     | Timestamp microseconds MSB         | Yes | 
 | 4     | Timestamp microseconds             | Yes | 
 | 5     | Timestamp microseconds             | Yes | 
 | 6     | Timestamp microseconds LSB         | Yes | 
 | 7     | Year MSB                           | Yes | 
 | 8     | Year LSB                           | Yes | 
 | 9     | Month                              | Yes | 
 | 10    | Day                                | Yes | 
 | 11    | Hour                               | Yes | 
 | 12    | Minute                             | Yes | 
 | 13    | Second                             | Yes | 
 | 14    | CLASS MSB                          | Yes | 
 | 15    | CLASS LSB                          | Yes | 
 | 16    | TYPE MSB                           | Yes | 
 | 17    | TYPE LSB                           | Yes | 
 | 18-33 | ORIGINATING GUID                   | Yes | 
 | 34    | DATA SIZE MSB                      | Yes | 
 | 35    | DATA SIZE LSB                      | Yes | 
 | 36-n  | data ... limited to max 512-25 = 487 bytes  | Yes | 
 | len-2 | CRC MSB (Calculated on HEAD + CLASS + TYPE + ADDRESS + SIZE + DATA…) | Yes | 
 | len-1 | CRC LSB  | Yes | 
 | opt   | Optional encryption data such as a 16/24/32-byte IV for AES follow here | No | 

The number above is the offset in the package. Len is the total datagram size.

Time should always be UTC time. If the time block is set to all zero the current time will be set by interface (VSCP Server for example).

### The packet format 1

 | Byte  | Description | Encrypted | 
 | :----:  | ----------- | :---------: | 
 | 0     | Packet type & encryption settings. | _Never encrypted_ | 
 | 1     | VSCP Level II Head MSB             | Yes | 
 | 2     | VSCP Level II Head LSB             | Yes | 
 | 3     | Timestamp nanoseconds MSB         | Yes | 
 | 4     | Timestamp nanoseconds             | Yes | 
 | 5     | Timestamp nanoseconds             | Yes | 
 | 6     | Timestamp nanoseconds             | Yes | 
 | 7     | Timestamp nanoseconds             | Yes | 
 | 8     | Timestamp nanoseconds             | Yes | 
 | 9     | Timestamp nanoseconds             | Yes | 
 | 10    | Timestamp nanoseconds LSB         | Yes | 
 | 11    | Reserved                           | Yes | 
 | 12    | Reserved                           | Yes | 
 | 13    | Reserved                           | Yes | 
 | 14    | CLASS MSB                          | Yes | 
 | 15    | CLASS LSB                          | Yes | 
 | 16    | TYPE MSB                           | Yes | 
 | 17    | TYPE LSB                           | Yes | 
 | 18-33 | ORIGINATING GUID                   | Yes | 
 | 34    | DATA SIZE MSB                      | Yes | 
 | 35    | DATA SIZE LSB                      | Yes | 
 | 36-n  | data ... limited to max 512-25 = 487 bytes  | Yes | 
 | len-2 | CRC MSB (Calculated on HEAD + CLASS + TYPE + ADDRESS + SIZE + DATA…) | Yes | 
 | len-1 | CRC LSB  | yes | 
 | opt   | Optional encryption data such as a 16/24/32-byte IV for AES follow here | No | 

The number above is the offset in the package. Len is the total datagram size.

Time should always be UTC time. If the time block is set to all zero the current time will be set by interface (VSCP Server for example).

Timestamp is nanoseconds since the epoch (GMT).

### The packet format 14 - Protocol

This packet can go both ways. It is used to send protocol commands and replies. The command/reply code is defined in the same way as the event type (16-bit) and the command/reply arguments are defined in the same way as the data field for events. The command/reply code and arguments are encrypted in the same way as for events.

 | Byte  | Description | Encrypted | 
 | :----:  | ----------- | :---------: | 
 | 0     | Packet type & encryption settings. | _Never encrypted_ | 
 | 1     | Command code MSB             | Yes |
 | 2     | Command code LSB             | Yes |
 | 3-n    | command argument         | Yes |
 | len-2 | CRC MSB (Calculated on HEAD + CLASS + TYPE + ADDRESS + SIZE + DATA…) | Yes | 
 | len-1 | CRC LSB  | yes | 
 | opt   | Optional encryption data such as a 16/24/32-byte IV for AES follow here | No |

### The packet format 15 - Reply

 | Byte  | Description | Encrypted | 
 | :----:  | ----------- | :---------: | 
 | 0     | Packet type & encryption settings. | _Never encrypted_ | 
 | 1     | Command code MSB             | Yes |
 | 2     | Command code LSB             | Yes |
 | 3     | Error code MSB             | Yes |
 | 4     | Error code LSB             | Yes |
 | 5-n    | Reply argument         | Yes |
 | len-2 | CRC MSB (Calculated on HEAD + CLASS + TYPE + ADDRESS + SIZE + DATA…) | Yes | 
 | len-1 | CRC LSB  | yes | 
 | opt   | Optional encryption data such as a 16/24/32-byte IV for AES follow here | No |

 The command codes are the same as the command codes for the commands they are responses to.

 The error code is the standard VSCP  error code. Zero is a success. Non-zero is an error code. See [VSCP error codes](https://docs.vscp.org/vscp/specification/4.0/#_error_codes) for more information.

 The reply argument can be used to return data from the command. For example, if the command was to read a register the reply argument would contain the value of the register. The format of the reply argument is defined in the same way as the data field for events.

##### Definition of type

 | Bits | Description | 
 | :----: | ----------- | 
 | 7,6,5,4 | Packet type.| 
 | 3,2,1,0 | Encryption. | 

##### Packet types

| Value | Description | 
 | :----: | ----------- | 
 | 0 | VSCP event frame type 0 |
 | 1 | VSCP event frame type 1 |
 | 2-13 | Reserved |
 | 14 | Command |
 | 15 | Reply |


##### Encryption types

 | Code | Description |
 | :----: | ----------- |
 | 0 | No encryption |
 | 1 | AES128 CBC encryption. 16-byte IV is appended to each frame. |
 | 2 | AES192 CBC encryption. 16-byte IV is appended to each frame. |
 | 3 | AES256 CBC encryption. 16-byte IV is appended to each frame. |
 | 4-15 | Reserved |

For encryption/decryption code using AES-128/192/256. Note that byte 0 of the frame is never encrypted. The encryption/decryption is instead carried out over byte 1 up to the CRC.

On the VSCP Server the md5 of the [vscptoken](https://docs.vscp.org/vscpd/13.1/#/configuring_the_vscp_daemon?id=security) is used as the key for AES128.

##### Definition of head

See [vscp.h](https://github.com/grodansparadis/vscp/blob/master/src/vscp/common/vscp.h)

 | Bits  | Description                                                         | 
 | :----: | -----------                                                         | 
 | 15    | Set if this is a dumb node. No MDF, register, nothing.              | 
 | 14    | GUID type                                                           |
 | 13    | GUID type                                                           | 
 | 12    | GUID type                                                           |  
 | 11-8  | Reserved (**Set to zero!**).                                        | 
 | 7,6,5 | Priority.                                                           | 
 | 4     | Hard-coded.                                                         | 
 | 3     | Don't calculate CRC if bit set.                                     | 
 | 2,1,0 | Rolling index.                                                      |  

Note also that the MSB is sent before the LSB (network byte order, Big Endian). So, for little endian machines such as a typical PC the byte order needs to be reversed for multi-byte types.

There is a 24-byte overhead to send one byte of data so this is not a protocol which should be used where an efficient protocol for data intensive applications is required and where data is sent in small packets.

The CRC used is the 16-bit CCITT type and it should be calculated across all bytes except for the CRC itself.

As indicated, the Class is 16-bits allowing for 65535 classes. Class 0000000x xxxxxxxx is reserved for the Level I classes. A low-end device should ignore all packages with a class > 511.

A packet traveling from a Level I device out to the Level II world should have an address translation done by the master so that a full address will be visible on the level II segment. A packet traveling from a Level II segment to a Level I segment must have a class with a value that is less then 512 in order for it to be recognized. If it has it is aimed for the Level I segment. Classes 512-1023 are reserved for packets that should stay in the Level II segment but in all other aspects (the lower nine bits + type) are defined in the same manner as for the low-end net.

The Level II register abstraction level also has more registers (32-bit address is used) and all registers are 32–bits wide. Registers 0-255 are byte wide and are the same as for level 1. If these registers are read at level 2 they still is read as 32-bit but have the unused bits set to zero. 

VSCP level II driver implementation [described here](https://github.com/grodansparadis/vscpl2drv-udp).

## Defined Commands

 | Code  | Token |Description |
 | :---: | ----- | ----------- |
 | 0 | NOOP | No Operation. |
 | 1 | QUIT | Quit. |
 | 2 | USER | Send username. |
 | 3 | PASS | Send password. |
 | 4 | CHALLENGE | Challenge security. |
 | 5 | SEND | Send event. |
 | 6 | RETR | Retrieve one or more events |
 | 7 | OPEN | Open a connection to a device. |
 | 8 | CLOSE | Close a connection to a device. |
 | 9 | CHKDATA | Check if events are available. |
 | 10 | CLEAR | Clear input queue. |
 | 11 | STAT | Get statistical information. |
 | 12 | INFO | Get status information. |
 | 13 | GETCHID | Get channel id. |
 | 14 | SETGUID | Set GUID for channel (privileged command). |
  | 15 | GETGUID | Get GUID for channel. |
  | 16 | VERSION | Get version for interface. |
  | 17 | SETFILTER | Set filter for channel. |
  | 18 | SETMASK | Set mask for channel. |
  | 19 | INTERFACE | List interfaces on device |
  | 19 | TEST | Perform tests. |
  | 20 | SHUTDOWN | Shutdown device (privileged command). |
  | 21 | RESTART | Restart device (privilegded command). |
  | 22-65279 | Reserved | Reserved. |
  | 65280-65535 | USER | User defined commands. |


### NOOP - NO OPeration 

Do nothing, just send a positive reply.

#### Argument
None

#### Argument

### QUIT - Quit session 

Send a reply and close the connection.

#### Argument
None

### USER - Send username

Send the username for authentication. The username is sent as the command argument. Optionally the password can be sent in the same command argument separated by a colon. If the password is not sent in the same command argument it will be sent in a separate PASS command.

Note that the username and password are not encrypted in the command argument. Instead, the encryption is applied to the entire command including the command argument. So, if encryption is used the username and password will be encrypted in the same way as for events.

It is perfectly fine to construct devices that do not care about user and password and that just accept any username and password. In this case the USER and PASS commands can be used to send any string as the username and password. Privileges are coupled to users so if they are used usernames should be unique and not shared between users.

If both username and password is given do a login on the device and retretive the credentials for the user if he/she exists.

#### Argument

| Argument | Description |
| :---: | ----------- |
| username | The username for authentication. |
| : | Separator |
| password | The password for authentication. Optional, can be sent in a separate PASS command. |

### PASS - Send password

Send the password for authentication. The password is sent as the command argument. 

See notes for USER command.

If username has previously been entered do a login on the device and retretive the credentials for the user if he/she exists. If a username command has not been seen report and error.

#### Argument

| Argument | Description |
| :---: | ----------- |
| password | The password for authentication. |

### CHALLENGE - Challenge security

The reponse to a CHALLENGE is a 16 byte random  number on hex format.

#### Argument
None

### SEND - Send event

Send an event. The command argument is the same as for the data field for events.

#### Argument
Event data. The format of the event data is defined in the same way as the data field for events.

| Argument | Description |
| :---: | ----------- |
| Event | The event to send on binary form |

The event is stored in the following format

| Byte  | Description |
| :----:  | ----------- | 
 | 0     | VSCP Level II Head MSB             |
 | 1     | VSCP Level II Head LSB             |
 | 2     | Timestamp nanoseconds MSB          |
 | 3     | Timestamp nanoseconds             |
 | 4     | Timestamp nanoseconds             |
 | 5     | Timestamp nanoseconds             |
 | 6     | Timestamp nanoseconds             |
 | 7     | Timestamp nanoseconds             |
 | 8     | Timestamp nanoseconds             |
 | 9     | Timestamp nanoseconds LSB         |
 | 10    | Reserved                           |
 | 11    | Reserved                           |
 | 12    | Reserved                           |
 | 13    | CLASS MSB                          |
 | 14    | CLASS LSB                          |
 | 15    | TYPE MSB                           |
 | 16    | TYPE LSB                           |
 | 17-34 | ORIGINATING GUID                   |
 | 35    | DATA SIZE MSB                      |
 | 36    | DATA SIZE LSB                      |
 | 37-n  | data ... limited to max 512-25 = 487 bytes  |

### RETR - Retrieve one or more events

Retrieve one or more events from the remote queue. The command argument is the number of events to retrieve. If the command argument is zero  one event will be retrieved. If the command argument is greater than zero that number of events will be retrieved (if available). If the command argument is less than zero (or absent) all events in the queue will be retrieved.

#### Argument
Nr of events to retrieve. Zero or absent means one event. Negative means all events.

| Byte | Description |
| :---: | --------- |
| 0 | Number of events to retreive MSB |
| 1 | Number of events to retreive MSB |

### OPEN - Open a connection to a device

Open a connection to a device. This opens the receive of asynchronious events to be received.

#### Argument
None

### CLOSE - Close a connection to a device

Close a connection to a device. This closes the receive of asynchronious events to flow.

#### Argument
None

### CHKDATA - Check if events are available

Check if events are available in the input queue. The reply argument is the number of events available in the input queue. If a channel is opened with the OPEN command the events will be sent as they arrive and the CHKDATA command is not needed and will return zero.

#### Argument
None

### CLEAR - Clear input queue

Clear the input queue. This will remove all events from the input queue.

#### Argument
None

### STAT - Get statistical information

Get statistical information about the device.

#### Argument
None

### INFO -- Get status information.

Get status information about the device.

#### Argument
None

### GETCHID - Get channel id

Get the channel id for the current channel. The channel id is a unique identifier for the channel and is used to identify the channel in the device.

#### Argument
None

### SETGUID - Set GUID for channel (privileged command)

Set the GUID for the channel. The command argument is the GUID to set for the channel.

The filter is supplied on binary form (16 bytes MSB first)

#### Argument
GUID to set for the channel. The GUID is a 16-byte value that is sent in the same format as the originating GUID for events.

| Argument | Description |
| :---: | ----------- |
| 0-15 | The GUID to set for the channel. The GUID is a 16-byte value that is sent in the same format as the originating GUID for events. MSB first. |

### GETGUID - Get GUID for channel

Get the GUID for the channel. The reply argument is the GUID for the channel.

#### Argument
None

### VERSION - Get version for interface

Get the version for the interface. The reply argument is the version for the interface.

#### Argument
None

### SETFILTER - Set filter for channel

Set the filter for the channel. The command argument is the filter to set for the channel. The mask can also be set at the same time with this command.

#### Argument
Filter to set for the channel. Mask can be included as a second argument.

The filter (and the optional mask) is supplied on binary form.

| Argument | Description |
| :---: | ----------- |
| 0 | Filter priority |
| 1-2 | Filter Class |
| 3-4 | Filter type |
| 5-20 | Filter GUID |
| 21 | OPTIONAL Mask priority |
| 22-23 | OPTIONAL Mask Class |
| 24-25 | OPTIONAL Mask type |
| 26-41 | OPTIONAL Mask GUID |

### SETMASK - Set mask for channel

Set the mask for the channel. The command argument is the mask to set for the channel.

#### Argument
Mask to set for the cannel. The mask is supplied on binary form.

| Argument | Description |
| :---: | ----------- |
| 0 | Mask priority |
| 1-2 | Mask Class |
| 3-4 | Mask type |
| 5-20 | Mask GUID |

### INTERFACE - List interfaces on device

List the interfaces on the device. The reply argument is a list of interfaces on the device.

#### Argument
None

### TEST - Perform tests

Perform tests on the device. The command argument is the test to perform. The reply argument is the result of the test.

#### Argument
Test number followed by optional test data. Testnumber zero is reserved for ALL tests.

| Argument | Description |
| :---: | ----------- |
| 0-1 | Test to perform |

### SHUTDOWN - Shutdown device (privileged command)

Shutdown the device. This is a privileged command and should only be allowed for users with the appropriate privileges.

#### Argument
None

### RESTART - Restart device (privilegded command)

Restart the device. This is a privileged command and should only be allowed for users with the appropriate privileges.

#### Argument
None
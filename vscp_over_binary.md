
The VSCP binary protocol is designed to be used on different types of transports such as TCP, UDP, Multicast, serial, etc. The protocol is designed to be simple and efficient for sending VSCP events and commands between devices. 

Encryption is available, but optional. When used it can be AES-128, AES-192 or AES-256 in CBC mode. The encryption is applied to the entire frame except for the first byte which contains the frame type and encryption settings. The encryption key is a common key with length of 128/192/256 bits that is secret and shared between the devices. Encryption gives confidentiality but not integrity. The integrity is instead provided by the CRC which is calculated on the encrypted data. The encryption settings are defined in the first byte of the frame and indicate if encryption is used and if so which encryption method is used. Overhead for encryption is 16 bytes for all encryption types as AES has a fixed block size of 128 bits, regardless of key length.

Encrypting frames has the advantage over TLS that it can be used on any transport and that it can be used in a peer-to-peer manner without the need for a client-server architecture. It also allows for end-to-end encryption between devices without the need for a secure tunnel between them. The disadvantage is that it does not provide integrity protection and that it requires a shared secret key which can be difficult to manage in large deployments. The main advantage is the simplicity and flexibility of the protocol which allows it to be used in a wide range of applications and scenarios and abovove all no need to update certificates on devices.

On higher end systems use TLS/SSL. On lower end systems this protocol might be an alternative.

It's important to distinguish between the frame format/type and the VSCP frame type. The frame format/type is defined by the first byte of a frame and indicates the type of frame and the encryption settings. The VSCP frame type is defined by the bits 8/9 in the VSCP header and indicates the type of event and the format of the timestamp. The difference between the two is:

  * **VSCP Frame type = 0** Frame type 0 has a timestamp in microseconds since the epoch (GMT) and seperate bytes that defines the time for year/month/day/hour/minute/second. This is the original binary frame type and should normally not be useed anymore. It is kept for backward compatibility reasons.
  * **VSCP Frame type = 1** Frame type 1 has a timestamp in nanoseconds since the epoch (GMT) and reserved bytes for future use. Year/month/day/hour/minute/second can be calculated from the timestamp if needed. This is the recommended frame format for current implementations.


# Frame format 0 - VSCP frame type = 0 :id=vscp-frame-type-0


If frame is of type 0 (defined by bits 8/9 of head MSB byte) the timestamp is in microseconds since the epoch (GMT).

 | Byte  | Description | Encrypted | 
 | :----:  | ----------- | :---------: | 
 | 0     | Frame type & encryption settings. | _Byte is never encrypted_ | 
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
 | 36-n  | data ... limited to max 512 bytes  | Yes | 
 | len-2 | CRC MSB (Calculated over HEAD + CLASS + TYPE + ADDRESS + SIZE + DATA…) | Yes | 
 | len-1 | CRC LSB  | Yes | 
 | opt   | Optional encryption data such as a 16/24/32-byte IV for AES follow here | No | 

The number above is the offset in the package. Len is the total datagram size.

Time should always be UTC time. If the time block is set to all zero the current time will be set by interface (VSCP Server for example).

# Frame format 0 - - VSCP frame type  = 1 :id=vscp-frame-type-1

If VSCP frametype is of type 1 (defined by bits 8/9 of head MSB byte) the timestamp is in nanoseconds since the epoch (GMT). 

 | Byte  | Description | Encrypted | 
 | :----:  | ----------- | :---------: | 
 | 0     | Frame type & encryption settings. | _Byte is never encrypted_ | 
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

# Frame format 14 - Protocol

This frame can go both ways. It is used to send protocol commands and replies. The command/reply code is defined in the same way as the event type (16-bit) and the command/reply arguments are defined in the same way as the data field for events. The command/reply code and arguments are encrypted in the same way as for events.

 | Byte  | Description | Encrypted | 
 | :----:  | ----------- | :---------: | 
 | 0     | Frame type & encryption settings. | _Byte is never encrypted_ | 
 | 1     | Command code MSB             | Yes |
 | 2     | Command code LSB             | Yes |
 | 3-n    | command argument         | Yes |
 | len-2 | CRC MSB (Calculated over HEAD + CLASS + TYPE + ADDRESS + SIZE + DATA…) | Yes | 
 | len-1 | CRC LSB  | yes | 
 | opt   | Optional encryption data such as a 16/24/32-byte IV for AES follow here | No |

# Frame format 15 - Reply

 | Byte  | Description | Encrypted | 
 | :----:  | ----------- | :---------: | 
 | 0     | Frame type & encryption settings. | _Byte is never encrypted_ | 
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

## Definition of type byte

 | Bits | Description | 
 | :----: | ----------- | 
 | 7,6,5,4 | Frame type.| 
 | 3,2,1,0 | Encryption. | 

## Frame types

| Value | Description | 
 | :----: | ----------- | 
 | 0 | VSCP event frame type 0 |
 | 1 | VSCP event frame type 1 |
 | 2-13 | Reserved |
 | 14 | Command |
 | 15 | Reply |


## Encryption types

 | Code | Description |
 | :----: | ----------- |
 | 0 | No encryption |
 | 1 | AES128 CBC encryption. 16-byte IV is appended to each frame. |
 | 2 | AES192 CBC encryption. 16-byte IV is appended to each frame. |
 | 3 | AES256 CBC encryption. 16-byte IV is appended to each frame. |
 | 4-15 | Reserved |

For encryption/decryption code using AES-128/192/256. Note that byte 0 of the frame is never encrypted. The encryption/decryption is instead carried out over byte 1 up to the CRC.

On the VSCP Server the md5 of the [vscptoken](https://docs.vscp.org/vscpd/13.1/#/configuring_the_vscp_daemon?id=security) is used as the key for AES128.

## Definition of VSCP head

See [vscp.h](https://github.com/grodansparadis/vscp/blob/master/src/vscp/common/vscp.h)

```mermaid
packet
  +3: "Rolling index"
  +1: "!CRC"
  +1: "HC"
  +3: "Priority"
  +2: "Frame"
  +2: "Reserved"
  +3: "GUID type"
  +1: "D"
```

 | Bits  | Description                                                         | 
 | :----: | -----------                                                         | 
 | 15    | Set if this is a dumb node. No MDF, register, nothing (D).              | 
 | 14,13,12    | GUID type                                                           | 
 | 11-10  | Reserved (**Set to zero!**).                                        | 
 | 9,8  | Frame type.                                                         | 
 | 7,6,5 | Priority.                                                           | 
 | 4     | Hard-coded (HC).                                                         | 
 | 3     | Don't calculate CRC if bit set.                                     | 
 | 2,1,0 | Rolling index.                                                      |  

Note also that the MSB is sent before the LSB (network byte order, Big Endian). So, for little endian machines such as a typical PC the byte order needs to be reversed for multi-byte types.

There is a 24-byte overhead to send one byte of data so this is not a protocol which should be used where an efficient protocol for data intensive applications is required and where data is sent in small packets.

The CRC used is the 16-bit CCITT type and it should be calculated across all bytes except for the CRC itself.

As indicated, the Class is 16-bits allowing for 65535 classes. Class 0000000x xxxxxxxx is reserved for the Level I classes. A low-end device should ignore all frames with a class > 511.

A frame traveling from a Level I device out to the Level II world should have an address translation done by the master so that a full address will be visible on the level II segment. A frame traveling from a Level II segment to a Level I segment must have a class with a value that is less then 512 in order for it to be recognized. If it has it is aimed for the Level I segment. Classes 512-1023 are reserved for frames that should stay in the Level II segment but in all other aspects (the lower nine bits + type) are defined in the same manner as for the low-end net.

The Level II register abstraction level also has more registers (32-bit address is used) and all registers are 32–bits wide. Registers 0-255 are byte wide and are the same as for level 1. If these registers are read at level 2 they still is read as 32-bit but have the unused bits set to zero.

VSCP level II driver implementation [described here](https://github.com/grodansparadis/vscpl2drv-udp).

# Commands

 | Code | Token | Description |
 | :---: | ----- | ----------- |
 | 0 | [NOOP](#noop) | No Operation. |
 | 1 | [QUIT](#quit) | Quit. |
 | 2 | [USER](#user) | Send username. |
 | 3 | [PASS](#pass) | Send password. |
 | 4 | [CHALLENGE](#challenge) | Challenge security. |
 | 5 | [SEND](#send) | Reserved. |
 | 6 | [RETR](#retr) | Retrieve one or more event(s) on nodes that does not have asynchronous event support. |
 | 7 | [OPEN](#open) | Open a connection to a device. |
 | 8 | [CLOSE](#close) | Close a connection to a device. |
 | 9 | [CHKDATA](#chkdata) | Check if events are available on nodes that does not have asynchronous event support. |
 | 10 | [CLEAR](#clear) | Clear input queue on nodes that does not have asynchronous event support. |
 | 11 | [STAT](#stat) | Get statistical information. |
 | 12 | [INFO](#info) | Get status information. |
 | 13 | [GETCHID](#getchid) | Get channel id. |
 | 14 | [SETGUID](#setguid) | Set GUID for the device (privileged command). |
  | 15 | [GETGUID](#getguid) | Get GUID for the device. |
  | 16 | [VERSION](#version) | Get version of binary interface. |
  | 17 | [SETFILTER](#setfilter) | Set filter for channel. |
  | 18 | [SETMASK](#setmask) | Set mask for channel. |
  | 19 | [INTERFACE](#interface) | List interfaces on device |
  | 30 | [TEST](#test) | Perform tests. |
  | 31 | [WCYD](#wcyd) | What Can You Do, find out what a node supports. |
  | 32 | [SHUTDOWN](#shutdown) | Shutdown device (privileged command). |
  | 33 | [RESTART](#restart) | Restart device (privilegded command). |
  | 34 | [TEXT](#text) | Go back to realtext mode. |
  | 35-65279 | Reserved | Reserved. |
  | 65280-65535 | USER | User defined commands. |

---
---

## NOOP - NO OPeration :id=noop

Do nothing, just send a positive reply.

### Argument
None

### Reply

| Byte | Description |
| :---: | ----------- |
| 0-1 | Command code for NOOP command (0x0000). |
| 2-3 | Error code. Zero is success, non-zero is error. |

---
---

## QUIT - Quit session :id=quit

Send a positive reply and close the connection.

### Argument
None

### Reply

| Byte | Description |
| :---: | ----------- |
| 0-1 | Command code for QUIT command (0x0001). |
| 2-3 | Error code. Zero is success, non-zero is error. |

---
---

## USER - Send username :id=user

Send the username for authentication. The username is sent as the command argument. Optionally the password can be sent in the same command argument separated by a colon.

If the password is not sent in the same command argument it will be sent in a separate [PASS](#pass) command.

Note that the username and password are not encrypted in the command argument. Instead, the encryption is applied to the entire frame including the command argument. So, if encryption is used the username and password will be encrypted in the same way as for events.

It is perfectly fine to construct devices that do not care about user and password and that just accept any username and password. In this case the **USER** and [PASS](#pass) commands can be used to accept anything that is received. Privileges are coupled to users so if privileges are used, usernames should be unique and not shared between users.

If both username and password is given do a login on the device and retretive the credentials for the user if he/she exists and the credentials are valid. If not return error and disconnect.

Send a positive reply if the user exists and a negative reply if the user does not exist. If a login is successful the credentials for the user will be used for subsequent commands. If a login is not successful the credentials will not be set and subsequent commands will be treated as if no user is logged in.

If no password is given the device should **always** accept the username and wait for a password to be sent in a separate [PASS](#pass) command where the check of the credentials will take place. If a [PASS](#pass) command is not received within a reasonable time (for example, 30 seconds) the device should return an error and disconnect.

It is perfectly fine to send multiple **USER** commands in a row. The last one will be the one that is used for authentication.

### Argument

| Argument | Description |
| :---: | ----------- |
| username | The username for authentication. Max 64 characters.|
| : | Optional colon separator if password is set. |
| password | The optional password for authentication. Can be sent in a separate [PASS](#pass) command. Max 64 characters.|

### Reply

| Byte | Description |
| :---: | ----------- |
| 0-1 | Command code for USER command (0x0002). |
| 2-3 | Error code. Zero is success, non-zero is error. |

---
---

## PASS - Send password :id=pass

Send the password for authentication. The password is sent as the command argument.

See notes for [USER](#user) command.

If username has previously been entered do a login on the device and retretive the credentials for the user if he/she exists and the credentials are valid. If not return error and disconnect. If a username command has not been seen report and error and disconnect.

If no username has been given the device should return an error and wait for a [USER](#user) command to restart the login process.

### Argument

| Argument | Description |
| :---: | ----------- |
| password | The password for authentication. Max 64 characters. |

### Reply

| Byte | Description |
| :---: | ----------- |
| 0-1 | Command code for PASS command (0x0003). |
| 2-3 | Error code. Zero is success, non-zero is error. |

---
---

## CHALLENGE - Challenge security :id=challenge

The reponse to a CHALLENGE is a 16 byte random number, aka session id,  on hex format.

### Argument
None

### Reply

| Byte | Description |
| :---: | ----------- |
| 0-1 | Command code for CHALLENGE command (0x0004). |
| 2-3 | Error code. Zero is success, non-zero is error. |
| 4-35 | 16 byte random number (session id) in hex format. |

---
---

## SEND - Send event (deprecated) :id=send

Send event to the device. The event is sent as the command argument in the same format as for events sent asynchronously. This command is deprecated and should not be used. Instead, events should be sent asynchronously and the [OPEN](#open) command should be used to open a channel for receiving asynchronous events.

### Argument

 | Argument | Description |
 | :---: | ----------- |
 | 0     | VSCP Level II Head MSB              |
 | 1     | VSCP Level II Head LSB             |
 | 2     | Timestamp nanoseconds MSB          |
 | 3     | Timestamp nanoseconds              |
 | 4     | Timestamp nanoseconds              |
 | 5     | Timestamp nanoseconds              |
 | 6     | Timestamp nanoseconds              |
 | 7     | Timestamp nanoseconds              |
 | 8     | Timestamp nanoseconds              |
 | 9     | Timestamp nanoseconds LSB          |
 | 10    | Reserved                           |
 | 11    | Reserved                           |
 | 12    | Reserved                           |
 | 13    | CLASS MSB                          |
 | 14    | CLASS LSB                          |
 | 15    | TYPE MSB                           |
 | 16    | TYPE LSB                           |
 | 17-32 | ORIGINATING GUID                   |
 | 33    | DATA SIZE MSB                      |
 | 34    | DATA SIZE LSB                      |
 | 35-n  | data ... limited to max 512 bytes  |

### Reply
| Byte | Description |
| :---: | ----------- | 
| 0-1 | Command code for SEND command (0x0005). |
| 2-3 | Error code. Zero is success, non-zero is error. |


---
---

## RETR - Retrieve one or more events

Retrieve one or more events from the remote queue. The command argument is the number of events to retrieve. If the command argument is zero or absent, one event will be retrieved. If the command argument is greater than zero that number of events will be retrieved (if available).

Events are retrieved in the same format as for events sent asynchronously.

This command is used on nodes that does not have asynchronous event support or which have their channel closed. On nodes that have asynchronous event support the events will be sent as they arrive and the RETR command is not needed and will always return a positive reply.

### Argument
Number of events to retrieve. Zero or absent means one event.

| Byte | Description |
| :---: | --------- |
| 0 | Number of events to retreive MSB |
| 1 | Number of events to retreive LSB |

### Reply

| Byte | Description |
| :---: | ----------- |
| 0-1 | Command code for RETR command (0x0006). |
| 2-3 | Error code. Zero is success, non-zero is error. |

Events are returned in the same format as for events sent asynchronously. If the command argument is greater than zero and that number of events is not available, all available events will be returned and a positive reply will be sent. If no events are available a negative reply with error code VSCP_ERROR_RCV_EMPTY (msg=vscp_binary_MSG_NO_MSG) will be sent.

---
---

## OPEN - Open a connection to a device :id=open

Open a connection to a channel on the device. This opens the receive of asynchronous events to be received.

### Argument
None

### Reply

| Byte | Description |
| :---: | ----------- |
| 0-1 | Command code for OPEN command (0x0007). |
| 2-3 | Error code. Zero is success, non-zero is error. |

---
---

## CLOSE - Close a connection to a device :id=close

Close a connection to a channel on the device. This closes the flow of asynchronous events. Events will still be collected in the input queue and can be retrieved with the RETR command or checked for availability with the CHKDATA command.

### Reply

| Byte | Description |
| :---: | ----------- |
| 0-1 | Command code for CLOSE command (0x0008). |
| 2-3 | Error code. Zero is success, non-zero is error. |

### Argument
None

---
---

## CHKDATA - Check if events are available :id=chkdata 

Check if events are available in the input queue. The reply is the number of events available in the input queue. If a channel is opened with the OPEN command the events will be sent as they arrive and the CHKDATA command is not needed and will always return zero.

### Argument
None

### Reply

| Byte | Description |
| :---: | ----------- |
| 0-1 | Command code for CHKDATA command (0x0009). |
| 2-3 | Error code. Zero is success, non-zero is error. |
| 4-7 | Number of events available in the input queue MSB first. |

---
---

## CLEAR - Clear input queue :id=clear

On a devices with asynchronous event support this command can be used to clear the events that have arrived but not yet been sent to the client. On a device without asynchronous event support this command can be used to clear the events that have arrived and are waiting in the input queue.

Before the [OPEN](#open) command has been received by the device the events will be collected in the input queue and can be retrieved with the [RETR](#retr) command or checked for availability with the [CHKDATA](#chkdata) command. If a channel is opened with the [OPEN](#open) command the events will be sent as they arrive and the CLEAR command will not have any effect on the events that have arrived but not yet been sent to the client.

### Argument
None

### Reply

| Byte | Description |
| :---: | ----------- |
| 0-1 | Command code for CLEAR command (0x000A). |
| 2-3 | Error code. Zero is success, non-zero is error. |

---
---

## STAT - Get statistical information :id=stat

Get statistical information about the device. Eight values are returned in the reply argument:

### Argument
None

### Reply

| Bytes | Description |
| :---: | ----------- |
| 0-1 | Command code for STAT command (0x000B). |
| 2-3 | Error code. Zero is success, non-zero is error. |
| 4-7 | Currently undefined value x MSB first. |
| 8-11 | Currently undefined value y MSB first. |
| 12-15 | Currently undefined value z MSB first. |
| 16-19 | Number of databytes received by the device MSB first. |
| 20-23 | Number of frames received by the device MSB first. |
| 24-27 | Number of databytes transmitted by the device MSB first. |
| 28-31 | Number of frames transmitted by the device MSB first. |  
| 32-35 | Number of overruns (send/receive) MSB first. |

---
---

## INFO -- Get status information :id=info

Get status information about the device.

### Argument
None

### Reply

| Byte | Description |
| :---: | ----------- |
| 0-1 | Command code for INFO command (0x000C ). |
| 2-3 | Error code. Zero is success, non-zero is error. |
| 4-7 | Channel status (user defined code) |
| 8-11 | Last error code |
| 12-15 | Last error subcode |
| 16-len (max: 91) | Last error string. Max 80 bytes including zero termination. |

---
---

## GETCHID - Get channel id :id=getchid

Get the channel id for the current channel. The channel id is a unique 32-bit identifier for the channel and is used to identify the channel in the device. A device that does not care about channels return zero.

### Argument
None

### Reply

| Byte | Description |
| :---: | ----------- |
| 0-1 | Command code for GETCHID command (0x000D). |
| 2-3 | Error code. Zero is success, non-zero is error. |
| 4-7 | Channel id. The channel id is a 32-bit value that identifies the channel. MSB first. |

---
---

## SETGUID - Set GUID for channel (privileged command) :id=setguid

Set the GUID for the device. The command argument is the GUID to setl.

Most devices form a GUID from a unique identifier such as a MAC address and a device id. This command can be used to set the GUID to a custom value. This is a privileged command and should only be allowed for users with the appropriate privileges.

### Argument
GUID to set for the device. T

| Argument | Description |
| :---: | ----------- |
| 0-1 | Command code for SETGUID command (0x000E). |
| 2-3 | Error code. Zero is success, non-zero is error. |
| 4-19 | The GUID to set for the device. The GUID is a 16-byte value that is sent in the same format as the originating GUID for events. MSB first. |

### Reply

| Byte | Description |
| :---: | ----------- |
| 0-1 | Command code for SETGUID command (0x000E). |
| 2-3 | Error code. Zero is success, non-zero is error. |

---
---

## GETGUID - Get GUID for device :id=getguid

Get the GUID for the device.

### Argument
None

### Reply

| Byte | Description |
| :---: | ----------- |
| 0-1 | Command code for GETGUID command (0x000F). |
| 2-3 | Error code. Zero is success, non-zero is error. |
| 4-19 | GUID for the device. The GUID is a 16-byte value that is sent in the same format as the originating GUID for events. MSB first. |

---
---

## VERSION - Get version for interface :id=version

Get the version for the interface. The reply argument is the version for the interface.

### Argument
None

### Reply

| Byte | Description |
| :---: | ----------- |
| 0-1 | Command code for VERSION command (0x0010). |
| 2-3 | Error code. Zero is success, non-zero is error. |
| 4-7 | Major version |
| 8-11 | Minor version |
| 12-15 | Patch version |

---
---

## SETFILTER - Set filter for channel :id=setfilter

Set the filter for the channel. The command argument is the filter to set for the channel. The mask can also be set at the same time with this command.

### Argument
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

### Reply

| Byte | Description |
| :---: | ----------- |
| 0-1 | Command code for SETFILTER command (0x0011). | |
| 2-3 | Error code. Zero is success, non-zero is error. | 

---
---

## SETMASK - Set mask for channel :id=setmask

Set the mask for the channel. The command argument is the mask to set for the channel.

### Argument
Mask to set for the cannel. The mask is supplied on binary form.

| Argument | Description |
| :---: | ----------- |
| 0 | Mask priority |
| 1-2 | Mask Class |
| 3-4 | Mask type |
| 5-20 | Mask GUID |

### Reply
| Byte | Description |
| :---: | ----------- |
| 0-1 | Command code for SETMASK command (0x0012). |
| 2-3 | Error code. Zero is success, non-zero is error. |

---
---

## INTERFACE - List interfaces on device :id=interface

List the interfaces on the device. The reply argument is a list of interfaces on the device.

### Argument
| First argument | Second argument | Description |
| :---: | :---: | ----------- |
| 0 | - | Get interface count |
| 1 | Index of the interface | Get interface information. The reply will contain the information for one interface. If the device has more than one interface this command can be sent multiple times to get the information for all interfaces. The argument is the index of the interface to get information for, starting from zero. |
| 2 | Index of the interface | Close interface. The argument is the index of the interface to close, starting from zero. This will close the interface and stop receiving/sending events on that interface. |
| 3 | Index of the interface | Open interface. The argument is the index of the interface to open, starting from zero. This will open the interface and start receiving/sending events on that interface. |

### Reply

#### Get interface count

| Byte | Description |
| :---: | ----------- |
| 0-1 | Command code for INTERFACE command (0x0013). |
| 2-3 | Error code. Zero is success, non-zero is error. |
| 4-5 | Interface count. |

#### Get interface information

| Byte | Description |
| :---: | ----------- |
| 0-1 | Command code for INTERFACE + 1 command (0x0014). |
| 2-3 | Error code. Zero is success, non-zero is error. |
| 6-7 | Interface index MSB first. |
| 8-23 | Interface GUID |
| 24-87 | Interface description. Max 64 bytes including null termination. |


#### Close interface

| Byte | Description |
| :---: | ----------- |
| 0-1 | Command code for INTERFACE + 2 command (0x0015). |
| 2-3 | Error code. Zero is success, non-zero is error. |
| 6-7 | Interface index MSB first. |

#### Open interface

| Byte | Description |
| :---: | ----------- |
| 0-1 | Command code for INTERFACE + 3 command (0x0016). |
| 2-3 | Error code. Zero is success, non-zero is error. |
| 6-7 | Interface index MSB first. |

---
---

## TEST - Perform tests :id=test

Perform tests on the device. The command argument is the test to perform. The reply argument is the result of the test.

### Argument
Test number followed by optional test data. Testnumber zero is reserved for ALL tests.

| Argument | Description |
| :---: | ----------- |
| 0-1 | Test to perform |

### Reply
| Byte | Description |
| :---: | ----------- |
| 0-1 | Command code for TEST command (0x0014). |
| 2-3 | Error code. Zero is success, non-zero is error. |
| 4-7 | Test result. The format of the test result is defined by the test that is performed. |

---
---

## WCYD - What Can You Do, find out what a node supports :id=wchyd
Find out what a node supports. The reply argument is a 64-bit bitfield with supported commands and features on the device. The bitfield is described [here](https://docs.vscp.org/spec/latest/#/./class2.protocol?id=type20)

### Argument
Eight bytes representing the 64-bit bitfield with supported commands and features on the device. MSB first.

### Reply
| Byte | Description |
| :---: | ----------- |
| 0-1 | Command code for WCYD command (0x0015). |
| 2-3 | Error code. Zero is success, non-zero is error. |
| 4-11 | 64-bit bitfield with supported commands and features on the device. MSB first. |

---
---

## SHUTDOWN - Shutdown device (privileged command) :id=shutdown

Shutdown the device. This is a privileged command and should only be allowed for users with the appropriate privileges.

### Argument
None

### Reply
| Byte | Description |
| :---: | ----------- |
| 0-1 | Command code for SHUTDOWN command (0x0016). |
| 2-3 | Error code. Zero is success, non-zero is error. |

---
---

## RESTART - Restart device (privilegded command) :id=restart

Restart the device. This is a privileged command and should only be allowed for users with the appropriate privileges.

### Argument
None

### Reply
| Byte | Description |
| :---: | ----------- |
| 0-1 | Command code for RESTART command (0x0017). |
| 2-3 | Error code. Zero is success, non-zero is error. |

---
---

## TEXT - Go back to realtext mode :id=text

Go back to realtext mode. This command is used in the VSCP tcp/ip link protocol to return into realtext mode leaving the binary protocol mode. If your device supports both the binary protocol and a realtext  protocol this command can be used to switch back to text mode.  If your device does not support the text protocol this command can be ignored and a negative reply can be returned.

The VSCP link protocol is designed to be able to switch between binary and text mode on the fly. This allows for example a client to connect to a device using the binary protocol, perform some operations and then switch back to text mode to interact with the device in a more human friendly way. The **BINARY** command is used on the text protocol to switch to binary mode.

### Argument
None

### Reply
| Byte | Description |
| :---: | ----------- |
| 0-1 | Command code for TEXT command (0x0018). |
| 2-3 | Error code. Zero is success, non-zero is error. |

---
---

[filename](./bottom_copyright.md ':include')

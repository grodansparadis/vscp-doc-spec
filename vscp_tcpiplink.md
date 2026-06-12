# VSCP tcp/ip link protocol

This protocol can be used by tcp/ip based nodes to export an interface to it's VSCP functionality. The device can be a device that implemets registers and have an MDF with specifi cconfigurable functionality or it can be a simple device that just have a tcp/ip interface and no MDF and just connect to some other interfaces which send and receive events. Or it can of course be a mixture of the two.

Originally the VSCP tcp/ip link interface was added to allow clients to connect to the [VSCP daemon](https://grodansparadis.github.io/vscp-daemon/#/). But as the protocol is very flexible it has evolved to be used for other purposes as well.

Mostly however the tcp/ip link interface is used by clients to connect to a server and to send and receive events. The tcp/ip link protocol is very much like the POP3 protocol. A command is sent (ending with CRLF) and a response line is received starting with either ”**+OK**” for success or ”**-OK**” for failure. The initial “token” is followed by some descriptive text that is separated from the initial token with “ - “ (a dash with a space on it's both sides).

The server device can be a VSCP daemon or it can be a lower end device with a built in tcp/ip interface. The protocol is very  light weight and can be used for many purposes. It is not only for sending and receiving events but also for control of the server/device and for configuration of the server/device.

## Port

Default Port for the VSCP tcp/ip link interface is 9598 but the interface can be available on several port and several interfaces on a specific hardware.

## Security

SSL/TLS is the obvious choice for a tcp/ip link. But if the tcp/ip server is on an embedded device with limited resources i addition to the need for cerificate updates on a regular basis, it may not be possible or practical to use SSL/TLS. For such devices a simple yet powerful AES-128/192/256 encryption schema is available. The encryption schema is described in the [vscp_over_binary.md](https://docs.vscp.org/spec/latest/#/./vscp_over_binary?id=security) specification document.

### Credentials

Username and password pairs for the tcp/ip link interface is used to login to a device that export a VSCP tcp/ip link interface. Actually they are not required for smaller simpled devices where there is only one users. It is up to the implementation to decide if credentials are needed or not. However for a device with more than one user the credentials are needed to determine which user is logged in and what access rights this user have.

Connected to a user account is the following information

#### The allowed host-list

A list with locations/computers/networks this user can access the interface from. Wild-card can be used so access from a single computer can be set as “192.168.1.8” but access for the hole subclass can be set as “192.168.1.*”.

#### Privilege level
This defines which commands the user have access to. The privilege level is a value between 0 and 15 where 0 is the lowest level and 15 is the highest level. A user with privilege level 0 only have access to commands that are marked with privilege level 0 in the command list. A user with privilege level 1 have access to commands with privilege level 0 and 1 and so on.

#### Event list

This defines the events the user can send. Wildcard can be used so hole clases can be allowed or blocked. 

#### Filter/mask for received events

This defines the events the user can receive.

## Test server
You can test the VSCP link protocol at

    tcp://vscp1.vscp.org:9598

the credentials are

    username: vscp
    password: secret

Using command line

    telnet vscp1.vscp.org 9598

will take you there.

# Protocol description


## Command and response format

The VSCP TCP protocol is very much like the POP3 protocol.

*  A command is sent (ending with CRLF)

*  A response line is received starting with either ”**+OK**” for success or ”**-OK**” for failure. The initial “token” is followed by some descriptive text that is separated from the initial token with “ - “ (a dash with a space on it's both sides).

For some commands there can be data in between the two lines. For instance the “**VERS**” command looks like this

    send: 'VERS<CR><LF>
    received line 1: '1,0,0<CR><LF>
    received line 2: '+OK - Success.<CR><LF>

## List of defined commands

 | Command  | Privilege | Link | From version | Description  |
 | :------- | :--: | :----: | :------------: | -----------  |
 | +        | 0         | yes  | 0.0.2        | Repeat the last command  |
 | [NOOP](./vscp_tcpiplink.md#tcpip-noop) | 0  | yes  | 0.0.1 | No operation. |
 | [HELP](./vscp_tcpiplink.md.md#tcpip-help) | 0  | no   | 0.0.2 | Give command help. |
 | [QUIT](./vscp_tcpiplink.md.md#tcpip-quit) | 0  | yes  | 0.0.1 | Close the connection. |
 | [USER](./vscp_tcpiplink.md.md#tcpip-user) | 0  | yes  | 0.0.1 | Username for login. |
 | [PASS](./vscp_tcpiplink.md.md#tcpip-pass) | 0  | yes  | 0.0.1 | Password for login. |
 | [CHALLENGE](./vscp_tcpiplink.md.md#tcpip-challenge) | 0         | yes  | 1.12.14.4 | Get session id. |
 | [SEND](./vscp_tcpiplink.md.md#tcpip-send) | 4         | yes  | 0.0.1 | Send an event. |
 | [RETR](./vscp_tcpiplink.md.md#tcpip-retr) | 2         | yes  | 0.0.1 | Retrieve one or several event(s). |
 | [RCVLOOP](./vscp_tcpiplink.md.md#tcpip-rcvloop) | 2         | yes  | 0.0.2        | Will retrieve events in an endless loop until the connection is closed by the client.  |
 | [QUITLOOP](./vscp_tcpiplink.md.md#tcpip-quitloop) | 2         | yes  | 0.4.29 | Terminate RCVLOOP |
 | [CDTA/CHKDATA](./vscp_tcpiplink.md.md#tcpip-chkdata) ((Both versions of the command should be supported))    | 1    | yes  | 0.0.1 | Check if there are events to retrieve. |
 | [CLRA/CLRALL](./vscp_tcpiplink.md.md#tcpip-clrall) ((Both versions of the command should be supported)) | 1         | yes  | 0.0.1 | Clear all events in in-queue.                                                                      |
 | [STAT](./vscp_tcpiplink.md.md#tcpip-stat) | 1         | yes  | 0.0.1 | Get statistics information. |
 | [INFO](./vscp_tcpiplink.md.md#tcpip-info) | 1         | yes  | 0.0.1 | Get status information. |
 | [CHID/GETCHID](./vscp_tcpiplink.md.md#tcpip-chid) ((Both versions of the command should be supported)) | 1         | yes  | 0.0.1 | Get channel ID. |
 | [SGID/SETGUID](./vscp_tcpiplink.md.md#tcpip-setguid) ((Both versions of the command should be supported)) | 6         | yes  | 0.0.1 | Set GUID for channel. |
 | [GGID/GETGUID](./vscp_tcpiplink.md.md#tcpip-getguid) ((Both versions of the command should be supported)) | 1         | yes  | 0.0.1 | Get GUID for channel. |
 | [VERS/VERSION](./vscp_tcpiplink.md.md#tcpip-version) ((Both versions of the command should be supported)) | 0         | yes  | 0.0.1 | Get the implemented VSCP tcp/ip link interface version. |
 | [SFLT/SETFILTER](./vscp_tcpiplink.md.md#tcpip-setfilter) ((Both versions of the command should be supported))            | 6 | yes  | 0.0.1 | Set incoming event filter. |
 | [SMSK/SETMASK](./vscp_tcpiplink.md.md#tcpip-setmask)  | 6         | yes  | 0.0.1 | Set incoming event mask.  |
 | [TEST](./vscp_tcpiplink.md.md#tcpip-test) | 15 | no   | 0.0.2 | Do test sequence. Only used for debugging.  |
 | [SHUTDOWN](./vscp_tcpiplink.md.md#tcpip-shutdown) | 15        | no   | 0.0.2 | Shutdown the device. |
 | [RESTART](./vscp_tcpiplink.md.md#tcpip-restart) | 15        | no   | 0.0.2 | Restart the device.  |
 | [INTERFACE](./vscp_tcpiplink.md.md#tcpip-interface) | 15        | yes   | 0.0.2 | Interface manipulation. Have secondary commands. |
 | [WCYD/WHATCANYOUDO](./vscp_tcpiplink.md.md#tcpip-whatcanyoudo) ((Both versions of the command should be supported)) | 0         | yes  | 0.4.29 | Request what this sever can do |
  | [BINARY](#tcpip-binary) | 0         | no   | 0.4.29 | Enter binary mode (if available) |

You can define your custom commands of course. Please prefix them with "X" to distinguish them from the standard commands. So, for instance, "XMYCOMMAND" is a good name for a custom command.

----
---- 

## NOOP - No operation :id=tcpip-noop

This operation does nothing. It just replies with ”**+OK**”.

### Argument
No argument.

### Response
    +OK - Success.<CR><LF>

----
---- 

## TEST - Run tests :id=tcpip-test

Run device specific tests. Command can have arguments. It replies with ”**+OK**” if test(s) is OK, error code otherwise. Argument is the test number or test name. If no argument is given all tests should be run. There arer no standard tests defined. It is up to the implementation to define the tests.

### Argument
No argument.

### Response
  test number or name<CR><LF>
  <one or more lines with test specific output>
  +OK - Success.<CR><LF>

----
---- 

##  QUIT - Close the connection :id=tcpip-quit

Close the connection to the host and sign off the user. The server should reply with ”**+OK**” before closing the connection.

### Argument
No argument.

### Response
  +OK - Success.<CR><LF>

----
---- 

##  HELP - Give help :id=tcpip-help

'HELP' alone gives help about all commands. "HELP 'command'" gives help about the specific 'command'.

----
---- 

## USER - Username for login :id=tcpip-user

Used to enter username for a password protected server.

Used on the following form:

    USER username<CR><LF>


### Argument
A user name with a maximum length of 64 characters.

### Response
A positive response

    +OK - User name accepted, password please.<CR><LF>

is always given even if the username is not known to the system. The credentials are checked in the next step after the PASS command is received. If seveveral user commands are sent the last sent is used.

----
---- 

## PASS - Password for login :id=tcpip-pass

Used to enter username for a password protected server.

Used on the following form:

    PASS password<CR><LF>

**If the credentials are found to be invalid the connection link should be closed.**

### Argument
A password with a maximum length of 64 characters.

### Response
  +OK - Success.<CR><LF>    
or
  -OK - Invalid username or password.<CR><LF>

----
---- 

## CHALLENGE - Get challenge session id :id=tcpip-challenge

Used to get a session unique id

Used on the following form:

    CHALLENGE<CR><LF>

and give a response such as

    +OK - e14712fa9d6a62ff388a701848e24a32

where "e14712fa9d6a62ff388a701848e24a32" is the 32 byte sid on hex format.

A new session id is formed every time this command is sent. The session id is used for encryption and decryption of data on the tcp/ip link. The session id is used as a iv for the AES encryption and decryption. The session id is generated by the server and is unique for each session. It is up to the implementation to decide how the session id is generated but it should be unique for each session and should be random enough to not be guessable.

### Argument
No argument.

### Response

  +OK - '128 bit sid on hex format'.<CR><LF>

----
---- 

## RESTART - Restart device :id=tcpip-restart

Restart the device. User must have highest privilege to be able to do this.

### Argument
No argument.

### Response

  +OK - Success.<CR><LF>
or
  -OK - Command is not supported here.<CR><LF>
if the device does not support this command.

----
---- 

##  SHUTDOWN - Shutdown device :id=tcpip-shutdown

Shutdown the device. Must have highest privilege to be able to do this.

### Argument
No argument.

### Response
  +OK - Success.<CR><LF>

----
---- 

## SEND - Send an event :id=tcpip-send

Used on the following form:

    send head,class,type,obid,datetime,timestamp,GUID,data1,data2,data3....
or
    send $variablename

The GUID is given on the form MSB-byte:MSB-byte-1:MSB-byte-2……. The GUID can also be given as ”-” in which case the GUID of the interface is used for the event.

datetime and timestamp can be sent in two different ways

1.) Legacy

**datetime** is UTC date time (Coordinated Universal Time) on ISO format
    YYYY-MM-DDTHH:MM:DD 

If timestamp is a relative time in microseconds. It can be empty in which case a timestamp will be set by the system. Before version *1.12.20.0* a timestamp of zero would be replaced by a system set timestamp this is not the case anymore.

When received the leagacy format should be conveted to the nanosecond timestamp format.

2.) With nanosecond timestamp

Leave datetime empty (keep the comma) and set timestamp to a 64-bit unix timestamp with nanosecond resolution. This is the number of nanoseconds since 1970-01-01T00:00:00Z with nanosecond resolution. 

The variable send form makes it possible to send the content in a remote variable on a system that have them. In this case give the name of the variable as argument preceded with a dollar ('$') sign.

**Example:**
Send a full GUID event

    send 0,20,3,,,,00:01:02:03:04:05:06:07:08:09:0A:0B:0C:0D:0E:0F,0,1,35<CR><LF>

Send Event. The example is the same as above but the GUID of the interface will be used.

    send 0,20,3,,,,-,0,1,35<CR><LF>

which is the same as

    send 0,20,3,,,,,0,1,35<CR><LF>    

Send event with UTC time set

    send 0,20,3,,2001-11-02T18:00:01,,-,0,1,35<CR><LF>

send event with GUID on textual form

    send 0,20,3,,,,{xxxxx...},0,1,35<CR><LF> 

where {xxxxx...} is the GUID in textual form. The format for the textual form is explained [here](https://grodansparadis.github.io/vscp-doc-spec/#/./vscp_globally_unique_identifiers).

With this format sending

    send 0,20,3,,,,{::FE:0:5:93:140:2:32:0:1},0,1,35<CR><LF>

This is the same as sending

    send 0,20,3,,,,{FF:FF:FF:FF:FF:FF:FF:FE:0:5:93:140:2:32:0:1},0,1,35<CR><LF>

All the above examples will send the same event [CLASS1.INFORMATION TYPE=3 ON event](http://docs.vscp.org/spec/latest/#/./class2.level1.information1), for zone=1, sub-zone=35

**Send event to specific interface**
It is possible to direct Level I events to a specific interface on a device. To do this use the Level II mirror Level I events ( Class=512-1023 VSCP Level II Level I events - CLASS2.LEVELI). This is events with class equal to 512 - 1023 which mirrors the Level I events but have the destination GUID in data bytes 0-15. Thees data-bytes is set to the interface (14 upper bits) and the node-ID for the node one wants to communicate with is in GUID[0]. This event will be sent to the correct interface.

So the above example would be

    send 0,20,3,,,0,-,00,0F,0E,0D,0C,0B,0A,09,08,07,06,05,04,03,02,01,00,00,01,35<CR><LF>

where class will become *532* (512 + 20) and where *00,0F,0E,0D,0C,0B,0A,09,08,07,06,05,04,03,02,01,00,00* is the interface the events should be routed to. Note the two zeros at the two least significant bytes always is zero for an interface and is reserved for node id's.

**Send content of variable**

    send $tempevent1

In this example the content of the variable tempevent1 is sent. The variable is of type event.

### Argument
Event on string format or variable name preceded with a dollar sign.

### Response
  +OK - Success.<CR><LF>

----
---- 

## RETR - Retrieve one or several event(s) :id=tcpip-retr

This command can be used to retrieve one or several events from the input queue. Events are returned as

    head,class,type,obid,datetime,timestamp,GUID,data0,data1,data2,...........

on legacy systems where timestamp is in microseconds. Newer systems will return

    head,class,type,obid,,timestamp,GUID,data0,data1,data2,...........

where timestamp is a 64-bit unix timestamp with nanosecond resolution. This is the number of nanoseconds since 1970-01-01T00:00:00Z with nanosecond resolution.

VSCP Event originating from a CANAL driver have the nickname of the node in the LSB of the GUID ( GUID[15] ). The rest of the GUID is the GUID for the interface.

If the rcvloop command has been used this command will return zero events and a positive reply. The events will instead be sent asynchronously as they arrive.

### Argument
Number of events to fetch. If no argument is given one event is fetched even if there are more in the queue.

If you try to fetch more events then there is events in the buffer "-OK" will be returned after the available number of events have been retrieved and been listed.

### Response

Used on the following form:

    RETR 2<CR><LF>

which gives

    0,20,3,0,2001-11-02T17:43:15,0,FF:FF:FF:FF:FF:FF:FF:FE:0:5:93:140:2:32:0:1
    0,20,4,0,2001-11-02T17:43:15,0,FF:FF:FF:FF:FF:FF:FF:FE:0:5:93:140:2:32:0:1
    +OK - Success

in the legacy format.

If no events is available in the queue

	-OK - No event(s) available

is received by the client.

If you try to fetch more events then there are in the queue you will get

    retr 100
    0,1,1,4,2001-11-02T17:43:15,0,FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:F5:00:04:00:00
    0,1,1,4,2001-11-02T17:43:15,0,FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:F5:00:04:00:00
    0,1,1,4,2001-11-02T17:43:15,0,FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:F5:00:04:00:00
    0,1,1,4,2001-11-02T17:43:15,0,FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:F5:00:04:00:00
    0,1,1,4,2001-11-02T17:43:15,0,FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:F5:00:04:00:00
    0,1,1,4,2001-11-02T17:43:15,0,FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:F5:00:04:00:00
 1. OK - No event(s) available

You request 100 events but there is only 6 available so you get a negative reply.

----
---- 

## RCVLOOP - Send events to client as soon as they arrive :id=tcpip-rcvloop

This command set the channel in a closed loop that only can be interrupted by a client closing the connection or by sending the CLOSELOOP command. The server will now send out an event as soon as it is reserved. This is done in a very effective way with high throughput. This means the client does not have to poll for new events. It just open one channel where it sends events and do control tasks and one channel where it receive evens.

To help in determining that the line is alive

    +OK

is sent with a two second interval. The format for the event data is the same as for RETR command.

Some applications may not implement this feature and should output

    -OK - Command not implemented<CR><LF>

to indicate this.

### Argument
No argument.

### Response
  +OK - Success.<CR><LF>

----
---- 

## QUITLOOP - quit receiving loop :id=tcpip-quitloop

Quit a receive loop started by the RCVLOOP command.

### Argument
No argument.

### Response
  +OK - Success.<CR><LF>

----
---- 

## CDTA/CHKDATA - Check if there are events to retrieve :id=tcpip-chkdata

This command are used to check how many events are in the input queue waiting for retrieval.

Used on the following form:

    CDTA<CR><LF>

and reply is

    8 <CR><LF>
    +OK<CR><LF>

### Argument
No argument.

### Response
  Number of events in queue<CR><LF>
  +OK - Success.<CR><LF>    

----
---- 

## CLRA/CLRALL - Clear all events in in-queue :id=tcpip-clrall

This command are used to clear all events in the input queue.

Used on the following form:

   CLRA<CR><LF>

and reply is

    +OK - All events cleared.<CR><LF>

### Argument
No argument.

### Response
  +OK - All events cleared.<CR><LF>

----
---- 

## STAT - Get statistics information :id=tcpip-stat

Get interface statistics information. The returned format is

    x,y,z,cntReceiveData,cntReceiveFrames,cntTransmitData,cntTransmitFrames

Where x,y,z currently is undefined values.

**Example:**

    STAT<CR><LF>

reply is
    0,0,0,12356,56,9182,20<CR><LF>
    +OK - Success.<CR><LF>

### Argument
No argument.

### Response
  x,y,z,cntReceiveData,cntReceiveFrames,cntTransmitData,cntTransmitFrames<CR><LF>
  +OK - Success.<CR><LF>

----
---- 

## INFO - Get status information :id=tcpip-info

This command fetch the status information for the interface. Returned format is

    channel-status,lasterrorcode,lasterrorsubcode,"lasterrorstr"

**Example:**

    INFO<CR><LF>

and the reply is

    7812,12,0,"Overrun"<CR><LF>
    +OK - Success.<CR><LF>

### Argument
No argument.

### Response
  channel-status,lasterrorcode,lasterrorsubcode,"lasterrorstr"<CR><LF>
  +OK - Success.<CR><LF>    

----
---- 

## CHID - Get channel ID :id=tcpip-chid

Get the channel ID for the communication channel. This is the same parameter as the obid which is present in events.

**Example:**

    CHID<CR><LF>

and the reply is

    1234<CR><LF>
    +OK<CR><LF>

### Argument
No argument.

### Response
  channel ID<CR><LF>
  +OK - Success.<CR><LF>    

----
---- 

## SGID/SETGUID - Set GUID for channel :id=tcpip-setguid

Set the GUID for this channel. The GUID is given on the form

The format is:

    SETGUID 0:1:2:3:4:5:6:7:8:9:10:11:12:13:14:15<CR><LF>

or
    SGID 0:1:2:3:4:5:6:7:8:9:10:11:12:13:14:15<CR><LF>

and reply is

    +OK<CR><LF>

### Argument
GUID on the form

    0:1:2:3:4:5:6:7:8:9:10:11:12:13:14:15

or

    {GUID on one of the accepted forms}


### Response
  +OK - Success.<CR><LF>    

----
---- 

## GGID/GETGUID - Get GUID for channel :id=tcpip-getguid

Get the GUID for this channel. The GUID is received on the form

    0:1:2:3:4:5:6:7:8:9:10:11:12:13:14:15<CR><LF>
    +OK<CR><LF>

### Argument
No argument.

### Response
  GUID<CR><LF>
  +OK - Success.<CR><LF>    

----
---- 

## VERS/VERSION - Get interface version :id=tcpip-version

Get the current version for the implemented tcp/ip link interface. The returned format is

    major-version,minor-version,sub-minor-version,build-version

**Note:** *build-version* added in version 13.0.0.14

### Argument
No argument.

### Response
  major-version,minor-version,sub-minor-version,build-version<CR><LF>
  +OK - Success.<CR><LF>


----
---- 

## SFLT/SETFILTER - Set incoming event filter :id=tcpip-setfilter

Set the incoming filter. The format is

    filter-priority, filter-class, filter-type, filter-GUID

**Example:**

    1,0x0000,0x0006,ff:ff:ff:ff:ff:ff:ff:01:00:00:00:00:00:00:00:00

Note: The GUID values always is given as hexadecimal values without a preceding “0x”.
Note: If you want to filter on nickname-ID you should filter on GUID LSB byte.

For a device with more than one filter the filter can be specified as an added numeric parameter of the above list. So

    1,0x0000,0x0006,ff:ff:ff:ff:ff:ff:ff:01:00:00:00:00:00:00:00:00,8

will set filter eight and so on.

### Argument
Filter on string form  
  filter-priority, filter-class, filter-type, filter-GUID

The filter GUID can be set on one of the standard forms for GUIDs  if surronded with {guid...}. The format for the standard forms is explained [here](https://grodansparadis.github.io/vscp-doc-spec/#/./vscp_globally_unique_identifiers).  

### Response
  +OK - Success.<CR><LF>

----
---- 

## SMSK/SETMASK - Set incoming event mask :id=tcpip-setmask

Set the incoming mask. The format is

    mask-priority, mask-class, mask-type, mask-GUID

**Example:**

    1,0x0000,0x0006,ff:ff:ff:ff:ff:ff:ff:01:00:00:00:00:00:00:00:00

Note: that the GUID values always is given as hexadecimal values without a preceding “0x”.
Note: If you want to mask on nickname-ID you should mask on GUID LSB byte.


For a device with more than one filter the mask can be specified as an added numeric parameter of the above list. So

    1,0x0000,0x0006,ff:ff:ff:ff:ff:ff:ff:01:00:00:00:00:00:00:00:00,8

will set mask eight and so on.

### Argument
Mask on string form  
  mask-priority, mask-class, mask-type, mask-GUID

The mask GUID can be set on one of the standard forms for GUIDs if surronded with {guid...}. The format for the standard forms is explained [here](https://grodansparadis.github.io/vscp-doc-spec/#/./vscp_globally_unique_identifiers).  

### Response
  +OK - Success.<CR><LF>

----
---- 

## WCYD / WHATCANYOUDO - Ask the capabilities of this server :id=tcpip-whatcanyoudo

This command reports server capabilities of this server.

The capabilities are described in a 64-bit array (8 bytes). The capabilities is reported on the form

    00-00-00-00-00-00-00-00
    +OK

where each pair of hex digits is a byte in the 64-bit capabilities structure. MSB is the first (left most) byte, follows by 64-bit value (1234567890ABCDEF). The 64-bit value at the end is optional but recommended.

The VSCP server 64-bit capability code is described in the specification document for [CLASS2.PROTOCOL, Type=20, High end server/service capabilities](http://docs.vscp.org/spec/latest/#/./class2.protocol?id=type20-0x14-high-end-serverservice-capabilities). It gives information about the capabilities of a VSCP server.

**note**

This response was changed in version 14.0.0 from

    +OK - 00-00-00-00-00-00-00-00

### Argument
No argument.

### Response
  capabilities in 8 bytes hex format<CR><LF>
  +OK - Success.<CR><LF>

----
---- 

## INTERFACE :id=tcpip-interface

List the interfaces on the device (if any).

Also low end devices that implement the vscp tcp/ip link protocol should implement this command. Typical for a devicve of this type is to have only one interface the device itself. Such a device list the full GUID of the device as the device as interface.



### list :id=tcpip-interface-list (deprecated)

List interfaces.

#### Argument
list and close can be given as argumenst but both are deprecated and should be ignored if given. The command should be used without arguments.


#### Response

The command will respond with

    'count' rows<CR><LF>
    interface-id1, type, interface-GUID1, interface_realname1<CR><LF>
    interface_id2, type, interface_GUID2, interface_realname2<CR><LF>
    ...
    interface_idn, type, interface_GUIDn, interface_realnamen<CR><LF>
    +OK - Success.<CR><LF>

type is

 | Type | Description |
 | :----: | ----------- |
 | 0    | Unknown (should not see this). |
 | 1    | Internal device/daemon client  |
 | 2    | Level I driver                 |
 | 3    | Level II driver                |
 | 4    | tcp/ip interface client        |
 | 5    | UDP interface client           |
 | 6    | Webserver interface client     |
 | 7    | Websocket interface client     |
 | 8    | REST interface client          |

----
---- 


----
---- 

### binary :id=tcpip-binary

If the device support binary mode this command can be used to switch to binary mode. In binary mode all commands and responses are sent as binary data. The format for the commands and responses is described in the document [VSCP over binary](./vscp_over_binary.md).

It is possible to switch back and forth between binary and text mode. 
The response to the binary command is

    +OK - Binary mode enabled<CR><LF>

or

    -OK - Binary mode not supported<CR><LF>

The binary protcol (VSCP_-GBD) is described[here](./vscp_over_binary.md)

### Argument
No argument.

### Response
  +OK - Success.<CR><LF>

----
----  




[filename](./bottom_copyright.md ':include')
 

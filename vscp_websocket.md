# VSCP websockets

# Interfaces

The [vscpl2drv-websocketdrv](https://github.com/grodansparadis/vscpl2drv-websocksrv) exports a  websocket interface. Embedded VSCP nodes and other software may also export this interface. The websocket interface makes it possible to have web widgets that are self contained and entirely written in JavaScript which can send and receive VSCP events. This means that you can create a simple web page, place your widgets on it and with or without a stand alone web server have a lightweight user interface. As phone, tablets and other devices generally also support HTML5. That is you have a general way for user interface creation. If you prefer apps. 

The websocket server can be reached on port 8884(default) and will use TLS/SSL if the web server is configured to use it. 

One important design goal when this interface was designed was to create an interface that also could be implemented on low end devices which needs a user interface. With just a few commands and some simple rules we have managed to do that. This means that we can expect user interfaces interacting with both small devices and larger software units.

There are two websocket protocol versions available of the websocket interface.

 - **ws1** which is a string based protocol.
 - **ws2** which is a JSON based protocol that is easier to use from JavaScript and other modern programming languages.

If you want to test the websocket functionality you can find some test code in the [vscpl2drv-websocksrv](https://github.com/grodansparadis/vscpl2drv-websocksrv) repository for html, node.js, javascript, python and C. You can find direct links to the code at the end of each of the protocol version sections of this document or go to [ws1](#ws1-examples) and [ws2](#ws2-examples).

## ws1 - String based websocket interface :id=ws1-description

### VSCP websocket server security :id=websocket-security

The websocket interface is protected by a user/password pair. The username/password is sent encrypted over the connection using AES-128 encryption leveraging a shared secret key (vscpkey) configured in the driver settings file.

I addition to the username/password which also groups users in security levels it is possible to have table where the hosts allowed to connect to the system is stored.

In addition to this TLS/SSL can be enabled on the interface.

Also a privilege based system is used to protect critical functionality. A user need a specific privilege to send an event for example and can be set up to be allowed just to send a limited set of events. Also a filter on incoming events is possible to set up to limit what a user can receive.

See the documentation for the [vscpl2drv-websocketdrv driver](https://github.com/grodansparadis/vscpl2drv-websocksrv)  for more information on how to set up users and privileges.



### VSCP Websocket Protocol Description :id=websocket-protocol-description

#### Accessing the websocket interface :id=ws1-access
```
You reach the ws1 interface by default at

```url
http[s]://server:port/ws1
```

where

 - *server* is the ip address or dns name of the server.
 - *port* is the port number configured for the websocket server (default is 8884).
 - *ws1* tells the server that you want to use the ws1 protocol. For ws2 use *ws2* instead.

The protocol is a text based protocol that is simple and effective. Only **AUTH** and **NOOP** commands are valid in a system where the client has not been authenticated.

#### Packet format :id=ws1-packet-format

The message frame consist of a semicolon separated text format that either is a command, a reply or an event. For  commands the first character is a capital 'C', for replies its either a '+' or a '-' and for events its an 'E'.

##### Format for commands :id=ws1-format-commands

```
'C' ; command ; optional data that may be separated by additional semicolons.
```

Positive reply 

```csv
'+' ; 'command'
``` 

Negative reply

```
'-' ; 'command' ; Error code ; Error in real text
```



**Example:**

```
'+' ; 'NOOP' 
``` 

telling that the NOOP command was successful.

```
'-' ; 'AUTH' ; 8 ; 'Not authorized'
```

telling that the AUTH command failed with error code 8 and the reason "Not authorized".


####  events :id=ws1-events

Both sent and received events have the same format.

```
'E' ; head , vscp_class , vscp_type ,obid, datetime, timestamp, GUID, data
```
where data is a comma separated list of data bytes in hexadecimal format.

When sending an event one can get a positive or negative reply.
    
Positive reply 

```
'+';'EVENT' 
```

Negative reply 

```
'-';'EVENT'; error-code; realtext-error
```

** Example:**
```
E;0,30,5,0,2000-01-01T12:33:14,0,FF:FF:FF:FF:FF:FF:FF:FE:00:26:55:CA:00:06:00:00,0x01,0x01
```

 | Code | Description | 
 | :----: | ----------- | 
 | C    | Command. Parameter is command and optional parameter(s). | 
 | +    | Positive Reply. If send in response to a command the command is also  returned on the form '+;command' | 
 | -    | Negative reply. Payload is error code followed by error message in English. '-;2;Syntax Error' | 
 | E    | Event. Payload is VSCP event. | 

### Commands :id=ws1-commands-overview

 | Command | Privilege | Description    | 
 | ------- | :---------: | -----------  | 
 | [NOOP](#ws1-noop)               | 0 | No operation   | 
 | [VERSION](#ws1-version)         | 0 | get protocol version   | 
 | [COPYRIGHT](#ws1-copyright)     | 0 | get interface copyright   | 
 | [AUTH](#ws1-auth)               | 0 | Authentication | 
 | [OPEN](#ws1-open)               | 0 | Open channel   | 
 | [CLOSE](#ws1-close)             | 0 | Close channel  | 
 | [SETFILTER](#ws1-sf)            | 6 | Set filter     | 
 | [CLRQUEUE](#ws1-clr)            | 1 | Clear input queue | 
 | [Send event](#ws1-send-event)   | 6 | Send event | 


You may be missing a __receive event__ above but received events are automatically delivered asynchronously to you after a channel has been opened. Very convenient when you want to keep a graphical element or similar updated.


#### NOOP:id=ws1-noop

No operation. Will always give a positive response.

```
C;NOOP
```

#### CHALLENGE:id=ws1-challenge

```
C;CHALLENGE
```

Send this command to initiate the authentication. This is process is normally started automatically on a connect.

####  AUTH:id=ws1-auth

This command is used by a client to authenticate itself. When connecting to a ws1 websocket ws interface it  will send something like

```
"+;AUTH0;55BCA4DC7C1FD9C3E6967F37C8747698" 
```

as a security challenge to the client (Also sent after a **CHALLENGE** command has been sent to a host by a client.). The _"55BCA4DC7C1FD9C3E6967F37C8747698"_ is a session id or sid that is different for every connection and which should be used as a 128 bit iv for the encrypted username/password.

The client now should send an authentication message on the form

```
"C;AUTH;sid;crypto"  
```

for example

```
C;AUTH;55BCA4DC7C1FD9C3E6967F37C8747698;42273E9F3440DABA5B0CC05242F742B2
```

where the sid is used as a 128-bit random iv for AES-128 encryption over

```
"username:password"
```

leveraging a shared 128-bit secret key (vscpkey) configured in the driver settings file. Following successful credential validation, the server will respond with

```
"+;AUTH1;userid;name;password;fullname;filtermask;rights;remotes;events;note"
```

and if invalid the server will respond with

```
"-;8,Not authorized"
```

When this happens a new sid is generated by the server and a client that want to return to login need to use the `CHALLENGE` command to get the new sid before trying to authenticate again.

Note that in addition to the credentials the client IP address may need to be valid for this user as it is possible to configure allowed IP addresses for each user in the configuration.

**Note:** its is not allowed to have a username with a semicolon in the name.

The standard vscp password hash is calculated over `username:password`. 

 - *userid* is the unique user id for this user.
 - *name* is the user name.
 - *password* is the hashed password for the user shown as stars.
 - *fullname* is the full name of the user.
 - *filtermask* is the filter/mask for this user shown as eight bytes separated with semicolon. This is the filter/mask that will be applied to incoming events for this user.
 - *rights* is a numerical value representing the rights for this user. 
 - *remotes* All allowed remotes as a comma separated string. An empty list means all remote hosts can connect.
 - *events* Get all allowed events as a comma separated string. An empty list means all events are allowed.
 - *note*  is a text note about the user and it is base64 coded to allow special characters.

#### OPEN :id=ws1-open

Start receiving events. Collected events in queue will be sent. Positive/negative response is returned.

**Example:** 

```
“C;OPEN” 
```

positive response is 

```
“+;OPEN”
```

####  CLOSE:id=ws1-close

Stop receiving events. Events are still collected in the receive queue on the server side and will be delivered when the connection is opened again. Positive/negative response is returned.

**Example:**

```
“C;CLOSE” 
```

positive response is 

```
“+;CLOSE”
```

####  CLRQUEUE / CLRQ  :id=ws1-clrq

Clear events in the servers input queue. Positive/negative response is returned.

**Example:**

```
“C;CLRQ” 
```

positive response is 

```
“+;CLRQ”
```

#### SETFILTER / SF :id=ws1-sf

Set filter/mask for incoming data. Positive/negative response is returned.

**Example:** 

```
“C;SF;filter-priority, filter-class, 
    filter-type, filter-GUID;mask-priority, 
    mask-class, mask-type, mask-GUID” 
```       

positive response is 

```
“+;SF”
```

Note that there is a semicolon between filter and mask information and commas between parts of each filter and mask.


#### Send event:id=ws1-send-event

The same string format is used to send events as receiving events.

 | 'E';head,vscp_class,vscp_type,obid,datetime,timestamp,GUID,data |
 | :--------------------------------------------------------------- |

and

 | +;EVENT |
 | :------- |

is received if it got sent and

 | -;EVENT;error-code;realtext-error | 
 | :--------------------------------- | 

is returned if there was a problem sending the event.

#### Version:id=ws1-version

The __VERSION__ command can be used to get the version of the protocol the server supports. The command is issued as

```
C;VERSION
```

And the server will respond with

```+;VERSION;major.minor.release.build
``` 

For example

```
+;VERSION;1.0.0.0
```

**Note** that this is the highest supported protocol version not the version of the firmware/software/driver.

#### Copyright:id=ws1-copyright

The __COPYRIGHT__ command can be used to get copyright information. The command is issued as

```C;COPYRIGHT
```
And the server will respond with something like

```
+;COPYRIGHT;Copyright (C) 1702 a Company 
```

This is the copyright information for the firmware/software/driver not the protocol.


### Errors:id=ws1-error-codes

This table list the errors that currently is defined

 | Error code | Error message | 
 | :----------: | ------------- | 
 | 0 | No error | 
 | 1 | Syntax error. | 
 | 2 | Unknown command. | 
 | 3 | Transmit buffer full. | 
 | 4 | Problem allocating memory.| 
 | 5 | Not authorized. | 
 | 6 | Not authorized to send events. | 
 | 7 | Not allowed to do that. |
 | 8 | Parse error, invalid format. |
 | 9 | Unknown type, only know "COMMAND" and "EVENT". |

### WS1 examples :id=ws1-examples

#### HTML5:id=ws1-examples-html5

A simple ws1 interface connection example is [here](https://github.com/grodansparadis/vscpl2drv-websocksrv/blob/main/test/test_ws1.html)

#### Python:id=ws1-examples-python
Code that issue some commands, send an event and waiting for incoming events is [here](https://github.com/grodansparadis/vscpl2drv-websocksrv/blob/main/test/test_ws1.py)

#### node.js
Code that issue some commands, send an event and waiting for incoming events is [here](https://github.com/grodansparadis/vscpl2drv-websocksrv/blob/main/test/test_ws1.js)

#### C:id=ws1-examples-c
Code that issue some commands, send an event and waiting for incoming events is [here](https://github.com/grodansparadis/vscpl2drv-websocksrv/blob/main/test/test_ws1.c)

## ws2 - JSON based websocket interface :id=ws2-description

The protocol is a JSON based protocol that is simple and effective. Only **AUTH** and **NOOP** commands are valid in a system where the client has not been authenticated.

### Packet format

Message traffic on the socket is on JSON format and there are a few different objects used.

### Command object :id=ws2-command-object

```json
{
    "type" : "C|CMD|COMMAND",
    "command" : "command",
    "args" : {
        arg-pairs or "null"
    },
    "error-code" : n,
    "error-str" : "error message"
}
```

This is the object a client send to execute a command. The _type_ can be set to either "C", "CMD" or "COMMAND".

_command_ should be set to the command to execute.

_args_ is either _null_ if the command has no arguments or a list of argument pairs if it have arguments.

Se AUTH command below for a command with arguments and the NOOP command for a command without arguments.

### Positive reply object :id=ws2-positive-reply-object


```json
{
    "type" : "+",
    "command" : "command",
    "args" : {
        ....
    }
}
```

A positive reply. _command_ tells which command the positive reply is associated with. The _args_ are optional arguments to the reply and is _null_ if there aree no arguments as in

```json
{
    "type" : "+",
    "command" : "command",
    "args" : null
}
```


### Negative reply object :id=ws2-negative-reply-object

```json
{
    "type" : "-",
    "command" : "command",
    "errcode" : n,
    "errstr" : "error message"
}
```

A negative reply. _command_ tells which command the negative reply is associated with. _error-code_ is set to a numerical error code describing the problem and _error-str_ is set to real text message that describe the error. [Error codes](#ws1-error-codes) are the same as for ws1 above.

### VSCP event object :id=ws2-event-object

This is either an event from a client to the device that exports the interface or an event from the device to the client. A client sending an event object will get a positive or negative reply object in return where command is set to "EVENT"

```json
{
    "type" : "EVENT",
    "event" :  {
       "vscpHead": 0,
       "vscpObId":  5,
       "vscpDateTime": "2020-01-27T20:47:55Z",
       "vscpTimeStamp": 3906069311,
       "vscpClass": 20,
       "vscpType": 3,
       "vscpGuid": "FF:FF:FF:FF:FF:FF:FF:F5:00:00:00:00:00:05:00:00",
       "vscpData": [15,14,13,12,11,10,9,8,7,6,5,4,3,2,0,0,1,35],
       "vscpNote": "An event note"
   }
}
```

Defaults are set for missing fields.

| Field | Description |
| :----- | :---------- |
| vscpHead | Set to zero |
| vscpObId | Set to zero |
| vscpDateTime | All fields set to zero. First interface the event passes will set it to "now" if all is zero. |
| vscpTimeStamp | Set to zero. First interface the event passes will set it to a valid value if zero. |
| vscpData | Zero data bytes. |


### Commands :id=ws2-command

### Commands :id=ws1-commands-overview

 | Command | Privilege | Description    | 
 | ------- | :---------: | -----------  | 
 | [NOOP](#ws2-noop)               | 0 | No operation   | 
 | [VERSION](#ws2-version)         | 0 | get protocol version   | 
 | [COPYRIGHT](#ws2-copyright)     | 0 | get interface copyright   | 
 | [AUTH](#ws2-auth)               | 0 | Authentication | 
 | [OPEN](#ws2-open)               | 0 | Open channel   | 
 | [CLOSE](#ws2-close)             | 0 | Close channel  | 
 | [SETFILTER](#ws2-sf)            | 6 | Set filter     | 
 | [CLRQUEUE](#ws1-clr)            | 1 | Clear input queue | 
 | [Send event](#ws1-send-event)   | 6 | Send event | 


You may be missing a __receive event__ above but received events are automatically delivered asynchronously to you after a channel has been opened. Very convenient when you want to keep a graphical element or similar updated.

#### AUTH :id=ws2-auth

The client send the _AUTH_ command to create a session with the server. This session is active until the client disconnect from the websocket and can be over tls if needed.

Two arguments must be supplied

##### iv :id=ws2-auth-sid

The sid argument is used as a 16 byte random iv for AES-128 encryption over

```"username:password"
```

When connecting to a ws2 websocket the websocket interface will send something like

```
{    
    "type" : "+", 
    "args" : [
    	"AUTH0",
        "5A475C082C80DCDF7F2DFBD976253B24"
    ]
}
```

as a security challenge to the client (Also sent after a **CHALLENGE** command has been sent to a host by a client.). The "5A475C082C80DCDF7F2DFBD976253B24" here is a session id or sid that is random and different for every connection.

##### crypto :id=ws2-auth-crypto

The sid argument is used as a 16 byte random iv for AES-128 encryption over

```
"username:password"
```

using  a common 128 bit **secret** key in hex format.  The [VSCP daemon](https://grodansparadis.github.io/vscp/#/) for example store this key in _/etc/vscp_ as a hex string but it can be stored in a secure place elsewhere or be embedded in the client software.

If the credentials is valid the server will respond with

```
{ 
    "type" : "+",  
    "command" : "AUTH",
    "args" : null  
}

```

The sid received form the websocket interface is just there for convenience for clients that have hard to to create a 128 bit random number with enough entropy. 

A client that want to create a new session should send an authentication message on the form

```json
{
    "type": "cmd",
    "command": "auth",
    "args": {
        "iv":"5A475C082C80DCDF7F2DFBD976253B24",
        "crypto":"69B1180D2F4809D39BE34E19C750107F"
    }
}
```
If the credentials are valid the response will be

```json
{ 
    "type" : "+",  
    "command" : "AUTH",  
}
```

and if invalid the server will respond with

```json
{ 
    "type" : "-",  
    "command" : "AUTH",  
    "error-code" : 8,
    "error-str" : "Not authorized"
}
```
The error code/message may be different depending on the cause of the negative reply. See [possible error codes](#ws1-error-codes) above.

Note that in addition to the credentials the client ip address must also be valid as of the configuration for the interface.

#### CHALLENGE :id=ws2-challenge

```json
{
  "type" : "CMD",
  "command" : "CHALLENGE"
  "args" : null
}
```

The challenge command can be sent to get the session id. The response is the same as the object received when connecting to the server

```json
{
    "type" : "+",
    "command": "CHALLENGE", 
    "args" : {
        "sid" : "3DED39018DBF0E8E4512A7CAC79FD487"
    }
}
```

#### OPEN :id=ws2-open

```json
{
  "type" : "CMD",
  "command" : "OPEN"
  "args" : null
}
```

Open the communication channel. It is now possible to send events and incoming events will be received instead of just being queued. 

#### CLOSE :id=ws2-close

```json
{
  "type" : "CMD",
  "command" : "CLOSE"
  "args" : null
}
```

Close the communication channel. It is no longer possible to send events after this has been done and incoming events will be queued.

#### SETFILTER / SF :id=ws2-setfilter

```json
{
  "type" : "CMD",
  "command" : "SETFILTER"
  "args" : {
    "mask_priority" : number,
    "mask_class" : number,
    "mask_type" : number,
    "mask_guid" : "00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00",
    "filter_priority" : number,
    "filter_class" : number,
    "filter_type" : number,
    "filter_guid" : "00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00"
  }
}
```

Set filter/mask for the communication channel so the channel just receive the events that is of interest to the client.

The reply is either a positive or a negative reply object.

#### CLRQUEUE / CLRQ :id=ws2-clrqueue

```json
{
  "type" : "CMD",
  "coommand" : "CLRQUEUE"
  "args" : null
}
```

Clear the incoming event queue for the client.

The reply is either a positive or a negative reply object.

#### VERSION / VER :id=ws2-version

```json
{
  "type" : "CMD",
  "coommand" : "VERSION"
  "args" : null
}
```

Get the version for the websocket protocol supported by the interface.

The reply is the following object

```json
{
  "type" : "+",
  "coommand" : "VERSION"
  "args" : {
      "version" : "major.minor.release-build"
  }
}
```


#### COPYRIGHT :id=ws2-copyright

```json
{
  "type" : "CMD",
  "command" : "COPYRIGHT"
  "args" : null
}
```

Get copyright information for the driver/firmware/software exporting the websocket interface.

The reply is the following object

```json
{
  "type" : "+",
  "command" : "COPYRIGHT"
  "args" : {
      "copyright" : "copyright text"
  }
}
```

### WS2 examples :id=ws2-examples

#### HTML5:id=ws2-examples-html5

A simple ws2 interface connection example is [here](https://github.com/grodansparadis/vscpl2drv-websocksrv/blob/main/test/test_ws2.html)

#### Python:id=ws2-examples-python
Code that issue some commands, send an event and waiting for incoming events is [here](https://github.com/grodansparadis/vscpl2drv-websocksrv/blob/main/test/test_ws2.py)

#### node.js:id=ws2-examples-nodejs
Code that issue some commands, send an event and waiting for incoming events is [here](https://github.com/grodansparadis/vscpl2drv-websocksrv/blob/main/test/test_ws2.js)

#### C:id=ws2-examples-c
Code that issue some commands, send an event and waiting for incoming events is [here](https://github.com/grodansparadis/vscp/blob/master/tests/websockets/test_ws2.c)

[filename](./bottom_copyright.md ':include')

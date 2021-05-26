# Appendix A - The user configuration file

The user database is not really part of the VSCP specification. But as it is used by several components in the VSCP framework it is specified here instead of individually in each component description. This to keep the documentation consistent.

The code of the functionality of the user database is defined in the two files [userlist.h](https://github.com/grodansparadis/vscp/blob/development/src/vscp/common/userlist.h) and [userlist.cpp](https://github.com/grodansparadis/vscp/blob/development/src/vscp/common/userlist.cpp). 

The user configuration file contains access information for users of the different interfaces in a VSCP system, tcp/ip, webserver, the ws1 and ws2 web-interfaces, the REST interface, etc.

This file have the same format for and is shared by several VSCP drivers and other functionality

The file is usually stored in the _/etc/vscp/_ folder of a Linux machine.

The file have the following format

 ```json
 {
	"users" : [
		{
      "user" : "admin",
      "fullname" : "Full name",
      "note" : "note about user-item",
      "credentials"  : "fastpbkdf2 over 'user:password' using 256 bit system key (stored: item:iv)",
      "filter" : "outgoing filter",
      "rights" : "comma separated list of rights",
      "remotes" : "comma separated list of hosts First char: +=allow -deny",
      "events" : "comma separated list of events "TX|RX|BOTH;vscp-class;vscp.type;priority"
		}
	]
}
```

Any number of users can be specified

##### user
The login user name.

##### fullname
The complete name of the user.

##### note
Optional note about the user.

##### credentials
credentials = encrypted_pw:iv where the encrypted_pw
is calculated over fastpbkdf2_hmac_sha256(user:password)

##### filter
Outgoing filter for this user on the form _head;class,type;guid_ This filter is applied before an event is sent out to te user. Default is for the user to receive all events.

##### rights
This is a comma separated list of rights for this user. This set what service the user is allowed to use. For the vscpl2drv-websrv driver possible values are

 - "admin" - User has _admin-rights_
   - Allowed to do everything.
 - "user" - This is a standard user.
   - Can use tcp/ip interface.
   - Can use websockets (ws1/ws2) interface.
   - Can use web interface.
   - Can use rest interface.
   - Can use UDP interface.
   - Can use Multicast interface.
   - Can send events.
   - Can receive events.
   - Can send level I control events.
   - Can send level II control events. 
 - "web" - This user can user the web interface.
   - Can send events.
   - Can receive events.
   - Can send level I control events.
   - Can send level II control events. 
 - "rest" - This user can use the REST interface. 
   - Can send events.
   - Can receive events.
   - Can send level I control events.
   - Can send level II control events.  
 - "tcp" - This user can use the tcp/ip interface.
   - Can send events.
   - Can receive events.
   - Can send level I control events.
   - Can send level II control events.  
 - "websockets" - This user can use the websockets (ws1/ws2) interfaces.
    - Can send events.
   - Can receive events.
   - Can send level I control events.
   - Can send level II control events. 
 - "mqtt" - This user can use MQTT.
   - Can send events.
   - Can receive events.
   - Can send level I control events.
   - Can send level II control events.  
 - "udp" - This user can use the UDP interface.
   - Can send events.
   - Can receive events.
   - Can send level I control events.
   - Can send level II control events.  
 - "multicast" - This user can use the multicast interface.
   - Can send events.
   - Can receive events.
   - Can send level I control events.
   - Can send level II control events. 
 - "driver" - This user is a driver.
   - Can send events.
   - Can receive events.
   - Can send level I control events.
   - Can send level II control events. 
 - "send-events" - This use can send events.
 - "receive-events" - This user can receive events.
 - "l1ctrl-events" - This user can send VSCP level I class = 0 control events.
 - "lsctrl-events" - This user can send VSCP level II class = 1024 control events.
 - "hlo-events" - This user can send HLO (class=xxx) events.
 - "set-filter" - This user can set the filter for the interface it is connected to.
 - "set-guid" - This user can set the interface GUID for the interface it is connected to.
 - "shutdown" - This user is allowed to issue the _shutdown_ command of the machine it is connected to.
 - "restart" - This user is allowed to issue the _restart_ command of the machine it is connected to.
 - "interface" - This user is allowed to issue the _interface_ command of the machine it is connected to.
 - "test"
 
 Instead of a tokens a 64-bit decimal value can be set or even a comma separated list of 64-bit values which will be OR'ed together.

##### remotes
This is a comma separated string of remote ip-addresses that this user is allowed to connect from. If the first character is a _'+'_ the user is allowed to connect from that ip-address. If the first character is a _'-'_ character the user is not allowed to connect from that ip-address. The ip-address can either be a ipv4 or a ipv6 address.

Instead of a comma separated string the information can be given as a json list

```json
"remotes" :[
    row1,
    row2,
    row3
]
```

##### events
This is a list of events the user is allowed to send and/or receive. If empty all events can be sent and received by the users. The parameter is a comma separated list of items of the form

```
TX|RX|BOTH;vscp-class;vscp-type
```

 - **TX** - Allowed to send events of the specified type.
 - **RX** - Allowed to receive event of the specified type.
 - **BOTH** - Allowed to send and receive events of the specified type.
 - **vscp-class** A VSCP class (number 0-65535). -1 to allow all VSCP classes. 
 - **vscp-type** A VSCP type (number 0-65535). -1 to allow all VSCP type of a class.

Events can be also be specified as a JSON list on the form

```json
"events" :[
    row1,
    row2,
    row3
]
```
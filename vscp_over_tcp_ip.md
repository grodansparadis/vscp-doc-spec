# VSCP over TCP/IP

**Default Port:** 9598

VSCP level II is designed for TCP/IP and other high-end network transport mechanisms which are able to handle a lot more data (487 bytes instead of 8) then Level I devices. With the additional bandwidth that normally is available it is ideal to always have a full addresses in packets for this type of media. That is the full GUID (node address) is available in the frame.

A telnet type client server protocol is used, see [sec:VSCP-TCP/IP-Protocol] for a full description of the available commands. The [VSCP daemon](http://www.vscp.org/docs/vscpd/doku.php) has this command set implemented in it's own tcp/ip interface, but a client only needs to implement a subset called the **VSCP tcp/ip link protocol**. 

The [TCP/IP driver](http://www.vscp.org/docs/vscpd/doku.php?id=level2_driver_tcpip_link) of the VSCP daemon can be used to connect one VSCP daemon to other remote VSCP daemons or to lighter clients that export the VSCP tcp/ip link protocol. A client and the VSCP daemon can have a connection that is persistent or the VSCP daemon can connect to the client on regular intervals to fetch and send events. It is of course also possible for a client to connect to a VSCP daemon through it's TCP/IP interface instead.

The [VSCP helper library c interface](http://www.vscp.org/docs/vscphelper/doku.php?id=start) can be used if you want to write code that connects to a remote client using the VSCP TCP/IP link protocol. This is includes connections to the VSCP daemon.

A RFC 854 (telnet) based protocol is supported over TCP/IP. The protocol is implemented in an extended form in the [VSCP Daemon](http://www.vscp.org/docs/vscpd/doku.php?id=start) and is described [here](http://www.vscp.org/docs/vscpd/doku.php?id=vscp_daemon_tcp_ip_control_interface). The protocol is very easy to implement in low resource clients and a driver is available that make connecting to a client a turn-key experience. Source for this implementation on Arduino and others is available in the [firmware repository](https///github.com/grodansparadis/vscp_firmware). For high security SSL is available as an option together with other security measures.

The VSCP Link Interface implemented in a node is described [here](http://www.vscp.org/docs/vscpfirmware/doku.php?id=start_l2#vcsp_link_interface_based_nodes_tcp_ip).


\\ 
----
{{  ::copyright.png?400  |}}

`<HTML>``<p style="color:red;text-align:center;">``<a href="http://www.paradiseofthefrog.com">`Paradise of the Frog AB`</a>``</p>``</HTML>`

 

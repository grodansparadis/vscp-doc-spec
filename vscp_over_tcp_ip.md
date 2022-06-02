# Introduction


VSCP level II is designed for TCP/IP and other high-end network transport mechanisms which are able to handle a lot more data (487 bytes instead of 8) then Level I devices. With the additional bandwidth that normally is available it is ideal to always have a full addresses in packets for this type of media. That is the full GUID (node address) is available in the frame.

A RFC-854 (telnet) based client server protocol is used, see [VSCP-TCP/IP-Protocol](./vscp_tcpiplink.md) for a full description of the available commands. A client only needs to implement a subset called the **VSCP tcp/ip link protocol** as described [here](./vscp_tcpiplink.md). The protocol is very easy to implement in low resource clients and a driver is available that make connecting to a client a turn-key experience. Source for this implementation on Arduino and others is available in the [firmware repository](https://github.com/grodansparadis/vscp_firmware). For high security SSL is available as an option together with other security measures.

The [VSCP daemon](https://grodansparadis.github.io/vscp/#/) has this command set implemented in it's own tcp/ip interface.

The [TCP/IP driver](https://github.com/grodansparadis/vscpl2drv-tcpiplink) of the VSCP daemon can be used to connect one VSCP daemon to other remote VSCP daemons or to lighter clients that export the VSCP tcp/ip link protocol. A client and the VSCP daemon can have a connection that is persistent or the VSCP daemon can connect to the client on regular intervals to fetch and send events. It is of course also possible for a client to connect to a VSCP daemon through it's TCP/IP interface instead.

The [VSCP helper library c interface](https://grodansparadis.github.io/vscp-helper-lib/#/) can be used if you want to write code that connects to a remote client using the VSCP TCP/IP link protocol. This is includes connections to the VSCP daemon.

The VSCP Link Interface implemented in a device is described [here](./vscp_tcpiplink.md).

**Default Port:** 9598

[filename](./bottom_copyright.md ':include')

 

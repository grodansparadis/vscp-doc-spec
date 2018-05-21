# Transport protocols (currently) used by VSCP

VSCP can use most physical Level/Lower level protocols to trasnport events. When the VSCP protocol/framework was designed its usefulness on the CAN bus was the main objective. The identifier length and many other things on Level I are therefore very “CAN-ish” in its design and behavior. CAN is however no prerequisite. The protocol works equally well over RS-232, RF-Links, Ethernet etc. CAN can be seen as the least common denominator.

Now VSCP has two protocol levels. Level I and level II.

Level I is effective over bandwidth limited links but don't have the full GUID of the nodes in the frames and some sort of lower level addressing system must be used. 

Level II use the full GUID and can handle more data. This level is useful for nodes which have more resources.



## Transport protocols currently used by VSCP

Below the implemented transports is described.


*  [VSCP over TCP/IP](VSCP over TCP/IP)

*  [VSCP over Ethernet (raw Ethernet)](VSCP over Ethernet (raw Ethernet))

*  [VSCP over UDP](VSCP over UDP)

*  [VSCP over TCP/IP Multicast](VSCP over TCP/IP Multicast)

*  [VSCP websocket](VSCP websocket)

*  [VSCP REST](VSCP REST)

*  [VSCP over CAN (CAN4VSCP)](VSCP over CAN (CAN4VSCP))

*  [VSCP over a serial channel (RS-232)](VSCP over a serial channel (RS-232))

*  [VSCP Level I over RS-485/RS-422](VSCP Level I over RS-485/RS-422)

*  [VSCP over IEEE 802.15.4](VSCP over IEEE 802.15.4)

*  [VSCP Droplet model](VSCP Droplet model)

*  [VSCP BumbleBeez Protocol](VSCP BumbleBeez Protocol)

*  [VSCP over MQTT](VSCP over MQTT)

*  [VSCP Text](VSCP Text)


{% include "./bottom_copyright.md" %}

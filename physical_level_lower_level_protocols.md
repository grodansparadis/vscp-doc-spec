# Transport protocols (currently) used by VSCP

VSCP can use most physical Level/Lower level protocols to trasnport events. When the VSCP protocol/framework was designed its usefulness on the CAN bus was the main objective. The identifier length and many other things on Level I are therefore very “CAN-ish” in its design and behavior. CAN is however no prerequisite. The protocol works equally well over RS-232, RF-Links, Ethernet etc. CAN can be seen as the least common denominator.

Now VSCP has two protocol levels. Level I and level II.

Level I is effective over bandwidth limited links but don't have the full GUID of the nodes in the frames and some sort of lower level addressing system must be used. 

Level II use the full GUID and can handle more data. This level is useful for nodes which have more resources.



## Transport protocols currently used by VSCP

Below the implemented transports is described.


*  [VSCP over TCP/IP](./vscp_over_tcp_ip.md)
*  [VSCP over Ethernet (raw Ethernet)](./vscp_over_ethernet_raw_ethernet.md)
*  [VSCP over UDP](./vscp_over_udp.md)
*  [VSCP over TCP/IP Multicast](./vscp_over_tcp_ip_multicast.md)
*  [VSCP websocket](./vscp_websocket.md)
*  [VSCP REST](./vscp_rest.md)
*  [VSCP over CAN (CAN4VSCP)](./vscp_over_can_can4vscp.md)
*  [VSCP over a serial channel (RS-232)](./vscp_over_a_serial_channel_rs-232.md)
*  [VSCP Level I over RS-485/RS-422](./vscp_level_i_over_rs-485_rs-422.md)
*  [VSCP over Bluetooth mesh](./vscp_over_bt_mesh.md)
*  [VSCP over IEEE 802.15.4](./vscp_over_ieee_802.15.4.md)
*  [VSCP Droplet model](./vscp_droplet_model.md)
*  [VSCP BumbleBeez Protocol](./vscp_bumblebeez_protocol.md)
*  [VSCP over MQTT](./vscp_over_mqtt.md)
*  [VSCP Text](./vscp_text.md)


[filename](./bottom_copyright.md ':include')

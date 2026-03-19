# VSCP Multicast

For VSCP multicast the address

    224.0.23.158 VSCP

should be used.Please see the following:

[https://www.iana.org/assignments/multicast-addresses](https://www.iana.org/assignments/multicast-addresses) and [https://www.tldp.org/HOWTO/Multicast-HOWTO.html](https://www.tldp.org/HOWTO/Multicast-HOWTO.html) 

Currently the multicast interface is used for heart beats and announcements of available services and to set up multicast groups that share events. For this port **9598** is always used.

General multicast information can be found [here](https://www.juniper.net/techpubs/en_US/junos12.1x46/topics/concept/multicast-ip-overview.html).

## Comparison between broadcast and multicast

| Comparison | Broadcast | Multicast |
| ---------- | --------- | --------- |
| Principle | Packets are sent to all hosts connected to the network. | Packets are sent only to their intended recipients in the network. |
| Transmission | One-to-all | One-to-many |
| Management | No need for group management | Need group management |
| Network | May cause network bandwidth waste and congestion | Controllable network bandwidth | 
| Rate | Slow | Fast |

## Packet format

See [VSCP general binary protocol](https://grodansparadis.github.io/vscp-doc-spec/#/./vscp_over_binary) for the general binary protocol. The UDP protocol is a subset of the general binary protocol


## Announcement

Announcements are done on the default VSCP port 9598.

Announcements is an important part of the traffic on the multicast channel.  There are a few different types.


*  VSCP announcements. Announce the availability of a VSCP device  and tell its capabilities.
*  High end device announce. Announce the availability of the device and its capability. All Level II nodes should have this functionality. 
*  Heart beats: Heart beats come in the form of heartbeats from servers and from high end nodes. Both send them out each minute or so. Also heartbeats are available form devices connected to a server or through a high end node. 

## Events

It's up to the implementer to decide what events should be available on a multicast channel by setting the receive/transmit filters/masks for the channel. Several channels can be set up on different ports forming different subnets. Normally just a filtered number of events is transmitted. A typical example of such a segment is a group of nodes on Ethernet.

[filename](./bottom_copyright.md ':include')


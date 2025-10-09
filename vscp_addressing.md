# VSCP Adressing

VSCP does not (normally) use adressing. Instead it uses a concept of *zones* and *subzones* to different among (groups of) devices. This is a very flexible way to address devices and allows for a very large number of devices to be _"addressed"_ in a flexible way.

Most events in the VSCP protocol is designed to be one to many. This means that an event is sent to a group of devices that are interested in the event. This is a very powerful concept that allows for a very flexible and powerful system to be built.The originating node does not know who will receive the event. It just sends it out and the devices that are interested in the event will receive it and act on it.

**BUT...** (even if addressing is not used) there are two classes that use adressing. `CLASS1.PROTOCOL` and `CLASS2.PROTOCOL` and it's a good reason for that, they need it.

## CLASS1.PROTOCOL

VSCP identify a device or remote node by it's GUID. This is a 128-bit number that is globally unique for each device that is hard coded into the device. The GUID is used to identify a device and can also be used to route events to the correct device. But the problem with is that level I frames only allow for a maximum of eight bytes of data. This is not enough to hold a GUID. Instead level I uses nickname addressing to identify devices. The nickname is a number between 0 and 255 that is assigned to the device. The nickname is here used instead of the GUID to address a device on the bus. The nickname is discovered by the device itself or assigned to a device by a host when the device is first connected to the bus. The nickname is stored in non-volatile memory in the device.

It is important to remeber that the GUID is still the real identity of the device. The nickname is just a shorter proxy address that is used to address the device on the bus. It is still hardly connected to the GUID.

For standard most level I cases only 253 devices can be connected to a VSCP bus at the lowest level. This is because the nickname 0 is reserved for a central host and 254 is used by a node that is in bootloder mode and is without a nickname and lastly 255 is used for node that does not have a nickname yet.

In some cases the nickname uses 16-bits and allow for more nodes on the bus. In this case also nickname=0 is reserved fro a central host, 0xFFFE for a node that has not yet got a nickname assigned to it and which is in bootloader mode. And last 0xFFFF is used for a node that has not yet got a nickname assigned to it.

## CLASS2.PROTOCOL

Level II frames use a 128-bit address to identify a device on the bus. Just as for level I only the protocol class `CLASS2.PROTOCOL` uses addresses. All other classes use zones and subzones to identify (groups of) devices.

## CLASS2.LEVEL1.PROTOCOL

Classes in the range 512-1023 also use  a 128-bit address to identify where events should go. This is used on a host interface that has many channels. Channels are identified by a 16-bit address, a GUID, and this GUID i called an interface GUID. Every single event in the 512-1023 range is addressed to a specific interface. 

An interface GUID is constructed so that the four lowest bytes are zero. This is the GUID for the first interface. The second interface has the two lowest bytes set to 1 and so on. With the two bytes forming a 16-bit number.

We use 

```
FF:FF:FF:FF:FF:FF:FF:F3:XX:XX:XX:XX:YY:YY:ZZ:ZZ
```

which is reserved for VSCP interfaces.

| GUID | Description |
|------|-------------|
| FF:FF:FF:FF:FF:FF:FF:F3:C0:A8:01:7A:00:00:00:01 | Host: F3:C0:A8:01, Interface: 0, node with nickname=1 |
| FF:FF:FF:FF:FF:FF:FF:F3:C0:A8:01:7A:00:01:00:20 | Host: F3:C0:A8:01, Interface: 1, node with nickname=32 |
| FF:FF:FF:FF:FF:FF:FF:F3:C0:A8:01:7A:00:01:xx:xx | Host: F3:C0:A8:01, Interface: 1, node with nickname=XX:XX |


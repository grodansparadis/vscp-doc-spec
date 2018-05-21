# Introduction

This specification is a reference document. With +500000 characters written by someone that is not native in English it may be a pain to read for many. If you just want to use VSCP & Friends skip to section 2. Go back to the specification when you are in doubt about usage or just need a deeper understanding of whats going on. VSCP is designed to make complex systems simple to use and not necessarily easy to build such complex systems. We expect a greater technical knowledge and at least the ability to read from people that build and maintain such systems. 

Another resource for information is the VSCP wiki [http://www.vscp.org/wiki/doku.php](http://www.vscp.org/wiki/doku.php) it holds a lot of useful information and howto's. 


*  The VSCP Daemon is documented [here](http://www.vscp.org/docs/vscpd/doku.php).

*  The helper library is documented [here](http://www.vscp.org/docs/vscphelper/doku.php)

*  The VSCP Works is documented [here](http://www.vscp.org/docs/vscpworks/doku.php).

## Introduction

VSCP is an open source standard protocol for m2m, IoT and other remote control and measurement applications. It enables simple, low-cost devices to be networked together with high-end computers and/or to work as an autonomous system, whatever the communication media is.

There are a lot of technologies and protocols that claims to be the perfect solution for (home) automation and SOHO (Small Office/Home Office) control, IoT, M2M. More and more RF solutions are now available: Bluetooth, Zigbee, Z-wave, Wifi, etc. Other systems use a dedicated bus based on RS-485, CAN, LIN, LON, TCP/IP, etc. or can sometimes support different transport layers: CANopen, KNX (EIB), C-Bus, LonWorks, etc.

Most of them are proprietary, some are somehow “open”, meaning you can participate if you are part of the alliance and pay your yearly fees, or similar. There also is small companies that have their own proprietary and completely closed protocols.

VSCP was designed with the following goals in mind:


*  Free and Open. No usage, patent or other costs for its implementation and usage. 

*  Low cost. 

*  K.I.S.S. (Keep it simple stupid.) Simplicity usually rules. 

* Discovery and identification. Installed devices should be possible to discover and be identified in an uniform way.

*  Uniform device configuration. Devices should be able to be configured in a uniform way.

*  Autonomous/distributed device functionality.

*  Uniform way to update/maintain device firmware.

Some features: 


*  Free and open for commercial and other use. 

*  Have two levels. Level I and Level II where level I is designed with CAN as the least common denominator. Can be used for TCP, UDP, RF, Mains communication, etc etc. 

*  Has globally unique IDs for each node. 

*  Has a mechanism to automatically assign a unique ID to a newly installed node and inform other nodes and possible hosts that a new node is available and ready. 

*  Use “registers” as a uniform way to configure nodes. 

*  Can use a “decision matrix” to program nodes with dynamic functionality. 

*  Has a common specification language “MDF” that describe a module in a uniform way that can be used by set up software and such. 

*  Has software and drivers for Windows and Linux. More added all the time. 

The VSCP Protocol was initially used in CAN networks. CAN is very reliable and cheap today and allow us to manufacture low cost nodes that can work reliably, efficiently and can be trusted in their day-to-day use. But VSCP can be used equally well in other environments than CAN.

To meet both low cost and performance, VSCP is divided into 2 levels. Level 1 is intended for low-end nodes (i.e. based on tiny micro-controllers) while Level 2 is intended for higher level and faster transport layers such as TCP/IP. All nodes can talk together but level 2 nodes achieve better performance when talking together, while level 1 nodes that don't require much processing can be implemented with very cheap technologies.

Furthermore, VSCP:


*  uses standard components and cables. 

*  is easy to configure.

## Open? What does that mean?

This protocol is open and free in all aspects that are possible. We want you to contribute work back to the project if you do your own work based on our code but we also like to make as much of this work useful also in commercial projects. The tool we have chosen to do this is the MIT license, the GNU public version 2 license. For firmware code we release is released under the MIT license.

The **VSCP server** and **VSCP Works** is released under GPL2 due to it's use of the Mongoose libraries which is released under this license. Helper libs and most drivers and other help programs are released under the MIT license.

## License

Alternative licenses for VSCP & Friends may be arranged by contacting **Grodans Paradis AB/Paradise of the Frog** at [info@grodansparadis.com](info@grodansparadis.com), [http://www.grodansparadis.com]


## Where is the project located?

Current information about VSCP (Very Simple Control Protocol) can be found at:
[http://www.vscp.org](http://www.vscp.org)

There is a forum/mailing lists available [here](https///groups.google.com/forum/#!forum/vscp) where you an ask for help or discuss VSCP development.


## When was the project started?

Many of the thoughts behind this protocol come from work done by Ake Hedman as early as 1986 but the high node costs at the time made it impossible to do the things VSCP can do today. The official start date/time is **2000-08-28 14:07 CET** when the EDA project [http://sourceforge.net/projects/eda](http://sourceforge.net/projects/eda) was registered at Sourceforge. EDA, is an acronym for **Event-Decision-Action** and is still preserved in the decision matrix of VSCP. 

##  Why another protocol? 

VCSP is designed to be used where other solutions are to expensive to implement. This can typically be in code overhead where most other protocols use more resources (flash/ram) on a micro-controller than the actual “application” adding a lot of cost to the project. VSCP can work with a typical lowest cost dumb nodes like the Microchip MCP250xx series, to a 1K-2K flash micro controller module up to a full implementation with all features in about 5K flash. VSCP is both free and open. Everyone can join the project and help to add features and functionality to the protocol. There is free firmware and driver code available for most micro-controllers which uses many communication techniques. Everyone is free to use this code and there is not requirement to share any new code you develop, although most choose to, in order to improve the code base. 

##  Why is the VSCP protocol needed? 

Most people don't remember the world looked like for PC developers before Windows were introduced. This was a time when the developer needed to ship a big bunch of floppy disks with his/hers application. One big pile of floppies where for different printers, another set of disk was for different graphical cards and yet another for different pointing devices etc. It was not uncommon to have one floppy for the application and fifteen to twenty for drivers.

Windows changed this. The OS introduced abstraction for devices and from that point drivers was something the OS dealt with and the application developer could concentrate on creating the application. This was the big reason behind the boom in software that made Microsoft and others successful.

VSCP does this for automation tasks. Look around and see how it looks today. We have applications that work for Zigbee, X10, KNX, LonWorks etc. Some try to combine them into one application but still it's a different thing to turn on a lamp using Zigbee, X10, KNX or whatever. In the best case the same user interface component can be used but still there is a need to differentiate between the technologies use also at that level and most important the knowledge about the technology is needed on the top level.

VSCP try to hide this. Drivers implement the interface to the technology and they all talk to the system using the VSCP protocol and understand VSCP protocol events. Compare this with printing under a modern OS. It's no difference today if you print to a Laser printer or a ink jet printer. Also it all works the same if the printer use protocol x, y or z. You are also still able to configure and print with the printers. This is where the abstraction comes into place.

To switch on a lamp (or a group of lamps) in VSCP we send a

    CLASS1.CONTROL, Type=5, TurnOn event.

A driver translate this event to its own format and does its specific work using its own protocol and return a

    CLASS1.INFORMATION, Type=3, ON event 

When its job is done as a confirmation for the rest of the system.

An application does not need to bother how the actual control is done. On the application level it's enough to implement a button and some visual indication to indicate the outcome of the operation.

A system to present some measurement data is another example. Think of a system with temperature sensors. They all use different technologies but a driver for each translate the temperature readings to a common

    CLASS1.MEASUREMENT, Type=6, Temperature measurement events. 

This event is region independent and format independent. It is easy to create a driver that log this value into a database. Also here in a common format. You can now build a web applet that shows the temperature for every possible temperature sensor. As the format is common and easy to collect in a database in a common way you can also write a statistical application that show temperature data and work for any temperature sensor.

The above is the most important reason for VSCP but there is more.

Each VSCP device have a common way it can be configured by. This means one high level software can be used for all devices. Note that a device necessarily does not need to implement this. Instead a driver can do that and make it look like a VSCP device. Typically is a 1-wire sensor where the driver can implement the parameters for it and export it in a common way.

All VSCP devices are described in a common way. The device itself holds this information and therefore when a device is found all information about how it is configured and used is available. Again this information can be implemented in the driver.

VSCP defines a lot more functionality and can be used all the way out to the actual device. Still the most important part is the abstraction. 

## How does it work?

### Events

VSCP is an event based system. Nodes generate events and nodes react on events. Normally events are not addressed but instead are broadcast on the bus. Its up to the receiving end to decide if its interested in the event or not. All events have an originating address for the node they are sent from. This is a GUID consisting of 16 bytes but a shorter, typically, one byte nickname-ID is used on most system. It is always possible to deduce the full GUID from the nickname. Events are divided into groups. First there is Level I and Level II events. Level I events are limited to a maximum of eight bytes of data while Level II events can have up to 488 bytes of data. The low maximum data count for Level I comes from that CAN has been used as the least common denominator. This does not limit VSCP Level I to be used only over CAN. Both Level I and Level II events are divided into a class and a type. The class defines a group of events of a specific type. Typical examples are classes for measurements, information and control. As mentioned above events are not addressed. This is not entirely true as one class in each level (CLASS1.PROTOCOL and CLASS2.PROTOCOL) have events that are addressed. These classes define protocol functionality that all nodes have to implement. Typical examples found there are event types for boot loader, register access and status information. Most of the events can use a zone/sub-zone to identify the group of nodes it is relevant to.

### Registers

Each node has a specified number of byte wide registers defined. This is the second interface to the black box the node represents. The register space of a node is 256 bytes divided in two halves. The lower part (0x00-0x7F) is application specific. The upper part content is mandatory and specified by VSCP. This space hold, among many other things, the firmware and hardware version of the node. The GUID, user module id, alarm status and similar registers. In the top of the mandatory register space is a 32 byte string stored, the MDF, which contains an URL that points to a location where to find an XML file that describe this module its registers and its functionality. The lower part of the register space is used to define control and status registers and more complex structures. The area is mapped and 65535 pages can be used if needed allowing for very complex scenarios if needed.

### MDF - Module Description File

The MDF file describe the module at a high level. It provides information about the manufacturer of the module, the events that can be expected from it and the definition of its register content. The MDF looks at the module from a high level perspective and can see floating point values, bit arrays, option tables in register space and thus give application software a way to present registers in a much more user friendly way. There is two way to obtain the MDF after getting it from the module by reading the registers holding it . As VSCP is designed for low end nodes it is normally to much for such a node to have the MDF stored internally. In this case the string points to a web server from which the XML can be downloaded and processed. In a more capable module with more resources the MDF is stored internally in which case the read string has zero length and in this case the MDF data can be fetched from the module itself. The node constructor decide which method he/she wants to use. The MDF also point out where drivers for different environments and systems for the module and user manuals etc can be found.

### DM - Decision Matrix

All nodes can optionally implement a decision matrix. This matrix is used to define one or a group of events that should trigger a predefined functionality at the module. In VSCP this is called the Event-Decision-Action mechanism from the predecessor of the project which was called EDA. A typical examples can be to trigger a relay. The module got one action that set the relay and another action that reset it. Typically this could be implemented hard coded so that the relay would be set when an ON-event was received and has been reset when an OFF-event was received. With the use of the DM it is easy to use any event to trigger the action not just the ON/OFF events. Physically the DM is located in register space just as any other parameters of the module so register access functions are used to changed it.

### Measurements

A special class is used for measurements and events for all SI units and derived units is defined. The class will grow over time when new types are needed. This means that for example a temperature measurement is normally sent as a Kelvin temperature. Celsius and Fahrenheit is also possible in this case and similar alternatives is available for other types but the SI unit is always the default. How the measurement is presented in the frame is also well specified. Bit field, string, integer, normalized integer (decimal) and floating point values are possible. The normalized integer is especially well suited for a low end system to send decimal data. As the event and its content is well specified it is very easy to interpret the data on the receiving end where it should be processed, stored in a database, logged or displayed.

### Putting it all together

As VSCP is event based, one often need to think a bit differently when constructing a system. A typical example is a tank with a level sensor and a pump which together construct a self contained system. A traditional system system would have used a master to control the pump and the sensor. In VSCP we allow for this also but try to distribute as much of the intelligence as possible to the nodes themselves. So what we do is to tell the level sensor to send level information with a predefined interval. Several sensors can be added for redundancy. We tell the pump that it should start to fill up the tank when the tank reach a low level and stop at a high level. This might be dangerous as the sensor may stop working, the cable get cut or whatever. In this case the we also program the pump goes to its safe state == pump off and alarming this state to the rest of the system when it does not receive sensor measurements any more.. This “safe state“ is often possible to find for most control situations. As the transport mechanism is unknown to the application, timing must be very lose for VSCP. We cannot be certain when an event arrives or if it arrives. Many transport mechanisms, such as CAN and TCP/IP, makes delivery more certain while other solutions like UDP, RF and PLC can be problematic. It is therefore very important that a sent event always get a confirmation event back. For some nodes this might not be important. A temperature node or the level sensor node above just send there measurements and don't care if someone uses them or not. This thinking is central. The node that originate an event should – if possible - know as little as possible about how the event it sends out will be used. This make the system very flexible. 

### The "Friends"

A software package called VSCP & Friends is available to support VSCP users. This package can be downloaded and used for free and contain a lot of application and code. Everything is available both for Windows and Linux based systems.

First and possibly most important it contain the VSCP daemon. This is a server software that makes it possible to control several VSCP segments over the Internet. 

The server expose a secure Internet interface and makes it possible to add drivers for segments of nodes or special equipment. A driver can communicate with the server using the CANAL interface for a Level I driver and the TCP/IP interface for a Level II driver. 

CANAL stands for CAN Abstraction Layer and was initially developed as a software layer between application software and CAN equipment. For the VSCP it is not limited to interface CAN equipment but CAN drivers for most CAN adapters such as PEAK, IXXAT, PORT etc is included in the package as many CAN users use the system.

A lot of code is available that confirms to the CANAL interface. This same code can be used to communicate directly to a device that use the CANAL driver as can be used to talk to the daemon. This makes, among many other advantages, it easy to build simulated systems that use the same code base as the resulting system.

The daemon can do a lot more such as remotely replace/install drivers, remotely handle users and permissions, set up and handle an internal decision matrix to set up a self contained control system etc.

VSCP Works is a client application that is included in the package. This application can be used to send/receive VSCP events to/from every segment/device that export a CANAL interface and also talk to a remote VSCP daemon. VSCP Works can be used to investigate register space on any VSCP node and will also have support for remote firmware upgrade. 

Server and client application is released under the GPL license. Libraries and classes is released under a modified LGPL license that make sure they can be used in proprietary projects.

Maybe the most important aspect of the VSCP & Friends package is that it can be used as an abstraction for interfacing other technologies and protocols. One just need to build a driver that translate the systems functionality to/from VSCP events and then install this driver for the VSCP daemon and then remote control functionality, software interface etc is directly available. This way one application interface can be constructed to control several technologies using different protocols. One can compare this to the situation for printers before windows was announced. Each application needed to distribute a stack of disks with printer drivers. Windows ended this by introducing the printer API abstraction for printers. VSCP & Friends does the same for SECO (SEensor/COntrol) devices .

A web interface named OHAS is under development that will make it possible to build dynamic control interfaces with drag and drop technology. 

### Summary

VSCP makes it easy and very cost effective to build systems with distributed intelligence. The protocol is placed in the Public Domain so it is therefore free for anyone to use and modify to their own needs. VSCP can be used all the way from the application down to the device but it can also be used as an abstraction to other technologies so one application can be written that transparently use several different technologies..

More information and downloads is available at [http://www.vscp.org](http://www.vscp.org)

{% include "./bottom_copyright.md" %}



# The VSCP Specification

![VSCP logo](./images/logo_100.png)

**Specification reversion:** 1.10.18 - 2018-03-20 
[HISTORY](vscp_specification_history.md)

This document is the official VSCP (Very Simple Control Protocol) specification. VSCP is an IoT framework mainly built for resource limited devices.

Apart from going through this document You can read all about and download VSCP from [the VSCP site](https://www.vscp.org "The VSCP site"). 

**VSCP is free.** Free to use. Free to change. Free to do whatever you want to do with it. VSCP is not owned by anyone. VSCP will stay free and gratis forever.

Author 2000-2018 Åke Hedman, [Grodans Paradis AB](https://www.grodansparadis.com), [akhe@grodansparadis.com](akhe@grodansparadis.com)  

This document is licensed under [Creative Commons BY 4.0](https://creativecommons.org/licenses/by/4.0/) and can be freely copied, redistributed, remixed, transformed, built upon as long as you give credits to the author.

Many people has helped to create and evolve this protocol: *Behzad Ardakani, Marcus Rejås, Charles Tewiah, Mark Marooth, Gediminas Simanskis, Henk Hofstra, Stefan Langer, Kurt Herremans, Jiri Kubias, Frank Sautter, Dinesh Guleria, David Steeman, Andreas Merkle, Arpad Toth, Anders Forsgren, Stuart O'Reilly* are valued contributors. 

If you use VSCP please consider contributing resources or time to the project ([http://vscp.org/support.php](http://vscp.org/support.php)). 

# Abstract

Collected in a package described as **VSCP & friends** a complete solution framework for measurement and control, also popular known as m2m (machine to machine) and IoT (Internet of Things), is described in this paper. VSCP (Very Simple Control Protocol) defines the protocol and the framework, “Friends” is the many software tools, examples and api's the are freely available. The protocol was placed in the public domain in year 2000 when the project first was started and is therefore free to use and implement for everyone commercially or otherwise. VSCP solves the uniform discovery and uniform configurations problems for small devices. It also uses a very well specified event format and supports global unique identifiers for nodes making a node identifiable wherever it is installed in the world. It has a register model to give a flexible common interface to node configuration and a model for controlling node functionality. VSCP does not assume anything about the lower level system. It works with different transport mechanism such as Ethernet, TCP/IP, Wireless, Zigbee, Bluetooth, CAN, GPRS, RS-232, USB. Every control and measurement situation can be described and implemented using VSCP. 


 
{% include "./bottom_copyright.md" %}




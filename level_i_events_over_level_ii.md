# Level I events over level II

A class in level II is classes described by a number between 512-65535. However classes between 512-1023 is a mirror of the level I classes. This space is called *level I classes over level ii* and is described here

Instead of writing numbere a class can be described as **CLASS2.level1.XXXX** indicate a specific (*XXXX* in this case) Level II class. Also the form **CLASS2.level1.XXXX=yy** can be seen where *yy* is the numerical form. 

This type of classes have the same data content as level I classes except that the data is shifted 16-bytes. The first 16 bytes are instead used for the destination GUID. This is typically the GUID for a specific node or a GUID for an interface on a node or at the [VSCP Daemon](https://docs.vscp.org/#vscpd).

----

Class definitions can be found in the header file **[vscp_class.h](https://github.com/grodansparadis/vscp/blob/master/src/vscp/common/vscp_class.h)** which is located located in the **src/vscp/common** folder of the [VSCP project repository](https://github.com/grodansparadis/vscp). In the same folder the file [vscp_type.h](https://github.com/grodansparadis/vscp/blob/master/src/vscp/common/vscp_type.h) can be found which contains defines for all types. Note that both of these files is auto generated.

## Auto generated support files

VSCP event documentation and support files are auto generated.  The full documentation and source for the scripts that generate misc. files is [here](https://github.com/grodansparadis/vscp-classes) if you are interested.

Current files is available here [https://www.vscp.org/events/](https://www.vscp.org/events/) The [docs](https://www.vscp.org/events/docs/) sub-folder here contains event documentation in markdown and also a [zip](https://www.vscp.org/events/docs/vscp_docs.zip) and a [tar](https://www.vscp.org/events/docs/vscp_docs.tgz) of all content. This information is used to generate the [VSCP specification document](https://docs.vscp.org/#vscpspec).

All files generated contains version information which is the date and time when the docs was generated. This information is embedded in the generated files (if possible) and is also available in [JSON form here (version.json)](https://www.vscp.org/events/version.json) and in [JSONP form here (version.jsonp)](https://www.vscp.org/events/version.jsonp). In automated processes compare the on-site version information in one of there file with the downloaded version and download a new version if a newer one is available.

C header files are are here for [event classes (vscp_class.h)](https://www.vscp.org/events/vscp_class.h) and here for [event types (vscp_type.h)](https://www.vscp.org/events/vscp_type.h). The files are automatically included in the [vscp](https://github.com/grodansparadis/vscp) and the [vscp-firmware](https://github.com/grodansparadis/vscp-firmware) packages.

**Python** VSCP event include files are here for [VSCP classes (vscp_class.py)](https://www.vscp.org/events/vscp_class.py) and here for [vscp types (vscp_type.py)](https://www.vscp.org/events/vscp_type.py). The files are automatically included in the [pyvscp package](https://github.com/grodansparadis/pyvscp).

The [vscp_hashclass.h](https://www.vscp.org/events/vscp_hashclass.h) and [vscp_hashtype.h](https://www.vscp.org/events/vscp_hashtype.h) files are headers for the vscp helper class.

For **JavaScript** VSCP events are available in [JSON format (vscp_events.json)](https://www.vscp.org/events/vscp_events.json) and in [JSONP format (vscp_events.jsonp)](https://www.vscp.org/events/vscp_events.jsonp). Furthermore [vscp_class.js](https://www.vscp.org/events/vscp_class.js) and [vscp_type.js](https://www.vscp.org/events/vscp_type.js) holds VSCP class and VSCP type information suitable for JavaScript.

**XML** format is available here ([vscp_events.xml](https://www.vscp.org/events/vscp_events.xml)).

**SQL** format is available here ([vscp_events.sql](https://www.vscp.org/events/vscp_events.sql)).

[filename](./bottom_copyright.md ':include')
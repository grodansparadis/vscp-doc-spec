# VSCP over MQTT

VSCP is really the prefect match for MQTT. See [MQTT-driver](https://github.com/grodansparadis/vscpl2drv-mqtt) for a description on how to use MQTT with the VSCP daemon. 

There is four different package formats available that a user can select from when working with VSCP over MQTT. 

## String

The string form where each event is on this form

    head,class,type,obid,datetime,timestamp,GUID,data1,data2,data3....

## XML

The XML format where each event is packed as

```xml
    <event
     head="3"
     obid="1234"
     datetime="2017-01-13T10:16:02"
     timestamp="50817"
     class="10"
     type="6"
     guid="00:00:00:00:00:00:00:00:00:00:00:00:00:01:00:02"
     sizedata="7"
     data="0x48,0x34,0x35,0x2E,0x34,0x36,0x34" />
```

### Optional extra attributes

As an option it is possible to add

```xml
    value = "1.23"
    unit = "0",
    sensorindex = "1",
    zone = "11",
    subzone = "22"
```

to the XML object to send decoded measurement info. 

**This is optional data and one should never rely on it to be present**

## JSON

The JSON format where each VSCP event is packed as

```json
{
    "vscpHead": 2,
    "vscpObId": 123,
    "vscpDateTime": "2017-01-13T10:16:02",
    "vscpTimeStamp":50817,
    "vscpClass": 10,
    "vscpType": 8,
    "vscpGuid": "00:00:00:00:00:00:00:00:00:00:00:00:00:01:00:02",
    "vscpData": [1,2,3,4,5,6,7],
    "note": "This is some text"
}
```
__Note the casing. The format is **not** case insensitive.__

### Optional extra fields

As an option it is possible to add

```json
measurement {
    "value" : 1.23,
    "unit" : 0,
    "sensorindex" : 1,
    "zone" : 11,
    "subzone" : 22
}
```

to the JSON object to send decoded measurement info. 

**This is optional data and one should never rely on it to be present**

## Binary
Encrypted binary format that use the [VSCP over UDP format](./vscp_over_udp.md). See the link for more information


## Topics

One can use the topics and the structure that is suitable for the task ahead. This setup is just a recommendation. Following the recommended schema will make different units from different makers work easy together. 

### Publish

The preferred topic for VSCP events published to a MQTT broker is

    vscp/guid/miso/class/type

**guid** is the actual guid fo the node, typically something like FF:FF:FF:FF:FF:FF:FF:FE:5C:CF:7F:C4:1E:7B:00:00

**miso** stands for master in/slave out and say that this is a flow of events from a remote node (slave) to a master (server).

**class** is the actual numerical VSCP class for the event.

**type** is the actual numerical VSCP type for the event.

A client can easily filter out events from a specific remote node and of a certain type using this schema.

### Subscribe

The topic for server published events is

    vscp/guid/mosi/class/type

**guid** is the actual guid for the node, typically something like FF:FF:FF:FF:FF:FF:FF:FE:5C:CF:7F:C4:1E:7B:00:00

**mosi** stands for master out slave in. This is how the VSCP daemon (by default) will publish events on a MQTT broker.

**class** is the actual numerical VSCP class for the event.

**type** is the actual numerical VSCP type for the event.

A client subscribe topic is usually set as something like

    vscp/FF:FF:FF:FF:FF:FF:FF:FE:5C:CF:7F:C4:1E:7B:00:00/mosi/#

in which case a remote node subscribes to all events sent **to** a specific node (itself).

The node can of course be more general and subscribe to

 vscp/+/mosi/#

In whish case it will receive all events sent to all remote nodes.



[filename](./bottom_copyright.md ':include')

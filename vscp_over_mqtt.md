# VSCP over MQTT

VSCP is really the prefect match for MQTT. See [MQTT-driver](https://github.com/grodansparadis/vscpl2drv-mqtt) for a description on how to use MQTT with the VSCP daemon. 

There is four different package formats available that a user can select from when working with VSCP over MQTT. 

## STRING

The string form where each event is on this form

    head,class,type,obid,datetime,timestamp,GUID,data1,data2,data3....

### MQTT auto detect string format 
First non white space character not 0x00, "<" or "{" ==> string format

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

See the JSON format for the possibility to skip (redundant) fields.

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

### MQTT auto detect XML format
First non white space character "<" ==> xml

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

### Minimize transfer load

Although a VSCP event on JSON format can look like

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

several of the fields can be skipped if the information is already known. 

**note** is extra of course and is never needed.

**vscpHead** Set to zero if absent.

**vscpObId** Should be read as zero if not present,

**vscpDateTime** Should be read as now and today if not present, that is todays date and time when the event was received.

**vscpTimeStamp** Should be set to a microsecond timestamp on the receiving side or be set to zero to let other layers set it.

**vscpData** If there is no data it can be left out.

**vscpGuid** If known it can be left out. Typically it can bne decuced from the MQTT topic.

So a minimum JSON formated MQTT event scan look like

```json
{
  "vscpClass": 10,
  "vscpType": 8,
  "vscpData": [1,2,3,4,5,6,7],
}
```

If the MQTT topic also contains the class and type they can also be skipped and only the date needs to be sent. In this case both the VSCP class and the VSCP type will be set to zero by the parser and need to be set by the application.

### MQTT auto detect JSON format
First non white space character "{" ==> JSON

## BINARY
Encrypted binary format that use the [VSCP over UDP format](./vscp_over_udp.md). See the link for more information

### MQTT auto detect BINARY format
First character 0x00 and content len > 0  ==>  Binary   (UDP format)


## Topics

One can use the topics and the structure that is suitable for the task ahead. This setup is just a recommendation. Following the recommended schema will make different units from different makers work easy together. 

### Publish

The preferred topic for VSCP events published to a MQTT broker is

    vscp/{{guid}}/{{class}}/{{type}}

**guid** is the actual guid fo the node, typically something like FF:FF:FF:FF:FF:FF:FF:FE:5C:CF:7F:C4:1E:7B:00:00

**class** is the actual numerical VSCP class for the event.

**type** is the actual numerical VSCP type for the event.

A client can easily filter out events from a specific remote node and of a certain type using this schema.

For level I drivers or level II drivers where it makes sense (vscpl2drv-tcpiplink is a good example) a topic on the form

    vscp/{{guid}}/{{class}}/{{type}}/{{nickname}}

is recommended. Here nickname is _256*GUID[14] + GUID[15]_ that is the unsigned integer formed by the two lsb bytes of the GUID. With this setting it is easier to also filter on nickname.

### Subscribe

This can be

```
vscp/#
```

whish will receive all vscp events published on a broker. Or it can be

```
vscp/{{guid}}/#
```

which will receive all events from a specific node defined by it's guid.

There is also a possibility to be more specific

```
vscp/+/10/6
```

which is all temperature measurements from all nodes. Or the same from a specific node

```
vscp/FF:FF:FF:FF:FF:FF:FF:FE:5C:CF:7F:C4:1E:7B:00:00/10/6
```

The topic for events published by nodes are typically

```
vscp/{{guid}}/{{class}}/{{type}}
```

**{{guid}}** is the actual guid for the node, typically something like _FF:FF:FF:FF:FF:FF:FF:FE:5C:CF:7F:C4:1E:7B:00:00_

**{{class}}** is the actual numerical VSCP class for an event.

**{{type}}** is the actual numerical VSCP type for an event.

A client subscribe topic is usually set as something like

```
vscp/FF:FF:FF:FF:FF:FF:FF:FE:5C:CF:7F:C4:1E:7B:00:00/#
```

in which case a remote node subscribes to all events sent **to** a specific node.

The node can of course be more general and subscribe to

 vscp/#

In whish case it will receive all events sent to all remote nodes.



[filename](./bottom_copyright.md ':include')

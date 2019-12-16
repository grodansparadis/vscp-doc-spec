# VSCP over MQTT

VSCP is really the prefect match for MQTT. See [MQTT-driver](https://github.com/grodansparadis/vscpl2drv-mqtt) for a description on how to use MQTT with the VSCP daemon. 

There is four different package formats available that a user can select from when working with VSCP over MQTT. 

The string form where each event is on this from

    head,class,type,obid,datetime,timestamp,GUID,data1,data2,data3....

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

The JSON format where ich VSCP event is packed as

```json
{
    "head": 2,
    "obid": 123,
    "datetime": "2017-01-13T10:16:02",
    "timestamp":50817,
    "class": 10,
    "type": 8,
    "guid": "00:00:00:00:00:00:00:00:00:00:00:00:00:01:00:02",
    "data": [1,2,3,4,5,6,7],
    "note": "This is some text"
}
```

and last an optionally encrypted binary format that use the [VSCP over UDP format](./vscp_over_udp.md). Follow the link for more information




[filename](./bottom_copyright.md ':include')

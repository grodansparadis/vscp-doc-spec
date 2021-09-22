# The VSCP Event

The _event_ is the central part in a VSCP based system. The actual event may look different on different transport mediums but the content is always the same or at least the event on the form it is can be translated directly to a VSCP event.

Here, as everywhere for VSCP, values are stored most significant bit/byte first.

The Event consist of the following parts

| Part | Description |
|:----:| ----------- |
| _head_ | Flags for the event |
| _class_ | The class of the event |
| _type_ | The type of the event |
| _GUID_ | The gloably unique id of the event |
| _data_ | The data of the event. Max 512 bytes. |
| _timestamp_ | A microsecond timestamp of the event. |
| _year_ | The UTC year of the event |
| _month_ | The UTC month of the event |
| _day_ | The UTC day of of the event |
| _hour_ | The UTC hour of of the event |
| _minute_ | The UTC minute of of the event |
| _second_ | The UTC second of of the event |

## Head
The Head is a byte that contains the flags for the event. The flags are defined in the following table.

| Flag | Description |
|:----:| ----------- |
| Bit 15 | Marks the GUID as a ipv6 address.|
| Bit 14 | Tells that the event comes form a dumb node. That is a node without registers etc. One can not talk to a dumb node but one can get data from it. |
| Bit 8-13 | These bits are reserved for future use. |
| Bit 7,6,5 | TYhe priority for the event. 0 is highest priority, 7 is lowest.|
| Bit 3 | Don't calculate CRC. Used for special packages. |
| Bit 2,1,0 | Rolling index. Increased for every event sent from a node. Used for special packages |

## VSCP Class
Each event belongs to a class. A class can typically be a measurement, some information, a control command, etc. The class is a 16 bit value. But for level I event only 9 bits are used.

All VSCP classes are defined and described later in this document.

## VSCP Type
Each event belongs to a type. The type tells more specific what the event is in the class. The type is a 16 bit value but for level I event only 8 bits are used.

All VSCP types are defined and described later in this document.

## GUID
The GUID (Globally Unique ID) is a 128 bit (16-byte) value that is unique for each node. The GUID is used to identify the node. The form for the GUID is a 16 byte array looking like

```
'25:00:00:00:00:00:00:00:00:00:00:00:0D:02:00:01'
```
## Data
The data is a variable length array of bytes. The maximum length is 512 bytes. But this size is for a Level II events. Level I events, which are esigned for low end devices, have a maximum data size of eight bytes.

## Timestamp
The timestamp is a microsecond timestamp of the event. This timestamp is relative to the previous event sent from the same device and can not be used for any timekeeping. The intention for it is just for inter event timing. The timestamp is a 32 bit value. Set to zero when it is not used. If it is zero the first intelligent interface will set it.

## The Date/Time block
The date/time block is a block of 7 bytes that contains the UTC date and time of the event. Year use two bytes and the rest use one byte each. The format is chosen to be easy to interpret for really low end devices.

If all the fields are zero the date/time is set to the current time by the first intelligent interface the event passes.

## obid
Sometimes one may see _obid_ (object id) in the event. This is a 32 bit value. It is used by handling software to keep account on which interface an event originated. This can be used to keep events sent on an interface to be sent out again on the same interface.

# Format
The actual format of an event depends on the transport that carries the event. For an event to be transported over TCP/IP and the event is in json format the event can look like this

```json
{
  "vscpClass":15,
  "vscpData":[0,0,0],
  "vscpDateTime":"2021-09-22T16:27:22Z",
  "vscpGuid":"25:00:00:00:00:00:00:00:00:00:00:00:0D:02:00:01",
  "vscpHead":96,
  "vscpNote":"",
  "vscpObId":0,
  "vscpTimeStamp":0,
  "vscpType":1
  "measurement": 
  {
    "sensorindex":0,
    "subzone":0,
    "unit":0,
    "value":0,
    "zone":0
  },
}
```

The measurement part is optional and is used for convenience in higher level software.

One can also see items like

```json
vscpClassToken:"VSCP_CLASS1_MEASUREMENT",
vscpTypeToken:"VSCP_TYPE_MEASUREMENT_ELECTRIC_CURRENT",
```

in a json representation of an event. Here the tokens are inserted to translate the event to a more human readable form.

- Things to note is that date/time always is in UTC. A microsecond part is allowed. The date/time is always in ISO 8601 format. If not set the first intelligent interface the event go trough will set it to the current UTC date/time.
- Timestamp is always in microseconds. If not available or zero the first intelligent interface the event go trough will set it to a relative microsecond timestamp valid for that interface.
- The GUID is always in the form of a string. It can be set to "-" and in that case it will be set to the GUID of the first interface the event go trough.

## Higher level software

The JSON format is (today) the most common format for higher level VSCP events. But other formats like string, XML or binary formats are possible. See [level I specifics](./vscp_level_i_specifics.md) and [level II specifics](./vscp_level_ii_specifics.md).




[filename](./bottom_copyright.md ':include')
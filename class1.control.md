# Class=30 (0x1E) - Control

    CLASS1.CONTROL

## Description

Control functionality. One of the main concepts of VSCP is that it is an event driven protocol. Commands are sent out as events to the network not as events to specific devices. A device can belong to a zone which select limit events of interest for the particular node.. If there is a need to control a specific device the registry model should be used. This is the only way to directly control a device. 

## Type=0 (0x00) - General event :id=type0
```
VSCP_TYPE_CONTROL_GENERAL
```
General Event.
----

## Type=1 (0x01) - Mute on/off :id=type1
```
VSCP_TYPE_CONTROL_MUTE
```
Mute/Un-mute all sound generating nodes in a zone 

 | Data byte | Description                                                        | 
 | :---------: | -----------                                                        | 
 | 0         | If equal to zero no mute else mute.                                | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

----

## Type=2 (0x02) - (All) Lamp(s) on/off :id=type2
```
VSCP_TYPE_CONTROL_ALL_LAMPS
```
Turn on/off lamps on nodes in zone.

 | Data byte | Description                                                        | 
 | :---------: | -----------                                                        | 
 | 0         | If equal to zero off else on.                                      | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

See also [CLASS1.CONTROL, Type=40](./class1.control.md#type40) and [CLASS1.CONTROL, Type=42](./class1.control.md#type41) which don't use byte 0 but instead are separated in two distinct events.

It is recommended to use the more general [CLASS1.CONTROL, Type=17](./class1.control.md#type41),[CLASS1.CONTROL, Type=18](./class1.control.md#type18),[CLASS1.CONTROL, Type=19](./class1.control.md#type19) to keep a higher abstraction level. This event is keept for compatibility with legacy systems.

----

## Type=3 (0x03) - Open :id=type3
```
VSCP_TYPE_CONTROL_OPEN
```
Perform open on all nodes in zone. 

 | Data byte | Description                                                         | 
 | :---------: | -----------                                                         | 
 | 0         | Optional byte that have a meaning given by the issuer of the event. Prefered use is _index_ for compability. | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.          | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.  | 


----

## Type=4 (0x04) - Close :id=type4
```
VSCP_TYPE_CONTROL_CLOSE
```
Perform close on all nodes in zone. 

 | Data byte | Description                                                         | 
 | :---------: | -----------                                                         | 
 | 0         | Optional byte that have a meaning given by the issuer of the event. Prefered use is _index_ for compability. | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.          | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.  | 


----

## Type=5 (0x05) - TurnOn :id=type5
```
VSCP_TYPE_CONTROL_TURNON
```
Turn On a nodes in a zone/subzone. 

 | Data byte | Description                                                         | 
 | :---------: | -----------                                                         | 
 | 0         | Optional byte that have a meaning given by the issuer of the event. Prefered use is _index_ for compability. | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.          | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.  | 


----

## Type=6 (0x06) - TurnOff :id=type6
```
VSCP_TYPE_CONTROL_TURNOFF
```
Turn Off a nodes in a zone/subzone. 

 | Data byte | Description                                                         | 
 | :---------: | -----------                                                         | 
 | 0         | Optional byte that have a meaning given by the issuer of the event. Prefered use is _index_ for compability. | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.          | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.  | 


----

## Type=7 (0x07) - Start :id=type7
```
VSCP_TYPE_CONTROL_START
```
Start all nodes in a zone.

 | Data byte | Description                                                         | 
 | :---------: | -----------                                                         | 
 | 0         | Optional byte that have a meaning given by the issuer of the event. Prefered use is _index_ for compability. | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.          | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.  | 

----

## Type=8 (0x08) - Stop :id=type8
```
VSCP_TYPE_CONTROL_STOP
```
Stop all nodes in zone. 

 | Data byte | Description                                                         | 
 | :---------: | -----------                                                         | 
 | 0         | Optional byte that have a meaning given by the issuer of the event. Prefered use is _index_ for compability. | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.          | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.  | 


----

## Type=9 (0x09) - Reset :id=type9
```
VSCP_TYPE_CONTROL_RESET
```
Perform Reset on all nodes in zone. 

 | Data byte | Description                                                         | 
 | :---------: | -----------                                                         | 
 | 0         | Optional byte that have a meaning given by the issuer of the event. Prefered use is _index_ for compability. | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.          | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.  | 


----

## Type=10 (0x0A) - Interrupt :id=type10
```
VSCP_TYPE_CONTROL_INTERRUPT
```
Perform Interrupt on all nodes in zone. 

 | Data byte | Description                                                        | 
 | :---------: | -----------                                                        | 
 | 0         | Interrupt level. (0 – 255 , zero is lowest interrupt level. ).   | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 


----

## Type=11 (0x0B) - Sleep :id=type11
```
VSCP_TYPE_CONTROL_SLEEP
```
Perform Sleep on all nodes in zone. 

 | Data byte | Description                                                         | 
 | :---------: | -----------                                                         | 
 | 0         | Optional byte that have a meaning given by the issuer of the event. Prefered use is _index_ for compability. | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.          | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.  | 


----

## Type=12 (0x0C) - Wakeup :id=type12
```
VSCP_TYPE_CONTROL_WAKEUP
```
Wakeup all nodes in zone. 

 | Data byte | Description                                                         | 
 | :---------: | -----------                                                         | 
 | 0         | Optional byte that have a meaning given by the issuer of the event. Prefered use is _index_ for compability. | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.          | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.  | 


----

## Type=13 (0x0D) - Resume :id=type13
```
VSCP_TYPE_CONTROL_RESUME
```
Resume all nodes in zone. 

 | Data byte | Description                                                         | 
 | :---------: | -----------                                                         | 
 | 0         | Optional byte that have a meaning given by the issuer of the event. Prefered use is _index_ for compability. | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.          | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.  | 


----

## Type=14 (0x0E) - Pause :id=type14
```
VSCP_TYPE_CONTROL_PAUSE
```
Pause all nodes in zone. 

 | Data byte | Description                                                         | 
 | :---------: | -----------                                                         | 
 | 0         | Optional byte that have a meaning given by the issuer of the event. Prefered use is _index_ for compability. | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.          | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.  | 


----

## Type=15 (0x0F) - Activate :id=type15
```
VSCP_TYPE_CONTROL_ACTIVATE
```
Activate all nodes in zone. 

 | Data byte | Description                                                         | 
 | :---------: | -----------                                                         | 
 | 0         | Optional byte that have a meaning given by the issuer of the event. Prefered use is _index_ for compability. | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.          | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.  | 


----

## Type=16 (0x10) - Deactivate :id=type16
```
VSCP_TYPE_CONTROL_DEACTIVATE
```
Deactivate all nodes in zone. 

 | Data byte | Description                                                         | 
 | :---------: | -----------                                                         | 
 | 0         | Optional byte that have a meaning given by the issuer of the event. Prefered use is _index_ for compability. | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.          | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.  | 


----

## Type=17 (0x11) - Set all devices off :id=type17
```
VSCP_TYPE_CONTROL_TURN_ALL_OFF
```
Turn off all devices identified by zone/subzone/index.

 | Data byte | Description                                                        | 
 | :-------: | -----------                                                        | 
 | 0         | Index. 255 is all indeces. | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-254). 255 is all sub-zones. | 
----

## Type=18 (0x12) - Set all devices on :id=type18
```
VSCP_TYPE_CONTROL_TURN_ALL_ON
```
Turn on all devices identified by zone/subzone/index.

 | Data byte | Description                                                        | 
 | :---------: | -----------                                                        | 
 | 0         | Index. 255 is all indeces. | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-254). 255 is all sub-zones. |  
----

## Type=19 (0x13) - Set all device on/off as of argument :id=type19
```
VSCP_TYPE_CONTROL_TURN_ALL_X
```
Turn on/off all devices identified by zone/subzone/index.

 | Data byte | Description                                                        | 
 | :---------: | -----------                                                      | 
 | 0         | Index. 255 is all indeces. | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-254). 255 is all sub-zones. | 
 | 3         | 0 = off, 1= on. | 
----

## Type=20 (0x14) - Dim lamp(s) :id=type20
```
VSCP_TYPE_CONTROL_DIM_LAMPS
```
Dim all dimmer devices on a segment to a specified dim value. 

This is mainly constructed for dimming of lamps but is general for all dimmable devices.

 | Data byte | Description                                                                             | 
 | :---------: | -----------                                                                             | 
 | 0         | Value (0 – 100) . 0 = off, 100 = full on. 254 dim down one step. 255 dim up one step. | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.                              | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                      | 

----

## Type=21 (0x15) - Change Channel :id=type21
```
VSCP_TYPE_CONTROL_CHANGE_CHANNEL
```
This is typical for changing TV channels or for changing AV amp input source etc. 

 | Data byte | Description                                                                                                                                                                                                                                                                                                                                               | 
 | :---------: | -----------                                                                                                                                                                                                                                                                                                                                               | 
 | 0         | A value between 0 and 127 indicates the channel number. A value between 128 to 157 is change down by the specified number of channels. A value between 160 to 191 is change up by the specified number of channels. A value of 255 means that this is an extended change channel event and that the channel number is sent in byte 3 and after if needed. | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.                                                                                                                                                                                                                                                                                                | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                                                                                                                                                                                                                                                                        | 

----

## Type=22 (0x16) - Change Level :id=type22
```
VSCP_TYPE_CONTROL_CHANGE_LEVEL
```
Change an absolute level. 

 | Data byte | Description                                                        | 
 | :---------: | -----------                                                        | 
 | 0         | Absolute level.                                                    | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

----

## Type=23 (0x17) - Relative Change Level :id=type23
```
VSCP_TYPE_CONTROL_RELATIVE_CHANGE_LEVEL
```

 Relative Change Level request
 
 | Data byte | Description                                                        | 
 | :---------: | -----------                                                        | 
 | 0         | Relative level.                                                    | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

----

## Type=24 (0x18) - Measurement Request :id=type24
```
VSCP_TYPE_CONTROL_MEASUREMENT_REQUEST
```
Measurement Request

| Data byte | Description                                                                                                                                                           | 
 | :---------: | -----------                                                                                                                                                           | 
 | 0         | Zero indicates all measurements supported by node should be sent (as separate events). Non-zero indicates a node specific index specifying which measurement to send. | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.                                                                                                            | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                                                                                    | 

----

## Type=25 (0x19) - Stream Data :id=type25
```
VSCP_TYPE_CONTROL_STREAM_DATA
```
Request to stream data

 | Data byte | Description                                                               | 
 | :---------: | -----------                                                               | 
 | 0         | Sequence number which is increase by one for each stream data event sent. | 
 | 1-7       | Stream data.                                                              | 

Use this event for streamed data out from a node. The source is then given by the nickname. If a specific received is needed use Zoned Stream. 

----

## Type=26 (0x1A) - Sync :id=type26
```
VSCP_TYPE_CONTROL_SYNC
```
Synchronize events on a segment. 

 | Data byte | Description                                                                                                                                  | 
 | :---------: | -----------                                                                                                                                  | 
 | 0         | Sensor index for a sensor within a module (see [data coding](./vscp_measurements?id=datacoding). 255 is all sensors. | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.                                                                                   | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                                                           | 

The sensor index can be used to index units within a module also or used as some other indexing schema. 

----

## Type=27 (0x1B) - Zoned Stream Data :id=type27
```
VSCP_TYPE_CONTROL_ZONED_STREAM_DATA
```
Request streamed data from nodes identified by zone/subzone.

 | Data byte | Description                                                               | 
 | :---------: | -----------                                                               | 
 | 0         | Sequence number which is increase by one for each stream data event sent. | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.                | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.        | 
 | 3-7       | Stream data.                                                              | 

----

## Type=28 (0x1C) - Set Pre-set :id=type28
```
VSCP_TYPE_CONTROL_SET_PRESET
```
Some nodes may have pre-set configurations to choose from. With this event a pre-set can be set for a zone/sub-zone.

A node that receive and act on this event send CLASS1.INFORMATION, 

Type=48 as a response event. 

 | Data byte | Description                                                        | 
 | :---------: | -----------                                                        | 
 | 0         | Code for pre-set to set.                                           | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

----

## Type=29 (0x1D) - Toggle state :id=type29
```
VSCP_TYPE_CONTROL_TOGGLE_STATE
```
Toggle the state of a node.

Note: This may be a bad design option as it often demands that the state should be known for the node on beforehand.

 | Data byte | Description                                                         | 
 | :---------: | -----------                                                         | 
 | 0         | Optional byte that have a meaning given by the issuer of the event. Prefered use is _index_ for compability. | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.          | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.  | 

----

## Type=30 (0x1E) - Timed pulse on :id=type30
```
VSCP_TYPE_CONTROL_TIMED_PULSE_ON
```
With this event it is possible to generate a timed pulse that is on for a specified time.

 | Data byte | Description                                                         |
 | :---------: | ----------- |
 | 0         | Optional byte that have a meaning given by the issuer of the event. Prefered use is _index_ for compability. |
 | 1         | Zone for which event applies to (0-254). 255 is all zones.      |
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.  |
 | 3         | Control byte.                                                       |
 | 4-7       | Set time as a long with MSB in the first byte.                      |

##### Control Byte

The control byte have the following bits defined

 | Bit | Description                                                          |
 | :---: | -----------                                                          |
 | 0-3 | Time code (see table below)                                          |
 | 4   | Reserved                                                             |
 | 5   | Reserved                                                             |
 | 6   | Send on event ( Class=20 Type = 3 (0x03) On ) when pulse goes on.    |
 | 7   | Send off event ( Class=20 Type = 4 (0x04) Off ) when pulse goes off. |

##### Time code

 | Code | Description                     |
 | :----: | -----------                     |
 | 0    | Time specified in microseconds. |
 | 1    | Time specified in milliseconds. |
 | 2    | Time specified in seconds.      |
 | 3    | Time specified in minutes.      |
 | 4    | Time specified in hours.        |
 | 5    | Time specified in days.         |

----

## Type=31 (0x1F) - Timed pulse off :id=type31
```
VSCP_TYPE_CONTROL_TIMED_PULSE_OFF
```
With this event it is possible to generate a timed pulse that is off for a specified time.

 | Data byte | Description                                                         | 
 | :---------: | -----------                                                         | 
 | 0         | Optional byte that have a meaning given by the issuer of the event. Prefered use is _index_ for compability. | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.          | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.  | 
 | 3         | Control byte.                                                       | 
 | 4-7       | Set time as a long with MSB in the first byte.                      | 

##### Control Byte

The control byte have the following bits defined

 | Bit | Description                                                          | 
 | :---: | -----------                                                          | 
 | 0-3 | Time code (see table below)                                          | 
 | 4   | Reserved                                                             | 
 | 5   | Reserved                                                             | 
 | 6   | Send on event ( Class=20 Type = 3 (0x03) On ) when pulse goes on.    | 
 | 7   | Send off event ( Class=20 Type = 4 (0x04) Off ) when pulse goes off. | 

##### Time code

 | Code | Description                     | 
 | :----: | -----------                     | 
 | 0    | Time specified in microseconds. | 
 | 1    | Time specified in milliseconds. | 
 | 2    | Time specified in seconds.      | 
 | 3    | Time specified in minutes.      | 
 | 4    | Time specified in hours.        | 
 | 5    | Time specified in days.         | 


----

## Type=32 (0x20) - Set country/language :id=type32
```
VSCP_TYPE_CONTROL_SET_COUNTRY_LANGUAGE
```
Set country and language.

 | Data byte | Description                                                        | 
 | :---------: | -----------                                                        | 
 | 0         | Country/Language code.                                             | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 
 | 3-7       | Country/Language code specific                                     | 

 | Language code | Description          | Example                                           | 
 | :---------: | -----------          | -------                                           | 
 | 0             | Custom coded system  | Byte 3 = 0 English, Byte 3 = 1 German or similar. | 
 | 1             | ISO 639-1            | nl for Dutch, en for English.                     | 
 | 2             | ISO 639-2/T          | nid for Dutch, eng for English.                   | 
 | 3             | ISO 639-2/B          | dut for Dutch, eng for English.                   | 
 | 4             | ISO 639-3            | nid for Dutch, eng for English.                   | 
 | 5             | IETF (RFC-5646/4647) | en-US for American English. en-GB British.        | 


ISO codes can be found [here](https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes)

----

## Type=33 (0x21) - Big Change level :id=type33
```
VSCP_TYPE_CONTROL_BIG_CHANGE_LEVEL
```
Big Change level can be used in situations when the one byte level of CLASS1.CONTROL, Type=22 is not enough.

 | Data byte | Description  | 
 | :---------: | -----------   | 
 | 0         | Index        | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.   | 
 | 3-7       | Level as signed integer. The range can be adjusted by the user by sending just the needed number of bytes (1-5) which form the signed integer (MSB first). | 

----

## Type=34 (0x22) - Move (shutter) up :id=type34
```
VSCP_TYPE_CONTROL_SHUTTER_UP
```
Move (shutter) up.

 | Data byte | Description                                                        | 
 | :---------: | -----------                                                        | 
 | 0         | Index.                                                             | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

----

## Type=35 (0x23) - Move (shutter) down :id=type35
```
VSCP_TYPE_CONTROL_SHUTTER_DOWN
```
Move (shutter) down.

 | Data byte | Description                                                        | 
 | :---------: | -----------                                                        | 
 | 0         | Index.                                                             | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

----

## Type=36 (0x24) - Move (shutter) left :id=type36
```
VSCP_TYPE_CONTROL_SHUTTER_LEFT
```
Move (shutter) left.

 | Data byte | Description                                                        | 
 | :---------: | -----------                                                        | 
 | 0         | Index.                                                             | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 


----

## Type=37 (0x25) - Move (shutter) right :id=type37
```
VSCP_TYPE_CONTROL_SHUTTER_RIGHT
```
Move (shutter) right.

 | Data byte | Description                                                        | 
 | :---------: | -----------                                                        | 
 | 0         | Index.                                                             | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

----

## Type=38 (0x26) - Move (shutter) to middle position :id=type38
```
VSCP_TYPE_CONTROL_SHUTTER_MIDDLE
```
Move (shutter) to middle position.

 | Data byte | Description                                                        | 
 | :---------: | -----------                                                        | 
 | 0         | Index.                                                             | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

----

## Type=39 (0x27) - Move (shutter) to preset position :id=type39
```
VSCP_TYPE_CONTROL_SHUTTER_PRESET
```
Move (shutter) to preset position.

 | Data byte | Description                                                        | 
 | :---------: | -----------                                                        | 
 | 0         | Index.                                                             | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 
 | 3         | Position 0-100.                                                    | 

----

## Type=40 (0x28) - (All) Lamp(s) on :id=type40
```
VSCP_TYPE_CONTROL_ALL_LAMPS_ON
```
Turn on all lamps in a zone.

 | Data byte | Description                                                        | 
 | :---------: | -----------                                                        | 
 | 0         |	Optional byte that have a meaning given by the issuer of the event. Prefered use is _index_ for compability.| 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

See also [CLASS1.CONTROL, Type=2](./class1.control.md#type2)

It is recommended to use the more general [CLASS1.CONTROL, Type=17](./class1.control.md#type41),[CLASS1.CONTROL, Type=18](./class1.control.md#type18), [CLASS1.CONTROL, Type=19](./class1.control.md#type19) to keep a higher abstraction level. This event is keept for compatibility with legacy systems.

----

## Type=41 (0x29) - (All) Lamp(s) off :id=type41
```
VSCP_TYPE_CONTROL_ALL_LAMPS_OFF
```
Turn off all lamps in a zone.

 | Data byte | Description                                                        | 
 | :---------: | -----------                                                        | 
 | 0         |	Optional byte that have a meaning given by the issuer of the event. Prefered use is _index_ for compability.| 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

See also [CLASS1.CONTROL, Type=2](./class1.control.md#type2)

It is recommended to use the more general [CLASS1.CONTROL, Type=17](./class1.control.md#type41),[CLASS1.CONTROL, Type=18](./class1.control.md#type18), [CLASS1.CONTROL, Type=19](./class1.control.md#type19) to keep a higher abstraction level. This event is keept for compatibility with legacy systems.

----

## Type=42 (0x2A) - Lock :id=type42
```
VSCP_TYPE_CONTROL_LOCK
```
Lock devices in a zone.

 | Data byte | Description                                                        |
 | :---------: | -----------                                                      |
 | 0         |	Optional byte that have a meaning given by the issuer of the event. Prefered use is _index_ for compability.| 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.         |
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. |

----

## Type=43 (0x2B) - Unlock :id=type43
```
VSCP_TYPE_CONTROL_UNLOCK
```
Unlock devices in a zone.

 | Data byte | Description                                                        |
 | :---------: | -----------                                                        |
 | 0         |	Optional byte that have a meaning given by the issuer of the event. Prefered use is _index_ for compability.| 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.         |
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. |

----

## Type=44 (0x2C) - PWM set :id=type44
```
VSCP_TYPE_CONTROL_PWM
```
With this event it is possible to set duty cycle output such as PWM.

 | Data byte | Description   |
 | :---------: | ----------- |
 | 0         | Repeat/counter: 0=repeat forever, >0 number of repeats |
 | 1         | Zone for which event applies to (0-254). 255 is all zones.      |
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.  |
 | 3         | Control byte.  |
 | 4         | Time-On MSB |
 | 5         | Time-On LSB |
 | 6         | Time-Off MSB |
 | 7         | Time-Off LSB |

##### Control Byte

The control byte have the following bits defined

 | Bit | Description |
 | :---: | ----------- |
 | 0-3 | Time code (see table below) |
 | 4   | Reserved  |
 | 5   | Reserved  |
 | 6   | Reserved  |
 | 7   | Reserved  |

##### Time code

 | Code | Description                     |
 | :----: | -----------                   |
 | 0    | Time specified in microseconds. |
 | 1    | Time specified in milliseconds. |
 | 2    | Time specified in seconds.      |
 | 3    | Time specified in minutes.      |
 | 4    | Time specified in hours.        |
 | 5    | Time specified in days.         |

----

## Type=45 (0x2D) - Lock with token :id=type45
```
VSCP_TYPE_CONTROL_TOKEN_LOCK
```
Lock devices with token.

 | Data byte | Description                                                        |
 | :---------: | -----------                                                      |
 | 0         |	Optional byte that have a meaning given by the issuer of the event. Prefered use is _index_ for compability.| 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.         |
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. |
 | 3-7 | Token. This token can be 1-5 bytes and length of event is set accordingly. It should be interpreted as an unsigned integer in the range 0-1099511627775. MSB byte is stored in first byte. |
 

----

## Type=46 (0x2E) - Unlock with token :id=type46
```
VSCP_TYPE_CONTROL_TOKEN_UNLOCK
```
Unlock devices with token.

 | Data byte | Description                                                        |
 | :---------: | -----------                                                      |
 | 0         |	Optional byte that have a meaning given by the issuer of the event. Prefered use is _index_ for compability.| 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.         |
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. |
 | 3-7 | Token. This token can be 1-5 bytes and length of event is set accordingly. It should be interpreted as an unsigned integer in the range 0-1099511627775. MSB byte is stored in first byte. |
 

----

## Type=47 (0x2F) - Set security level :id=type47
```
VSCP_TYPE_CONTROL_SET_SECURITY_LEVEL
```
Set security level.

 | Data byte | Description                                                        |
 | :---------: | -----------                                                      |
 | 0         | Security level to set. 0-255 (Higher value is higher security level).  |
 | 1         | Zone for which event applies to (0-254). 255 is all zones.         |
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. |
 

----

## Type=48 (0x30) - Set security pin :id=type48
```
VSCP_TYPE_CONTROL_SET_SECURITY_PIN
```
Set security pin.

 | Data byte | Description                                                        |
 | :---------: | -----------                                                      |
 | 0         |	Optional byte that have a meaning given by the issuer of the event. Prefered use is _index_ for compability.| 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.         |
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. |
 | 3-7 | Security pin. This pin can be 1-5 bytes and length of event is set accordingly. It should be interpreted as an unsigned integer in the range 0-1099511627775. MSB byte is stored in first byte. |
 

----

## Type=49 (0x31) - Set security password :id=type49
```
VSCP_TYPE_CONTROL_SET_SECURITY_PASSWORD
```
Set security password.

 | Data byte | Description                                                        |
 | :---------: | -----------                                                      |
 | 0         |	Optional byte that have a meaning given by the issuer of the event. Prefered use is _index_ for compability.| 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.         |
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. |
 | 3-7 | Security password. This password can be 1-5 bytes and length of event is set accordingly. It should be interpreted as a UTF-8 string of length equal to the event data length minus 3 bytes |
 

----

## Type=50 (0x32) - Set security token :id=type50
```
VSCP_TYPE_CONTROL_SET_SECURITY_TOKEN
```
Set security token.

 | Data byte | Description                                                        |
 | :---------: | -----------                                                      |
 | 0         |	Optional byte that have a meaning given by the issuer of the event. Prefered use is _index_ for compability.| 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.         |
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. |
 | 3-7 | Token. This token can be 1-5 bytes and length of event is set accordingly. It should be interpreted as an unsigned integer in the range 0-1099511627775. MSB byte is stored in first byte. |
 

----

## Type=51 (0x33) - Request new security token :id=type51
```
VSCP_TYPE_CONTROL_REQUEST_SECURITY_TOKEN
```
Request new security token.

 | Data byte | Description                                                        |
 | :---------: | -----------                                                      |
 | 0         |	Optional byte that have a meaning given by the issuer of the event. Prefered use is _index_ for compability.| 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.         |
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. |
 
 

----

## Type=52 (0x34) - Increment :id=type52
```
VSCP_TYPE_CONTROL_INCREMENT
```
Increment value.

 | Data byte | Description  | 
 | :---------: | -----------   | 
 | 0         | Optional byte that have a meaning given by the issuer of the event. Prefered use is _index_ for compability.        | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.   | 
 | 3-7       | Increment as unsigned integer. The range can be adjusted by the user by sending just the needed number of bytes (1-5) which form the unsigned integer (MSB first). If omitted (or 0) 1 is assumed as default increment value. | 

----

## Type=53 (0x35) - Decrement :id=type53
```
VSCP_TYPE_CONTROL_DECREMENT
```
Decrement value.

 | Data byte | Description  | 
 | :---------: | -----------   | 
 | 0         | Optional byte that have a meaning given by the issuer of the event. Prefered use is _index_ for compability.        | 
 | 1         | Zone for which event applies to (0-254). 255 is all zones.        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.   | 
 | 3-7       | Decrement as unsigned integer. The range can be adjusted by the user by sending just the needed number of bytes (1-5) which form the unsigned integer (MSB first). If omitted (or 0) 1 is assumed as default decrement value. | 

----

[filename](./bottom_copyright.md ':include')
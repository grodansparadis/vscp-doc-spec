# Class=513 (0x0201) - Class2 Level I Alarm

    CLASS2.LEVEL1.ALARM

## Description

This class mirrors the [CLASS1.ALARM](./class1.alarm.md) class but use a different data format with a GUID stored in the first 16 bytes of the data followed by the standard data thus offset with 16-bytes.

See [CLASS2.PROTOCOL1](./class2.protocol1.md) for more information on the data format.


## Type=0 (0x00) - General event {#type0}
    VSCP_TYPE_ALARM_GENERALGeneral Event. 

----

## Type=1 (0x01) - Warning {#type1}
    VSCP_TYPE_ALARM_WARNINGIndicates a warning condition. 

 | Data byte | Description | 
 | :---------: | ----------- | 
 | 0 | **0**=off. **1**=on. | 
 | 1 | Zone for which event applies to (0-255). 255 is all zones. | 
 | 2 | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

If both or one of zone/sub-zone are omitted they should be interpreted as if they where 255. 


----

## Type=2 (0x02) - Alarm occurred {#type2}
    VSCP_TYPE_ALARM_ALARMIndicates an alarm condition. 

 | Data byte | Description | 
 | :---------: | ----------- | 
 | 0 | **0**=off. **1**=on. | 
 | 1 | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2 | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

If both or one of zone/sub-zone are omitted they should be interpreted as if they where 255. 


----

## Type=3 (0x03) - Alarm sound on/off {#type3}
    VSCP_TYPE_ALARM_SOUNDAlarm sound should be turned on or off. 

 | Data byte | Description | 
 | :---------: | ----------- | 
 | 0 | **0**=off. **1**=on. | 
 | 1 | Zone for which event applies to (0-255). 255 is all zones. | 
 | 2 | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

If both or one of zone/sub-zone are omitted they should be interpreted as if they where 255. 


----

## Type=4 (0x04) - Alarm light on/off {#type4}
    VSCP_TYPE_ALARM_LIGHTAlarm light should be turned on or off. 

 | Data byte | Description | 
 | :---------: | ----------- | 
 | 0 | **0**=off. **1**=on. | 
 | 1 | Zone for which event applies to (0-255). 255 is all zones. | 
 | 2 | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

If both or one of zone/sub-zone are omitted they should be interpreted as if they where 255. 


----

## Type=5 (0x05) - Power on/off {#type5}
    VSCP_TYPE_ALARM_POWERPower has been lost or is available again. 

 | Data byte | Description | 
 | :---------: | -----------  | 
 | 0 | **0**=off. **1**=on. | 
 | 1 | Zone for which event applies to (0-255). 255 is all zones. | 
 | 2 | Sub-zone for which event applies to (0-255). 255 is all sub-zones.| 

If both or one of zone/sub-zone are omitted they should be interpreted as if they where 255. 


----

## Type=6 (0x06) - Emergency Stop {#type6}
    VSCP_TYPE_ALARM_EMERGENCY_STOPEmergency stop has been hit/activated. All systems on the zone/sub-zone should go to their inactive/safe state.
 
 | Data byte | Description | 
 | :---------: | ----------- | 
 | 0 | **0**=off. **1**=on. | 
 | 1 | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2 | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

If both or one of zone/sub-zone are omitted they should be interpreted as if they where 255. 


----

## Type=7 (0x07) - Emergency Pause {#type7}
    VSCP_TYPE_ALARM_EMERGENCY_PAUSEEmergency pause has been hit/activated. All systems on the zone/sub-zone should go to their inactive/safe state but preserve there settings. 

 | Data byte | Description | 
 | :---------: | ----------- | 
 | 0 | **0**=off. **1**=on. | 
 | 1 | Zone for which event applies to (0-255). 255 is all zones. | 
 | 2 | Sub-zone for which event applies to (0-255). 255 is all subzones. | 

If both or one of zone/sub-zone are omitted they should be interpreted as if they where 255. 


----

## Type=8 (0x08) - Emergency Reset {#type8}
    VSCP_TYPE_ALARM_EMERGENCY_RESETIssued after an emergency stop or pause in order for nodes to reset and start operating .

 | Data byte | Description | 
 | :---------: | ----------- | 
 | 0 | **0**=off. **1**=on. | 
 | 1 | Zone for which event applies to (0-255). 255 is all zones. | 
 | 2 | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

If both or one of zone/sub-zone are omitted they should be interpreted as if they where 255. 


----

## Type=9 (0x09) - Emergency Resume {#type9}
    VSCP_TYPE_ALARM_EMERGENCY_RESUMEIssued after an emergency pause in order for nodes to start operating from where they left of without resetting their registers . 

 | Data byte | Description | 
 | :---------: | ----------- | 
 | 0 | **0**=off. **1**=on. | 
 | 1 | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2 | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

If both or one of zone/sub-zone are omitted they should be interpreted as if they where 255. 


----

## Type=10 (0x0A) - Arm {#type10}
    VSCP_TYPE_ALARM_ARMIssued after an alarm system has been armed. 

 | Data byte | Description | 
 | :---------: | ----------- | 
 | 0 | **0**=off. **1**=on. | 
 | 1 | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2 | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

If both or one of zone/sub-zone are omitted they should be interpreted as if they where 255. 


----

## Type=11 (0x0B) - Disarm {#type11}
    VSCP_TYPE_ALARM_DISARMIssued after an alarm system has been disarmed. 

 | Data byte | Description | 
 | :---------: | ----------- | 
 | 0 | **0**=off. **1**=on. | 
 | 1 | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2 | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

If both or one of zone/sub-zone are omitted they should be interpreted as if they where 255.


----

## Type=12 (0x0C) - Watchdog {#type12}
    VSCP_TYPE_ALARM_WATCHDOGIssued when a watchdog has been triggered. 

 | Data byte | Description | 
 | :---------: | ----------- | 
 | 0 | index. | 
 | 1 | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2 | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

If both or one of zone/sub-zone are omitted they should be interpreted as if they where 255.




----

{% include "./bottom_copyright.md" %}
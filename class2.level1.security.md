# Class=514 (0x0202) - Class2 Level I Security

    CLASS2.LEVEL1.SECURITY

## Description

This class mirrors the [CLASS1.SECURITY](./class1.security.md) class but use a different data format with a GUID stored in the first 16 bytes of the data followed by the standard data thus offset with 16-bytes.

See [CLASS2.PROTOCOL1](./class2.protocol1.md) for more information on the data format.
## <a name="type0">Type=0 (0x00) - General event</a>
    VSCP_TYPE_SECURITY_GENERALGeneral Event.
----

## <a name="type1">Type=1 (0x01) - Motion Detect</a>
    VSCP_TYPE_SECURITY_MOTIONA motion has been detected. 

 | Data byte | Description | 
 | :---------: | ----------- | 
 | 0 | User defined data. | 
 | 1 | Zone for which event applies to (0-255). 255 is all zones. | 
 | 2 | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

If both or one of zone/sub-zone are omitted they should be interpreted as if they where 255. 

----

## <a name="type2">Type=2 (0x02) - Glass break</a>
    VSCP_TYPE_SECURITY_GLASS_BREAKA glass break event has been detected. 

 | Data byte | Description | 
 | :---------: | -----------  | 
 | 0 | User defined data. | 
 | 1 | Zone for which event applies to (0-255). 255 is all zones. | 
 | 2  | Sub-zone for which event applies to (0-255). 255 is all subzones. | 

If both or one of zone/sub-zone are omitted they should be interpreted as if they where 255. 

----

## <a name="type3">Type=3 (0x03) - Beam break</a>
    VSCP_TYPE_SECURITY_BEAM_BREAKA beam break event has been detected. 

 | Data byte | Description | 
 | :---------: | ----------- | 
 | 0 | User defined data. | 
 | 1 | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2 | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

If both or one of zone/sub-zone are omitted they should be interpreted as if they where 255. 

----

## <a name="type4">Type=4 (0x04) - Sensor tamper</a>
    VSCP_TYPE_SECURITY_SENSOR_TAMPERA sensor tamper has been detected. 

 | Data byte | Description | 
 | :---------: | ----------- | 
 | 0 | User defined data. | 
 | 1 | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2 | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

If both or one of zone/sub-zone are omitted they should be interpreted as if they where 255. 

----

## <a name="type5">Type=5 (0x05) - Shock sensor</a>
    VSCP_TYPE_SECURITY_SHOCK_SENSORA shock sensor event has been detected. 

 | Data byte | Description | 
 | :---------: | ----------- | 
 | 0 | User defined data. | 
 | 1 | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2 | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

If both or one of zone/sub-zone are omitted they should be interpreted as if they where 255. 

----

## <a name="type6">Type=6 (0x06) - Smoke sensor</a>
    VSCP_TYPE_SECURITY_SMOKE_SENSORA smoke sensor event has been detected. 

 | Data byte | Description | 
 | :---------: | ----------- | 
 | 0 | User defined data. | 
 | 1 | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2 | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

If both or one of zone/sub-zone are omitted they should be interpreted as if they where 255. 

----

## <a name="type7">Type=7 (0x07) - Heat sensor</a>
    VSCP_TYPE_SECURITY_HEAT_SENSORA heat sensor event has been detected. 

 | Data byte | Description | 
 | :---------: | ----------- | 
 | 0 | User defined data. | 
 | 1 | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2 | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

If both or one of zone/sub-zone are omitted they should be interpreted as if they where 255. 

----

## <a name="type8">Type=8 (0x08) - Panic switch</a>
    VSCP_TYPE_SECURITY_PANIC_SWITCHA panic switch event has been detected. 

 | Data byte | Description | 
 | :---------: | ----------- | 
 | 0 | User defined data. | 
 | 1 | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2 | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

If both or one of zone/sub-zone are omitted they should be interpreted as if they where 255. 

----

## <a name="type9">Type=9 (0x09) - Door Contact</a>
    VSCP_TYPE_SECURITY_DOOR_OPENIndicates a door sensor reports that a door is open. 

 | Data byte | Description | 
 | :---------: | ----------- | 
 | 0 | User defined data. | 
 | 1 | Zone for which event applies to (0-255). 255 is all zones. | 
 | 2 | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

If both or one of zone/sub-zone are omitted they should be interpreted as if they where 255.

----

## <a name="type10">Type=10 (0x0A) - Window Contact</a>
    VSCP_TYPE_SECURITY_WINDOW_OPENIndicates a window sensor reports that a window is open.

 | Data byte | Description | 
 | :---------: | ----------- | 
 | 0 | User defined data. | 
 | 1 | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2 | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

If both or one of zone/sub-zone are omitted they should be interpreted as if they where 255.

----

## <a name="type11">Type=11 (0x0B) - CO Sensor</a>
    VSCP_TYPE_SECURITY_CO_SENSORCO sensor has detected CO at non secure level

 | Data byte | Description | 
 | :---------: | ----------- | 
 | 0 | User defined data. | 
 | 1 | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2 | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

If both or one of zone/sub-zone are omitted they should be interpreted as if they where 255.

----

## <a name="type12">Type=12 (0x0C) - Frost detected</a>
    VSCP_TYPE_SECURITY_FROST_DETECTEDA frost sensor condition is detected

 | Data byte | Description | 
 | :---------: | ----------- | 
 | 0 | User defined data. | 
 | 1 | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2 | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

If both or one of zone/sub-zone are omitted they should be interpreted as if they where 255.

----

## <a name="type13">Type=13 (0x0D) - Flame detected</a>
    VSCP_TYPE_SECURITY_FLAME_DETECTEDFlame is detected.

 | Data byte | Description | 
 | :---------: | -----------  | 
 | 0 | User defined data. | 
 | 1 | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2 | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

If both or one of zone/sub-zone are omitted they should be interpreted as if they where 255.

----

## <a name="type14">Type=14 (0x0E) - Oxygen Low</a>
    VSCP_TYPE_SECURITY_OXYGEN_LOWLow oxygen level detected.

 | Data byte | Description | 
 | :---------: | ----------- | 
 | 0 | User defined data. | 
 | 1 | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2 | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

If both or one of zone/sub-zone are omitted they should be interpreted as if they where 255.

----

## <a name="type15">Type=15 (0x0F) - Weight detected.</a>
    VSCP_TYPE_SECURITY_WEIGHT_DETECTEDWeight-detector triggered.

 | Data byte | Description | 
 | :---------: | -----------  | 
 | 0 | User defined data. | 
 | 1 | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2 | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

If both or one of zone/sub-zone are omitted they should be interpreted as if they where 255.

----

## <a name="type16">Type=16 (0x10) - Water detected.</a>
    VSCP_TYPE_SECURITY_WATER_DETECTEDWater has been detected.

 | Data byte | Description | 
 | :---------: | ----------- | 
 | 0 | User defined data. | 
 | 1 | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2 | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

If both or one of zone/sub-zone are omitted they should be interpreted as if they where 255.

----

## <a name="type17">Type=17 (0x11) - Condensation detected.</a>
    VSCP_TYPE_SECURITY_CONDENSATION_DETECTEDCondensation (humidity) detected.

 | Data byte | Description | 
 | :---------: | ----------- | 
 | 0 | User defined data. | 
 | 1 | Zone for which event applies to (0-255). 255 is all zones. | 
 | 2 | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

If both or one of zone/sub-zone are omitted they should be interpreted as if they where 255.

----

## <a name="type18">Type=18 (0x12) - Noise (sound) detected.</a>
    VSCP_TYPE_SECURITY_SOUND_DETECTEDNoise (sound) has been detected.

 | Data byte | Description | 
 | :---------: | ----------- | 
 | 0 | User defined data. | 
 | 1 | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2 | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

If both or one of zone/sub-zone are omitted they should be interpreted as if they where 255.

----

## <a name="type19">Type=19 (0x13) - Harmful sound levels detected.</a>
    VSCP_TYPE_SECURITY_HARMFUL_SOUND_LEVELHarmful sound levels detected.

 | Data byte | Description | 
 | :---------: | ----------- | 
 | 0 | User defined data. | 
 | 1 | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2 | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

If both or one of zone/sub-zone are omitted they should be interpreted as if they where 255.

----

## <a name="type20">Type=20 (0x14) - Tamper detected.</a>
    VSCP_TYPE_SECURITY_TAMPERTamper detected.

 | Data byte | Description | 
 | :---------: | ----------- | 
 | 0 | User defined data. | 
 | 1 | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2 | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

----

{% include "./bottom_copyright.md" %}
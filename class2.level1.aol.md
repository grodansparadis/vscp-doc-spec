# Class=562 (0x0232) - Class2 Level I AOL

    CLASS2.LEVEL1.AOL

## Description

This class mirrors the [CLASS1.AOL](./class1.aol.md) class but use a different data format with a GUID stored in the first 16 bytes of the data followed by the standard data thus offset with 16-bytes.

See [CLASS2.PROTOCOL1](./class2.protocol1.md) for more information on the data format.
## <a name="type0">Type=0 (0x00) - General event</a>
    VSCP_TYPE_AOL_GENERALGeneral Event.
----

## <a name="type1">Type=1 (0x01) - System unplugged from power source</a>
    VSCP_TYPE_AOL_UNPLUGGED_POWERThis node was unplugged from its power source.

 | Data byte | Description                                                        | 
 | :---------: | -----------                                                        | 
 | 0         | Index for record.                                                  | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

----

## <a name="type2">Type=2 (0x02) - System unplugged from network</a>
    VSCP_TYPE_AOL_UNPLUGGED_LANThis node was unplugged from the network.

 | Data byte | Description                                                        | 
 | :---------: | -----------                                                        | 
 | 0         | Index for record.                                                  | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

----

## <a name="type3">Type=3 (0x03) - Chassis intrusion</a>
    VSCP_TYPE_AOL_CHASSIS_INTRUSIONThis node detected chassis intrusion.

 | Data byte | Description                                                        | 
 | :---------: | -----------                                                        | 
 | 0         | Index for record.                                                  | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

----

## <a name="type4">Type=4 (0x04) - Processor removal</a>
    VSCP_TYPE_AOL_PROCESSOR_REMOVALThis node detected processor removal.

 | Data byte | Description                                                        | 
 | --------- | -----------                                                        | 
 | 0         | Index for record.                                                  | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

----

## <a name="type5">Type=5 (0x05) - System environmental errors</a>
    VSCP_TYPE_AOL_ENVIRONMENT_ERRORThis node detected system environmental errors.

 | Data byte | Description                                                        | 
 | :---------: | -----------                                                        | 
 | 0         | Index for record.                                                  | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

----

## <a name="type6">Type=6 (0x06) - High temperature</a>
    VSCP_TYPE_AOL_HIGH_TEMPERATUREThis node detected high temperature.

 | Data byte | Description                                                        | 
 | :---------: | -----------                                                        | 
 | 0         | Index for record.                                                  | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

----

## <a name="type7">Type=7 (0x07) - Fan speed problem</a>
    VSCP_TYPE_AOL_FAN_SPEEDThis node detected Fan speed problem.

 | Data byte | Description                                                        | 
 | :---------: | -----------                                                        | 
 | 0         | Index for record.                                                  | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

----

## <a name="type8">Type=8 (0x08) - Voltage fluctuations</a>
    VSCP_TYPE_AOL_VOLTAGE_FLUCTUATIONSThis node detected Voltage fluctuations.

 | Data byte | Description                                                        | 
 | :---------: | -----------                                                        | 
 | 0         | Index for record.                                                  | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

----

## <a name="type9">Type=9 (0x09) - Operating system errors</a>
    VSCP_TYPE_AOL_OS_ERRORThis node detected Operating system errors.

 | Data byte | Description                                                        | 
 | :---------: | -----------                                                        | 
 | 0         | Index for record.                                                  | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

----

## <a name="type10">Type=10 (0x0A) - System power-on error</a>
    VSCP_TYPE_AOL_POWER_ON_ERRORThis node detected System power-on errors.

 | Data byte | Description                                                        | 
 | :---------: | -----------                                                        | 
 | 0         | Index for record.                                                  | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

----

## <a name="type11">Type=11 (0x0B) - System is hung</a>
    VSCP_TYPE_AOL_SYSTEM_HUNGThis node detected System is hung.

 | Data byte | Description                                                        | 
 | :---------: | -----------                                                        | 
 | 0         | Index for record.                                                  | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

----

## <a name="type12">Type=12 (0x0C) - Component failure</a>
    VSCP_TYPE_AOL_COMPONENT_FAILUREThis node detected Component failure.

 | Data byte | Description                                                        | 
 | :---------: | -----------                                                        | 
 | 0         | Index for record.                                                  | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

----

## <a name="type13">Type=13 (0x0D) - Remote system reboot upon report of a critical failure</a>
    VSCP_TYPE_AOL_REBOOT_UPON_FAILUREThis node detected Remote system reboot upon report of a critical failure.

 | Data byte | Description                                                        | 
 | :---------: | -----------                                                        | 
 | 0         | Index for record.                                                  | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

----

## <a name="type14">Type=14 (0x0E) - Repair Operating System</a>
    VSCP_TYPE_AOL_REPAIR_OPERATING_SYSTEMThis node detected Repair Operating System.

 | Data byte | Description                                                        | 
 | :---------: | -----------                                                        | 
 | 0         | Index for record.                                                  | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

----

## <a name="type15">Type=15 (0x0F) - Update BIOS image</a>
    VSCP_TYPE_AOL_UPDATE_BIOS_IMAGEThis node detected Update BIOS image.

 | Data byte | Description                                                        | 
 | :---------: | -----------                                                        | 
 | 0         | Index for record.                                                  | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

----

## <a name="type16">Type=16 (0x10) - Update Perform other diagnostic procedures</a>
    VSCP_TYPE_AOL_UPDATE_DIAGNOSTIC_PROCEDUREThis node detected Update Perform other diagnostic procedures.

 | Data byte | Description                                                        | 
 | :---------: | -----------                                                        | 
 | 0         | Index for record.                                                  | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 

----

{% include "./bottom_copyright.md" %}
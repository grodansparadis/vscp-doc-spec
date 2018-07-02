# Class=506 (0x01FA) - Diagnostic

    CLASS1.DIAGNOSTIC

## Description

Diagnostic functionality. 

The diagnostic events can be used to report malfunctions and errors. 

## <a name="type0">Type=0 (0x00) - General event</a>
    VSCP_TYPE_DIAGNOSTIC_GENERAL
General Event. 


 | Data byte | Description | 
 | :---------: | ----------- | 
 | 0         | index. Often used as an index for channels/subdevices within a module. | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones. | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 
        
----

## <a name="type1">Type=1 (0x01) - Overvoltage</a>
    VSCP_TYPE_DIAGNOSTIC_OVERVOLTAGE
Over voltage has been diagnosed. 

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type2">Type=2 (0x02) - Undervoltage</a>
    VSCP_TYPE_DIAGNOSTIC_UNDERVOLTAGE
Under voltage has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type3">Type=3 (0x03) - USB VBUS low</a>
    VSCP_TYPE_DIAGNOSTIC_VBUS_LOW
Low voltage on USB VBUS has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type4">Type=4 (0x04) - Battery voltage low</a>
    VSCP_TYPE_DIAGNOSTIC_BATTERY_LOW
Low battery voltage has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


----

## <a name="type5">Type=5 (0x05) - Battery full voltage</a>
    VSCP_TYPE_DIAGNOSTIC_BATTERY_FULL
Battery full voltage has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type6">Type=6 (0x06) - Battery error</a>
    VSCP_TYPE_DIAGNOSTIC_BATTERY_ERROR
Battery error has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type7">Type=7 (0x07) - Battery OK</a>
    VSCP_TYPE_DIAGNOSTIC_BATTERY_OK
Functional battery has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


----

## <a name="type8">Type=8 (0x08) - Over current</a>
    VSCP_TYPE_DIAGNOSTIC_OVERCURRENT
Over current has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


----

## <a name="type9">Type=9 (0x09) - Circuit error</a>
    VSCP_TYPE_DIAGNOSTIC_CIRCUIT_ERROR
Circuit error has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


----

## <a name="type10">Type=10 (0x0A) - Short circuit</a>
    VSCP_TYPE_DIAGNOSTIC_SHORT_CIRCUIT
Short circuit has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type11">Type=11 (0x0B) - Open Circuit</a>
    VSCP_TYPE_DIAGNOSTIC_OPEN_CIRCUIT
Open Circuit has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type12">Type=12 (0x0C) - Moist</a>
    VSCP_TYPE_DIAGNOSTIC_MOIST
Moist has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type13">Type=13 (0x0D) - Wire failure</a>
    VSCP_TYPE_DIAGNOSTIC_WIRE_FAIL
Wire failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type14">Type=14 (0x0E) - Wireless faliure</a>
    VSCP_TYPE_DIAGNOSTIC_WIRELESS_FAIL
Wireless faliure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type15">Type=15 (0x0F) - IR failure</a>
    VSCP_TYPE_DIAGNOSTIC_IR_FAIL
IR failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type16">Type=16 (0x10) - 1-wire failure</a>
    VSCP_TYPE_DIAGNOSTIC_1WIRE_FAIL
1-wire failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type17">Type=17 (0x11) - RS-222 failure</a>
    VSCP_TYPE_DIAGNOSTIC_RS222_FAIL
RS-222 failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type18">Type=18 (0x12) - RS-232 failure</a>
    VSCP_TYPE_DIAGNOSTIC_RS232_FAIL
RS-232 failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type19">Type=19 (0x13) - RS-423 failure</a>
    VSCP_TYPE_DIAGNOSTIC_RS423_FAIL
RS-423 failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


----

## <a name="type20">Type=20 (0x14) - RS-485 failure</a>
    VSCP_TYPE_DIAGNOSTIC_RS485_FAIL
RS-485 failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type21">Type=21 (0x15) - CAN failure</a>
    VSCP_TYPE_DIAGNOSTIC_CAN_FAIL
CAN failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


----

## <a name="type22">Type=22 (0x16) - LAN failure</a>
    VSCP_TYPE_DIAGNOSTIC_LAN_FAIL
LAN failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type23">Type=23 (0x17) - USB failure</a>
    VSCP_TYPE_DIAGNOSTIC_USB_FAIL
USB failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type24">Type=24 (0x18) - Wifi failure</a>
    VSCP_TYPE_DIAGNOSTIC_WIFI_FAIL
Wifi failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type25">Type=25 (0x19) - NFC/RFID failure</a>
    VSCP_TYPE_DIAGNOSTIC_NFC_RFID_FAIL
NFC/RFID failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type26">Type=26 (0x1A) - Low signal</a>
    VSCP_TYPE_DIAGNOSTIC_LOW_SIGNAL
Low signal has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type27">Type=27 (0x1B) - High signal</a>
    VSCP_TYPE_DIAGNOSTIC_HIGH_SIGNAL
High signal has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


----

## <a name="type28">Type=28 (0x1C) - ADC failure</a>
    VSCP_TYPE_DIAGNOSTIC_ADC_FAIL
ADC failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type29">Type=29 (0x1D) - ALU failure</a>
    VSCP_TYPE_DIAGNOSTIC_ALU_FAIL
ALU failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type30">Type=30 (0x1E) - Assert</a>
    VSCP_TYPE_DIAGNOSTIC_ASSERT
An assert has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type31">Type=31 (0x1F) - DAC failure</a>
    VSCP_TYPE_DIAGNOSTIC_DAC_FAIL
DAC failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type32">Type=32 (0x20) - DMA failure</a>
    VSCP_TYPE_DIAGNOSTIC_DMA_FAIL
DMA failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type33">Type=33 (0x21) - Ethernet failure</a>
    VSCP_TYPE_DIAGNOSTIC_ETH_FAIL
Ethernet failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


----

## <a name="type34">Type=34 (0x22) - Exception</a>
    VSCP_TYPE_DIAGNOSTIC_EXCEPTION
Exception has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type35">Type=35 (0x23) - FPU failure</a>
    VSCP_TYPE_DIAGNOSTIC_FPU_FAIL
Floating point unit (FPU) failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type36">Type=36 (0x24) - GPIO failure</a>
    VSCP_TYPE_DIAGNOSTIC_GPIO_FAIL
General purpose I/O (GPIO) failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type37">Type=37 (0x25) - I2C failure</a>
    VSCP_TYPE_DIAGNOSTIC_I2C_FAIL
I2C failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type38">Type=38 (0x26) - I2S failure</a>
    VSCP_TYPE_DIAGNOSTIC_I2S_FAIL
I2C failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type39">Type=39 (0x27) - Invalid configuration</a>
    VSCP_TYPE_DIAGNOSTIC_INVALID_CONFIG
Invalid configuration has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type40">Type=40 (0x28) - MMU failure</a>
    VSCP_TYPE_DIAGNOSTIC_MMU_FAIL
Memory Management Unit (MMU) failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type41">Type=41 (0x29) - NMI failure</a>
    VSCP_TYPE_DIAGNOSTIC_NMI
Non mask-able interrupt (NMI) failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type42">Type=42 (0x2A) - Overheat</a>
    VSCP_TYPE_DIAGNOSTIC_OVERHEAT
Overheat has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type43">Type=43 (0x2B) - PLL fail</a>
    VSCP_TYPE_DIAGNOSTIC_PLL_FAIL
Phased Locked Loop (PLL) fail has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type44">Type=44 (0x2C) - POR failure</a>
    VSCP_TYPE_DIAGNOSTIC_POR_FAIL
Power ON Reset (POR) fail has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type45">Type=45 (0x2D) - PWM failure</a>
    VSCP_TYPE_DIAGNOSTIC_PWM_FAIL
Pulse Width Modulation (PWM) failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type46">Type=46 (0x2E) - RAM failure</a>
    VSCP_TYPE_DIAGNOSTIC_RAM_FAIL
Random Access Memory (RAM) failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type47">Type=47 (0x2F) - ROM failure</a>
    VSCP_TYPE_DIAGNOSTIC_ROM_FAIL
Read only memory (ROM) failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type48">Type=48 (0x30) - SPI failure</a>
    VSCP_TYPE_DIAGNOSTIC_SPI_FAIL
Serial peripheral interface (SPI) failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type49">Type=49 (0x31) - Stack failure</a>
    VSCP_TYPE_DIAGNOSTIC_STACK_FAIL
Stack failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


----

## <a name="type50">Type=50 (0x32) - LIN bus failure</a>
    VSCP_TYPE_DIAGNOSTIC_LIN_FAIL
LIN bus failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


----

## <a name="type51">Type=51 (0x33) - UART failure</a>
    VSCP_TYPE_DIAGNOSTIC_UART_FAIL
UART failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type52">Type=52 (0x34) - Unhandled interrupt</a>
    VSCP_TYPE_DIAGNOSTIC_UNHANDLED_INT
Unhandled interrupt has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type53">Type=53 (0x35) - Memory failure</a>
    VSCP_TYPE_DIAGNOSTIC_MEMORY_FAIL
Memory failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type54">Type=54 (0x36) - Variable range failure</a>
    VSCP_TYPE_DIAGNOSTIC_VARIABLE_RANGE
Variable range failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type55">Type=55 (0x37) - WDT failure</a>
    VSCP_TYPE_DIAGNOSTIC_WDT
Watch Dog Timer (WDT) failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type56">Type=56 (0x38) - EEPROM failure</a>
    VSCP_TYPE_DIAGNOSTIC_EEPROM_FAIL
EEPROM failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type57">Type=57 (0x39) - Encryption failure</a>
    VSCP_TYPE_DIAGNOSTIC_ENCRYPTION_FAIL
Encryption failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type58">Type=58 (0x3A) - Bad user input failure</a>
    VSCP_TYPE_DIAGNOSTIC_BAD_USER_INPUT
Bad user input failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type59">Type=59 (0x3B) - Decryption failure</a>
    VSCP_TYPE_DIAGNOSTIC_DECRYPTION_FAIL
Decryption failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type60">Type=60 (0x3C) - Noise</a>
    VSCP_TYPE_DIAGNOSTIC_NOISE
Noise has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type61">Type=61 (0x3D) - Boot loader failure</a>
    VSCP_TYPE_DIAGNOSTIC_BOOTLOADER_FAIL
Boot loader failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


----

## <a name="type62">Type=62 (0x3E) - Program flow failure</a>
    VSCP_TYPE_DIAGNOSTIC_PROGRAMFLOW_FAIL
Program flow failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type63">Type=63 (0x3F) - RTC faiure</a>
    VSCP_TYPE_DIAGNOSTIC_RTC_FAIL
Real Time Clock (RTC) failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type64">Type=64 (0x40) - System test failure</a>
    VSCP_TYPE_DIAGNOSTIC_SYSTEM_TEST_FAIL
System test failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type65">Type=65 (0x41) - Sensor failure</a>
    VSCP_TYPE_DIAGNOSTIC_SENSOR_FAIL
Sensor failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type66">Type=66 (0x42) - Safe state entered</a>
    VSCP_TYPE_DIAGNOSTIC_SAFESTATE
Safe state entered has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type67">Type=67 (0x43) - Signal implausible</a>
    VSCP_TYPE_DIAGNOSTIC_SIGNAL_IMPLAUSIBLE
Signal implausible has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type68">Type=68 (0x44) - Storage fail</a>
    VSCP_TYPE_DIAGNOSTIC_STORAGE_FAIL
Storage fail has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type69">Type=69 (0x45) - Self test OK</a>
    VSCP_TYPE_DIAGNOSTIC_SELFTEST_FAIL
Self test OK has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type70">Type=70 (0x46) - ESD/EMC/EMI failure</a>
    VSCP_TYPE_DIAGNOSTIC_ESD_EMC_EMI
ESD/EMC/EMI failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type71">Type=71 (0x47) - Timeout</a>
    VSCP_TYPE_DIAGNOSTIC_TIMEOUT
Timeout has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type72">Type=72 (0x48) - LCD failure</a>
    VSCP_TYPE_DIAGNOSTIC_LCD_FAIL
LCD failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type73">Type=73 (0x49) - Touch panel failure</a>
    VSCP_TYPE_DIAGNOSTIC_TOUCHPANEL_FAIL
Touch panel failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type74">Type=74 (0x4A) - No load</a>
    VSCP_TYPE_DIAGNOSTIC_NOLOAD
No load has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type75">Type=75 (0x4B) - Cooling failure</a>
    VSCP_TYPE_DIAGNOSTIC_COOLING_FAIL
Cooling failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type76">Type=76 (0x4C) - Heating failure</a>
    VSCP_TYPE_DIAGNOSTIC_HEATING_FAIL
Heating failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type77">Type=77 (0x4D) - Transmission failure</a>
    VSCP_TYPE_DIAGNOSTIC_TX_FAIL
Transmission failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type78">Type=78 (0x4E) - Receiption failure</a>
    VSCP_TYPE_DIAGNOSTIC_RX_FAIL
Receiption failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

## <a name="type79">Type=79 (0x4F) - External IC failure</a>
    VSCP_TYPE_DIAGNOSTIC_EXT_IC_FAIL
A failure in an external IC circuit has been detected.

 | Data byte | Description                                                                                       | 
 | :---------: | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

----

{% include "./bottom_copyright.md" %}
# Class=506 (0x1FA) Diagnostic

    CLASS1.DIAGNOSTIC
    
## Description

Diagnostic functionality. 

The diagnostic events can be used to report malfunctions and errors. 

##   Type0 (0x00) General. ===== 

General diagnostic event. 

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 
                    1
##   Type1 (0x01) Overvoltage. ===== 

Over voltage has been diagnosed. 

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type2 (0x02) Undervoltage. ===== 

Under voltage has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type3 (0x03) USB VBUS low. ===== 

Low voltage on USB VBUS has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type4 (0x04) Battery voltage low. ===== 

Low battery voltage has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type5 (0x05) Battery full voltage. ===== 

Battery full voltage has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type6 (0x06) Battery error. ===== 

Battery error has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type7 (0x07) Battery OK. ===== 

Functional battery has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type8 (0x08) Over current. ===== 

Over current has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type9 (0x09) Circuit error. ===== 

Circuit error has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type10 (0x0A) Short circuit. ===== 

Short circuit has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type11 (0x0B) Open Circuit. ===== 

Open Circuit has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type12 (0x0C) Moist. ===== 

Moist has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type13 (0x0D) Wire failure. ===== 

Wire failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type14 (0x0E) Wireless faliure. ===== 

Wireless faliure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type15 (0x0F) IR failure. ===== 

IR failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type16 (0x10) 1-wire failure. ===== 

1-wire failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type17 (0x11) RS-222 failure. ===== 

RS-222 failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type18 (0x12) RS-232 failure. ===== 

RS-232 failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type19 (0x13) RS-423 failure. ===== 

RS-423 failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type20 (0x14) RS-485 failure. ===== 

RS-485 failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type21 (0x15) CAN failure. ===== 

CAN failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type22 (0x16) LAN failure. ===== 

LAN failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type23 (0x17) USB failure. ===== 

USB failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type24 (0x18) Wifi failure. ===== 

Wifi failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type25 (0x19) NFC/RFID failure. ===== 

NFC/RFID failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type26 (0x1A) Low signal. ===== 

Low signal has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type27 (0x1B) High signal. ===== 

High signal has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type28 (0x1C) ADC failure. ===== 

ADC failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type29 (0x1D) ALU failure. ===== 

ALU failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type30 (0x1E) Assert. ===== 

An assert has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type31 (0x1F) DAC failure. ===== 

DAC failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type32 (0x20) DMA failure. ===== 

DMA failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type33 (0x21) Ethernet failure. ===== 

Ethernet failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type34 (0x22) Exception. ===== 

Exception has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type35 (0x23) FPU failure. ===== 

Floating point unit (FPU) failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type36 (0x24) GPIO failure. ===== 

General purpose I/O (GPIO) failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type37 (0x25) I2C failure. ===== 

I2C failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type38 (0x26) I2S failure. ===== 

I2C failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type39 (0x27) Invalid configuration. ===== 

Invalid configuration has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type40 (0x28) MMU failure. ===== 

Memory Management Unit (MMU) failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type41 (0x29) NMI failure. ===== 

Non mask-able interrupt (NMI) failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type42 (0x2A) Overheat. ===== 

Overheat has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type43 (0x2B) PLL fail. ===== 

Phased Locked Loop (PLL) fail has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type44 (0x2C) POR failure. ===== 

Power ON Reset (POR) fail has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type45 (0x2D) PWM failure. ===== 

Pulse Width Modulation (PWM) failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type46 (0x2E) RAM failure. ===== 

Random Access Memory (RAM) failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type47 (0x2F) ROM failure. ===== 

Read only memory (ROM) failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type48 (0x30) SPI failure. ===== 

Serial peripheral interface (SPI) failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type49 (0x31) Stack failure. ===== 

Stack failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type50 (0x32) LIN bus failure. ===== 

LIN bus failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type51 (0x33) UART failure. ===== 

UART failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type52 (0x34) Unhandled interrupt. ===== 

Unhandled interrupt has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type53 (0x35) Memory failure. ===== 

Memory failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type54 (0x36) Variable range failure. ===== 

Variable range failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type55 (0x37) WDT failure. ===== 

Watch Dog Timer (WDT) failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type56 (0x38) EEPROM failure. ===== 

EEPROM failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type57 (0x39) Encryption failure. ===== 

Encryption failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type58 (0x3A) Bad user input failure. ===== 

Bad user input failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type59 (0x3B) Decryption failure. ===== 

Decryption failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type60 (0x3C) Noise. ===== 

Noise has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type61 (0x3D) Boot loader failure. ===== 

Boot loader failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type62 (0x3E) Program flow failure. ===== 

Program flow failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type63 (0x3F) RTC faiure. ===== 

Real Time Clock (RTC) failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type64 (0x40) System test failure. ===== 

System test failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type65 (0x41) Sensor failure. ===== 

Sensor failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type66 (0x42) Safe state entered. ===== 

Safe state entered has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

#define VSCP_TYPE_DIAGNOSTIC_SIGNAL_IMPLAUSIBLE             67

##   Type67 (0x43)Signal implausible. ===== 

Signal implausible has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type68 (0x44) Storage fail. ===== 

Storage fail has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type69 (0x45) Self test OK. ===== 

Self test OK has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type70 (0x46) ESD/EMC/EMI failure. ===== 

ESD/EMC/EMI failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type71 (0x47) Timeout. ===== 

Timeout has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type72 (0x48) LCD failure. ===== 

LCD failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type73 (0x49) Touch panel failure. ===== 

Touch panel failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type74 (0x4A) no load. ===== 

No load has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type75 (0x4B) Cooling failure. ===== 

Cooling failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type76 (0x4C) Heating failure. ===== 

Heating failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type77 (0x4D) Transmission failure. ===== 

Transmission failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type78 (0x4E) Receiption failure. ===== 

Receiption failure has been diagnosed.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type79 (0x4F) External IC failure. ===== 

A failure in an external IC circuit has been detected.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/subdevices within a module.                            | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

\\ 
----
{{  ::copyright.png?400  |}}

`<HTML>``<p style="color:red;text-align:center;">``<a href="http://www.paradiseofthefrog.com">`Paradise of the Frog AB`</a>``</p>``</HTML>`


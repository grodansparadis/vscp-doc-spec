# Class=508 (0x1FC) Error

    CLASS1.ERROR
    
## Description

Error reporting functionality that follow the errors defined in the [vscp.h](https///github.com/grodansparadis/vscp_software/blob/master/src/vscp/common/vscp.h) header file.


##   Type0 (0x00) Success. ===== 

This error message is used to report success that is no error.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/sub devices within a module.                           | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type1 (0x01) Error. ===== 

This error message is used to indicate an error condition.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/sub devices within a module.                           | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type7 (0x07) Channel error. ===== 

This error message is used to indicate a (communication) channel problem.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/sub devices within a module.                           | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type8 (0x08) fifo empty error. ===== 

This error message is used to indicate a fifo empty problem.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/sub devices within a module.                           | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type9 (0x09) fifo full error. ===== 

This error message is used to indicate a fifo full problem.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/sub devices within a module.                           | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type10 (0x0A) fifo size error. ===== 

This error message is used to indicate a fifo size problem.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/sub devices within a module.                           | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type11 (0x0B) fifo wait error. ===== 

This error message is used to indicate a fifo wait problem.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/sub devices within a module.                           | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type12 (0x0C) generic error. ===== 

This error message is used to indicate a generic error.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/sub devices within a module.                           | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type13 (0x0D) hardware error. ===== 

This error message is used to indicate a hardware error.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/sub devices within a module.                           | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type14 (0x0E) initialization error. ===== 

This error message is used to indicate a initialization error.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/sub devices within a module.                           | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type15 (0x0F) missing initialization error. ===== 

This error message is used to indicate a missing initialization error.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/sub devices within a module.                           | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type16 (0x10) initialization ready. ===== 

This error message is used to indicate a initialization ready error.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/sub devices within a module.                           | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type17 (0x11) not supported. ===== 

This error message is used to indicate a not supported error.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/sub devices within a module.                           | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type18 (0x12) overrun error. ===== 

This error message is used to indicate an overrun error.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/sub devices within a module.                           | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type19 (0x13) receiver empty error. ===== 

This error message is used to indicate a receiver empty error.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/sub devices within a module.                           | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type20 (0x14) register error. ===== 

This error message is used to indicate a register error.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/sub devices within a module.                           | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type21 (0x15) transmitter full error. ===== 

This error message is used to indicate a transmitter full error.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/sub devices within a module.                           | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##  Type = 22-27 (0x16-0x1B) reserved

Reserved

##   Type28 (0x1C) library error. ===== 

This error message is used to indicate a library error.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/sub devices within a module.                           | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type29 (0x1D) procedural address error. ===== 

This error message is used to indicate a procedural address error.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/sub devices within a module.                           | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type30 (0x1E) only one instance error. ===== 

This error message is used to indicate an only one instance error.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/sub devices within a module.                           | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type31 (0x1F) sub driver error. ===== 

This error message is used to indicate a sub driver error.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/sub devices within a module.                           | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type32 (0x20) timeout error. ===== 

This error message is used to indicate a timeout error.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/sub devices within a module.                           | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 


##   Type33 (0x21) not open error. ===== 

This error message is used to indicate a not open error.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/sub devices within a module.                           | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type34 (0x22) parameter error. ===== 

This error message is used to indicate a parameter error.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/sub devices within a module.                           | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type35 (0x23) memory error. ===== 

This error message is used to indicate a memory error.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/sub devices within a module.                           | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type36 (0x24) internal error. ===== 

This error message is used to indicate a internal error.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/sub devices within a module.                           | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type37 (0x25) communication error. ===== 

This error message is used to indicate a communication error.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/sub devices within a module.                           | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type38 (0x26) user error. ===== 

This error message is used to indicate a user error.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/sub devices within a module.                           | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type39 (0x27) password error. ===== 

This error message is used to indicate a password error.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/sub devices within a module.                           | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type40 (0x28) connection error. ===== 

This error message is used to indicate a connection error.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/sub devices within a module.                           | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type41 (0x29) invalid handle error. ===== 

This error message is used to indicate a invalid handle error.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/sub devices within a module.                           | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

##   Type42 (0x2A) operation failed error. ===== 

This error message is used to indicate an operation failed error.

 | Data byte | Description                                                                                       | 
 | --------- | -----------                                                                                       | 
 | 0         | index. Often used as an index for channels/sub devices within a module.                           | 
 | 1         | Zone for which event applies to (0-255). 255 is all zones.                                        | 
 | 2         | Sub-zone for which event applies to (0-255). 255 is all sub-zones.                                | 
 | 3-7       | Can be present or not be present. If present the bytes give additional user specific information. | 

\\ 
----
{{  ::copyright.png?400  |}}

`<HTML>``<p style="color:red;text-align:center;">``<a href="http://www.paradiseofthefrog.com">`Paradise of the Frog AB`</a>``</p>``</HTML>`

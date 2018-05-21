# Class=65 (0x41) Measurement with zone

    CLASS1.MEASUREZONE


Measurements with zone information. This class mirrors the standard measurement events is [CLASS1.MEASUREMENT=10](http://www.vscp.org/docs/vscpspec/doku.php?id=class1.measurement) with the difference that index, zone, and sub-zone is added. This in turn limits the data-coding options to normalized integer (see [Data-coding](http://www.vscp.org/docs/vscpspec/doku.php?id=data_coding) for a description). The default unit for the measurement should always be used.

 | Byte | Description                                                        | 
 | ---- | -----------                                                        | 
 | 0    | Index for sensor.                                                  | 
 | 1    | Zone for which event applies to (0-255). 255 is all zones.         | 
 | 2    | Sub-zone for which event applies to (0-255). 255 is all sub-zones. | 
 | 3    | Data coding.                                                       | 
 | 4-7  | Data with format defined by byte 0.                                | 

{% include "./bottom_copyright.md" %}

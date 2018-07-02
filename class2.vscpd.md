# Class=65535 (0xFFFF) - VSCP Daemon internal events

    CLASS2.VSCPD

## Description

This class is reserved for internal events used by the decision matrix mechanism of the [VSCP Daemon](https://www.vscp.org/docs/vscpd/doku.php). Events of this type should never be visible on a physical bus. 

## <a name="type0">Type=0 (0x00) - General event</a>
    VSCP2_TYPE_VSCPD_GENERAL
General Event.
----

## <a name="type1">Type=1 (0x01) - Loop</a>
    VSCP2_TYPE_VSCPD_LOOP
Event is generated each loop in the DM or if no events is received every 100 ms (configurable value). No data is defined.

----

## <a name="type3">Type=3 (0x03) - Pause</a>
    VSCP2_TYPE_VSCPD_PAUSE
The machine/daemon is going to a pause state. No data is defined.

----

## <a name="type4">Type=4 (0x04) - Activate</a>
    VSCP2_TYPE_VSCPD_ACTIVATE
The machine/daemon is going from a pause state. No data is defined.

----

## <a name="type5">Type=5 (0x05) - Second</a>
    VSCP2_TYPE_VSCPD_SECOND
Event is generated each new second. No data is defined. 

----

## <a name="type6">Type=6 (0x06) - Minute</a>
    VSCP2_TYPE_VSCPD_MINUTE
Event is generated each new minute. No data is defined. 

----

## <a name="type7">Type=7 (0x07) - Hour</a>
    VSCP2_TYPE_VSCPD_HOUR
Event is generated each new Hour. No data is defined. 

----

## <a name="type8">Type=8 (0x08) - Noon</a>
    VSCP2_TYPE_VSCPD_NOON
Event is generated at 12:00 each day. No data is defined. 

----

## <a name="type9">Type=9 (0x09) - Midnight</a>
    VSCP2_TYPE_VSCPD_MIDNIGHT
Event is generated at 00:00 each day. No data is defined.

----

## <a name="type11">Type=11 (0x0B) - Week</a>
    VSCP2_TYPE_VSCPD_WEEK
Event is generated when a new week starts (config setting). No data is defined.

----

## <a name="type12">Type=12 (0x0C) - Month</a>
    VSCP2_TYPE_VSCPD_MONTH
Event is generated when a new month starts. No data is defined.

----

## <a name="type13">Type=13 (0x0D) - Quarter</a>
    VSCP2_TYPE_VSCPD_QUARTER
Event is generated when a new quarter starts. No data is defined.

----

## <a name="type14">Type=14 (0x0E) - Year</a>
    VSCP2_TYPE_VSCPD_YEAR
Event is generated when a new year starts. No data is defined.

----

## <a name="type15">Type=15 (0x0F) - Random-minute</a>
    VSCP2_TYPE_VSCPD_RANDOM_MINUTE
Event is generated randomly over a minute as is sent once each minute. No data is defined.

----

## <a name="type16">Type=16 (0x10) - Random-hour</a>
    VSCP2_TYPE_VSCPD_RANDOM_HOUR
Event is generated randomly over an hour and is sent once each hour. No data is defined.

----

## <a name="type17">Type=17 (0x11) - Random-day</a>
    VSCP2_TYPE_VSCPD_RANDOM_DAY
Event is generated randomly over a day and is sent once each day. No data is defined.

----

## <a name="type18">Type=18 (0x12) - Random-week</a>
    VSCP2_TYPE_VSCPD_RANDOM_WEEK
Event is generated randomly over a week and is sent once each week. No data is defined.

----

## <a name="type19">Type=19 (0x13) - Random-month</a>
    VSCP2_TYPE_VSCPD_RANDOM_MONTH
Event is generated randomly over a month and is sent once each month. No data is defined.

----

## <a name="type20">Type=20 (0x14) - Random-year</a>
    VSCP2_TYPE_VSCPD_RANDOM_YEAR
Event is generated randomly over a year and is sent once each year. No data is defined.

----

## <a name="type21">Type=21 (0x15) - Dusk</a>
    VSCP2_TYPE_VSCPD_DUSK
Event is from calculated dusk. No data is defined.

----

## <a name="type22">Type=22 (0x16) - Dawn</a>
    VSCP2_TYPE_VSCPD_DAWN
Event is from calculated dawn. No data is defined.
----

## <a name="type23">Type=23 (0x17) - Starting up</a>
    VSCP2_TYPE_VSCPD_STARTING_UP
The machine/daemon is starting up. This is the first event sent after a machine start up. Shutting down . No data is defined.

----

## <a name="type24">Type=24 (0x18) - Shutting down</a>
    VSCP2_TYPE_VSCPD_SHUTTING_DOWN
The machine/daemon is shutting down. This is the last event sent before a machine is shutting off. No data is defined. 

----

## <a name="type25">Type=25 (0x19) - Timer started</a>
    VSCP2_TYPE_VSCPD_TIMER_STARTED
A timer has been started.

Argument is timer ID and start time for the timer. 

 | Byte | Description                                        | 
 | :----: | -----------                                        | 
 | 0    | 32 bit timer ID. MSB.                              | 
 | 1    | 32 bit timer ID.                                   | 
 | 2    | 32 bit timer ID.                                   | 
 | 3    | 32 bit timer ID. LSB.                              | 
 | 4    | Start time in milliseconds as a 32-bit value. MSB. | 
 | 5    | Start time in milliseconds as a 32-bit value.      | 
 | 6    | Start time in milliseconds as a 32-bit value.      | 
 | 7    | Start time in milliseconds as a 32-bit value. LSB. | 

Max timer value is about 49 days. 
----

## <a name="type26">Type=26 (0x1A) - Timer paused</a>
    VSCP2_TYPE_VSCPD_TIMER_PAUSED
A timer has been paused.

Argument is timer ID and time when timer was paused. 

 | Byte | Description                                        | 
 | :----: | -----------                                        | 
 | 0    | 32 bit timer ID. MSB.                              | 
 | 1    | 32 bit timer ID.                                   | 
 | 2    | 32 bit timer ID.                                   | 
 | 3    | 32 bit timer ID. LSB.                              | 
 | 4    | Start time in milliseconds as a 32-bit value. MSB. | 
 | 5    | Start time in milliseconds as a 32-bit value.      | 
 | 6    | Start time in milliseconds as a 32-bit value.      | 
 | 7    | Start time in milliseconds as a 32-bit value. LSB  | 

----

## <a name="type27">Type=27 (0x1B) - Timer resumed</a>
    VSCP2_TYPE_VSCPD_TIMER_RESUMED
A timer has been restarted.

Argument is timer ID and time when timer was restarted. 

 | Byte | Description                                        | 
 | :----: | -----------                                        | 
 | 0    | 32 bit timer ID. MSB.                              | 
 | 1    | 32 bit timer ID.                                   | 
 | 2    | 32 bit timer ID.                                   | 
 | 3    | 32 bit timer ID. LSB.                              | 
 | 4    | Start time in milliseconds as a 32-bit value. MSB. | 
 | 5    | Start time in milliseconds as a 32-bit value.      | 
 | 6    | Start time in milliseconds as a 32-bit value.      | 
 | 7    | Start time in milliseconds as a 32-bit value. LSB. | 

----

## <a name="type28">Type=28 (0x1C) - Timer stopped</a>
    VSCP2_TYPE_VSCPD_TIMER_STOPPED
A timer has been stopped.

Argument is timer ID and time when timer was stopped. 

 | Byte | Description                                        | 
 | :----: | -----------                                        | 
 | 0    | 32 bit timer ID. MSB.                              | 
 | 1    | 32 bit timer ID.                                   | 
 | 2    | 32 bit timer ID.                                   | 
 | 3    | 32 bit timer ID. LSB.                              | 
 | 4    | Start time in milliseconds as a 32-bit value. MSB. | 
 | 5    | Start time in milliseconds as a 32-bit value.      | 
 | 6    | Start time in milliseconds as a 32-bit value.      | 
 | 7    | Start time in milliseconds as a 32-bit value. LSB. | 

----

## <a name="type29">Type=29 (0x1D) - Timer Elapsed</a>
    VSCP2_TYPE_VSCPD_TIMER_ELLAPSED
A timer has elapsed.

Argument is timer ID. 

 | Byte | Description           | 
 | :----: | -----------           | 
 | 0    | 32 bit timer ID. MSB. | 
 | 1    | 32 bit timer ID.      | 
 | 2    | 32 bit timer ID.      | 
 | 3    | 32 bit timer ID. LSB. | 

----

## <a name="type30">Type=30 (0x1E) - New Calculations</a>
    VSCP2_TYPE_VSCPD_NEW_CALCULATION
This event will be sent once each 24 hours when new astronomical calculations has been performed. The event can be useful if one need to do things when the sunrise/sunset etc times changes.

----

{% include "./bottom_copyright.md" %}
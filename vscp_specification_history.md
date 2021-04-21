# VSCP Specification history

 | Date       | By   | Description |
 | ---------- | ---- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
 | 2021-04-21 | AKHE | Added VSCP_CLASS1_MEASUREMENT, VSCP_TYPE_MEASUREMENT_REACTIVE_POWER (64) |
 | 2021-04-21 | AKHE | Added VSCP_CLASS1_MEASUREMENT, VSCP_TYPE_MEASUREMENT_REACTIVE_ENERGY (65) |
 | 2021-04-21 | AKHE | Added VSCP_CLASS1_INFORMATION, VSCP_TYPE_INFORMATION_PROXIMITY_DETECTED (88) |
 | 2021-04-21 | AKHE | Default uint for VSCP_CLASS1_MEASUREMENT, VSCP_TYPE_MEASUREMENT_POWER_FACTOR is changed to cos angel |
 | 2021-03-12 | AKHE | Added new section definitions. |
 | 2021-03-12 | AKHE | Corrected header definition for Raw Ethernet/Muilticast and UDP. |
 | 2021-01-17 | AKHE | Added comments about detecting VSCP format when frame is sent over MQTT. |
 | 2020-12-14 | AKHE | Added CLASS2.LEVEL1.MEASUREMENT,VSCP_TYPE_MEASUREMENT_POWER_FACTOR.  Added Watt hours added as a convenience unit to energy. Added CLASS1.SECURTITY, VSCP_TYPE_SECURITY_GAS. Added CLASS1.SECURITY, VSCP_TYPE_SECURITY_VIBRATION, Added Added CLASS1.SECURITY,VSCP_TYPE_SECURITY_IN_MOTION and Added CLASS1.SECURITY,VSCP_TYPE_SECURITY_NOT IN_MOTION. As suggested by Maarten Zanders. |
 | 2020-12-02 | AKHE | Skipped the directional topic notation for MQTT as suggested by Maarten Zanders |
 | 2020-12-02 | Troky | Added increment/decrement events. 30.52/30.53/20.86/20.87 |
 | 2020-12-02 | Troky | Fixed formatting |
 | 2020-12-01 | AKHE | Added CLASS1.CONFIGURATION class after suggestion from Troky | 
 | 2020-11-30 | AKHE | Changed MQTT "miso"/"mosi" MQTT notation to "->"/"<-" to get rid of "master" confusion | 
 | 2020-11-25 | AKHE | Added info about optional measurement info in JSON and XML frames. | 
 | 2020-10-06 | AKHE | Corrected MQTT format so it is valid. Added topic recommendations. |
 | 2020-06-15 | AKHE | Added data coding for 64-bit float. |
 | 2020-05-20 | AKHE | Added example to data coding description for 32-bit float. |
 | 2020-05-17 | AKHE | Some extended measurement events was missing in level I over level II space |
  Measurement section added. 1.11.3 |
 | 2020-03-25 | AKHE | VSCP_TYPE_INFORMATION_ENTER and VSCP_TYPE_INFORMATION_EXIT added after suggestion from Troky. 1.11.2 |
 | 2020-03-04 | AKHE  | Fixed format for JSON VSCP Event definition. Fixed links to other docs.  1.11.1 |
 | 2020-02-20 | AKHE  | XML and JSON format changed to be consistent with all code. |
 | 2020-01-23 | AKHE  | Multipart HLO frames are no more |
 | 2020-01-21 | AKHE | Encryption added to HLO events. |
 | 2020-01-02 | AKHE | Version 1.10.19 |
 | 2020-01-02 | AKHE | HLO objects moved to it's own class (1028) - Version 1.10.19 |
 | 2019-11-07 | AKHE | Added CLASS2.PROTOCOL, Type=42, High Level Object |
 | 2019-11-01 | AKHE | Added the measurement extension classes. Added Level III driver internal events. |
 | 2019-10-05 | AKHE | Clarified byte order. |
| 2019-10-15 | AKHE | Added new events to CLASS1.SECURITY and CLASS1.CONTROL suggested by troky. |
| 2019-10-09 | AKHE | Added hex to VSCP over serial frames |
| 2019-10-08 | AKHE | Assigned new GUID |
| 2019-09-25 | AKHE | Added class1.control, Type=44, VSCP_TYPE_CONTROL_PWM suggested by 'troky' |
| 2019-09-23 | AKHE | CLASS1.ALARM, Byte 0 changed to original. |
| 2019-08-29 | AKHE | CLASS1.DATA, Type=5, Signal Strength, new unit = 2 is dBm |
 | 2019-08-21 | AKHE | Added note about JSON/XML packed events and corrected info about XML timestamp. |
| 2019-08-19 | AKHE | CLASS1.WEATHER/CLASS1.WEATHER_FORECAST Type=52 index/zone/subzone added for consistency |
 | 2019-08-16 | AKHE | CLASS1.WEATHER/CLASS1.WEATHER_FORECAST Type=52 UV Index added |
 | 2019-05-27 | AKHE | Server capabilities code now include 'variables', 'DM' and 'interfaces'. CLASS1024, Type=20 and WCYD command for tcp/ip link. |
 | 2019-04-02 | AKHE | JSON representation for VSCP event corrected. |
 | 2018-10-18 | AKHE | Added CLASS1.INFORMATION, Type=80, "Updated" |
 | 2018-10-04 | AKHE | Added CLASS1.ALARM, Type = 12, VSCP_TYPE_ALARM_WATCHDOG. Fixed reported typo. |
 | 2018-10-03 | AKHE | CLASS1.INFORMATION, Type=77 Date/time bitfields corrected. |
 | 2018-09-21 | AKHE | Added CLASS1.INFORMATION, Type=78/70 RISING/FALLING. |
 | 2018-05-18 | AKHE | Added reserved GUID for groups (16-bits). |
 | 2018-04-17 | AKHE | Added [CLASS1.INFORMATION, Type=77](./class1.information.md#type_77_0x4d_datetime) which combines date and time in one event. |
 | 2018-04-16 | AKHE | Clarified that time is give in UTC. |
 | 2018-03-04 | AKHE | Max data size for Level II events is changed from 487 to 512 to make things simpler. |
 | 2018-02-18 | AKHE | New [raw ethernet frame](./vscp_over_ethernet_raw_ethernet.md) specified  |
 | 2018-02-09 | AKHE | Bit 14 in head is now a flag for a dumb node. A dumb node does not have registers, mdf etc. |
 | 2018-02-05 | AKHE | [CLASS1.CONTROL, Type=42, Lock](./class1.control.md#type_42_0x2a_lock) and  [CLASS1.CONTROL, Type=43, Unlock](./class1.control.md#type_43_0x2b_unlock) and [CLASS1.INFORMATION, Type=75, Lock](./class1.information.md#type_75_0x4b_lock) and [CLASS1.INFORMATION, Type=76, Unlock](./class1.information.md#type_76_0x4c_unlock) |
 | 2017-12-07 | AKHE | Simplified license section. |
 | 2017-09-11 | AKHE | [ CLASS1.DATA Type=4](./class1.data.md#type_4_0x04_relative_strength ) units changed.                                                                                                                                                                                                                                                                                                                                                                                                            |
 | 2017-09-10 | AKHE | New coding units added for [CLASS1.DATA Type=4](./class1.data.md#type_4_0x04_relative_strength) - db (decibel), dbuv (decibel microvolts), dbmv   (decibel millivolts). Creds: Stuart O'Reilly |
 | 2017-07-28 | AKHE | [CLASS1.ALARM](./class1.alarm.md) now have byte 1 specified as "0=off. 1=on" in first byte. |
 | 2017-07-04 | AKHE | Added event [CLASS2.PROOCOL, Type=32, Level II who is there response](./class2.protocol.md#type_32_0x20_level_ii_who_is_there_response) |
 | 2017-07-04 | AKHE | Clarified CLASS1.PROTOCOL, Type=16 and fixed typo for CLASS1.PROTOCOL, Type=25   |
 | 2017-06-28 | AKHE | Clarified CLASS1.PROTOCOL, Type=2 New node online for Level II. |
 | 2017-06-14 | AKHE | UDP and Multicast frames was missing century byte. |
 | 2017-05-30 | AKHE | The Multicast and UDP frames now contain the UTC time block just as the VSCP events do. Encryption codes defined for UDP/Multicast. |
 | 2017-01-12 | AKHE | CLASS1.MEASUREZONE(65) and CLASS1.SETVALUEZONE(85) had wrong description of data content |
 | 2016-12-29 | AKHE | Added new classes \\ CLASS1.MEASUREMENT, VSCP_TYPE_MEASUREMENT_SOUND_DENSITY, 59 \\  CLASS1.MEASUREMENT, VSCP_TYPE_MEASUREMENT_SOUND_LEVEL,60 \\  CLASS1.DIAGNOSTIC, VSCP_TYPE_DIAGNOSTIC_EXT_IC_FAIL,79 \\  CLASS1.ALARM, VSCP_TYPE_ALARM_ARM,10 \\ CLASS1.ALARM, VSCP_TYPE_ALARM_DISARM,11 \\ CLASS1.INFORMATION, VSCP_TYPE_INFORMATION_DATE,72 \\  CLASS1.INFORMATION, VSCP_TYPE_INFORMATION_TIME,73 \\ CLASS1.INFORMATION, VSCP_TYPE_INFORMATION_WEEKDAY,74  |
 | 2016-10-11 | AKHE | Preliminary info about [Setup screens](./vscp_module_description_file.md#setup_screens) added. |
 | 2016-03-23 | AKHE | Added some more descriptive text to the logging class [CLASS1.LOG](./class1.log.md#description) |
 | 2016-03-18 | AKHE | Added new event CLASS2.VSCPD, New Calculation (30) |
 | 2016-02-11 | AKHE | Added some more info about the string measurement format CLASS2.MEASUREMENT_STR   |
 | 2016-01-13 | AKHE | Added JSON event spec. (./level_ii_specifics#json_representation.md) and measurement optional tags |
 | 2015-11-18 | AKHE | Abstraction types listed/defined [here](vscp_register_abstraction_model.md#abstractions) |
 | 2015-10-23 | AKHE | Allow for real text name to appear in heat beat data for a Level II node  |
 | 2015-10-21 | AKHE | Added CLASS2.INFORMATION, Type=3 (0x03) Proxy heart beat.  |
 | 2015-10-21 | AKHE | Added CLASS2.PROTOCOL, Type=20 (0x14) High end server capabilities  |
 | 2015-10-14 | AKHE | [ CLASS1_PROTOCOL, Type=28 High End Server Response](,/class1.protocol.md#type_28_0x1c_high_end_server_response ) have changed capabilities bit values. |
 | 2015-09-10 | AKHE | [ CLASS1_INFORMATION, Type = 9 (0x09) Node Heartbeat](./class1.information.md#type_9_0x09_node_heartbeat ) is now mandatory for all Level I nodes. For Level 2 nodes [ CLASS1_INFORMATION, Type=2 (0x0002) Level II Node Heartbeat](./class2.information.md#type_2_0x0002_level_ii_node_heartbeat ) is now  |
 | 2015-09-10 | AKHE | [Level II Class=1040 (0x410) Measurement string](./class2.measurement_str.md#description) have unit byte increased to 255 instead of 3. |
 | 2015-07-07 | AKHE | Cleared up define of data byte for CLASS1.DATA. Added CLASS1.DATA, Type=6, Count. KWh is optional unit 1 for energy. |
 | 2015-06-26 | AKHE | Introduces [Setup Recipes](./vscp_module_description_file.md&#setup_recipes) |
 | 2015-06-17 | AKHE | Extended read now can read 256 registers. Suggested by Stefan Langer. Bursts of events is now sent with lowest priority. |
 | 2015-05-22 | AKHE | Changed meaning for CLASS1.DIAGNOSTIC Type 53 and 64.  |
 | 2015-05-22 | AKHE | CLASS1.DIAGNOSTIC and CLASS1.ERROR added. CLASS1.SECURITY, Type=20, Tamper added. |
 | 2015-05-21 | AKHE | Added events CLASS1.INFORMATION, Type=59-68 and CLASS1.CONTROL, Type=34-39   |
 | 2015-05-17 | AKHE | Clarified the use of id in CLASS1.LOG  |
 | 2015-04-23 | AKHE | Register tags and attributes explained. |
 | 2015-04-23 | AKHE | fgcolor and bgcolor can now be set as register attributes.  |
 | 2015-04-21 | AKHE | Added register blocks (type/size attributes) to mdf specification.  |
 | 2015-04-09 | AKHE | GUID **FF:FF:FF:FF:FF:FF:FF:F7:00:00:00:00:00:00:00:00**  series reserved for VSCP & Friends demo code |
 | 2015-04-03 | AKHE | Added information on how to embed HTML inside mdf tags.  |
 | 2015-03-03 | AKHE | Added warning about end to end data rate for CLASS1.PROTOCOL, Type=36 (0x24) Embedded MDF response.  |
 | 2015-02-24 | AKHE | It's now possible to have several frames sent as payload inside a serial frame. Also there is a capabilities request/response pair defined to be able to ask capabilities from a device. |
 | 2013-10-13 | AKHE | Class 1026 (0x402) Level II Information, Type=2 Heart Beat added   |
 | 2014-10-01 | AKHE | CLASS1.INFORMATION, VSCP_TYPE_INFORMATION_CALCULATED_NOON added.  |
 | 2014-09-30 | AKHE | 1.10.12 Public. |
 | 2014-09-29 | AKHE | Added new types to CLASS1.INFORMATION                         VSCP_TYPE_INFORMATION_NAUTICAL_SUNRISE_TWILIGHT_START =54                    VSCP_TYPE_INFORMATION_NAUTICAL_SUNSET_TWILIGHT_START        =55                       VSCP_TYPE_INFORMATION_ASTRONOMICAL_SUNRISE_TWILIGHT_START=56             VSCP_TYPE_INFORMATION_ASTRONOMICAL_SUNSET_TWILIGHT_START=57  |
 | 2014-09-28 | AKHE | 1.10.11 Added class CLASS1.WEATHER and CLASS2.WEATHER_FORECAST. Added CLASS1.INFORMATION, Type=52, Civil sunrise twilight time and CLASS1.INFORMATION, Type=53, Civil sunset twilight time. Removed CLASS1.ONEWIRE, CLASS1.X10, CLASS1.LON, CLASS1.EIB, CLASS1.SNAP, CLASS1.CBUS. Classes will remain reserved so users using them can continue to do so. |
 | 2014-09-16 | AKHE | Added info about TABLE commands to tcp/ip interface documentation. Added info about udp port config settings and changed tcp port settings so they now are correct.   |
 | 2014-09-15 | AKHE | Added info about the QUITLOOP command.  |
 | 2014-09-04 | AKHE | Described the websocket authentication process.  |
 | 2014-09-04 | AKHE | added auth property to websocket setting. Removed port. Now the same port is used both for webserver and or for websockets. |
 | 2014-08-29 | AKHE | Added CLASS1.CONTROL Type=33 (0x21) Big Change level and CLASS1.INFORMATION Type=51 (0x33) Big Level Changed  |
 | 2014-02-26 | AKHE | Added info about "authdomin" in configuration files. |
 | 2014-08-26 | AKHE | 1.10.9 Added missing codes for actions.  |
 | 2014-09-28 | AKHE | Added CLASS1.WATHER amd CLASS1.WATHER_FORECAST Removed CLASS1.ONEWIRE, CLASS1.X10,  CLASS1.LON, CLASS1.EIB, CLASS1.SNAP, CLASS1.CBUS   |
 | 2014-08-19 | AKHE | 1.10.8  |
 | 2014-08-12 | AKHE | Fixed action substitute table. |
 | 2014-08-07 | AKHE | RS-232 protocol final. |
 | 2014-08-04 | AKHE | VSCPGetStatus method added to the Level II interface. Also introduced the limited Level II driver. |
 | 2014-04-16 | AKHE | Added info about where to find websocket samples and HTML framework.  |
 | 2014-04-12 | AKHE | Added missing variable types. Cleared description of tcp/ip protocols. Added some initial info about the bumblebee and the droplet protocols. Started a description of VSCP over MQTT, VSCP REST and VSCP TEXT  |
 | 2014-04-03 | AKHE | Added `<redirect>` tag to mdf. |
 | 2014-03-31 | AKHE | 1.10.4  |
 | 2014-03-23 | AKHE | Added CLASS1.MEASUREMENT32 which mimic CLASS1.MEASUREMENT but has a single precision floating point value and the data coding byte as data. |
 | 2014-02-28 | AKHE | Proofreading fixes by Andreas Merkle  |
 | 2013-11-08 | AKHE | Added new register 162 that restores default configuration. Version 1.10.0 |
 | 2013-10-17 | AKHE | Added info about new action parameter escapes. %event.class.str - Class as textstring %event.type.str - Type as teststring %measurement.float - measurement as a float %measurement.string - meaurements as a string %eventdata.realtext	- Try to display event data in a human readable form. |
 | 2013-09-04 | AKHE | Added info about webpage extension in drivers.  |
 | 2013-07-23 | AKHE | Added info about mimetypes path in VSCP daemon configuration section.  |
 | 2013-07-17 | AKHE | Clarified Loglevel: now 0-8. Can use numeric or textual form. |
 | 2013-07-16 | AKHE | Added info about the thermometer widget. |
 | 2013-07-11 | AKHE | Explained how GUID's are formed for interfaces in the GUID configuration setting for the VSCP daemon.   |
 | 2013-07-01 | AKHE | Added info about VSCPBlockingSend and VSCPBlockingReceive additions in the Level II API. |
 | 2013-06-27 | AKHE | Added new section 16 HTML5 websocket - widgets describing the HTML5 websocket widgets.  |
 | 2013-06-24 | AKHE | Class=85 (0x55) Set value with zone added. Clarified that string measurement value still represent a numeric value. |
 | 2013-06-19 | AKHE | Missed originating address in RS-485/422 packages added.  |
 | 2013-05-30 | AKHE | Added info about MQTT driver.  |
 | 2013-05-29 | AKHE | Removed host,port,username and password common variables for level II drivers. |
 | 2013-05-28 | AKHE | rootpath changed to webrootpath in configuration file Examples of configuration added to Level II drivers Info about tcp/ip driver added.  |
 | 2013-05-27 | AKHE | 1.9.4   |
 | 2013-05-27 | AKHE | lmsensors driver and socketcan driver described. |
 | 2013-05-24 | AKHE | OHAS Section removed. Stepped to 1.9.3  |
 | 2013-05-13 | AKHE | Changed Level II Driver interface. "flags" parameter in open method removed.  |
 | 2013-04-09 | AKHE | Added device family registers and device type registers.canal and vscp header removed. Stepped version to 1.9.0  |
 | 2012-09-21 | AKHE | GUID is now at first position in data for CLASS2.PROTOCOL. Read/write and readwriterespons is affected. CLASS2.PROTOCOL config-events has been removed.  |
 | 2012-03-27 | AKHE | Added info about new switches to the VSCP daemon configuration. |
 | 2012-03-27 | AKHE | Frank Sautter fixes * made some clarification to the normalized integers * removed some spelling errors * removed a lot of greengrocers's apostrophes * ID, GUID and hex values consistently uppercase * '0\texttimes{}' to '0x' Reversion history moved here |
 | 2012-02-22 | AKHE | Added descriptions of indexed arrays in register space for a module to the mdf xml descriptions. |
 | 2012-02-15 | AKHE | Added two extra bytes to Type = 8 (0x08) Drop nickname-ID / Reset Device. One for delayed statup and one for controlflags. Suggested by Stefan Langer. |
 | 2011-04-26 | AKHE | Added Class=65 (0x41) index,zone,sub-zone measurement.  |
 | 2011-04-20 | AKHE | Added type CLASS1.CONTROL Type = 32 (0x20) Set country/language.  |
 | 2011-02-08 | AKHE | Added Class=60 (0x3C) Floating point measurement. |
 | 2010-06-15 | AKHE | CLASS =0,Protocol Type = 32 (0x20) Who is there response had a typo where index byte had gone lost. Fixed.  |
 | 2010-06-15 | AKHE | Bit 30 in control word for 32-bit DM is obsolete and has been removed. (This is therefore no longer true GUID should be checked (=1) or not checked (=0). Action Param should start with GUID at offset).  |
 | 2010-02-20 | AKHE | Added firmware tag to mdf specification. |
 | 2009-10-11 | AKHE | Added node capabilities byte to Class=0, Type = 27 (0x1B) High end server probe.  |
 | 2009-07-12 | AKHE | Added deamon internal timer events.  |
 | 2009-03-06 | AKHE | Changed recommended voltage level from 9-16V to 9-28V   |
 | 2009-03-06 | AKHE | Added some firmware uploader ack/nack events.  |
 | 2008-10-24 | AKHE | Added some new tokens. Version stepped to 1.5.6 |
 | 2008-10-20 | AKHE | Version stepped to 1.5.5  |
 | 2008-10-20 | AKHE | VSCP over MiWi added. |
 | 2008-10-20 | AKHE | CLASS1.PROTOCOL, Type=40 Get Event interest and CLASS1.PROTOCOL, Type=41 Get Event interest response has been added. |
 | 2008-10-20 | AKHE | CLASS1.INFORMATION, Type=50, 0x32 Overflow has been added. |
 | 2008-08-30 | AKHE | CLASS1.INFORMATION, Type=49, 0x31 Detect has been added.  |
 | 2008-07-04 | AKHE | Rearranged the Extended Page read/write events fully. |
 | 2008-07-01 | AKHE | CLASS1.PROTOCOL, Type = 32 (0x20) Who is there response. inserted because it it was previously missed.  |
 | 2008-06-26 | AKHE | Added Class=50 (0x32) Alert On LAN and Ethernet low level protocol description.  |
 | 2008-06-12 | AKHE | CLASS1.MEASUREMENT, Type=48 removed as it was a duplicate for Type=24  |
 | 2008-05-17 | AKHE | The recommended bitrate over CAN is changed from 500 kbps to 125 kbps. o Class=0, Type = 31 (0x1F) Who is there? Is now mandatory. o Class=0, Type = 36 (0x24) Extended Read register. Is now mandatory. o Class=0, Type = 37 (0x25) Extended Read/Write response. Is now mandatory. o Class=0, Type = 38 (0x26) Extended Write Register. Is now mandatory. o Class=0, Type = 39 (0x27) Extended Page Read. Is now mandatory. o Class=0, Type = 40 (0x28) Extended Page Write. Is now mandatory. |
 | 2008-04-20 | AKHE | New common register added ( 153/0x99 ) Number of register pages used.  |
 | 2007-11-04 | AKHE | Added wireless class + GPS events. |
 | 2007-10-29 | AKHE | Sunrise/Sunset events added for Class=20 (0x14) Information  |
 | 2007-05-04 | AKHE | Changed MDF types to ISO types. |
 | 2007-05-03 | AKHE | Added Bluetooth type to CLASS1.INFORMATION, Type=37 for Bluetooth proximity.  |
 | 2006-04-24 | AKHE | Event CLASS1.INFORMATION, Action Trigger (43) has been added.   |
 | 2005-09-01 | AKHE | Spec moved to wiki. Version 1.40. Added a switch to the DM control for VSCP Level II that can be used to mark the ending row in the current decision matrix matrix. This can save a lot of time for the EDA parsing especially if the matrix is in external EEPROM.   |
 | 2005-05-11 | AKHE | First version of multimedia class added. Better explanation of paged read/write * Max buffer size introduced for device. * Decision matris format for Level I/Level II fina. * Paged DM introduced to save register space. * Replaced 32.bit CRC with 16-bit CRC for VSCP bootloader. * Clarified CLASS1.PROTOCOL * Event “Measurement Request “ added. * Event Chan Level/Relative Change Level added.                                                                                        |
 | 2005-02-15 | AKHE | Fixed typo in CLASS.CONTROL TYPE=9  |
 | 2005-02-15 | AKHE | Bootloader support Register No bootloader suppoert = 0xFF instead of 0x00. |
 | 2005-02-06 | AKHE | Many, many changes and fixes. Mostly additions to Level II texts.  |
 | 2005-01-15 | AKHE | CAN standard speed changed to 500 kbps.   |
 | 2004-12-14 | AKHE | Fixed an error in the data specification format byte definition.  |
 | 2004-12-05 | AKHE | English proofreading done. Some new events added for logging.   |
 | 2004-09-21 | AKHE | Clarified the UDP package format. |
 | 2004-09-21 | AKHE | index added for data and event class. |
 | 2004-09-20 | AKHE | Bootloade rinfo in XML data. |
 | 2004-08-26 | AKHE | Page Read/Write final.  |
 | 2004-08-26 | AKHE | Register assigned for boot loader algorithm. |
 | 2004-08-26 | AKHE | GPS event added. |
 | 2004-08-26 | AKHE | Module description file final. |
 | 2004-08-26 | AKHE | Decision Matrix definition for uP final. |
 | 2004-06-21 | AKHE | Added the database message for the phone class. Page read/write added. 2004-08-26 – Clarified the hard coded bit and the functionality.  |
 | 2004-06-11 | AKHE | X10 Message detail added. M.U.M.I.N. class replaced with CBUS class.  |
 | 2004-06-11 | AKHE | Dusk and Dawn events added.  |
 | 2004-06-11 | AKHE | EDA Decision matrix format for uP added. Also control function to get size and offset to the decision matrix.  |
 | 2004-06-05 | AKHE | SYNC and CRC removed from Ethernet packages. |
 | 2004-06-01 | AKHE | The initial reminder for the CCITT checksum was wrong (0x0000 instead of 0xFFFF).  |
 | 2004-06-01 | AKHE | Fahrenheit allowed as an optional unit for temperature.  |
 | 2004-06-01 | AKHE | Private GUID has been defines that can be used in the same way as 192.168.0.0 and 10.0.0.0 is used on the Internet.  |
 | 2004-06-01 | AKHE | For Level II messages the data part must not be larger then 487 bytes (512-25), This was previously 1024 bytes but a total package size of 512 bytes should not be to avoid fragmentation problems. |
 | 2004-05-27 | AKHE | Fixed typo- in appendix A where the reserved GUIDs ranges was wrong.  |
 | 2004-04-07 | AKHE | read & write did not have the destination address given. This is now in byte 0.  |
 | 2004-04-06 | AKHE | Full address field used 1-254 instead of 1-127. 0x00 is reserved for master. 0xFF is reserved for a node with no nickname assigned.   |
 | 2004-04-06 | AKHE | Start for GUID storage should be 0xD0.   |
 | 2004-04-05 | AKHE | Fixed typo max 100 meters should be 500 meters.  |
 | 2004-01-26 | AKHE | Level 2 introduced. 2004-03-01 — Settled for master less solution.  |
 | 2004-10-22 | AKHE | A all lights on/off and a dimmer control type added. |

[filename](./bottom_copyright.md ':include')

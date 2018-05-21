# Summary

## Introduction

* [About this document](README.md)
* [VSCP - what is it?](introduction.md)

## Essential VSCP Parts

*  [VSCP Level I Specifics](vscp_level_i_specifics.md)
*  [VSCP Level II Specifics](level_ii_specifics.md)
*  [Globally Unique Identifiers GUID](globally_unique_identifiers.md)
*  [Register Abstraction Model](register_abstraction_model.md)
*  [Decision Matrix](decision_matrix.md)
*  [Data coding](data_coding.md)
*  [Module Description File - MDF](module_description_file.md)
*  [VSCP boot loader algorithm](vscp_boot_loader_algorithm.md)
*  [VSCP Multicast](vscp_multicast.md)


## Transport protocols used by VSCP

* [Low level protocols](physical_level_lower_level_protocols.md)
    *  [Dumb nodes](vscp_dumb.md)
    *  [VSCP over TCP/IP](vscp_over_tcp_ip.md)
    *  [VSCP over Ethernet (raw Ethernet)](vscp_over_ethernet_raw_ethernet.md)
    *  [VSCP over UDP](vscp_over_udp.md)
    *  [VSCP over TCP/IP Multicast](vscp_over_tcp_ip_multicast.md)
    *  [VSCP over websocket](vscp_websocket.md)
    *  [VSCP over RESTful interface](vscp_rest.md)
    *  [VSCP over CAN (CAN4VSCP)](vscp_over_can_can4vscp.md)
    *  [VSCP over a serial channel (RS-232)](vscp_over_a_serial_channel_rs-232.md)
    *  [VSCP Level I over RS-485/RS-422](vscp_level_i_over_rs-485_rs-422.md)
    *  [VSCP over Bluetooth mesh](vscp_over_bt_mesh.md)
    *  [VSCP over IEEE 802.15.4](vscp_over_ieee_802.15.4.md)
    *  [VSCP Droplet model](vscp_droplet_model.md)
    *  [VSCP BumbleBeez Protocol](vscp_bumblebeez_protocol.md)
    *  [VSCP over MQTT](vscp_over_mqtt.md)
    *  [VSCP Text](vscp_text.md)



## Level I events

*  [Level I Events](level_i_events.md)
*  [CLASS1.PROTOCOL(0)](class1.protocol.md)
*  [CLASS1.ALARM(1)](class1.alarm.md)
*  [CLASS1.SECURITY(2)](class1.security.md)
*  [CLASS1.MEASUREMENT(10)](class1.measurement.md)
*  [CLASS1.DATA(15)](class1.data.md)
*  [CLASS1.INFORMATION(20)](class1.information.md)
*  [CLASS1.CONTROL(30)](class1.control.md)
*  [CLASS1.MULTIMEDIA(28)](class1.multimedia.md)
*  [CLASS1.AOL(50)](class1.aol.md)
*  [CLASS1.MEASUREMENT64(60)](class1.measurement64.md)
*  [CLASS1.MEASUREZONE(65)](class1.measurezone.md)
*  [CLASS1.MEASUREMENT32(70)](class1.measurement32.md)
*  [CLASS1.SETVALUEZONE(85)](class1.setvaluezone.md)
*  [CLASS1.WEATHER(90)](class1.weather.md)
*  [CLASS1.WEATHER_FORECAST(95)](class1.weather_forecast.md)
*  [CLASS1.PHONE(100)](class1.phone.md)
*  [CLASS1.DISPLAY(102)](class1.display.md)
*  [CLASS1.IR(110)](class1.ir.md)
*  [CLASS1.GPS(206)](class1.gps.md)
*  [CLASS1.WIRELESS(212)](class1.wireless.md)
*  [CLASS1.DIAGNOSTIC(506)](class1.diagnostic.md)
*  [CLASS1.ERROR(508)](class1.error.md)
*  [CLASS1.LOG(509)](class1.log.md)
*  [CLASS1.LABORATORY(510)](class1.laboratory.md)
*  [CLASS1.LOCAL(511)](class1.local.md)


## Level II events

*  [Level II Events](level_ii_events.md)
*  [CLASS2.PROTOCOL1(512)](class2.protocol1.md)
*  [CLASS2.PROTOCOL(1024)](class2.protocol.md)
*  [CLASS2.CONTROL(1025)](class2.control.md)
*  [CLASS2.INFORMATION(1026)](class2.information.md)
*  [CLASS2.TEXT2SPEECH(1027)](class2.text2speech.md)
*  [CLASS2.CUSTOM(1029)](class2.custom.md)
*  [CLASS2.DISPLAY(1030)](class2.display.md)
*  [CLASS2.MEASUREMENT_STR(1040)](class2.measurement_str.md)
*  [CLASS2.MEASUREMENT_FLOAT(1060)](class2.measurement_float.md)
*  [CLASS2.VSCPD(65535)](class2.vscpd.md)
           

## Appendix

*  [Appendix A - Assigned GUIDs](appendix_a.md)
*  [Specification history](vscp_specification_history.md)

## Other documentation**

*  [VSCP Server](https///www.vscp.org/docs/vscpd/doku.php?id=start)
*  [VSCP Helper lib](https///www.vscp.org/docs/vscphelper/doku.php?id=start)
*  [VSCP Works](https///www.vscp.org/docs/vscpworks/doku.php?id=start)
*  [VSCP Firmware](https///www.vscp.org/docs/vscpfirmware/doku.php)
*  [VSCP L1 Framework](https///github.com/BlueAndi/vscp-framework/blob/master/README.md)
*  [VSCP Arduino](https///github.com/BlueAndi/vscp-arduino)
*  [VSCP Javascript lib.](https///www.vscp.org/docs/html5/doku.php)
*  [VSCP HTML demo](https///www.vscp.org/docs/html5/doku.php)
*  [General VSCP wiki](https///www.vscp.org/wiki/doku.php)
# VSCP TEXT

** Experimental**

VSCP events sent over text links of any kind such as email, SMS or even an uploaded text file over a ftp-link is just standard events with abbreviations where abbreviations are human readable commands and responses that is used instead of GUID's, zones, subzones and events. Typically a user can send an SMS with 

    READ TEMPERATURE IN KITCHEN 

and get the read temperature reported back.

The first and most important is the event style.

    head,class,type,obid,datetime,time-stamp,GUID,data1,data2,data3....

That is a line started with a number will be interpreted as an event of the above form. A hard way to send command but a method that still can be useful for M2M communication over text links. In the same way a line received over a VSCP text link with a number at the first position should be interpreted as a VSCP event. So in abbreviations one has to make sure that a temperature value response has a space or something in front of the number.

*A full description of this functionality will follow.*



{% include "./bottom_copyright.md" %}

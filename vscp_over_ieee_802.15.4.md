# VSCP over IEEE 802.15.4

**Preliminary Information. May change in future specifications.**

Two protocols are used over 802.15.4, VSCP Droplet protocol av VSCP BumbleBee protocol.

#### 802.15.4 payload usage

The 802.15.4 payload is max 122 bytes. This payload can carry one or more VSCP events. The first byte tell how many events there is in the frame. 

 | Byte              | Description                          | 
 | ----              | -----------                          | 
 | 0                 | Number of VSCP events in frame (1-x) | 
 | 1                 | Head (see below)                     | 
 | 2                 | VSCP class                           | 
 | 3                 | VSCP type                            | 
 | 4                 | Start of data. Max eight byte. Min 0 | 
 | 4 + datacount + 1 | head for next event if any           | 

##### Definition of head

 | Bits    | Description             | 
 | ----    | -----------             | 
 | 7,6,5   | Priority                | 
 | 4       | bit 9 of VSCP class     | 
 | 3,2,1,0 | reserved (Set to zero!) | 



\\ 
----
{{  ::copyright.png?400  |}}

`<HTML>``<p style="color:red;text-align:center;">``<a href="http://www.paradiseofthefrog.com">`Paradise of the Frog AB`</a>``</p>``</HTML>` 

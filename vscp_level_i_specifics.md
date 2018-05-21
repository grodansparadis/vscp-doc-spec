# VSCP Level I Specifics

## Level I Node types

On each segment there can be two kind of nodes. Dynamic and hard-coded. 

### Dynamic nodes

This is the most common node type. Dynamic nodes are VSCP nodes that confirm fully to the Level I part of this document. This means they have


*  a GUID. 

*  the register model implemented. 

*  all or most control events of class zero implemented. As a minimum register read/write should be implemented in addition to the events related to the nickname discovery. 

*  Have the hard coded bit in the ID is set to zero. 

*  Must react on PROBE event on its assigned address with a probe ACK and should send out the ACK with the hard coded bit set.

Sample implementations are available at [http://www.vscp.org ]

### Hard coded nodes

VSCP hard-coded nodes have a nickname that is set in hardware and cant be changed.

Very simple hard coded nodes can therefore be implemented. A node that sends out an event at certain times is typical and a button node that sends out an on-event when the button is pressed is another example. 

## Address or “nickname” assignment for Level I nodes

All nodes in a VSCP network segment need a way to get their nicknames IDs, this is called the nickname discovery process.

A VSCP Level 1 segment can have a maximum of 254 nodes + an additional 254 possible hard coded nodes. A segment can have a master that handles address or nickname assignment but this is not a requirement.

After a node has got its nickname-ID it should save this ID in permanent non-volatile storage and use it until it is told to stop using it. Even if a node forgets its nickname a segment controller must have a method to reassign the ID to the node. The master needs to store the nodes full address to accomplish this. 

### Node segment initialization. Dynamic nodes

In a segment where a new node is added the following scenario is used. 

##### Step 1

The process starts by pressing a button or similar on the node. If the node has a nickname assigned to it, it forgets this nickname and enters the initialization state. Uninitiated nodes use the reserved node-ID 0xFF. 

##### Step 2

The node sends a probe event (CLASS1.PROTOCOL, TYPE=2,[sub:CLASS1_PROTOCOL,TYPE=2, Probe]) to address 0 (the address reserved for the master of a segment) using 0xFF as its own address. The priority of this event is set to 0x07. The master (if available) now has a chance to assign a nickname to the node ((CLASS1.PROTOCOL, TYPE=2, [sub:CLASS1.PROTOCOL, TYPE=6, Set Nickname]). Five seconds may be a good interval for which this assignment should happen.

If no nickname assignment occurs the node checks the other possible nicknames (1-254) in turn. The node listens for a response event, probe ACK (CLASS1.PROTOCOL, TYPE=2, [sub:CLASS1_PROTOCOL,TYPE=3, Probe Ack]), from a node (which may already have the nickname assigned) for five seconds before concluding that the ID is free and then uses the ID as its own nickname-ID. On slower medium increase this timeout at will.

It is recommended that some visual indication is shown to indicate success. A blinking green led that turns steady green after a node has got its nickname is the recommended indication. If there is a response for all addresses a failure condition is set (segment full) and the node goes to sleep.

On an insecure medium such as RF (good practice also for CAN) it is recommended that the Probe is sent several time in a row to make sure that the nickname actually is free. This is actually a good method on all low level protocols and at least three tests are recommended. 

##### Step 3

After it assigns a nickname to itself the node sends nickname-ID accepted using its new nickname-ID to inform the segment of its identity. 

##### Step 4

It's now possible for other nodes to check the capabilities of this new node using read etc commands.

Only one node at the time can go through the initialization process.

The following picture shows the nickname discovery process for a newly added node on a segment



![VSCP Works](./images/1_home_akhe_vscp_spec_images_nickname_seq.jpg)


##### Node discovery

 1.  The node which initially has its nickname set to 0xFF probe for a segment controller. Class = 0, Type = 2 
 2.  No segment controller answers the probe and a new probe is therefore sent to a node with nickname=1. Again Class=0, Type=2. 
 3.  There is a node with nickname= 1 already on the segment and it answers the probe with “probe ACK” Class=0, Type=3. The initiating node now knows this nickname is already in use. 
 4.  A new probe is sent to a node with nickname=2. Again Class=0, Type=2. 
 5.  No ACK is received and the node concludes that the nickname=2 is free and assigns it to itself. It then sends a probe again with the new nickname assigned reporting a “new node on line”.

Before an installation in a large system it is better to preassigned IDs to the nodes. This is just done by connecting each of the nodes to a PC or similar and assigning IDs to each of them, one at the time. After that they can be installed at there location and will use this ID for the rest if there life or until told otherwise. 

### Node segment initialization. Hard coded nodes.

Things are a little different for hard coded nodes.

If a hard coded node has its address set in hardware it starts working on the segment immediately.

If the nickname discovery method is implemented it goes through the same steps (1-3) as the dynamic node. In this case all hard coded nodes on the segment must recognize and react on the probe-event.

The hard coded bit should always be set for a hard coded node regardless if the nickname discovery method is implemented or not. 

### Node segment initialization.. Silent dynamic nodes.

Sometimes it can be an advantage to build modules that start up as silent nodes. This is typical for a RS-485 or similar segment. This type of nodes only listen to traffic before they get initialized by a host. In this case the nickname discovery process is not started for a node when it is powered up for the first time. This type on node instead starts to listen for the CLASS1.PROTOCOL, Type=23 (GUID drop nickname-ID / reset device.) event. When this series of events is received and the GUID is the same as for the module the module starts the nickname discovery procedure as of above.

Using this method it is thus possible, for example, to let a user enter the GUID of a module and let some software search and initialize the node. As only the last four bytes of the GUID are unknown if the manufacturer GUID is known this is easy to enter for a user with the addition of a list box for the manufacturer.

The active nickname process is still a better choice as it allows for automatic node discovery without user intervention and should always be the first choice.

This is an example on the way it works

You have two nodes and assign unique IDs from there serial numbers


*  Node 1 have serial number 0001 

*  Node 2 have serial number 0002

Combined with your GUID this will be


*  Node 1 have GUID aa bb cc dd 00 00 00 00 00 00 00 00 00 00 00 01 

*  Node 2 have GUID aa bb cc dd 00 00 00 00 00 00 00 00 00 00 00 02

When you start up your nodes they see they don't have assigned nickname-ID (= 0xFF) so they just sit back and listen.

When your PC app. want to initialize the new nodes it sends


*  CLASS1.PROTOCOL Type 23 Data 00 aa bb cc dd

*  CLASS1.PROTOCOL Type 23 Data 01 00 00 00 00

*  CLASS1.PROTOCOL Type 23 Data 02 00 00 00 00

*  CLASS1.PROTOCOL Type 23 Data 03 00 00 00 01

At this stage your node knows it should enter the initialization phase and it will try to discover a new nickname using 0xFF as its nickname.

This will be several CLASS.PROTOCOL Type 2 staring with 0 (server) as the probe ID and increasing the probe ID as long as CLASS.PROTOCOL Type 3 is received (i.e other nodes say they use that id).

If this is the first node on the bus it will claim nickname-ID = 1. This ID should (normally( be stored in EEPROM and will be used without the sequence above next time the node is started.

The PC now continue with the other node sending


*  CLASS1.PROTOCOL Type 23 Data 00 aa bb cc dd

*  CLASS1.PROTOCOL Type 23 Data 01 00 00 00 00

*  CLASS1.PROTOCOL Type 23 Data 02 00 00 00 00

*  CLASS1.PROTOCOL Type 23 Data 03 00 00 00 02

and this node will start its initialization procedure and find a free ID.

Note that this process is only done the first time you put a fresh new node on a bus. Next time the ID the node finds will be used directly from the time the node starts up.

If you always have a PC present let it send CLASS1.PROTOCOL, Type 6 to the uninitialized node when the node send the probe to the server (.CLASS.PROTOCOL Type 2 with probe id=0xFF and origin 0xFF) 

### Examples

A typical scenario for a segment without a Master can be a big room where there are several switches to turn a light on or off. During the installation the switches are installed and initialized.

When each switch is initialized it checks the segment for a free nickname and grabs it and stores it in local non-volatile memory. By being connected to the segment the installer makes note of the IDs. It is of course also possible to set the nicknames to some desired value instead.

Additionally, VSCP aware relays are installed and also initialized to handle the actual switching of lighting. Again each in turn are initialized and the segment unique nickname noted.

At this stage the switches and the relay nodes have no connection with each other. One can press any switch and an on-event is sent on the segment but the relays don't know how to react on it.

We do this by entering some elements in the decision matrix of the relay nodes.


*  If on-event is received from node with nickname n1 set relay on. 

*  If on-event is received from node with nickname n2 set relay on. 

*  If on-event is received from node with nickname n3 set relay on.

etc and the same for off-event


*  If off-event is received from node with nickname n1 set relay off. 

*  If off-event is received from node with nickname n2 set relay off. 

*  If off-event is received from node with nickname n3 set relay off.

As the decision matrix also is stored in the nodes non volatile storage, the system is now coupled together in this way until changed sometime in the future.

To have switches in this way that send on and off events is not so smart when you have a visible indication (lights go on or off) and it would have been much better to let the switches send only an on-event and let the relay-node decide what to do. In this case the decision matrix would look:


*  If on-event is received from node with nickname n1 toggle relay state. 

*  If on-event is received from node with nickname n2 toggle relay state. 

*  If on-event is received from node with nickname n3 toggle relay state.

But how about a situation when we need a visual indication on the switch for instance? This can be typical when we turn a boiler or something like that off. The answer is simple. We just look for a event from the device we control. In the decision matrix of the switches we just enter


*  If on-event is received from node with nickname s1 - status light on. 

*  If off-event is received from node with nickname s1 - status light off.

It's very easy to add a switch to the scenario above and it can be even easier if the zone concepts are used. In this concept each switch on/off event add information on which zone it controls and the same change is done in the decision matrix we get something like:


*  If an on-event is received for zone x1 turn on relay.

We now get even more flexible when we need to add/change the setup.

What if I want to control the lights from my PC?

No problem just send the same on-event to the zone from the PC. The relay and the switches will behave just as a new switch has been added.

What if I want a remote control that controls the lighting?

Just let the remote control interface have a decision matrix element that sends out the on-event to the zone when the selected key is pressed.

What if I want the lights to be turned on when the alarm goes off?

Same solution here. Program the alarm control to send the on-event to the zone on alarm.

*You imagination is the only limitation….*

{% include "./bottom_copyright.md" %}`

# Decision Matrix

## Event handling and Rules

Every event on a VSCP segment can be seen as an event. To be of any use to anyone a decision has to be taken on what to do as a result of the event. This is done in a decision matrix, which is a standardized way to write the rules that take care of events. To get something done when a specific event is detected some sort of action mechanism is needed.

The event-decision-action model or eda-model is the way we look at the functionality of a VSCP-node. First of all a node can be a level I or level II node. A level I node can perform actions from all level I events. A level II node can handle both level I and level II events. In fact when we define rules we define them at the highest level. 

## The model

To be able to build a software model that is common for several device/machine/situation types and environments we have to make a model to suit the typical control situation. The model is very simple and is also very easy to implement on different target environments. 

###  Event 

Something happens that triggers some kind of input. This could be the elapse of a timer, a delivered temperature reading, a triggered fire alarm etc. Without this state there is nothing to do. We call this state the EVENT - state. 

### Decision

If an event occurs we may react in some way to this happening. This reaction comes after a decision about if and how the event should be handled. We use a decision matrix to control the logic of our decisions. Every element in the decision matrix handles one event and performs one action. A decision matrix element is also capable of generating events and can in this way perform several actions on the behalf of one event. 

### Action

The action is the function, thread, procedure, method or other functionality that should be carried out as a result of an event.

The states represented by EVENT + DECISION + ACTION are treated as one transaction. All steps must be handled for the transaction to be marked as completed.

So when you describe the functionality of a VSCP-node you say


*  This node reacts on the following events. 

*  This node can perform the following actions.

To make the node a useful piece of equipment it needs a decision matrix. This matrix can be implemented with no possibility for a user to change it or it can be undefined and left for the user to specify. 

### Decision matrix for Level I nodes.

In resource-limited environments, such as a microprocessor, the previously discussed matrix format takes up to much space and a more resource friendly format is therefore defined. Here the class + type bytes formats the event.

This matrix has no trigger for data values. This has to be done internally by the application using user defined codes.

A matrix row consists of 8 bytes and has the following format 

##### Level I decision matrix

 | Byte 0 | Byte 1 | Byte 2     | Byte 3       | Byte 4    | Byte 5      | Byte 6 | Byte 7           | 
 | ------ | ------ | ------     | ------       | ------    | ------      | ------ | ------           | 
 | oaddr  | flags  | class-mask | class-filter | type-mask | type-filter | action | action-parameter | 

###  oaddr 

oaddr is the originating node nickname. We are only interested in events from the specific node given by oaddr if bit 6 of flags is set. For example we may be interested in events only from node 0x00, a segment controller, or 0xFF, a node without a nickname. If bit 6 of flags is not set, oaddr will not be checked and events from all nodes will be accepted iof all other criteria match.

### flag

 | Bit # | Description                                                               | 
 | ----- | -----------                                                               | 
 | 7     | Row is enabled if set to 1                                                | 
 | 6     | oaddr should match nickname of event (=1) or don't care (=0)              | 
 | 5     | Indicates (if set to 1) that the originating address should be hard-coded | 
 | 4     | Match Zone to trigger DM entry if set to 1                                | 
 | 3     | Match sub-zone to trigger DM entry if set to 1.                           | 
 | 2     | Reserved                                                                  | 
 | 1     | Class-mask bit 8                                                          | 
 | 0     | Class-filter bit 8                                                        | 

The enable bit can be used to disable a decision matrix row while it is edited.

The zone and use sub-zone bits can be activated to have a check on the zone/sub-zone information of an event. That is the zone/sub-zone of the machine must match the one of the event to trigger the DM row. Bits 0/1 are the ninth bit of the filter/mask not enable bits.

### class-mask / class-filter

A class that should trigger this decision matrix row is defined in class-mask and class-filter with bit eight for both taken from the flags byte.

The following table illustrates how this works 

##### Truth table for filter/mask

 | Mask bit n | Filter bit n | Incoming event class bit n | Accept or reject bit n | 
 | ---------- | ------------ | -------------------------- | ---------------------- | 
 | 0          | x            | x                          | Accept                 | 
 | 1          | 0            | 0                          | Accept                 | 
 | 1          | 0            | 1                          | Reject                 | 
 | 1          | 1            | 0                          | Reject                 | 
 | 1          | 1            | 1                          | Accept                 | 

Think of the mask as having ones at positions that are of interest and the filter telling what the value should be for those bit positions that are of interest.


*  So to only accept one class set all mask bits to one and enter the class in filter. 

*  To accept all classes set the mask to 0. In this case filter don't care.

### type-mask / type-filter

A type that should trigger this decision matrix row is defined in type-mask and type-filter with bit eight for both taken from the flags byte.

A similar truth table as for the class-mask/filter is used. 

### action

This is the action or operation that should be performed if the filtering is satisfied. Only action code 0x00 is predefined and means No-Operation. All other codes are application specific and typical application defined codes could do measurement, send predefined event etc. 

### action-parameter

A numeric action can be set and its meaning is application specific.

### General

The number of matrix rows are limited in a micro controller. The control class has an event defined that gets the number of elements in the matrix and the location of the matrix in the register model of the node (Get Decision matrix info, [CLASS1.PROTOCOL, Type=33](./class1.protocol.md#type_33_0x21_get_decision_matrix_info)).

The matrix information is read and written with the standard read/write control functions. And is placed in the standard low register range (<0x80) or in an optional page in this area.

Note that there is no demand that a node implements a decision matrix. If not implemented the Get Decision matrix info just returns a zero size.

A special paged feature is available for the decision matrix to save register space. If the offset for the decision matrix is 0x7e the decision matrix is indexed. This means that 0x7e is the index and 0x7f is the data. Read a byte from the matrix by first setting the index to the position you want to read and reading the byte in 0x7f. Set index to the position you want to write and write data into 0x7f.

Method [CLASS1.PROTOCOL TYPE=32](./class1.protocol.md#type_32_0x20_who_is_there_response) is used to fetch decision matrix information for a specific node. 

It is important to note that the decision matrix can contain any number of lines for a specific event element. So one incoming event can trigger many actions.

Events are marked as handled when the action thread is started. This can be bad in some situations where the event chain is dependent on the action to complete its task before any new work is done. In this case it is better to continue the event chain by posting an event from the action thread instead of setting the following event as a next event in the decision matrix.

The decision matrix structure gives us the freedom to implement events that perform:


*  Exactly one action. 
*  Several actions. 
*  Several actions in a sequence.

## Decision matrix for Level II nodes.

There is a lot more freedom to set up a decision matrix structures on level II nodes due to less space constraints.One implementation is the decision matrix in the VSCP Daemon which is described [here](https://www.vscp.org/docs/vscpd/doku.php?id=vscp_daemon_decision_matrix).

A general form is discussed here. To understand how this decision matrix is updated one needs to understand how it is set up. Each line of the matrix is built from a table of entries of the following form: 

 | byte 0-3 | byte 4-7 | byte 8-11 | byte 12-13 | byte 14-n        | 
 | -------- | -------- | --------- | ---------- | ---------        | 
 | mask     | filter   | control   | action     | action-parameter | 

where the action-parameter has device specific length. 

## Mask (32-bit)

This is a bit mask, which has ones at the bit positions of the event that is interesting. So 0xFFFFFFFF makes all events interesting. Class is in the high word. Type is in the low word. For a truth table see the class-mask for Level I decision matrices. 

### Filter (32-bit)

This is a bit mask, which tells the value for bits that is of interest. Class is in the high word. Type is in the low word. For a truth table see the class-mask for Level I decision matrices. 

### Control(32-bit)

##### Control bits

 | bit # | Description                                                                                           | 
 | ----- | -----------                                                                                           | 
 | 31    | Enabled if set to 1. If disabled the decision matrix element is ignored.                              | 
 | 30    | Reserved.                                                                                             | 
 | 29    | Marks end of matrix. No more valid entries in the DM after this line. Used to save parsing resources. | 
 | 28    | Reserved.                                                                                             | 
 | 27    | Reserved.                                                                                             | 
 | 26    | Reserved.                                                                                             | 
 | 25    | Reserved.                                                                                             | 
 | 24    | Reserved.                                                                                             | 
 | 23    | Reserved.                                                                                             | 
 | 22    | Reserved.                                                                                             | 
 | 21    | Reserved.                                                                                             | 
 | 20    | Reserved.                                                                                             | 
 | 19    | Reserved.                                                                                             | 
 | 18    | Reserved.                                                                                             | 
 | 17    | Reserved.                                                                                             | 
 | 16    | Reserved.                                                                                             | 
 | 15    | Reserved.                                                                                             | 
 | 14    | Reserved.                                                                                             | 
 | 13    | Reserved.                                                                                             | 
 | 12    | Reserved.                                                                                             | 
 | 11    | Reserved.                                                                                             | 
 | 10    | Reserved.                                                                                             | 
 | 9     | Reserved.                                                                                             | 
 | 8     | Reserved.                                                                                             | 
 | 7     | Reserved.                                                                                             | 
 | 6     | Reserved.                                                                                             | 
 | 5     | Match index of this module to trigger DM entry. Byte 0 of data.                                       | 
 | 4     | Match zone of this module to trigger DM entry. Byte 1 of data.                                        | 
 | 3     | Match sub-zone of this module to trigger DM entry. Byte 2 of data.                                    | 
 | 2     | Reserved.                                                                                             | 
 | 1     | Reserved.                                                                                             | 
 | 0     | Reserved.                                                                                             | 

Specific node implement ions decide how to interpret bits or not. Just some or none of the bits can be used if that suits the implement ion. 

### Action (16-bit)

This is the what should be carried out to make this action happen. This is a 16-bit cod that is application specific. 0x0000 is the only code that is predefined as no operation. 

### Action Parameters

This is a variable length text-string/binary array that can contain parameters for the action. Format is application dependent. Can be omitted if no parameters are used.

A decision matrix row is 14 bytes plus the size of the action parameters.

A special paged feature is available for the decision matrix to save register space. If the offset for the decision matrix is 0x80 - dm-row-size (a DM row aligned to the upper register border) it is implied that the register position just below, 0x80 -dm-row-size - 1, contains a register that is an index to the row that has its first byte at 0x80 - dm-row-size.

The index byte is used to select rows and the selected row is available from the byte after the index byte to the 0x80 border.

Method [CLASS1.PROTOCOL TYPE=32](./class1.protocol.md#type_32_0x20_who_is_there_response) is used to fetch decision matrix information for a specific node. Byte six of the response tells the actual size for a decision matrix row.

The Level II Decision Matrix has no entry for originating address. The action parameter field can be used for this information if needed. 

[filename](./bottom_copyright.md ':include')

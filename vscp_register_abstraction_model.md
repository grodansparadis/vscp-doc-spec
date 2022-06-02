# Register Abstraction Model

Functionality of a device in VSCP is exposed to the world through 8-bit registers. Much like a IC circuit expose information to the world in electronic systems. This is useful only for the lowest level devices. Higher level devices and users usually get the information in the registers presented as higher level value. This low level information is something the VSCP systems can hide with the help of the MDF information (see [Module-Description-File](./vscp_module_description_file.md)). This is this why we talk about an abstraction model. 

The 'abstraction' comes from the fact that registers normally is not a real thing. Register abstractions only look at the world thrue byte-wide register glasses. So even if a variable for example is a 32-bit signed number some where in memory it will be presented as four registers in the register abstraction. Writing to the registers that abstracts the variable will actually write the 32-bit variable. Same for reading.

Above the register abstraction model is **remote variables** (defined below) which describe the system in higher level terms such as int's strings and logical values. Remote variables maps directly to registers. 

The end result is that only two methods is need to be implemented. Read and write a register. After thye are in place all remote configuration issues can be handled.

## Level I - Register Abstraction Model

Byte wide bit registers are a central part of the VSCP specification. All nodes Level I as well as Level II should be possible to be configured by reading/writing these registers. Some of the register are the same for all nodes and are also the same between Level I and Level II nodes. The difference is that Level II can have a lot more registers defined in it's 32-bit abstracted register space.

Registers 0x00 – 0x7F are application specific. Registers between 0x80 – 0xFF are reserved for VSCP usage. If the node has implemented the decision matrix it is stored in application register space.

Reading of an unimplemented register should return 0x00.  

The VSCP registers are defined as follows: 

### Register abstraction model:id=register_abstraction_model

_Note:_ Add 0xFFFFFF80 to an address below to get the corresponding level II standard register abstraction address.

 | Address   | Access Mode | Description  | 
 | -------   | ----------- | -----------  | 
 | 0x00–0x7F |             | Device specific (a page). Unimplemented registers should return zero. | 
 | 128/0x80  | Read Only   | Alarm status register content (!= 0 indicates alarm). Condition is reset by a read operation. The bits represent different alarm conditions. |
 | 129/0x81  | Read Only   | VSCP Major version number this device is constructed for. | 
 | 130/0x82  | Read Only   | VSCP Minor version number this device is constructed for. | 
 | 131/0x83  | Read/Write  | VSCP error counter (was Node control flags prior to 1.6) | 
 | 132/0x84  | Read/Write  | User ID 0 – Client settable node-ID byte 0. | 
 | 133/0x85  | Read/Write  | User ID 1 – Client settable node-ID byte 1. | 
 | 134/0x86  | Read/Write  | User ID 2 – Client settable node-ID byte 2. | 
 | 135/0x87  | Read/Write  | User ID 3 – Client settable node-ID byte 3. | 
 | 136/0x88  | Read/Write  | User ID 4 – Client settable node-ID byte 4. | 
 | 137/0x89  | Read only   | Manufacturer device ID byte 0. | 
 | 138/0x8A  | Read only   | Manufacturer device ID byte 1. | 
 | 139/0x8B  | Read only   | Manufacturer device ID byte 2. | 
 | 140/0x8C  | Read only   | Manufacturer device ID byte 3. | 
 | 141/0x8D  | Read only   | Manufacturer sub device ID byte 0. | 
 | 142/0x8E  | Read only   | Manufacturer sub device ID byte 1. | 
 | 143/0x8F  | Read only   | Manufacturer sub device ID byte 2. | 
 | 144/0x90  | Read only   | Manufacturer sub device ID byte 3. | 
 | 145/0x91  | Read only   | Nickname-ID for node if assigned or 0xFF if no nickname-ID assigned. | 
 | 146/0x92  | Read/Write  | Page select register MSB | 
 | 147/0x93  | Read/Write  | Page Select register LSB | 
 | 148/0x94  | Read Only   | Firmware major version number. | 
 | 149/0x95  | Read Only   | Firmware minor version number. | 
 | 150/0x96  | Read Only   | Firmware sub minor version number. | 
 | 151/0x97  | Read Only   | Boot loader algorithm used. 0xFF for no boot loader support. Codes for algorithms are specified here [CLASS1.PROTOCOL, Type=12](./class1.protocol#id=type12) | 
 | 152/0x98  | Read Only   | Buffer size. **Deprecated from version 1.14.2**. Always return zero in new code when the register is read. The value here gives an indication for clients that want to talk to this node if it can support the larger mid level Level I control events which has the full GUID. If set to 0 the default size should used. That is 8 bytes for Level I and 512 for Level II. | 
 | 153/0x99  | Read Only   | Number of register pages used. If not implemented one page is assumed. Set to zero if your device have more then 255 pages. **Deprecated**: Use the MDF instead as the central place for information about actual number of pages.    | 
 | 154/0x9A  | Read Only   | Standard device family code (MSB) Devices can belong to a common register structure standard. For such devices this describes the family coded as a 32-bit integer. Set all bytes to zero if not used. Also 0xff is reserved and should be interpreted as zero was read. *Added in version 1.9.0 of the specification* | 
 | 155/0x9B  | Read Only   | Standard device family code *Added in version 1.9.0 of the specification* | 
 | 156/0x9C  | Read Only   | Standard device family code *Added in version 1.9.0 of the specification* | 
 | 157/0x9D  | Read Only   | Standard device family code (LSB) *Added in version 1.9.0 of the specification* | 
 | 158/0x9E  | Read Only   | Standard device type (MSB) This is part of the code that specifies a device that adopts to a common register standard. This is the type code represented by a 32-bit integer and defines the type belonging to a specific standard. *Added in version 1.9.0 of the specification* | 
 | 159/0x9F  | Read Only   | Standard device type *Added in version 1.9.0 of the specification*  | 
 | 160/0xA0  | Read Only   | Standard device type  *Added in version 1.9.0 of the specification* | 
 | 161/0xA1  | Read Only   | Standard device type (LSB) *Added in version 1.9.0 of the specification*  | 
 | 162/0xA2  | Write Only  | Standard configuration should be restored for a unit if first 0x55 and then 0xAA is written to this location and is done so withing one second. *Added in version 1.10.0 of the specification* | 
 | 163/0xA3  | Read Only  | Firmware device code MSB. *Added in version 1.13.0 of the specification* |
 | 164/0xA4  | Read Only  | Firmware device code LSB. *Added in version 1.13.0 of the specification* |
 | 165/0xA5-207/0xCF | —         | Reserved for future use. Return  | 
 | 208/0xD0-223/0xDF | Read Only   | 128-bit (16-byte) globally unique ID (GUID) identifier for the device. This identifier uniquely identifies the device throughout the world and can give additional information on where driver and driver information can be found for the device. MSB for the identifier is stored first (in 0xD0). | 
 | 224/0xE0-255/0xFF | Read Only   | Module Description File URL. A zero terminates the ASCII string if not exactly 32 bytes long. The URL points to a file that gives further information about where drivers for different environments are located. Can be returned as a zero string for devices with low memory. For a node with an embedded MDF return a zero string. The CLASS1.PROTOCOL, Type=34/35 can then be used to get the information if available. | 

#### User ID

This is a register space that can be used to store installation values as for example a location code of where the unit is installed.

#### Manufacturer device ID/Manufacturer sub device ID

The manufacturer of the device can store whatever they like in thees registers. Typical use is for hardware version. Firmware version. Batch numbers. Serial numbers and such. 

#### Page select

The page select registers can be used to switch pages for the lower 128 byte. Its important that an application that uses the page functionality switch back to page 0x0000 when its ready. Applications can use the page registers as a mutex which is signaled when not zero. 

#### Standard device families and types

Added in version 1.9.0 of the specification

Some devices has a need for a common register structure standard. This is defined by two 32-bit values in the standard register space. The family value defines the group of devices the module belongs to and the type value describes the specific device type in that family it belongs to. Families and device types are still to be defined.

#### Firmware device code

Added in version 1.13.0 of the specification

The firmware code is used to distinguish a device type of a module from one another so that the correct firmware can be loaded to a module. Typically a board have different firmware codes here for different microprocessors used as reversions of the board is shipped over time. The firmware code can be given in the MDF file and makes it possible to prevent the wrong firmware being loaded to a module.  

Return zero if not used.

## Level II - Register Abstraction Model

The level II abstraction model is the same as Level I but covers a much wider address space. For level II the register space from address 0xFFFF0000 to 0xFFFFFFFF is reserved for standard registers. The level I standard register space is present in this area at address 0xFFFFFF80 to 0xFFFFFFFF.
 

## Remote variables:id=remote-variables

**Note:** Remote variables where called *abstractions* in previous versions (1.13) of the specification.

A VSCP device is describing it's configuration to the world with the register model described above where each register is eight bit in width. This is often inconvenient for a human user who is used to higher level types and this is what *remote variables* is defined for. They sit above registers and specify higher level types as strings, floats, integers and other such higher level types.

Just as register definitions, remote variables live there life in the [Module Description file (MDF)](./vscp_module_description_file.md).

The following remote variables are currently defined

 | Remote variable | Description | 
 | ----------- | ----------- | 
 | string      | A text string (UTF8 coded). Can be indexed. See below.  | 
 | bool        | A 1 bit value specified as true or false.  | 
 | int8_t      | A 8 bit signed number. Hexadecimal if it starts with "0x" else decimal. | 
 | uint8_t     | An unsigned 8  bit number. Hexadecimal if it starts  with "0x" else decimal.  | 
 | int16_t     | A 16 bit signed number. Hexadecimal if it starts with "0x" else decimal.      | 
 | uint16_t    | A 16 bit unsigned number. Hexadecimal if it starts with "0x" else decimal.    | 
 | int32_t     | A 32 bit signed number. Hexadecimal if it starts with "0x" else decimal.      | 
 | uint32_t    | A 32 bit unsigned number. Hexadecimal if it starts with "0x" else decimal.    | 
 | int64_t     | A 64 bit signed number. Hexadecimal if it starts with "0x" else decimal.      | 
 | uint64_t    | A 64 bit unsigned number. Hexadecimal if it starts with "0x" else decimal.    | 
 | float       | Data is coded as a IEEE-754 1985 floating point value That is a total of 32-bits. The most significant byte is stored first.  | 
 | double      | IEEE-754, 64 Bits, double precision.  That is a total of 64-bits. The most significant byte is stored first.        | 
 | date        | Must be passed in the format dd-mm-yyyy and mapped to "yy yy mm dd" that is four bytes, MSB->LSB  | 
 | time        | Must be passed in the format hh:mm:ss where hh is 24 hour clock and mapped to "hh mm ss" MSB->LSBthat is four bytes.   |  

A note on floating point numbers and storage (source Wikipedia)

*"Although the ubiquitous x86 of today use little-endian storage for all types of data (integer, floating point, BCD), there have been a few historical machines where floating point numbers were represented in big-endian form while integers were represented in little-endian form." ... "However, on modern standard computers (i.e., implementing IEEE 754), one may in practice safely assume that the endianness is the same for floating point numbers as for integers, making the conversion straightforward regardless of data type."*

The following remote variables has been removed as of version 1.13 of the VSCP specification

 | Remote variable | Description | 
 | ----------- | ----------- | 
 | bitfield    | A field of bits. Width tells how many bits the field consist of. When read from a device the number of bits will always be in even octets with unused bits set to zero. Bitfield is taken from MSB part thrue LSB and continues that way on next octet in the series. | 
 | guid        | Holds the 16 bytes of a GUID. Stored on the form  11:22:33:... MSB->LSB  |
###  synonyms

 | Remote variable | Description               | 
 | ----------- | -----------               | 
 | char        | Is the same as "int8_t".  | 
 | byte        | Is the same as "uint8_t". | 
 | short       | Is the same as "int16_t". | 
 | integer     | Is the same as "int16_t". | 
 | long        | Is the same as "int32_t". | 
 | ulong       | Is the same as "uint32_t".|

### indexed storage

In versions prior to 1.13 of the specification all remote variables with a size > 2 could be stored indexed. This is only true for the *string* type from version 1.13. An indexed string is stored in two bytes in register space. Index (0-255) in the first byte and the value for the indexed position of the string in the second byte.

[filename](./bottom_copyright.md ':include')


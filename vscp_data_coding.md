# Data coding

For the measurement class and the data class all data is sent in a form that is related to the default format of the data. The number of data bytes in the frame also reflects the size of the variable. In this definition there is a very important assumption. If two nodes should be able to talk to each other they have to know each others data formats. So our assumption is that if a node is interested in what another node has to say it must learn its data format. Also if a node needs to control another node it has to learn its data format to do so.

As a guideline the format defined bellow for the first data byte of a data frame can be used but if a user likes to use another format it is perfectly fine to do so. 

## Definitions for bits in control byte

 | coding(bits 7,6,5) | unit (bits 4,3) | Sensor index (bits 2,1,0) | 
 | ------------------ | --------------- | ------------------------- | 

Tells how data that follows should be interpreted. This is used for [CLASS1.MEASUREMENT](./class1.measurement.md) and [CLASS1.DATA](./class1.data.md) among others. 

### Control byte, coding - Bits 5,6,7

Represent one of several numerical representations in which the data that follows can be represented as. 

#### 000b Bit Format

The data should be represented as a set of bits. This can be used for picture coding etc. 

#### 001b Byte Format( 0x20 )

The data should be represented as a set of bytes. 

#### 010b String Format( 0x40 )

The data should be represented as an ASCII numerical string. Max seven characters that together represent a number. A "." should always be used as possible decimal separator independent of locale. Example “-123”, “1.3456”, “0.00001” etc

#### 011b Integer Format( 0x60 )

Data is coded as a signed integer. The integer is coded in the bytes that follows and can be 1-7 bytes where the most significant byte always is in byte 1 (big endian).


*  If total event length=2 the data is a 8-bit integer or 1 byte. 

*  If total event length=3 the data is a 16-bit integer or 2 bytes. 

*  If total event length=4 the data is a 24-bit integer or 3 bytes. 

*  If total event length=5 the data is a 32-bit integer or 4 bytes.

*  If total event length=6 the data is a 40-bit integer or 5 bytes. 

*  If total event length=7 the data is a 48-bit integer or 6 bytes. 

*  If total event length=8 the data is a 56-bit integer or 7 bytes. 

#### 100b Normalized integer format( 0x80 )

Data is coded as a normalized integer. In this case the format byte is followed by the normalizer byte.

The normalizer byte is the exponent of the following integer and coded as 'sign (bit 7) and magnitude (bits 0-6)', representing an exponent in the range-(2^{6}-1) to 2^{6}-1. Thus bits 0-6 describe how many places the decimal point has to be shifted and bit 7 the direction of the shift (0 = right; 1 = left).

The actual integer (mantissa) is coded in the bytes that follows and can be 1-6 bytes where the most significant byte always is in byte 2. This integer is always signed and given as a two's complement number.

##### Example

    0x02 0x1B 0x22
    0x1B22 = 6946 decimal
    0x02 has bit 7 cleared meaning the decimal point has to be shifted 2 steps to
     the right i.e. the value is 6946 * 10^2 = 694600
     which is the same as multiplying the value by 10^2 = 100

##### Example

    0x85 0x8D
    0x8D = -115 decimal
    0x85 has bit 7 set meaning the decimal point has to be shifted 5 steps to the 
     left i.e. the value is -115 * 10^(-5) = -0.00115
     which is the same as dividing the value by 10^5 = 100000

##### Example

    0x81 0x01 0x07
    0x0107 = 263 decimal
    0x81 has bit 7 set meaning the decimal point has to be shifted 1 step to the 
     left i.e. the value is 263 * 10^(-1) = 26.3
     which is the same as dividing the value by 10^1 = 10 

####  101b Floating point value( 0xA0 )

Data is coded as a IEEE-754 1985 floating point value

    s eeeeeeee mmmmmmmmmmmmmmmmmmmmmmm 

That is a total of 32-bits. The most significant byte is stored first. The frame holds a total of five bytes. The full definition is at [https://www.psc.edu/general/software/packages/ieee/ieee.html] and further info at [https://en.wikipedia.org/wiki/IEEE_754-1985] 

#### 110b Reserved.( 0xC0 )

The format is yet to be defined. 

#### 111b Reserved( 0xE0 )

The format is yet to be defined.

### Control byte, unit - Bits 3,4

This bits tell how the data should be interpreted. Typically this is a unit like Centigrade, Fahrenheit or Kelvin for a temperature value. 00b Standard unit. All other codes in this field are event class/type specific.

### Control byte, sensor index - Bits 0,1,2

Zero based sensor index which can be used if there are more then one sensor handled by the node. 

# MEASUREMENTS

There are many measurement types in VSCP and more will be defined as time goes. The goal is to have all SI units defined and also there derivatives as needs arise. But as measurements are a very important part of an IoT/M2M protocol there are also many classes defined which carry the types. Each class with it's own properties.

## Level I measurement classes

[CLASS1.MEASUREMENT (10)](./class1.measurement.md)
This is the main measurement class. It is built to be as resource efficient as possible if that is what one want but it also accept single precision floating point and strings.

**VSCP_CLASS2_LEVEL1_MEASUREMENT** is the same except that it's class is 512 + 10 and that the first 16-byte of data is the interface GUID where the Level I event carried over Level II should be delivered as a Level I event again.

[CLASS1.MEASUREMENT64(60)](./class1.measurement64.md)

Used for double precision floating point measurements over Level I. Sensor index is always zero and so is the measurement unit so a temperature for example must be sent with Kelvin as it's unit. Working in a low end device this may be the only eay to get this kind of precision but if it is possible to affoard the overhead of Level II [CLASS2.MEASUREMENT_FLOAT(1060)](./class2.measurement_float.md) is a much better choice.

**VSCP_CLASS2_LEVEL1_MEASUREMENT64** is the same except that it's class is 512 + 64 and that the first 16-byte of data is the interface GUID where the Level I event carried over Level II should be delivered as a Level I event again. 

[CLASS1.MEASUREZONE(65)](./class1.measurezone.md)

**VSCP_CLASS2_LEVEL1_MEASUREMENTZONE** is the same except that it's class is 512 + 65 and that the first 16-byte of data is the interface GUID where the Level I event carried over Level II should be delivered as a Level I event again.

[CLASS1.MEASUREMENT32(70)](./class1.measurement32.md)

**VSCP_CLASS2_LEVEL1_MEASUREMENT32** is the same except that it's class is 512 + 70 and that the first 16-byte of data is the interface GUID where the Level I event carried over Level II should be delivered as a Level I event again.

[CLASS1.SETVALUEZONE(85)](./class1.setvaluezone.md)

**VSCP_CLASS2_LEVEL1_SETVALUEZONE** is the same except that it's class is 512 + 85 and that the first 16-byte of data is the interface GUID where the Level I event carried over Level II should be delivered as a Level I event again.

## Level II measurement classes

[CLASS2.MEASUREMENT_STR(1040)](./class2.measurement_str.md)


[CLASS2.MEASUREMENT_FLOAT(1060)](./class2.measurement_float.md)





[filename](./bottom_copyright.md ':include')

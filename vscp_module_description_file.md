# Module Description File

The Module Description File (MDF) is a file that describes a general hardware module. The format of the file can be used to describe any logical or physical device. After parsing the MDF a higher level device (a machine) or user (a human) know how to configure and handle the described module. 

All VSCP modules have an area in memory that is common to all devices that contains the URL for the MDF. This area can be read and then the MDF can be downloaded and parsed.

The file should be UTF-8 encoded and contain either **XML** or **JSON** data. 

**numbers** All numbers can be set as decimal(no prefix), hexadecimal(prefix with 0x), octal(prefix with 0o) or binary(prefix with 0b). 



## The content of a MDF file

The MDF file have the following general structure:

 - **General module information** such as model, version etc.
 - **Manufacturer**: Info about the maker of the module such as name, address, phone number, etc.
 - **Files**: A list oif files related to the module. This can be firmare, pictures, videos, manuals etc.
 - **bootloader information**: Info on how to load firmware to the module.
 - **registers**: A list of byte wide registers the module have.
 - **remote variables**: A list of remote variables the module have. Remote variables was called *abstractions* in previous versions of the specification.
 - **events**: A list of events (and there format) the module can generate/receive.
 - **decision matrix**: Describes the decision matrix for the module if it have one.
 - **setup**: Is macros to setup and configure and control a module using wizard like interfacec.

## XML Format Specification
### Format notes 

#### Register definitions
Register definitions must be available for all nodes (if the module have registers defined). 

#### Automatic remote variables
A register which does not have a a remote variable defined to describe it in a high level way will have a default remote variable constructed from its offset as

    register''offset''

for example

    register1 

The type for the remote variable in this case will always be “uint8_t” 

#### Newlines
“\n” can be used to define a new line in descriptive text. It will be translated in an appropriate way by the renderer.

## File overall structure

```xml
<vscp>
	<redirect mdf-path="url" />

	<module>
     "The module is described here"
  </module>

</vscp>		
```

### Redirect
The redirect can be used to tell the parser to download the MDF from a different URL. 

### Module
In the **module**-block the module is described. Currently only one module can be defined in a mdf file. This may change in the future.
## Module information

Every module should have an initial block that describes the module. This block is called the **General module information**. The block looks like this

```xml
<vscp>
	<module>
    <level>1/2</level>
    <changed>1873-10-22</changed>
    <name>aaaaaaaa</name>
	<model>bbbbb</model>    
	<version>cccccc</version>
	<description lang="en">yyyyyyyyyyyyyyyyyyyyyyyyyyyy</description>
    <infourl lang="en">Main driver info help (web) page url</infourl>     
		
	<!-- Max package size a node can receive -->    
	<buffersize>8</buffersize> 
</module>    
```

#### level
VSCP level of protocol this module works with. Defaults to 1 if not present.

#### changed
Date on ISO format for last change of file.

#### name
Name is the name of the module. A unique describing name is recommended. This name will be translated to lower case and is used as the name of the module when referring to it in software.

**note** In previous version the name of the module was language specific just as descriptions and info url's. This is no longer the case. If

```xml
<vscp>
	<module>
    <name lang="en">aaaaaaaa</name>
    <name lang="sn">bbbbbbbb</name>
```

the last parsed name will be used.

#### model
This is the model of the module. Format is defined by the designer.

#### version
This is the version of the module. Format is defined by the designer.

#### description
The description is a short description of the module. It is recommended to use a language specific description. If no language attribute is given "en" for English will be used. The language code should be a valid two letter (ISO 639-1 code)[https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes6].

Descriptions can be multiline and can use "\n" to define a new line.

As an example

```xml
  <description lang="en">xxxxxxxxxxxxxxxxxxxxxxxxxxxx</description>
  <description lang="lt">yyyyyyyyyyyyyyyyyyyyyyyyyyyy</description>
  <description lang="es">zzzzzzzzzzzzzzzzzzzzzzzzzzzz</description>
```

will create an English, Lithuanian, and a Spanish description. Software that handle languages can then switch between languages fast and efficiently.

#### infourl
The infourl is an url pointing to a full description of the module in the language given by the **lang** attribute. It is recommended to use a language specific infourl. If no language attribute is given "en" for English will be used. The language code should be a valid two letter (ISO 639-1 code)[https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes6].

As an example

```xml
  <infourl lang="en">https://www.somewhere.com</infourl>
  <infourl lang="lt">https://www.somewhere.lt</infourl>
  <infourl lang="es">https://www.somewhere.es</infourl>
```

points to web pages that have info in three different languages.

#### buffersize
For Level II nodes the buffer size specify the max VSCP data a node can receive.  This makes it possible to have nodes, that due to low internal resources, that can receive events, but not all events, just those under a specified maximum size. The default is eight bytes which is the data size for a level I node. Set to <= 512 for a level II nodes.

### manufacturer:id=manudacturer_xml
The manufacturer block describes the manufacturer of the module.

#### name
Name is the name of the company that manufactured the module.

**note** In previous version the name of the module was language specific just as descriptions and info url's. This is no longer the case.

#### Address
The address block looks like this

```xml
<address>
  <street>Some street in Camden, London</street>
  <town>Camden</town>
  <city>London</city>
  <postcode>Postal code</postcode>
  <state>xxxxxx<</state>
  <region>London</region>
  <country>Country</country>
</address>
```

and specify the address to the manufacturer of the module. Use the tags that are appropriate for your project.

**note** In previous version the address of the module was language specific just as descriptions and info url's. This is no longer the case. Only one address can be defined.


#### Telephone
This is a phone number of the manufacturer. As many phone numbers as one like can be defined. The format is

```xml
<telephone>
  <number>+46 8 40011835</number>
  <description lang="en">office exchange</description>
  <infourl lang="en">https://www.somewhere.com</infourl>
</telephone>
```
The infourl is optional.

#### Fax
This is a telefax number of the manufacturer. As many fax numbers as one like can be defined. The format is

```xml
<fax>
  <number>+46 8 40011837</number>
  <description lang="en">office fax</description>
  <infourl lang="en">https://www.somewhere.com</infourl>
</fax>
```
The infourl is optional.
#### Email
This is an email address of the manufacturer. As many email addresses as one like can be defined. The format is

```xml
<email>
  <address>info@vscp.org</address>
  <description lang="en">office exchange</description>
  <infourl lang="en">https://www.somewhere.com</infourl>
</email>
```
The infourl is optional.
#### Web
This is a web address of the manufacturer. As many web addresses as one like can be defined. The format is

```xml
<web>
  <url>https://www.somewhere.com</url>
  <description lang="en">office exchange</description>
  <infourl lang="en">https://www.somewhere.com</infourl>
</web>
```
The infourl is optional.

### Files:id=files_xml

```xml
<files>
  <firmware>...</firmware>
  <picture>...</picture>
  <video>...</video>
  <manual>...</manual>
  <driver>...</driver>
  <setup>...</setup>
</files>
```

This block contains info about files that are related to the module. _picture_, _videos_, _firmware_, _driver_ and _manual_ are current defined types of files. _setup_ is reserved for future use.

#### firmware:id=firmware_xml

In the firmware block you can specify links to firmware file that is used by the module and describe them. The format is

```xml
<files>
  <firmware name="some name"
            target="target" 
            targetcode="target"
            url="path" 
            format="format" 
            size="size"
            date="ISO date" 
            md5="hexadecimal md5 hash"
            version_major="a" 
            version_minor="b" 
            version_subminor="c">
    <url>https://www.somewhere.com/firmware.zip</url>
    <description lang="en">Firmware description</description>
    <infourl lang="en">https://www.somewhere.com</infourl>
  </firmware>
</files>
```

Any number of language specific _descriptions_ and/or _infourl_'s can be set for each firmware item. If no language attribute is given "en" for English will be used. The language code should be a valid two letter (ISO 639-1 code)[https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes6].

##### Attributes

| Name       | Description  | 
| :----      | :----------- | 
| **name**   | A name for the item. |
| **target** | Set the target for the file here. The target is typically processor and architecture specific. Examples are "RP2040", "ESP32C3", "PIC18F2558", "PIC18F26K50" and so on. It is up to the maker of the module to define unique values. | 
| **targetcode** | Set the target code for the file here. The target code is typically a 16-bit unsigned value that is stored in the nodes flash. If not null a firmware file that should be written to a node should have the same target code value as the the device registers have written to them. |
| **url**   | The url from which the firmware file can be fetched. |
| **path**  | (Deprecated alternative to "url"). The url to the firmware file. |
| **format** | The format of the firmware file. "intelhex8", "intelhex16", "uf2" is current valid values. |
| **size**  | The size of the firmware file in bytes. Zero if not set.|
| **date**  | Release date for the firmware. |
| **version_major** | Major version number for firmware. |
| **version_minor** | Minor version number for firmware. |
| **version_subminor** | Sub minor version number for firmware. |
| **md5** | MD5 checksum for the firmware file as hexadecimal string. Empty if not used. |

For "target" and "format" you can really use anything that your bootloader software understands. Values listed here are values recognized by vscp-works bootloader.

#### Example

```xml
<files>
  <firmware name="Firmware for PIC18F2558" 
            target="pic18f2558"
            targetcode="0x00" 
            url="https://github.com/grodansparadis/can4vscp-vilnius/releases/download/v1.04/Vilnius_pic18f2580_1_0_4_relocated.hex" 
            format="intelhex8" 
            date="2020-05-15" 
            version_major="1" 
            version_minor="0" 
            version_subminor="4">
    <description lang="en"> Firmware (PIC18F2580) for the Vilnius A/D module for use with the VSCP Bootloader wizard. </description>
  </firmware>
  <firmware name="Firmware for PIC18F26K58" 
            target="pic18f26k58"
            targetcode="0x02" 
            url="https://github.com/grodansparadis/can4vscp-vilnius/releases/download/v1.0.3/Vilnius_2580_1_0_3.hex" 
            format="intelhex8" 
            date="2016-03-23" 
            version_major="1" 
            version_minor="0" 
            version_subminor="4">
    <description lang="en"> Firmware (PIC18F26K80) for the Vilnius A/D module for use with the VSCP Bootloader wizard. </description>
  </firmware>
  <firmware name="Firmware for PIC18F2558" 
            target="pic18f2558" 
            targetcode="0x00" 
            url="https://github.com/grodansparadis/can4vscp-vilnius/releases/download/v1.0.0/Vilnius_1.0.0.hex" 
            format="intelhex8" 
            date="2015-07-07" 
            version_major="1" 
            version_minor="0" 
            version_subminor="3">
    <description lang="en"> Firmware for the Vilnius A/D module for use with the VSCP Bootloader wizard. </description>
  </firmware>
  <firmware name="Firmware for PIC18F2558" 
            target="pic18f2558"
            targetcode="0x00"  
            url="https://github.com/grodansparadis/can4vscp-vilnius/releases/download/v1.0.0/Vilnius_1.0.0.hex" 
            format="intelhex8" 
            date="2015-07-07" 
            version_major="1" 
            version_minor="0" 
            version_subminor="0">
    <description lang="en"> Firmware for the Vilnius A/D module for use with the VSCP Bootloader wizard. </description>
  </firmware>
</files>
```

#### picture:id=picture_xml

In the picture block you can specify a link to an image file that in some way is related the module and describe it. The format is

```xml
<files>
  <picture url="path" format="jpeg" date="ISO date" version_major="a" version_minor="b" version_subminor="c">
    <url>https://www.somewhere.com/picture.jpg</url>
    <description lang="en">Description of picture</description>
    <infourl lang="en">https://www.somewhere.com</infourl>
  </picture>
</files>
```

Any number of anguage specific descriptions and/or infourl's can be set for each picture item. If no language attribute is given "en" for English will be used. The language code should be a valid two letter code (ISO 639-1 code)[https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes6].

##### Attributes

| Name      | Description  | 
| :----     | :----------- | 
| **name**   | A name for the item. |
| **url**   | The url from which the picture file can be fetched. |
| **path**  | (Deprecated alternative to "url"). The url to the picture file. |
| **format** | The format of the picture file. "png", "jpeg" and "jpg" is current valid values. |
| **date** | Publish date in ISO format. |

#### video:id=video_xml

In the video block you can specify a link to a video file that in some way is related the module and describe it. The format is

```xml
<files>
  <video url="path" format="mp4">
    <url>https://www.somewhere.com/video.mp4</url>
    <description lang="en">Description of picture</description>
    <infourl lang="en">https://www.somewhere.com</infourl>
  </video>
</files>
```

Any number of language specific descriptions and/or infourl's can be set for each video item. If no language attribute is given "en" for English will be used. The language code should be a valid two letter code (ISO 639-1 code)[https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes6].

##### Attributes

| Name      | Description  | 
| :----     | :----------- | 
| **name**   | A name for the item. |
| **url**   | The url from which the video file can be fetched. |
| **path**  | (Deprecated alternative to "url"). The url to the video file. |
| **format** | The format of the video file. "mp4", "mov" and "avi" is current valid values. |
| **date** | Publish date in ISO format. |

#### manual:id=manual_xml

In the manual block you can specify a link to a manual file that in some way is related to the module and describe it. The format is

```xml
<files>
  <manual name="manual1" url="path" format="pdf">
    <url>https://www.somewhere.com/manual.pdf</url>
    <description lang="en">Description of manual</description>
    <infourl lang="en">https://www.somewhere.com</infourl>
  </manual>
</files>
```

Any number of language specific descriptions and/or infourl's can be set for each manual item. If no language attribute is given "en" for English will be used. The language code should be a valid two letter code (ISO 639-1 code)[https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes6].

##### Attributes

| Name      | Description  | 
| :----     | :----------- | 
| **name**   | A name for the item. |
| **url**   | The url from which the video file can be fetched. |
| **path**  | (Deprecated alternative to "url"). The url to the video file. |
| **format** | The format of the video file. "txt", "md" (markdown), "html" and "pdf" is current valid values. |
| **lang**  | The language of the manual. The language code should be a valid two letter code (ISO 639-1 code)[https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes6]. |
| **date** | Publish date in ISO format. |
| **version_major** | Major version number for manual. |
| **version_minor** | Minor version number for manual. |
| **version_subminor** | Sub minor version number for manual. |

#### driver:id=driver_xml

In the driver block you can specify a link to a driver for a specific version of an operation system file that in some way is related the module and describe it. Typically this is a device driver or a VSCP daemon driver or similar. zip and gz packed files are allowed. The format is

```xml
<files>
  <driver name="driver1" 
          url="path" 
          type="VSCP Daemon" 
          os="windows" 
          osver="10"
          architecture="amd64"
          version_major="1" 
          version_minor="0" 
          version_subminor="0">
    <url>https://www.somewhere.com/driver.zip</url>
    <description lang="en">Description of driver</description>
    <infourl lang="en">https://www.somewhere.com</infourl>
  </driver>
</files>
```

Any number of language specific descriptions and/or infourl's can be set for each driver item. If no language attribute is given "en" for English will be used. The language code should be a valid two letter code (ISO 639-1 code)[https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes6].

##### Attributes

| Name      | Description  | 
| :----     | :----------- | 
| **name**   | A name for the item. |
| **url**   | The url from which the driver file can be fetched. |
| **path**  | (Deprecated alternative to "url"). The url to the driver file. |
| **os** | The operating system. Examples are "Debian Linux", "Microsoft Windows", "Apple IOS" etc |
| **osver** | The version of the operating system. Examples are "10", "8.1" etc |
| **architecture** | OS architecture (amd64, arm64, x86 etc) |
| **date** | Release date in ISO-format |
| **version_major** | Major version number for driver. |
| **version_minor** | Minor version number for driver. |
| **version_subminor** | Sub minor version number for driver. |
| **md5** | MD5 checksum for the driver file as hexadecimal string. Empty if not used. |

#### setup:id=setup_xml

In the setup block you can specify a link to a setup file that contain a VSCP setup script that do a specific setup of the device. The format is

```xml
<files>
  <setup name="setup1" url="path" format="vscpjs">
    <url>https://www.somewhere.com/setup.js</url>
    <description lang="en">Description of setup script</description>
    <infourl lang="en">https://www.somewhere.com</infourl>
  </setup>
</files>
```

Any number of language specific descriptions and/or infourl's can be set for each setup item. If no language attribute is given "en" for English will be used. The language code should be a valid two letter code (ISO 639-1 code)[https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes6].

##### Attributes

| Name      | Description  | 
| :----     | :----------- | 
| **name**   | A name for the item. |
| **url**   | The url from which the video file can be fetched. |
| **path**  | (Deprecated alternative to "url"). The url to the video file. |
| **format** | The format of the setup file. "vscpjs" for VSCP javascript setup is the only current valid value. |
| **date** | Publish date in ISO format. |
| **version_major** | Major version number for setup. |
| **version_minor** | Minor version number for setup. |
| **version_subminor** | Sub minor version number for setup. |

### Bootloader block:id=bootloader_xml

```xml
<boot>
  <algorithm>Algorithm code</algorithm>
  <blocksize>Size of each block</blocksize>
  <blockcount>Number of blocks</blockcount>
</boot>
```

The bootloader block specify the bootloader algorithm that should be used to download firmware code to the module. The code for a specific module is defined in standard register *151/0x97*. The possible codes is here [CLASS1.PROTOCOL, Type=12](./class1.protocol.md#id=type12).

Firmware listed in the *Module Description File* file block have a [targetcode](#firmware) as an attribute. This code specify the hardware for a version of the a module the firmware is intended for. Typically the code is different for modules of the same type which have different versions of micro processor, memory, peripherals etc and therefore need different versions of the firmware. A bootloader should read this register and verify the targetcode with the content of the target code registers before loading firmware as loading wrong firmware version can brick a module.

### Registers:id=registers_xml

```xml
<registers>
  <reg>...</reg>
  <reg>...</reg>
  <reg>...</reg>
  <reg>...</reg>
  <reg>...</reg>
  <reg>...</reg>
</registers>
```

All defined registers of a module is defined in the registers block. The format is

```xml
<reg  name="symbolic name for register. Should be unique."
      page="The page that contains the register"
      offset="offset to register in the page"
      type="'std'(default)/'block'/'dmatrix1'"
      span="Number of registers for 'block' an 'dmatrix1' types. Default = 1"
      width="Width in bits for register (1-8 bits). Default = 8"
      size="(Deprecated) Size in bytes for register. Default = 1"
      min="Minimum value for register. Default = 0"
      max="Maximum value for register. Default = 255"
      access="r/w/rw"
      default="VSCP Works specific: Default value in string form. Default is 'UNDEF'". 
      fgcolor="VSCP Works specific: foreground color" 
      bgcolor="VSCP Works specific: background color" >
  <description lang="en">Description of register</description>
  <infourl lang="en">Link to url that have language specific information about the register</infourl>
  <remotevar>....</remotevar>
</reg>
```
An alternative (but deprecated) form is

```xml
<reg  page="The page that contains the register"
      offset="offset to register in the page"
      type="'std'(default)/'block'/'dmatrix1'"
      span="Number of registers for 'block' an 'dmatrix1' types. Default = 1"
      width="Width in bits for register (1-8 bits). Default = 8"
      size="(Deprecated) Size in bytes for register. Default = 1"
      min="Minimum value for register. Default = 0"
      max="Maximum value for register. Default = 255"
      access="r/w/rw"
      default="VSCP Works specific: Default value in string form. Default is 'UNDEF'". 
      fgcolor="VSCP Works specific: foreground color" 
      bgcolor="VSCP Works specific: background color" >
  <name lang="en">symbolic name for register Should be unique.</name>
  <description lang="en">Description of register</description>
  <infourl lang="en">Link to url that have language specific information about the register</infourl>
  <access>rw</access>
  <remotevar>....</remotevar>
</reg>
```

#### Attributes

| Name      | Description  | 
| :----     | :----------- | 
| **name**   | A name for the item. Should be unique.|
| **page**   | The page on whish the register is located. |
| **offset** | The zero based offset on the page where the register is defined. Level I: 0-127. Level II: 0-0xFFFFFFFE |
| **type**   | Specify the register type. A register is by default defined as 'std' which is a standard register. But 'block' can be used for a consecutive number of registers. Another form is 'dmatrix1' which is the standard level I decision matrix. For the non standard form span tells the number of registers used in the block and the full decision matrix |
| **span**   | Number of bytes for the register. This defaults to one as expected. But for the 'block' and the 'dmatrix1' types it tell the number of consecutive bytes used. Both 'block' and 'dmatrix1' types of registers will get names specified from the name attribute with a incrementing number appended for each register (name1, name2, name3...) |
| **width**   | Can be used to limit the registers bit width from 8-1. Default is eight. |
| **size**   | (Deprecated. Do not use) Size in bytes for register. Default = 1 |
| **min**   | Minimum value for register. Default = 0 |
| **max**   | Maximum value for register. Default = 255 |
| **access** | Specify the access rights for the register. Can be 'r' (read), 'w' (write) or 'rw' (read/write. Default is 'rw' |
| **default** | VSCP Works specific: Default value in string form. Default is 'UNDEF' Used by VSCP Works to restore default value to a register. |
| **fgcolor** | VSCP Works specific: foreground color. Used as foreground color by VSCP Works when rendering this register row. |
| **bgcolor** | VSCP Works specific: background color. Used as background color by VSCP Works rendering this register row. |
| **remotevar** | You are able to define a remote variable embeded in a register definitition. All key/value values that are available for remotevar below is available here to. Absent key/value values will have defaults from the register defines. If left without content defaults will be used for all key/value pairs. |


Any number of language specific descriptions and/or infourl's can be set for each register item. If no language attribute is given "en" for English will be used. The language code should be a valid two letter code (ISO 639-1 code)[https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes6].

The 'name' tag can be set also in a none attribute way. This is true for the 'access' tag as well. This usage is deprecated.

#### Example 1
A typical register definition:

```xml
<registers>
  <reg name="Zone"
      page="0" 
      offset="0"
      access="readwrite" 
      default="0x11" 
      gcolor="0x01000" 
      bgcolor="0x0003d4">
    <description lang="en">Zone this module belongs to</description>
  </reg>
  <reg name="Subzone"
      page="0" 
      offset="1"
      access="readwrite" 
      default="0x01" 
      gcolor="0x01000" 
      bgcolor="0x0003d4">
    <description lang="en">Subzone this module belongs to</description>
  </reg>  
</registers>
```

#### Example 2
A register with max min values and which just use four bits and language dependent descriptions.

```xml
<registers>
  <reg name="limited register"
      page="0x30" 
      offset="88"
      access="rw" 
      width="0x04"
      min="0"
      max="15">
    <description lang="en">Limited register</description>
    <description lang="se">Begränsat register</description>
    <description lang="lt">Ribotas registras</description>
    <description lang="zh">有限的寄存器</description>
  </reg> 
</registers>
```

#### Example 3
A register of block type

```xml
<registers>
  <reg name="Control_register"
      page="11" 
      offset="0x55"
      span="8"
      access="r" 
      type="block">
    <description lang="en">
      This is register of block type.\n
      Description is\n
      multiline\n
    </description>
  </reg> 
</registers>
```

When rendered in VSCP Works or other programs this be rendered as:

```
control_register0
control_register1
control_register2
control_register3
control_register4
control_register5
control_register6
control_register7
```

#### Register value lists:id=register_value_lists_xml

Register definitions can have values lists. A value list is a list of values that can be used for a register.

```xml
<reg name="RegValueList" 
     page="0" 
     offset="1" 
     default="88"
     access="rw">
  <description lang="en">English description of the register.</description>
  <description lang="se">Svensk beskrivning av registret.</description>
  <valuelist>
    <item name="Item0" value="0x0">
      <description lang="en">Description item 0</description>
      <infourl lang="en">InfoURL item 0</infourl>
    </item>
    <item name="Item1" value="0x1">
      <description lang="en">Description item 1</description>
      <infourl lang="en">InfoURL item 1</infourl>
    </item>
    <item name="Item2" value="0x2">
      <description lang="en">Description item 2</description>
      <infourl lang="en">InfoURL item 2</infourl>
    </item>
  </valuelist>
</reg>
```

The valuelist specify a number of values (*items*)  that can be used for a register. These values will be rendered as a drop down list in VSCP Works from which the user can select a value. Each item have a name and a value. The name is used to identify the item in the drop down list. The value is the actual value that will be used when the register is written. Language dependent descriptions and/or infourl's can be set for each item. If no language attribute is given "en" for English will be used. The language code should be a valid two letter code (ISO 639-1 code)[https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes6].

##### Attributes

| Name      | Description  | 
| :----     | :----------- | 
| **name**   | A name for the value item. |
| **value**   | Value for the item. |

Any number of language specific descriptions and/or infourl's can be set for each value item. If no language attribute is given "en" for English will be used. The language code should be a valid two letter code (ISO 639-1 code)[https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes6].

#### Register bit fields:id=register_bit_fields_xml

You can define a register as a bit field. A bit field is a register that is split into a number of bits. The bits are defined in a bit field list. There can be a maximum of eight bits defined for a register.

```xml
<reg name="RegBits" 
     page="0" 
     offset="14"
     access="rw">
  <description lang="en">Register bits</description>
  <bit name="Bit0"
       pos="0" 
       width="2" 
       default="2"> 
    <description lang="en">Reserved.</description>
    <description lang="se">Reserverad.</description>
    <infourl lang="en">en url0</infourl>
    <infourl lang="se">se url0</infourl>
    <valuelist>
      <item value="0" name="Bit value 0">
        <description lang="en">Bit value description item 0</description>
        <infourl lang="en">Bit url0</infourl>
      </item>
      <item value="1" name="Bit value 1">
        <description lang="en">Bit value description item 1</description>
        <infourl lang="en">Bit url1</infourl>
      </item>
      <item value="2" name="Bit value 2">
        <description lang="en">Bit value description item 2</description>
        <infourl lang="en">Bit url2</infourl>
      </item>
      <item value="3" name="Bit value 3">
        <description lang="en">Bit value description item 3</description>
        <description lang="se">Bit värde beskrivning item 3</description>
        <infourl lang="en">Bit url3</infourl>
        <infourl lang="se">Bit url3 se</infourl>
      </item>
    </valuelist>
  </bit>
  <bit name="bit1"
       pos="2" 
       default="false">
    <description lang="en">Reserved1.</description>
  </bit>
  <bit name="bit2"
       pos="3" 
       default="false">
    <description lang="en">Reserved2.</description>
  </bit>
  <bit name="bit3"
       pos="4"
       width="3" 
       default="7"
       access="r"
       min="3",
       max="7">
</reg>
```

As seen above [valuelists](#register_value_lists) can be used for bit fields as well. See docs above.

##### Attributes

| Name      | Description  | 
| :----     | :----------- | 
| **name**  | A name for the bit field. |
| **pos**   | Bit position in the byte (0-7). |
| **width** | The number of bits in the bit field. If set to 2 with pos=0 then bit 0 and bit 1 will be used for the bit field. |
| **default** | Default value for the bit field. 'true'/'false' or a numerical value. |
| **min**   | Minimum value for register. Default = 0 |
| **max**   | Maximum value for register. Default = 255 |
| **access** | Specify the access rights for the register. Can be 'r' (read), 'w' (write) or 'rw' (read/write. Default is 'rw' |

Any number of language specific descriptions and/or infourl's can be set for each register item. If no language attribute is given "en" for English will be used. The language code should be a valid two letter code (ISO 639-1 code)[https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes6].

### Remote Variables (Abstractions):id=remote_variables_xml

Types for remote varaibles are documented [here](./vscp_register_abstraction_model.md#remote-variables)

```xml
<remotevars>
  <remotevar name="remotevariable1"
                type="uint16_t" 
                default="1234" 
                page="0" 
                offset="19"
                bitpos="0" 
                access="r"
                fgcolor="0x112233" 
                bgcolor="0xE0E0FF">
    <description lang="en">Remote variable description.</description>
    <description lang="se">Beskrivning av variable.</description>
    <infourl lang="en">Remote var url en</infourl>
    <infourl lang="se">Variabel url se</infourl>
  </remotevar>
</remotevars>  
```

or alternatively

```xml
<remotevars>
  <remotevar type="uint16_t" 
                default="1234" 
                page="0" 
                offset="19" 
                fgcolor="0x112233" 
                bgcolor="0xE0E0FF">
    <name>ch0_value</name>
    <description lang="en">A/D value for channel 0.</description>
    <description lang="se">A/D värde för kanal 0.</description>
    <infourl lang="en">Remote var url3</infourl>
    <infourl lang="se">Remote var url3 se</infourl>
    <access>r</access>
  </remotevar>
</remotevars>
```

Remote variables or *abstractions*, as they was named in previous versions of the VSCP specification, is a higher level view of register space. Here we look at the storage using well known variable typers such as stings, integers and floats. This makes it easier to use the register values in a configuration script etc.

All remote variables are mapped into register space and are stored there big endian, that is with the high byte in the first byte. An 16-bit integer will accordingly be stored with the MSB byte in the first register and the LSB in the second byte and so on.

There is no need to define remote variables for bytes as they are already defined in the register space. Automatic remote variables will be created for registers that do not have a remote variable defined. These will be named as follows:


_rv_<register_name>_

So for example if you have a register named "Reg1" then the remote variable will be named "_rv_reg1_".

Needless to say names with this pattern are reserved.

#### Attributes

| Name      | Description  | 
| :----     | :----------- | 
| **name**  | A name for the remote variable. |
| **type**  | A type for the remote variable. Remote variable types are [here](./vscp_register_abstraction_model.md#remote-variables). |
| **page**  | The page where the remote variable is stored. |
| **offset**  | The offset off the page where the MSB of the remote variable is stored. |
| **bitpos**  | The bit of a register used for a boolean. If not set and the type is boolean bit 0 will be used. No meaning for other types. |
| **size**  | The size of a remote variable that is of type string. The size is the max size of the buffer. |
| **access** | Specify the access rights for the remote variable. Can be 'r' (read), 'w' (write) or 'rw' (read/write. Default is 'rw' |
| **default** | Default value for the bit field. 'true'/'false' or a numerical value. |
| **min**   | Minimum value for register. Default = 0 |
| **max**   | Maximum value for register. Default = max for type |

In the same way as registers remote variables can also have valuelists and bit fields. See docs above.

#### Example with valuelist

```xml
<remotevar name="value_test1" 
      type="byte" 
      default="1" 
      page="1" 
      offset="24" 
      acess="rw"
      bgcolor="0xD8F2F5" >
  <description lang="en">Value test 1</description>
  <valuelist>
    <item name="item0" value="0x00">
      <description lang="en">Description item 0</description>
      <infourl lang="en">InfoURL item 0</infourl>
    </item>
    <item name="Item1" value="0x01" >
      <description lang="en">Description item 1</description>
      <infourl lang="en">InfoURL item 1</infourl>
    </item>
    <item name="Item2" value="0x02">
      <description lang="en">Description item 2</description>
      <infourl lang="en">InfoURL item 2</infourl>
    </item>
    <item name="Item3" value="0x03">
      <description lang="en">Description item 3</description>
      <infourl lang="en">InfoURL item 3</infourl>
    </item>
  </valuelist>
</remotevar>
```
#### Example with bit fields

```xml
<remotevar name="bit_test1" 
           type="byte" 
           default="0" 
           page="1" 
           offset="40" 
           acess="rw"
           bgcolor="0xD8F2F5" >
  <description lang="en">Bit test 1.</description>
  <bit name="reserved" pos="0" width="2" default="2">
    <description lang="en">Reserved.</description>
    <description lang="se">Reserverad.</description>
    <infourl lang="en">en url0</infourl>
    <infourl lang="se">se url0</infourl>
    <valuelist>
      <item value="0" name="Bit value 0">
        <description lang="en">Bit value description item 0</description>
        <infourl lang="en">Bit url0</infourl>
      </item>
      <item value="1" name="Bit value 1">
        <description lang="en">Bit value description item 1</description>
        <infourl lang="en">Bit url1</infourl>
      </item>
      <item value="2" name="Bit value 2">
        <description lang="en">Bit value description item 2</description>
        <infourl lang="en">Bit url2</infourl>
      </item>
      <item value="3" name="Bit value 3">
        <description lang="en">Bit value description item 3</description>
        <description lang="se">Bit värde beskrivning item 3</description>
        <infourl lang="en">Bit url3</infourl>
        <infourl lang="se">Bit url3 se</infourl>
      </item>
    </valuelist>
  </bit>
  <bit pos="1" default="false" name="Reserved1">
    <description lang="en">Reserved1.</description>
  </bit>
  <bit pos="2" default="false">
    <name>Reserved2</name>
    <description lang="en">Reserved2.</description>
  </bit>
  <bit pos="3" default="false">
    <name>Reserved3</name>
    <description lang="en">Reserved3.</description>
  </bit>
  <bit pos="4" default="false">
    <name>Reserved4</name>
    <description lang="en">Reserved4.</description>
  </bit>
  <bit pos="5" default="false">
    <name>Reserved5</name>
    <description lang="en">Reserved5.</description>
  </bit>
  <bit pos="6" default="false">
    <name>Reserved6</name>
    <description lang="en">Reserved6.</description>
  </bit>
  <bit pos="7" default="false">
    <name>Reserved7</name>
    <description lang="en">Reserved7.</description>
  </bit>
</remotevar>
```

### Alarms:id=alarm

```xml
<alarm>
  <bit pos="7" name="Reserved7">
    <description lang="en"> Reserved 7. </description>
    <infourl lang="en">https://www.somewhere.com/info7.html</infourl>
  </bit>
  <bit pos="6" name="Reserved7">
    <description lang="en"> Reserved 6. </description>
    <infourl lang="en">https://www.somewhere.com/info6.html</infourl>
  </bit>
  <bit pos="5" name="Reserved7">
    <description lang="en"> Reserved 5. </description>
    <infourl lang="en">https://www.somewhere.com/info5.html</infourl>
  </bit>
  <bit pos="4" name="Reserved7">
    <description lang="en"> Reserved 4. </description>
    <infourl lang="en">https://www.somewhere.com/info4.html</infourl>
  </bit>
  <bit pos="3" name="Reserved7">
    <description lang="en"> Reserved 3. </description>
    <infourl lang="en">https://www.somewhere.com/info3.html</infourl>
  </bit>
  <bit pos="2" name="Reserved7">
    <description lang="en"> Reserved 2. </description>
    <infourl lang="en">https://www.somewhere.com/info2.html</infourl>
  </bit>
  <bit pos="1" name="HighAlarm">
    <description lang="en"> High alarm. The value of one of the A/D channels has gone above the high alarm level. </description>
    <infourl lang="en">https://www.somewhere.com/info1.html</infourl>
  </bit>
  <bit pos="0" name="LowAlarm">
    <description lang="en"> Low alarm. The value of one of the A/D channels has gone under the low alarm level. </description>
    <infourl lang="en">https://www.somewhere.com/info0.html</infourl>
  </bit>
</alarm>
```

The alarm block specify the meaning of the alarm bits in the standard alarm register [128/0x80](./vscp_register_abstraction_model.md#register_abstraction_model). In the block there is a bit filed of max eight bit definitions each describing the alarm bits of the register. You just need to specify the bits that is used.

#### Attributes

| Name      | Description  | 
| :----     | :----------- | 
| **name**  | A name for the alarm bit. |

Any number of language specific descriptions and/or infourl's can be set for each register item. If no language attribute is given "en" for English will be used. The language code should be a valid two letter code (ISO 639-1 code)[https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes6].

### Decision Matrix:id=dm_xml

```xml
<dmatrix level="1" spart-page="3" start-offset="0" rowcnt="0" rowsize="8">
  <action name="action1" code="0x00">
    <description lang="en">English description of the action 0.</description>
    <description lang="se">Svensk beskrivning av action 0.</description>
    <infourl lang="en">url1_en</infourl>
    <infourl lang="se">url1_se</infourl>
    <param name="parameter" offset="0" min="0" max="3">
      <description lang="en">Description of parameter for action 0.</description>
      <infourl lang="en">https://www.somewhere.com/info0.html</infourl>
    </param>
  </action>
  <action name="action2" code="0x01">
    <description lang="en">English description of the action 1.</description>
    <description lang="se">Svensk beskrivning av action 1.</description>
    <infourl lang="en">url1_en</infourl>
    <infourl lang="se">url1_se</infourl>
    <param name="parameter" offset="0" min="0" max="3">
      <description lang="en">Description of parameter for action 1.</description>
      <infourl lang="en">https://www.somewhere.com/info0.html</infourl>
    </param>
  </action>
</dmatix>
```
or alternatively

```xml
<dmatrix>
  <level>1</level>
  <start page="3" offset="0"/>
  <rowcnt>4</rowcnt>
  <action code="0x00">
    <param offset="0" min="0" max="3">
      <name lang="en">Counter</name>
      <description lang="en"> Counter 0-3 to start. </description>
      <infourl lang="en">https://www.somewhere.com/info0.html</infourl>
    </param>
  </action>
</dmatix>
```

If the module have a [decision matrix](./vscp_decision_matrix.md) it can be defined here. You specify where in the register space the decision matrix is located and the numer of rows for the matrix. The decision matrix holds an array of actions. Each row in the matrix is a row in the register space. The actions are defined in the action block.

For a level I decision matrix there is one and only one parameter for each action. For Level II decision matrixes however there can be several (defined by the attribute *rowsize*). In both cases the parameter(s) is described in the param block. 

#### Attributes dmatrix

| Name      | Description  | 
| :----     | :----------- | 
| **level**  | Decision matrix level 1/2. Default=1. |
| **start-page**  | The page where the decision matrix is stored in register space. |
| **start-offset**  | The offset of the register page where the decision matrix is stored. |
| **rowcnt**  | Number of decision matrix rows. |
| **rowsize**  | Number of decision matrix bytes on each row. For a level I decision matrix this is always eight. Default=8. |

#### Attributes action

| Name      | Description  | 
| :----     | :----------- | 
| **name**  | Name for the action. |
| **code**  | The numerical code for the action (0-255). |

#### Attributes action parameter

| Name      | Description  | 
| :----     | :----------- | 
| **name**  | Name for the action parameter. |
| **offset**  | Parameter field offset. Always zero for level I decision matrix as it always have only one parameter. Default = 0 |
| **min**  | Minimum value for the parameter. Default = 0. |
| **max**  | Maximum value for the parameter. Default = 255. |

Any number of language specific descriptions and/or infourl's can be set for each register item. If no language attribute is given "en" for English will be used. The language code should be a valid two letter code (ISO 639-1 code)[https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes6].

##### Example

```xml
<dmatrix level="1" start-page="3" star-offset="0" rowcnt="4">
  <action name="NOOP" code="0x00">
    <description lang="en">No operation.</description>
    <description lang="se">Ingen operation.</description>
    <infourl lang="en">url0_en</infourl>
    <infourl lang="se">url0_se</infourl>
  </action>
  <action name="Start counter" code="0x01">
    <description lang="en"> Set the enable bit and thereby start the counter given by the argument which should be a value of 0-3 representing counter0 - counter3. </description>
    <description lang="se"> Sätt aktiveringsbiten och starta den räknare som anges av argumentet vilket skall vara ett värde 0-3 för counter0 - counter3. </description>
    <infourl lang="en">url1_en</infourl>
    <infourl lang="se">url1_se</infourl>
    <param name="counter" offset="0" min="0" max="3">
      <description lang="en"> Counter 0-3 to start. </description>
      <valuelist>
        <item name="Counter 0" value="0x00">
          <description lang="en">Counter 0.</description>
          <description lang="se">Räknare 0.</description>
          <infourl lang="en">url0_en</infourl>
          <infourl lang="se">url0_se</infourl>
        </item>
        <item name="Counter 1" value="0x01">
          <description lang="en">Counter 1.</description>
          <description lang="se">Räknare 1.</description>
          <infourl lang="en">cnt_url1_en</infourl>
          <infourl lang="se">cnt_url1_se</infourl>
        </item>
        <item value="0x02" name="counter2">
          <description lang="en">Counter 2.</description>
          <description lang="se">Räknare 2.</description>
          <infourl lang="en">cnt_url2_en</infourl>
          <infourl lang="se">cnt_url2_se</infourl>
        </item>
        <item name="Counter 3" value="0x33">
          <description lang="en">Counter 3.</description>
          <description lang="se">Räknare 3.</description>
          <infourl lang="en">cnt_url3_en</infourl>
          <infourl lang="se">cnt_url3_se</infourl>
        </item>
      </valuelist>
    </param>
  </action>
  <action code="0x02" name="Stop counter">
    <description lang="en"> Clear the enable bit and thereby stop the counter given by the argument which should be a value of 0-3 representing counter0 - counter3. </description>
    <param name="Counter">
      <description lang="en"> Counter 0-3 to start. </description>
      <valuelist>
        <item name="Counter 0" value="0x0">
          <description lang="en">Counter 0</description>
        </item>
        <item name="Counter 1" value="0x01">
          <description lang="en">Counter 1</description>
        </item>
        <item name="Counter 2" value="0x02">
          <description lang="en">Counter 2</description>
        </item>
        <item name="Counter 3" value="0x03">
          <description lang="en">Counter 3</description>
        </item>
      </valuelist>
    </param>
  </action>
  <action name="Clear counter" code="0x03">
    <description lang="en"> Clear the the value for the counter given by the argument which should be a value of 0-3 representing counter0 - counter3. </description>
    <param name="Counter">
    <description lang="en"> Counter 0-3 to start. </description>
    <valuelist>
      <item name="Counter 0" value="0x0">
        <description lang="en">Counter 0</description>
      </item>
      <item name="Counter 1" value="0x01">
        <description lang="en">Counter 1</description>
      </item>
      <item name="Counter 2" value="0x02">
        <description lang="en">Counter 2</description>
      </item>
      <item name="Counter 3" value="0x03">
        <description lang="en">Counter 3</description>
      </item>
    </valuelist>
  </param>
  </action>
  <action name="Reload counter" code="0x04">
    <name lang="en">Reload counter</name>
    <description lang="en"> Load the reload value to the counter given by the argument which should be a value of 0-3 representing counter0 - counter3. </description>
    <param name="Counter">
      <description lang="en"> Counter 0-3 to start. </description>
      <valuelist>
        <item name="Counter 0" value="0x0">
          <description lang="en">Counter 0</description>
        </item>
        <item name="Counter 1" value="0x01">
          <description lang="en">Counter 1</description>
        </item>
        <item name="Counter 2" value="0x02">
          <description lang="en">Counter 2</description>
        </item>
        <item name="Counter 3" value="0x03">
          <description lang="en">Counter 3</description>
        </item>
      </valuelist>
    </param>
  </action>
  <action name="Count" code="0x05">
    <description lang="en"> Add or subtract one from a counter depening on its count direction setting. </description>
    <param Name="Counter">
      <description lang="en"> Counter 0-3 to start. </description>
      <valuelist>
        <item name="Counter 0" value="0x0">
          <description lang="en">Counter 0</description>
        </item>
        <item name="Counter 1" value="0x01">
          <description lang="en">Counter 1</description>
        </item>
      </valuelist>
    </param>
  </action>
  <action name="ActionBits" code="0x06">
    <description>Action With Bits</description>
    <param name="ParamBits"> 
      <description lang="en">Param With Bits</description>
      <bit pos="0" width="4" name="Lowbits">
        <description lang="en">Test bit description low bits.</description>
        <description lang="se">Test bit beskrivning low bits.</description>
        <infourl lang="en">test infourl low bits</infourl>
        <infourl lang="se">test infourl låga bitar</infourl>
      </bit>
      <bit name="HighBits" pos="4" width="2">
        <description lang="en">Test bit description high bits.</description>
        <description lang="se">Test bit beskrivning high bits.</description>
        <infourl lang="en">test infourl high bits</infourl>
        <infourl lang="se">test infourl höga bitar</infourl>
      </bit>
      <bit name="ValueBits" pos="6" width="2">
        <description lang="en">Test bit description value bits.</description>
        <description lang="se">Test bit beskrivning value bits.</description>
        <infourl lang="en">test infourl value bits</infourl>
        <infourl lang="se">test infourl value bitar</infourl>    
        <valuelist>
          <description lang="en">Value list in bit array.</description>
          <item name="Value1">
            <description lang="en">Value1 description.</description>
            <description lang="se">Beskrivning av värde.</description>
            <infourl lang="en">Value1 infourl.</infourl>
            <infourl lang="se">Värde 1 infourl.</infourl>
          </item>
          <item name="Value2">
            <description lang="en">Value2 description.</description>
            <infourl lang="en">Value2 infourl.</infourl>
          </item>
        </valuelist>
      </bit>
    </param>
  </action>
</dmatrix>
```

### Events:id=events_xml

```xml
<events>
  <event Name="Counter data" class="xxxx" type="yyyy" priority="4" direction="out">
    <description lang="en">Info about event in english</description>
    <data name="byte0" offset="0">
      <name lang="en">English description of data byte 0</name>
      <infourl lang="en">https://www.somewhere.com/info0.html</infourl>
    </data>
    <data name="byte1" offset="1">
      <name lang="en">English description of data byte 1</name>
      <infourl lang="en">https://www.somewhere.com/info0.html</infourl>
    </data>
    <data name="byte2" offset="2">
      <name lang="en">English description of data byte 2</name>
      <infourl lang="en">https://www.somewhere.com/info0.html</infourl>
    </data>
  </event>
</events>
```

In the *event* block events that the module can receive and handle is described but maybe even more importantly events that the module send out itself can be 34 described. A *data* block is defined for each data byte of the event describing it.

For data blocks bit fields and value lists can be used. See description above for more information.

#### Attributes event

| Name      | Description  |
| :----     | :----------- |
| **name**  | Name for the event. |
| **class** | Event class. Mandatory. Can be set to '-' whish means all classes. |
| **type**  | Event type. Mandatory. Can be set to '-' whish means all types. |
| **priority** | Priority for the event. Default=3. |
| **dir**  | Direction of event. "in" is incoming event. "out" is outgoing event. Default="out" |

#### Attributes event data

| Name | Description  | 
| :----     | :----------- | 
| **name**  | Name for the event data byte. |
| **offset**  | Data byte offset. |

Event data can use value lists and bit fields. See description above for more information.

#### Example

```xml
<events>
  <event name="Counter data" class="0x00f" type="0x06" priority="4" dir="out">
    <description lang="en"> Count data steam event sent on regular intervals 
      if activated. Coding: Integer. Unit: none. </description>
    <data name="Datacoding" offset="0">
      <description lang="en"> Will contain 0b01100xxx where xxx is the counter 
      (0-3/4-7) and where 0-3 is the counter 32-bit value and 4-7 is the 
      32-bits of the 64-bit counter value stored internally. </description>
      </data>
      <data name="MSB of counter value" offset="1">
        <description lang="en"> Byte 0 (MSB) of 32-bit counter value. </description>
    </data>
    <data name="Counter value" offset="2">
      <description lang="en"> Byte 1 of 32-bit counter value. </description>
    </data>
    <data name="Counter value" offset="3">
      <description lang="en"> Byte 2 of 32-bit counter value. </description>
    </data>
    <data name="LSB of counter value" offset="4">
      <description lang="en"> Byte 3 (LSB) of 32-bit counter value. </description>
    </data>
  </event>
    <event name="Alarm occurred" class="0x001" type="0x01" priority="4" dir="out">
      <description lang="en"> If an alarm is armed this event is sent 
        when it occurs and the corresponding alarm bit is set in the 
        alarm register. </description>
      <data name="" offset="0">
        <name lang="en">Index</name>
        <description lang="en"> Counter alarm has occured on (0-3). </description>
      </data>
      <data name="" offset="1">
        <name lang="en">Zone</name>
        <description lang="en"> Is set to the zone for the module. </description>
      </data>
      <data name="" offset="2">
        <name lang="en">Sub zone</name>
        <description lang="en"> Sub zone for channel or sub zone for module if 
        channel sub zone is zero. </description>
      </data>
  </event>
  <event name="Frequency measurement" class="0x00A" type="0x09" 
    priority="4" dir="out">
    <description lang="en"> Frequency measurement event sent on regular 
      intervals if activated. Coding: 32-bit integer. Unit: Hertz. </description>
    <data name="Data coding" offset="0">
      <description lang="en"> Datacoding: 0b01100xxx where xxx is 
        the counter (0-3) </description>
    </data>
    <data name="Frequency 32-bit value (MSB)" offset="1">
      <description lang="en"> Frequency value as 32-bit floating point value 
        with MSB in first byte. </description>
    </data>
    <data name="Frequency 32-bit value" offset="2">
      <description lang="en"> Frequency value as 32-bit floating point value 
        with MSB in first byte. </description>
    </data>
    <data name="Frequency 32-bit value" offset="3">
      <description lang="en"> Frequency value as 32-bit floating point value 
        with MSB in first byte. </description>
    </data>
    <data name="Frequency 32-bit value (LSB)" offset="4">
      <description lang="en"> Frequency value as 32-bit floating point value 
        with MSB in first byte. </description>
    </data>
  </event>
  <event name="Measurement Event" class="0x00A" type="-" priority="4" dir="out">
    <description lang="en"> Measurement values of all kinds can be sent 
      as a result of linearization. 
      For example can an input counting S0 pulses be translated 
      to KWh and watt </description>
    <data name="Datacoding" offset="0">
      <description lang="en"> Datacoding: Always as a 
        32-bit floating point value. 
        0b101yyxxx where yy is the unit and xxx is the counter (0-3) </description>
    </data>
    <data name="32-bit floating point value (MSB)" offset="1">
      <description lang="en"> MSB of the 32-bit floating point value 
        that has been calculated from the 
        linearization equation. </description>
    </data>
    <data name="32-bit floating point value" offset="2">
      <description lang="en"> 32-bit floating point value that has been calculated 
        from the linearization equation. </description>
    </data>
    <data name="32-bit floating point value" offset="3">
      <description lang="en"> 32-bit floating point value that has been calculated 
        from the linearization equation. </description>
    </data>
    <data name="32-bit floating point value (LSB)" offset="4">
      <description lang="en"> LSB of the 32-bit floating point value that has 
        been calculated from the linearization equation. </description>
    </data>
  </event>
</events>
```

## Real life MDF XML formatted file examples

### Kelvin NTC10K

The Kelvin NTC10K is one of [Grodans Paradis AB's](https://www.grodansparadis.com/) modules and it has it's product page [here](https://github.com/grodansparadis/can4vscp-kelvin-ntc10k). The MDF file for this modules is [here](https://www.eurosource.se/ntc10KA_1.xml).

### Paris relay module

The Paris module is another module from Grodans Paradis AB and it is documented [here](https://github.com/grodansparadis/can4vscp-paris). The MDF file for this modules is [here](https://www.eurosource.se/paris_010.xml).

---

## JSON Format Specification

### General JSON format

JSON is a file containing objects and arrays. Each item in an object is a key value pair. Each item in an array is an object item. Values and items can be strings, numbers, booleans or objects. Forming a tree like structure. 

```json
{
  "redirect": "http://www.example.com/",
  "module": {
    ...  
    "manufacturer": {
      ...
    },
    "boot" : {
      ...
    },
    "files" : {
      "picture" : [
        {
          ...
        },
        {
          ...
        }
      ],
      "video" : [
        {
          ...
        },
        {
          ...
        }
      ],
      "firmware" : [
        {
          ...
        },
        {
          ...
        }
      ],
      "manual" : [
        {
          ...
        },
        {
          ...
        }
      ],
      "driver" : [
        {
          ...
        },
        {
          ...
        }
      ],
      "setup" : [
        {
          ...
        },
        {
          ...
        }
      ],
    },
    "register" : [
      {
        ...
      },
      {
        ... 
      }
    ],
    "remotevar" : [
      {
        ...
      },
      {
        ... 
      }
    ],
    "alarm" : {
        ...
    },
    "dmatrix": {
        ...
    },
    "event" : [
      {
        ...
      },
      {
        ... 
      }
    ]
  }  
}
	
```

| JSON elements | Description |
| ----- | ----------- |
| **redirect** | Redirect URL for the module. If it's there the MDF file will not be parsed instead parsaing will be done on the file the redirect url points to. |
| **module** | Module information. Th erest of thetags are inside the module object. |
| **manufacturer** | Manufacturer information. |
| **boot** | Boot information. |
| **files** | Files information. Picture, Video, firmware, driver, manual and setup files related to the module is defined here. |
| **register** | Register information is defined here. |
| **remotevar** | Remote variable information is defined here. |
| **alarm** | Alarm information. |
| **dmatrix** | Decission matrix information. |
| **event** | Event information. |

### A note on JSON file content

### Descriptions
Many keys can be defined both as string, number or object. The description key is typical. It can have a value that is a string in which case it is set as an english description. But it can also be an object in which case the language is defined as keys to each description in that language. The language key shall be set as a two character (ISO 639-1 lanuage code)[https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes6].

Like this

```json
"description": "description in english"
```

or multilingual as this

```json
"description" : {
	"eng": "English description",
	"swe": "Svensk beskrivning"
}
```
Language tags is two letter [ISO 3166-1 alpha-2](https://en.wikipedia.org/wiki/ISO_3166-1_alpha-2)

### infourl

Info URL's point to a web page that contains information about the item where they are located. The same is tru for them as for descriptions. They can be defined like this


```json
"infourl": "url to info in english "
```

or multilingual as this

```json
"infourl" : {
	"eng": "English info url",
	"swe": "Svensk info url"
}
```
Language tags is two letter [ISO 3166-1 alpha-2](https://en.wikipedia.org/wiki/ISO_3166-1_alpha-2)

### numbers

As JSON can only handle decimal numbers it is possible to define positive numbers as hexadecimal, octal or binary using a string form. If the number has no prefix is will be interpreted as a decimal number, if it has a **0x** prefix it vill be interprested as a hexadecimal number, if it has a **0o** prefix it will be interpreted as an octal number and if it has a **0b** prefix it will be interpreted as a binary number.

 - **12** will be interpreted as a decimal number.
 - **0xFF00** will be interpreted as a hexadecimal number.
 - **0o7700** will be interpreted as an octal number.
 - **0b11010101** will be interpreted as a binary number.

This is only valid for numbers that is positive. Negative numbers are not supported in this way and must be of numeric type.

## Module
In the **module**-object the module is described. Currently only one module can be defined in a mdf file. This may change in the future.

```json
{
  "redirect": "http://www.example.com/",
  "module" : {
    ....
  }
}
```

| Name | Description |
| ----- | ----------- |
| **redirect** | Redirect URL for the module. If it's there the MDF file will not be parsed instead parsaing will be done on the file the redirect url points to. |
| **module** | Module information. Th erest of thetags are inside the module object. |
| **manufacturer** | Manufacturer information. |
| **boot** | Boot information. |
| **files** | Files information. Picture, Video, firmware, driver, manual and setup files related to the module is defined here. |
| **register** | Register information is defined here. |
| **remotevar** | Remote variable information is defined here. |
| **alarm** | Alarm information. |
| **dmatrix** | Decission matrix information. |
| **event** | Event information. |

### Redirect
If set the redirect key should be the first key-pair in the module object. The redirect key can be used to tell the parser to download the MDF from a different URL. If it is defined the file pointed to by the redirect url should be downloaded and parsed instead of the loaded MDF file.

### Module information

Every module should have an initial block that describes the module. This block is called the **General module information**. The block looks like this

```json
{
  "module": {
    "level": "1/2",
    "name": "Simple B test",
    "model": "Simple B model",
    "version": "B",
    "changed": "2021-11-02",
    "description": {
      "en": "This is an english description",
      "es": "Esta es una descripción en inglés",
      "pt": "Esta é uma descrição em inglês",
      "zh": "这是英文说明",
      "se": "Det här är en engelsk beskrivning",
      "lt": "Tai yra angliškas aprašymas",
      "de": "Dies ist eine englische Beschreibung",
      "eo": "Ĉi tio estas angla priskribo"
    },
    "infourl": {
      "en": "https://www.english.en",
      "es": "https://www.spanish.es",
      "pt": "https://www.portuguese.pt",
      "zh": "https://www.chineese.zh",
      "se": "https://www.swedish.se",
      "lt": "https://www.lithuanian.lt",
      "de": "https://www.german.de",
      "eo": "https://www.esperanto.eo"
    },
    "buffersize": 8,

  "manufacturer": {
    "name" : "Grodans Paradis AB",
    "address": {
      "street": "Brattbergavägen 17",
      "city": "Los",
      "town": "Loos",
      "postcode": "82770",
      "state": "HA",
      "Region": "Hälsingland",
      "country" : "Sweden"
    },
    "telephone": [
      {
        "number": "+46 8 40011835",
        "description": {
          "en": "Main Reception",
          "se": "Huvudreception"
        }
      }
    ],
    "fax": [
      {
        "number": "+46 8 40011835",
        "description": {
          "en": "Non working fax",
          "se": "Icke fungerande fax"
        }
      }
    ],
    "email": [
      {
        "address": "support@grodansparadis.com",
        "description": {
          "en": "Support email"
        }
      },
      {
        "address": "sales@grodansparadis.com",
        "description": "Sales inquires email"
      },
      {
        "address": "info@grodansparadis.com",
        "<description": {
          "en": "General email"
        }
      }
    ],
    "web": [
      {
        "address": "http://www.grodansparadis.com",
        "description": {
          "en": "Main web site"
        }
      },
      {
        "url": "http://shop.grodansparadis.com",
        "description": {
          "en": "on-line store"
        }
      }
    ]
  }
}
```

#### level
Level of the VSCP protocol this module works with. Can be 1 or 2 and defaults to 1 if not present.

#### name
Name is the name of the module. A unique describing name is recommended. This name will be translated to lower case and is used as the name of the module when referring to it in software.

#### model
This is the model of the module. Format is defined by the designer.

#### version
This is the version of the module. Format is defined by the designer.

#### description
The description is a short description of the module. It is recommended to use a language specific description. If no language attribute is given "en" for English will be used. The language code should be a valid two letter (ISO 639-1 code)[https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes6].

Descriptions can be multiline and can use "\n" to define a new line.

As an example

```json
{
  "decription": {
    "en" : "xxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "lt" : "yyyyyyyyyyyyyyyyyyyyyyyyyyyy",
    "es" : "zzzzzzzzzzzzzzzzzzzzzzzzzzzz"
  }
}
```

will create an English, Lithuanian, and a Spanish description. Software that handle languages can then switch between languages fast and efficiently.

#### infourl
The infourl is an url pointing to a full description of the module in the language given by the **lang** attribute. It is recommended to use a language specific infourl. If no language attribute is given "en" for English will be used. The language code should be a valid two letter (ISO 639-1 code)[https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes6].

As an example

```json
{
  "infourl": {
    "en" : "https://www.somewhere.com",
    "lt" : "https://www.somewhere.lt",
    "es" : "https://www.somewhere.es"
}
```

points to web pages that have info in three different languages.

#### buffersize
For Level II nodes the buffer size specify the max VSCP data a node can receive.  This makes it possible to have nodes, that due to low internal resources, that can receive events, but not all events, just those under a specified maximum size. The default is eight bytes which is the data size for a level I node. Set to <= 512 for a level II nodes.

### manufacturer:id=manufacturer_json
The manufacturer block describes the manufacturer of the module.

#### name
Name is the name of the company that manufactured the module.


#### Address
The address block looks like this

```json
{
  "address": {
    "street": "Brattbergavägen 17",
    "city": "Los",
    "town": "Loos",
    "postcode": "82770",
    "state": "HA",
    "Region": "Hälsingland",
    "country" : "Sweden"
  }
}
```

and specify the address to the manufacturer of the module. Use the tags that are appropriate for your project.


#### Telephone
This is a phone number of the manufacturer. As many phone numbers as one like can be defined. The format is

```json
{
  "telephone": [
    {
      "number": "+46 8 40011835",
      "description": {
        "en": "Main Reception",
        "se": "Huvudreception"
      }
    }
  ]
}
```
The infourl is optional.

#### Fax
This is a telefax number of the manufacturer. As many fax numbers as one like can be defined. The format is

```json
{
  "fax": [
    {
      "number": "+46 8 40011835",
      "description": {
        "en": "Non working fax",
        "se": "Icke fungerande fax"
      }
    }
  ]
}
```
The infourl is optional.

#### Email
This is an email address of the manufacturer. As many email addresses as one like can be defined. The format is

```json
{
  "email": [
    {
      "address": "info@vscp.org",
      "description": {
        "en": "General email"
      },
      "infourl": "https://www.somewhere.com"
    }
  ]
}
```
The infourl is optional.

#### Web
This is a web address of the manufacturer. As many web addresses as one like can be defined. The format is

```json
{
  "web": [
    {
      "address": "http://www.vscp.org",
      "description": {
        "en": "General web site"
      },
      "infourl": "https://www.somewhere.com"
    }
  ]
}
```

The infourl is optional.

### boot:id=boot_json

```json
{
  "boot": {
    "algorithm": 1,
    "blocksize": 8,
    "blockcount": 4096,
  }
}
```

The bootloader object specify the bootloader algorithm that should be used to download firmware code to the module. The code for a specific module is defined in standard register *151/0x97*. The possible codes is here [CLASS1.PROTOCOL, Type=12](./class1.protocol.md#id=type12).

Firmware listed in the *Module Description File* file block have a [targetcode](#firmware) as an attribute. This code specify the hardware for a version of the a module the firmware is intended for. Typically the code is different for modules of the same type which have different versions of micro processor, memory, peripherals etc and therefore need different versions of the firmware. A bootloader should read this register and verify the targetcode with the content of the target code registers before loading firmware as loading wrong firmware version can brick a module.

### Files:id=files_json

```json
{
  "files": [
    {
      ...
    },
  ],
  "video": [
    {
      ...
    }
  ],
  "firmware": [
    {
      ...
    }
  ],
  "driver": [
    {
      ...
    }
  ],
  "manual": [
    {
      ...
    }
  ],
  "setup": [
    {
      ...
    }
  ]
}
```
#### picture:id=picture_json

In the picture block you can specify a link to an image file that in some way is related the module and describe it. The format is

```json
"files" : [
  "picture" : [
    {
     "url" : "path",
     "format" : "jpeg",
     "date" : "ISO date",
     "version_major" : "a",
     "version_minor" : "b",
     "version_subminor" : "c",
      "url" : "https://www.somewhere.com/picture.jpg",
      "description" :  {
        "en" : "Description of picture"
      },
      "infourl" : {
        "en" : "htps://www.somewhere.com"
      }
    }
  ]
]
```

Any number of anguage specific descriptions and/or infourl's can be set for each picture item. If no language attribute is given "en" for English will be used. The language code should be a valid two letter code (ISO 639-1 code)[https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes6].

##### Keys

| Name      | Description  | 
| :----     | :----------- | 
| **name**   | A name for the item. |
| **url**   | The url from which the picture file can be fetched. |
| **path**  | (Deprecated alternative to "url"). The url to the picture file. |
| **format** | The format of the picture file. "png", "jpeg" and "jpg" is current valid values. |

#### video:id=video_json

In the video block you can specify a link to a video file that in some way is related the module and describe it. The format is

```json
"files" : [
  {
    "video" : [
      { 
        "url" : "path",
        "format" : "mp4",
        "url" : "https://www.somewhere.com/video.mp4",
        "description" : {
          "en" : "Description of picture"
        },
        "infourl" : {
          "en" : "htps://www.somewhere.com"
        }
      }
    ]
  }
]
```

Any number of language specific descriptions and/or infourl's can be set for each video item. If no language attribute is given "en" for English will be used. The language code should be a valid two letter code (ISO 639-1 code)[https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes6].

##### Keys

| Name      | Description  | 
| :----     | :----------- | 
| **name**   | A name for the item. |
| **url**   | The url from which the video file can be fetched. |
| **path**  | (Deprecated alternative to "url"). The url to the video file. |
| **format** | The format of the video file. "mp4", "mov" and "avi" is current valid values. |

#### manual:id=manual_json

In the manual block you can specify a link to a manual file that in some way is related to the module and describe it. The format is

```json
"files" : [
  {
    "manual" : [
      { 
        "name" : "driver1",
        "url" : "path",
        "format" : "pdf",
        "url" : "https://www.somewhere.com/manual.pdf",
        "description" : {
          "en" : "Description of picture"
        },
        "infourl" : {
          "en" : "htps://www.somewhere.com"
        }
      }
    ]
  }
]
```

Any number of language specific descriptions and/or infourl's can be set for each manual item. If no language attribute is given "en" for English will be used. The language code should be a valid two letter code (ISO 639-1 code)[https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes6].

##### Keys

| Name      | Description  | 
| :----     | :----------- | 
| **name**   | A name for the item. |
| **url**   | The url from which the video file can be fetched. |
| **path**  | (Deprecated alternative to "url"). The url to the video file. |
| **format** | The format of the video file. "txt", "md" (markdown), "html" and "pdf" is current valid values. |
| **lang**  | The language of the manual. The language code should be a valid two letter code (ISO 639-1 code)[https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes6]. |

In the driver object you can specify a link to a driver for a specific version of an operation system file that in some way is related the module and describe it. Typically this is a device driver or a VSCP daemon driver or similar. zip and gz packed files are allowed. The format is

#### driver:id=driver_json


```json
"files": [
  {
    "driver": [
      {
        "name": "driver1",
        "url": "path",
        "type":"mp4", 
        "os": "windows",
        "osver": 10,
        "version_major": 1,
        "version_minor": 0, 
        "version_subminor": 0,
        "url": "https://www.somewhere.com/driver.zip",
        "description": {
          "en": "Description of driver"
        },
        "infourl": {
          "en": "htps://www.somewhere.com"
        }
      }
    ]
  }
]
```

Any number of language specific descriptions and/or infourl's can be set for each driver item. If no language attribute is given "en" for English will be used. The language code should be a valid two letter code (ISO 639-1 code)[https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes6].

##### Keys

| Name      | Description  | 
| :----     | :----------- | 
| **name**   | A name for the item. |
| **url**   | The url from which the video file can be fetched. |
| **path**  | (Deprecated alternative to "url"). The url to the video file. |
| **os** | The operating system. Examples are "Debian Linux", "Microsoft Windows" etc |
| **osver** | The version of the operating system. Examples are "10", "8.1" etc |
| **version_major** | Major version number for driver. |
| **version_minor** | Minor version number for driver. |
| **version_subminor** | Sub minor version number for driver. |
| **md5** | MD5 checksum for the driver file as hexadecimal string. Empty if not used. |

#### setup:id=setup_json

In the setup block you can specify a link to a setup file that contain a VSCP setup script that do a specific setup of the device. The format is

```json
"files" : [
  {
    "setup" : [
      {
        "name" : "setup1",
        "url" : "path",
        "format" : "pdf",
        "url" : "https://www.somewhere.com/setup.js",
        "description": {
          "en": "Description of driver"
        },
        "infourl": {
          "en": "htps://www.somewhere.com"
        }
      }
    ]
  }  
]
```

Any number of language specific descriptions and/or infourl's can be set for each setup item. If no language attribute is given "en" for English will be used. The language code should be a valid two letter code (ISO 639-1 code)[https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes6].

##### Keys

| Name      | Description  | 
| :----     | :----------- | 
| **name**   | A name for the item. |
| **url**   | The url from which the video file can be fetched. |
| **path**  | (Deprecated alternative to "url"). The url to the video file. |
| **format** | The format of the setup file. "vscpjs" for VSCP javascript setup is the only current valid value. |

### Register:id=register_json

```json
{
  "register" : [
    {
      ...
    }
    {
      ...
    }
    {
      ...
    }
  ]
}
```

All defined registers of a module is defined in the registers block. The format is

```json
{
  "register" : [ 
    {  
      "name" : "symbolic name for register. Should be unique.",
      "page" : "The page that contains the register",
      "offset" : "offset to register in the page",
      "type" : "'std'(default)/'block'/'dmatrix1'",
      "span" : "Number of registers for 'block' an 'dmatrix1' types. Default = 1",
      "width" : "Width in bits for register (1-8 bits). Default = 8",
      "size" : "(Deprecated) Size in bytes for register. Default = 1",
      "min" : "Minimum value for register. Default = 0",
      "max" : "Maximum value for register. Default = 255",
      "access" : "r/w/rw",
      "default": "VSCP Works specific: Default value in string form. Default is 'UNDEF'", 
      "fgcolor": "VSCP Works specific: foreground color", 
      "bgcolor" : "VSCP Works specific: background color",
      "description" : [
          "en" : "Description of register"
      ],
      "infourl" : [
        "en" : "Link to url that have language specific information about the register"
      ].
      "remotevar" : {
        ...
      }
    }
  ]
}
```

#### Keys

| Name      | Description  | 
| :----     | :----------- | 
| **name**   | A name for the item. Should be unique.|
| **page**   | The page on whish the register is located. |
| **offset** | The zero based offset on the page where the register is defined. Level I: 0-127. Level II: 0-0xFFFFFFFE |
| **type**   | Specify the register type. A register is by default defined as 'std' which is a standard register. But 'block' can be used for a consecutive number of registers. Another form is 'dmatrix1' which is the standard level I decision matrix. For the non standard form span tells the number of registers used in the block and the full decision matrix |
| **span**   | Number of bytes for the register. This defaults to one as expected. But for the 'block' and the 'dmatrix1' types it tell the number of consecutive bytes used. Both 'block' and 'dmatrix1' types of registers will get names specified from the name attribute with a incrementing number appended for each register (name1, name2, name3...) |
| **width**   | Can be used to limit the registers bit width from 8-1. Default is eight. |
| **size**   | (Deprecated. Do not use) Size in bytes for register. Default = 1 |
| **min**   | Minimum value for register. Default = 0 |
| **max**   | Maximum value for register. Default = 255 |
| **access** | Specify the access rights for the register. Can be 'r' (read), 'w' (write) or 'rw' (read/write. Default is 'rw' |
| **default** | VSCP Works specific: Default value in string form. Default is 'UNDEF' Used by VSCP Works to restore default value to a register. |
| **fgcolor** | VSCP Works specific: foreground color. Used as foreground color by VSCP Works when rendering this register row. |
| **bgcolor** | VSCP Works specific: background color. Used as background color by VSCP Works rendering this register row. |
| **remotevar** | You are able to define a remote variable embeded in a register definitition. All key/value values that are available for remotevar below is available here to. Absent key/value values will have defaults from the register defines. If left without content defaults will be used for all key/value pairs. |

Any number of language specific descriptions and/or infourl's can be set for each register item. If no language attribute is given "en" for English will be used. The language code should be a valid two letter code (ISO 639-1 code)[https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes6].

Numeric values can be set as a numeric value or as a string. The string can be defined as a hexadecimal value (prefix: 0x, a decimal (no prefix), an octal value (prefix: 0o) or a binary value (prefix: 0b).

Note that

```
"remotevar" : {
}
```

is valid and will set all key/value pairs to defaults.

#### Value lists

Registers can have valuelists taht define valid possible values

```json
"valuelist" : [
  {
    "value" : "0x00",
    "name" : "Off",
    "description" : {
      "en" : "The device is off",
      "se" : "Enheten är av"
    },
    "infourl" : {
      "gb": "English help url",
      "se": "Svensk hjälp url",
      "lt": "Lietuvos padeda url"
    }
  },
  {
    "value" : "0x01",
    "name" : "On",
    "description" : {
      "en" : "The device is on",
      "se" : "Enheten är på"
    },
    "infourl" : {
      "gb": "English help",
      "se": "Svensk hjälp",
      "lt": "Lietuvos padeda"
    }
  },
  {
    "value" : "0xff",
    "name" : "Disabled",
    "description" : {
      "en" : "Device is disabled",
      "se" : "Enheten är avstängd"
    },
    "infourl" : {
      "gb": "English help",
      "se": "Svensk hjälp",
      "lt": "Lietuvos padeda"
    }
  }
]
```

#### Bit fields

Registers can have bit fields that define bits and groups of bits of the register. It is possible to use value lists for bit groups.

```json
"bit": [
  {
    "pos": 0,
    "width": 1,
    "default": 0,
    "min": 0,
    "max": 7,
    "access" : "rw",
    "name" : "English bit or bitfield name 0",
    "description" : {
      "gb": "English description bitfield 0",
      "se": "Svensk beskrivning bitfield 0",
      "lt": "Lietuvos aprašymas bitfield 0"
    },
    "infourl" : {
      "gb": "English help bitfield 0",
      "se": "Svensk hjälp bitfield 0",
      "lt": "Lietuvos padeda bitfield 0"
    },
    "valuelist" : [
      {
        "value" : "0x00",
        "name" : "Off",
        "description" : {
          "en" : "The device is off",
          "se" : "Enheten är av"
        },
        "infourl" : {
          "gb": "English help url",
          "se": "Svensk hjälp url",
          "lt": "Lietuvos padeda url"
        }
      },
      {
        "value" : "0x01",
        "name" : "On",
        "description" : {
          "en" : "The device is on",
          "se" : "Enheten är på"
        },
        "infourl" : {
          "gb": "English help",
          "se": "Svensk hjälp",
          "lt": "Lietuvos padeda"
        }
      },
      {
        "value" : "0x07",
        "name" : "Disabled",
        "description" : {
          "en" : "Device is disabled",
          "se" : "Enheten är avstängd"
        },
        "infourl" : {
          "gb": "English help",
          "se": "Svensk hjälp",
          "lt": "Lietuvos padeda"
        }
      }

    ]
  },
  {
    "pos": "0x03",
    "width": "0x02",
    "default": false,
    "access": "r",
    "min": "0x01",
    "max": "0x07",
    "name" : "English bit or bitfield name 1",
    "description" : {
      "gb": "English description bitfield 1",
      "se": "Svensk beskrivning bitfield 1",
      "lt": "Lietuvos aprašymas bitfield 1"
    },
    "infourl" : {
      "gb": "English help bitfield 1",
      "se": "Svensk hjälp bitfield 1",
      "lt": "Lietuvos padeda bitfield 1"
    }
  }
]
```

#### Example

```json
{
  "register" : [
      {
        "page": 2,
        "offset": "0x22",
        "span": 1,
        "width": 8,
        "min" : 2,
        "max" : 128,
        "access" : "rw",
        "default": 99,
        "rowpos" : 11,
        "bgcolor" : "0xfff3d4",
        "fgcolor" : "0x001200",        
        "name" : "Register example 1",
        "description" : {
          "en" : "Just a byte register with color settings",
          "se" : "Ett vanligt register med färginställningar"
        },
        "infourl" : {
          "en" : "https://one.com",
          "se" : "https://two.com"
        }
      },
      {
        "page": "0x02",
        "offset": "0x31",
        "default": "0x88",
        "width": "0x04",
        "span": "0x01",
        "min" : "0x00",
        "max" : "0x000f",
        "access" : "r",
        "default": "0xfd",
        "rowpos" : "0xaa",
        "bgcolor" : "0x00f3d4",
        "fgcolor" : "0x100000",
        "name" : "Register example 2",
        "description" : {
          "en" : "Register with value list",
          "se" : "Beskrivning med värde lista"
        },
        "infourl" : {
          "gb": "English help",
          "se": "Svensk hjälp",
          "lt": "Lietuvos padeda"
        },
        "valuelist" : [
          {
            "value" : "0x00",
            "name" : "Off",
            "description" : {
              "en" : "The device is off",
              "se" : "Enheten är av"
            },
            "infourl" : {
              "gb": "English help url",
              "se": "Svensk hjälp url",
              "lt": "Lietuvos padeda url"
            }
          },
          {
            "value" : "0x01",
            "name" : "On",
            "description" : {
              "en" : "The device is on",
              "se" : "Enheten är på"
            },
            "infourl" : {
              "gb": "English help",
              "se": "Svensk hjälp",
              "lt": "Lietuvos padeda"
            }
          },
          {
            "value" : "0xff",
            "name" : "Disabled",
            "description" : {
              "en" : "Device is disabled",
              "se" : "Enheten är avstängd"
            },
            "infourl" : {
              "gb": "English help",
              "se": "Svensk hjälp",
              "lt": "Lietuvos padeda"
            }
          }
        ]
      },
      {
        "name" : "Register example 3",
        "page": 99,
        "offset": 2,
        "default": "0x55",
        "width" : 8,
        "span" : 3,
        "type" : "block",
        "min" : 0,
        "max" : 255,
        "access" : "w",
        "rowpos" : "200",
        "bgcolor" : "0xfffff3d4",
        "fgcolor" : "0xffffffff",        
        "description" : {
          "en" : "Register with bits",
          "se" : "Beskrivning med bitar"
        },
        "infourl" : {
          "gb": "English help bits",
          "se": "Svensk hjälp bits",
          "lt": "Lietuvos padeda bits"
        },
        "bit": [
          {
            "pos": 0,
            "width": 3,
            "default": 4,
            "min": 0,
            "max": 7,
            "access" : "rw",
            "name" : "English bit or bitfield name 0",
            "description" : {
              "gb": "English description bitfield 0",
              "se": "Svensk beskrivning bitfield 0",
              "lt": "Lietuvos aprašymas bitfield 0"
            },
            "infourl" : {
              "gb": "English help bitfield 0",
              "se": "Svensk hjälp bitfield 0",
              "lt": "Lietuvos padeda bitfield 0"
            }
          },
          {
            "pos": "0x03",
            "width": "0x02",
            "default": false,
            "access": "r",
            "min": "0x01",
            "max": "0x07",
            "name" : "English bit or bitfield name 1",
            "description" : {
              "gb": "English description bitfield 1",
              "se": "Svensk beskrivning bitfield 1",
              "lt": "Lietuvos aprašymas bitfield 1"
            },
            "infourl" : {
              "gb": "English help bitfield 1",
              "se": "Svensk hjälp bitfield 1",
              "lt": "Lietuvos padeda bitfield 1"
            }
          }
        ]
      },
      {
        "name" : "Register example 4",
        "page": 12,
        "offset": 22,
        "span":128,
        "type": "dmatrix1"
      }
    ]    
  } 
}
```

### Remote variables:id=remotevars_json

Types for remote varaibles are documented [here](./vscp_register_abstraction_model.md#remote-variables)

```json
{
  "remotevars" : [
    {
      ...
    }
    {
      ...
    }
    {
      ...
    }
  ]
}
```
and each remote variable object looks like

```json
"remotevars" : [
  {
    "name" : "remotevariable1",
    "type" : "uint16_t",
    "default" : "1234",
    "page": 0,
    "offset": 19,
    "access" : "r",
    "fgcolor" : "0x112233" ,
    "bgcolor" : "0xE0E0FF",
    "description" : [ 
      {
        "en": "Remote variable description.",
        "se": "Beskrivning av variable."
      }
    ],
    "infourl": [ 
      {
        "en": "Remote var url en",
        "se": "Variabel url se"
      }
    ]
  }
]
```


Remote variables or *abstractions*, as they was named in previous versions of the VSCP specification, is a higher level view of register space. Here we look at the storage using well known variable typers such as stings, integers and floats. This makes it easier to use the register values in a configuration script etc.

All remote variables are mapped into register space and are stored there big endian, that is with the high byte in the first byte. An 16-bit integer will accordingly be stored with the MSB byte in the first register and the LSB in the second byte and so on.

There is no need to define remote variables for bytes as they are already defined in the register space. Automatic remote variables will be created for registers that do not have a remote variable defined. These will be named as follows:


_rv_<register_name>_

So for example if you have a register named "Reg1" then the remote variable will be named "_rv_reg1_".

Needless to say names with this pattern are reserved.
#### Keys

| Name      | Description  | 
| :----     | :----------- | 
| **name**  | A name for the remote variable. |
| **type**  | A type for the remote variable. Remote variable types are [here](./vscp_register_abstraction_model.md#remote-variables). |
| **page**  | The page where the remote variable is stored. |
| **offset**  | The offset off the page where the MSB of the remote variable is stored. |
| **bitpos**  | The bit of a register used for a boolean. If not set and the type is boolean bit 0 will be used. No meaning for other types. |
| **size**  | The size of a remote variable that is of type string. The size is the max size of the buffer. |
| **access** | Specify the access rights for the remote variable. Can be 'r' (read), 'w' (write) or 'rw' (read/write. Default is 'rw' |

In the same way as registers remote variables can also have valuelists and bit fields. See docs above.

#### Example with valuelist

```json
"remotevar" : [
  {
    "name" : "Remote variable 1",
    "type": "short", 
    "default":"8",
    "access": "rw",
    "page" :"2",
    "offset" :18,
    "rowpos": 99,
    "bgcolor" :"0xCCFFFF",
    "fgcolor" :"0x123456",
    
    "description" : {
      "en": "English description remotevar 1",
      "se": "Svensk beskrivning remotevar 1",
      "lt": "Lietuvos padeda remotevar 1"
    },
    "infourl" : {
      "gb": "English help remotevar 1",
      "se": "Svensk hjälp remotevar 1",
      "lt": "Lietuvos padeda remotevar 1"
    }
  },
  {
    "name" : "Remote variable 2",
    "type": "uint8", 
    "default": "0x22",
    "access": "r",
    "page" : "0x11",
    "offset" :"12",
    "rowpos": "0x04",
    "bgcolor" :"0x777777",
    "fgcolor" :"0x888888",        
    "description" : {
      "en": "English description remotevar 2",
      "se": "Svensk beskrivning remotevar 2",
      "lt": "Lietuvos padeda remotevar 2"
    },
    "infourl" : {
      "en": "English help remotevar 2",
      "se": "Svensk hjälp remotevar 2",
      "lt": "Lietuvos padeda remotevar 2"
    },
    "valuelist" : [
      {
        "value" : "0x00",
        "name" : "Low",
        "description" : {
          "en" : "Low speed",
          "se" : "Låg hastighet",
          "lt" : "??????????"
        },
        "infourl" : {
          "gb": "English help 1 vl2",
          "se": "Svensk hjälp 1 vl2",
          "lt": "Lietuvos padeda 1 vl2"
        }
      },
      {
        "value" : "0x01",
        "name" : "Medium",
        "description" : {
          "en" : "Medium speed",
          "se" : "Medium hastighet"
        },
        "infourl" : {
          "gb": "English help 2 vl2",
          "se": "Svensk hjälp 2 vl2",
          "lt": "Lietuvos padeda 2 vl2"
        }
      },
      {
        "value" : "0x03",
        "name" : "High",
        "description" : {
          "en" : "High speed",
          "se" : "Hög hastighet"
        },
        "infourl" : {
          "gb": "English help 3 vl2",
          "se": "Svensk hjälp 3 vl2",
          "lt": "Lietuvos padeda 3 vl2"
        }
      }
    ] 
  },
  {
    "name" : "Remote variable 3",
    "type": "uint32", 
    "default":"0",
    "access": "rw",
    "page" :"9",
    "offset" :98,
    "rowpos": "0x44",
    "bgcolor" :"0x999999",
    "fgcolor" :"0xAAAAAA",
    
    "description" : {
      "en": "English description 3",
      "se": "Svensk beskrivning 3",
      "lt": "Lietuvos padeda 3"
    },
    "infourl" : {
      "gb": "English help 3",
      "se": "Svensk hjälp 3",
      "lt": "Lietuvos padeda 3"
    },
    "bit": [
      {
        "pos": 0,
        "width": 3,
        "default": 4,
        "min": 0,
        "max": 7,
        "access" : "rw",
        "name" : "Bitfield name 0",
        "description" : {
          "gb": "English description bitfield 0",
          "se": "Svensk beskrivning bitfield 0",
          "lt": "Lietuvos aprašymas bitfield 0"
        },
        "infourl" : {
          "gb": "English help bitfield 0",
          "se": "Svensk hjälp bitfield 0",
          "lt": "Lietuvos padeda bitfield 0"
        }
      },
      {
        "pos": 3,
        "width": 2,
        "default": false,
        "access": "r",
        "name" : "Bitfield name 1",
        "description" : {
          "gb": "English description bitfield 1",
          "se": "Svensk beskrivning bitfield 1",
          "lt": "Lietuvos aprašymas bitfield 1"
        },
        "infourl" : {
          "gb": "English help bitfield 1",
          "se": "Svensk hjälp bitfield 1",
          "lt": "Lietuvos padeda bitfield 1"
        },
        "valuelist" : [
          {
            "value" : "0x00",
            "name" : "Low",
            "description" : {
              "en" : "Low speed",
              "se" : "Låg hastighet"
            },
            "infourl" : {
              "gb": "English help 1 vl2",
              "se": "Svensk hjälp 1 vl2",
              "lt": "Lietuvos padeda 1 vl2"
            }
          },
          {
            "value" : "0x01",
            "name" : "Medium",
            "description" : {
              "en" : "Medium speed",
              "se" : "Medium hastighet"
            },
            "infourl" : {
              "gb": "English help 2 vl2",
              "se": "Svensk hjälp 2 vl2",
              "lt": "Lietuvos padeda 2 vl2"
            }
          },
          {
            "value" : "0x03",
            "name" : "High",
            "description" : {
              "en" : "High speed",
              "se" : "Hög hastighet"
            },
            "infourl" : {
              "gb": "English help 3 vl2",
              "se": "Svensk hjälp 3 vl2",
              "lt": "Lietuvos padeda 3 vl2"
            }
          }
        ] 
      }
    ]
  }    
]
```


### Alarms:id=alarm_json

```json
"alarm" [
  { 
    "pos": "7", 
    "name": "Reserved7",
    "description": [ 
      {
        "en": "Reserved 7"
      }
    ],
    "infourl": [ 
      {
        "en": "https://www.somewhere.com/info7.html"
      }
    ]
  }
  { 
    "pos": "6", 
    "name": "Reserved6",
    "description": [ 
      {
        "en": "Reserved 6"
      }
    ],
    "infourl": [ 
      {
        "en": "https://www.somewhere.com/info6.html"
      }
    ]
  }
  { 
    "pos": "5",
    "name": "Reserved5",
    "description": [ 
      {
        "en": "Reserved 5"
      }
    ],
    "infourl": [ 
      {
        "en": "https://www.somewhere.com/info5.html"
      }
    ]
  }
  { 
    "pos": "4",
    "name": "Reserved4",
    "description": [ 
      {
        "en": "Reserved 4"
      }
    ],
    "infourl": [ 
      {
        "en": "https://www.somewhere.com/info4.html"
      }
    ]
  }
  { 
    "pos": "3", 
    "name": "Reserved3",
    "description": [ 
      {
        "en": "Reserved 3"
      }
    ],
    "infourl": [ 
      {
        "en": "https://www.somewhere.com/info3.html"
      }
    ]
  }
  { 
    "pos": "2", 
    "name": "Reserved2",
    "description": [ 
      {
        "en": "Reserved 2"
      }
    ],
    "infourl": [ 
      {
        "en": "https://www.somewhere.com/info2.html"
      }
    ]
  }
  { 
    "pos": "1", 
    "name": "HighAlarm",
    "description": [ 
      {
        "en": "High alarm. The value of one of the A/D channels has gone above the high alarm level."
      }
    ],
    "infourl": [ 
      {
        "en": "https://www.somewhere.com/info2.html"
      }
    ]
  }
  { 
    "pos": "0", 
    "name": "LowAlarm",
    "description": [ 
      {
        "en": "Low alarm. The value of one of the A/D channels has gone under the low alarm level."
      }
    ],
    "infourl": [ 
      {
        "en": "https://www.somewhere.com/info2.html"
      }
    ]
  }
]
```

The alarm block specify the meaning of the alarm bits in the standard alarm register [128/0x80](./vscp_register_abstraction_model.md#register_abstraction_model). In the block there is a bit filed of max eight bit definitions each describing the alarm bits of the register. You just need to specify the bits that is used.

#### Keys

| Name      | Description  | 
| :----     | :----------- | 
| **name**  | A name for the alarm bit. |

Any number of language specific descriptions and/or infourl's can be set for each register item. If no language attribute is given "en" for English will be used. The language code should be a valid two letter code (ISO 639-1 code)[https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes6].


### Decision Matrix:id=dm_json

```json
"dmatrix" : {
  "level" : 1,
  "start-page" : "0x10",
  "start-offset": 88,
  "rowcount" : 10,
  "rowsize" : 8,
  "action": [
    {
      "name": "action 1",
      "code": "0x01",
      "description" : {
        "en": "English description dm action 1",
        "se": "Svensk beskrivning dm action 1",
        "lt": "Lietuvos padeda dm action 1"
      },
      "infourl" : {
        "en": "English help dm action 1",
        "se": "Svensk hjälp dm action 1",
        "lt": "Lietuvos padeda dm action 1"
      },
      "param": [
        {
          "name" : "parm 1",
          "description" : {
            "en": "English description dm param 1",
            "se": "Svensk beskrivning dm param 1",
            "lt": "Lietuvos padeda dm param 1"
          },
          "infourl" : {
            "en": "English help dm param 1",
            "se": "Svensk hjälp dm param 1",
            "lt": "Lietuvos padeda dm param 1"
          }
        }
      ]
    }
  ]
}   

```

If the module have a [decision matrix](./vscp_decision_matrix.md) it can be defined here. You specify where in the register space the decision matrix is located and the numer of rows for the matrix. The decision matrix holds an array of actions. Each row in the matrix is a row in the register space. The actions are defined in the action block.

For a level I decision matrix there is one and only one parameter for each action. For Level II decision matrixes however there can be several (defined by the attribute *rowsize*). In both cases the parameter(s) is described in the param block. 

#### Keys dmatrix

| Name      | Description  | 
| :----     | :----------- | 
| **level**  | Decision matrix level 1/2. Default=1. |
| **start-page**  | The page where the decision matrix is stored in register space. |
| **start-offset**  | The offset of the register page where the decision matrix is stored. |
| **rowcnt**  | Number of decision matrix rows. |
| **rowsize**  | Number of decision matrix bytes on each row. For a level I decision matrix this is always eight. Default=8. |

#### Keys action

| Name      | Description  | 
| :----     | :----------- | 
| **name**  | Name for the action. |
| **code**  | The numerical code for the action (0-255). |

#### Keys action parameter

| Name      | Description  | 
| :----     | :----------- | 
| **name**  | Name for the action parameter. |
| **offset**  | Parameter field offset. Always zero for level I decision matrix as it always have only one parameter. Default = 0 |
| **min**  | Minimum value for the parameter. Default = 0. |
| **max**  | Maximum value for the parameter. Default = 255. |

Any number of language specific descriptions and/or infourl's can be set for each register item. If no language attribute is given "en" for English will be used. The language code should be a valid two letter code (ISO 639-1 code)[https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes6].

#### Example

```json
"dmatrix" : {
  "level" : 1,
  "start-page" : "0x10",
  "start-offset": 88,
  "indexed": false,
  "rowcount" : 10,
  "rowsize" : 8,
  "action": [
    {
      "name": "action 1",
      "code": "0x01",
      "description" : {
        "en": "English description dm action 1",
        "se": "Svensk beskrivning dm action 1",
        "lt": "Lietuvos padeda dm action 1"
      },
      "infourl" : {
        "en": "English help dm action 1",
        "se": "Svensk hjälp dm action 1",
        "lt": "Lietuvos padeda dm action 1"
      },
      "param": [
        {
          "name" : "parm 1",
          "description" : {
            "en": "English description dm param 1",
            "se": "Svensk beskrivning dm param 1",
            "lt": "Lietuvos padeda dm param 1"
          },
          "infourl" : {
            "en": "English help dm param 1",
            "se": "Svensk hjälp dm param 1",
            "lt": "Lietuvos padeda dm param 1"
          },
          "bit": [
            {
              "name" : "Bitfield name 0",
              "pos": 0,
              "width": 3,
              "default": 7,
              "min": 0,
              "max": 7,
              "access" : "rw",
              "description" : {
                "gb": "English description",
                "se": "Svensk beskrivning",
                "lt": "Lietuvos aprašymas"
              },
              "infourl" : {
                "gb": "English help",
                "se": "Svensk hjälp",
                "lt": "Lietuvos padeda"
              }
            },
            {
              "name" : "Bitfield name 1",
              "pos": 3,
              "width": 2,
              "default": false,
              "description" : {
                "gb": "English description",
                "se": "Svensk beskrivning",
                "lt": "Lietuvos aprašymas"
              },
              "infourl" : {
                "gb": "English help",
                "se": "Svensk hjälp",
                "lt": "Lietuvos padeda"
              },
              "valuelist" : [
                {
                  "value" : "0x00",
                  "name" : "Low",
                  "description" : {
                    "en" : "Low speed",
                    "se" : "Låg hastighet"
                  },
                  "infourl" : {
                    "gb": "English help 1 vl2",
                    "se": "Svensk hjälp 1 vl2",
                    "lt": "Lietuvos padeda 1 vl2"
                  }
                },
                {
                  "value" : "0x01",
                  "name" : "Medium",
                  "description" : {
                    "en" : "Medium speed",
                    "se" : "Medium hastighet"
                  },
                  "infourl" : {
                    "gb": "English help 2 vl2",
                    "se": "Svensk hjälp 2 vl2",
                    "lt": "Lietuvos padeda 2 vl2"
                  }
                },
                {
                  "value" : "0x03",
                  "name" : "High",
                  "description" : {
                    "en" : "High speed",
                    "se" : "Hög hastighet"
                  },
                  "infourl" : {
                    "gb": "English help 3 vl2",
                    "se": "Svensk hjälp 3 vl2",
                    "lt": "Lietuvos padeda 3 vl2"
                  }
                }
              ] 
            }
          ]
        },
        {
          "name" : "parm 2",
          "description" : {
            "en": "English description dm param 2",
            "se": "Svensk beskrivning dm param 2",
            "lt": "Lietuvos padeda dm param 2"
          },
          "infourl" : {
            "en": "English help dm param 2",
            "se": "Svensk hjälp dm param 2",
            "lt": "Lietuvos padeda dm param 2"
          }
        }              
      ]
    },
    {
      "name": "action 2",
      "code": "0x02",
      "description" : {
        "en": "English description dm action 2",
        "se": "Svensk beskrivning dm action 2",
        "lt": "Lietuvos padeda dm action 2"
      },
      "infourl" : {
        "gb": "English help dm action 2",
        "se": "Svensk hjälp dm action 2",
        "lt": "Lietuvos padeda dm action 2"
      },
      "parm": [
        {
          "name" : "parm 2",
          "description" : {
            "en": "English description dm param 1",
            "se": "Svensk beskrivning dm param 1",
            "lt": "Lietuvos padeda dm param 1"
          },
          "infourl" : {
            "gb": "English help dm param 1",
            "se": "Svensk hjälp dm param 1",
            "lt": "Lietuvos padeda dm param 1"
          },
          "valuelist" : [
            {
              "value" : "0x00",
              "name" : "Low",
              "description" : {
                "en" : "Low speed",
                "se" : "Låg hastighet"
              },
              "infourl" : {
                "gb": "English help 1 vl2",
                "se": "Svensk hjälp 1 vl2",
                "lt": "Lietuvos padeda 1 vl2"
              }
            },
            {
              "value" : "0x01",
              "name" : "Medium",
              "description" : {
                "en" : "Medium speed",
                "se" : "Medium hastighet"
              },
              "infourl" : {
                "gb": "English help 2 vl2",
                "se": "Svensk hjälp 2 vl2",
                "lt": "Lietuvos padeda 2 vl2"
              }
            },
            {
              "value" : "0x02",
              "name" : "High",
              "description" : {
                "en" : "High speed",
                "se" : "Hög hastighet"
              },
              "infourl" : {
                "gb": "English help 3 vl2",
                "se": "Svensk hjälp 3 vl2",
                "lt": "Lietuvos padeda 3 vl2"
              }
            }
          ] 
        }
      ]
    }
  ]
}
```


### Events:id=events_json

```json
"events" : [
  {
    "name": "test event 1",
    "class" : 10,
    "type": 6,
    "direction": "in",
    "priority": "low",
    "description" : {
      "en": "English event description 3",
      "se": "Svensk event beskrivning 3",
      "lt": "Lietuvos event padeda 3"
    },
    "infourl" : {
      "en": "English event help 3",
      "se": "Svensk event hjälp 3",
      "lt": "Lietuvos event padeda 3"
    },
    "data" : [
      {
        "name": "test event data 1",
        "description" : {
          "en": "English event data description 3",
          "se": "Svensk event data beskrivning 3",
          "lt": "Lietuvos event data padeda 3"
        },
        "infourl" : {
          "en": "English event data help 3",
          "se": "Svensk event data hjälp 3",
          "lt": "Lietuvos event data padeda 3"
        }
      },
      {
        ...
      },
      {
        ...
      }
    ]
  },
  {
    ...
  }
]
```

In the *event* object events that the module can receive and handle is described but maybe even more importantly events that the module send out itself can be 34 described. A *data* block is defined for each data byte of the event describing it.

For data blocks bit fields and value lists can be used. See description above for more information.

#### Keys for event

| Name      | Description  |
| :----     | :----------- |
| **name**  | Name for the event. |
| **class** | Event class. Mandatory. Can be set to '-' whish means all classes. |
| **type**  | Event type. Mandatory. Can be set to '-' whish means all types. |
| **priority** | Priority for the event. Default=3. |
| **dir**  | Direction of event. "in" is incoming event. "out" is outgoing event. Default="out" |

#### Keys for event data

| Name | Description  | 
| :----     | :----------- | 
| **name**  | Name for the event data byte. |
| **offset**  | Data byte offset. |

Event data can use value lists and bit fields. See description above for more information.

#### Example

```json
"events" : [
  {
    "name": "test event 1",
    "class" : 10,
    "type": 6,
    "direction": "in",
    "priority": "low",
    "description" : {
      "en": "English event description 3",
      "se": "Svensk event beskrivning 3",
      "lt": "Lietuvos event padeda 3"
    },
    "infourl" : {
      "en": "English event help 3",
      "se": "Svensk event hjälp 3",
      "lt": "Lietuvos event padeda 3"
    },
    "data" : [
      {
        "name": "test event data 1",
        "description" : {
          "en": "English event data description 3",
          "se": "Svensk event data beskrivning 3",
          "lt": "Lietuvos event data padeda 3"
        },
        "infourl" : {
          "en": "English event data help 3",
          "se": "Svensk event data hjälp 3",
          "lt": "Lietuvos event data padeda 3"
        },
        "bit": [
          {
            "pos": 0,
            "width": 3,
            "default": 4,
            "min": 0,
            "max": 7,
            "access" : "rw",
            "name" : "Bitfield name 0",
            "description" : {
              "en": "English description bit 0",
              "se": "Svensk beskrivning bit 0",
              "lt": "Lietuvos aprašymas bit 0"
            },
            "infourl" : {
              "en": "English help bit 0",
              "se": "Svensk hjälp bit 0",
              "lt": "Lietuvos padeda bit 0"
            }
          },
          {
            "pos": 3,
            "width": 2,
            "access" : "r",
            "default": false,
            "name" : "Bitfield name 1",
            "description" : {
              "en": "English description bit 1",
              "se": "Svensk beskrivning bit 1",
              "lt": "Lietuvos aprašymas bit 1"
            },
            "infourl" : {
              "en": "English help bit 1",
              "se": "Svensk hjälp bit 1",
              "lt": "Lietuvos padeda bit 1"
            },
            "valuelist" : [
              {
                "value" : "0x00",
                "name" : "Low",
                "description" : {
                  "en" : "Low speed",
                  "se" : "Låg hastighet"
                },
                "infourl" : {
                  "en": "English help 1 vl2",
                  "se": "Svensk hjälp 1 vl2",
                  "lt": "Lietuvos padeda 1 vl2"
                }
              },
              {
                "value" : "0x01",
                "name" : "Medium",
                "description" : {
                  "en" : "Medium speed",
                  "se" : "Medium hastighet"
                },
                "infourl" : {
                  "en": "English help 2 vl2",
                  "se": "Svensk hjälp 2 vl2",
                  "lt": "Lietuvos padeda 2 vl2"
                }
              },
              {
                "value" : "0x03",
                "name" : "High",
                "description" : {
                  "en" : "High speed",
                  "se" : "Hög hastighet"
                },
                "infourl" : {
                  "en": "English help 3 vl2",
                  "se": "Svensk hjälp 3 vl2",
                  "lt": "Lietuvos padeda 3 vl2"
                }
              }
            ] 
          }
        ]           
      }
    ]        
  }    
]
```

## Real life MDF XML formatted file examples

Some example files can be found [here](https://github.com/grodansparadis/vscp/tree/development/tests/mdfparser/json).


## Resources

  * [VSCP MDF parser library](https://github.com/grodansparadis/vscp-mdf-parser-lib)
  * [VSCP Works](https://github.com/grodansparadis/vscp-works-qt)
  * [Howto: Get MDF content in JSON or JSONP format](https://grodansparadis.com/wordpress/?p=1492)
  * [Howto: Read MDF content with node.js](https://grodansparadis.com/wordpress/?p=3984)


[filename](./bottom_copyright.md ':include')

# Module Description File

The VSCP registers 0xE0-0xFF specifies the Module Description File URL (without `<nowiki>`“http://”`</nowiki>` which is implied). The file is in XML format and defines a modules functionality, registers and events. The intended use is for application software to be able to get information about a node and its functionality in an automated way.

On Level II devices this information can be available in the configuration data and be locally stored on the node. If language tags are missing for a name or a description or in an other place where they are valid English should be assumed.

**Coding:** UTF-8

## Real life file examples

### Kelvin NTC10K

The Kelvin NTC10K is one of [Grodans Paradis AB's](http://www.grodansparadis.com/) modules and it has it's product page [here](http://www.grodansparadis.com/kelvinntc10k/kelvin_ntc10ka.html). The MDF file for this modules is [here](http://www.eurosource.se/ntc10KA_1.xml).


*  Paris relay board - [http://www.eurosource.se/paris_010.xml](http://www.eurosource.se/paris_010.xml)

### Paris relay module

The Paris module is another module from Grodans Paradis AB and it is documented [here](http://www.grodansparadis.com/paris/paris.html). The MDF file for this modules is [here](http://www.eurosource.se/paris_010.xml).

## XML Format Specification

##### Notes 

Register definitions must be available for all nodes (if it has registers defined). A register which does not have a an abstraction defined will be handled with a default abstraction constructed from its offset as

    register''offset''

for example

    register1 

The type will always be “uint8_t” in this case

“\n” can be used for a new line in text. 

If you want to insert HTML as content use a construct like this
`<code=xml>`
<![CDATA[
`<html>`
    `<head>`
        `<script/>`
    `<head>`
    `<body>`
        Your HTML's body
    `</body>`
`</html>`
]]>
`</code>`

this is especially useful for info, description and help items.

##### Format

`<code=xml>`
`<?xml version = "1.0" encoding = "UTF-8" ?>`   
<!-- Version 0.0.6     2012-10-01  
    "string"    - Text string  
    "bitfield"  - a field of bits. Width tells how many bits the field consist 
                of. When read from a device the number of bits will always be 
				in even octets with unused bits set to zero. Bitfield is 
                taken from MSB part thrue LSB and continues that way on 
                next octet in the series.   
    "bool"      - 1 bit number specified as true or false.  
    "int8_t"    - 8  bit number. Hexadecimal if it starts with "0x" else decimal.  
    "uint8_t"   - Unsigned 8  bit number. Hexadecimal if it starts 
				with "0x" else decimal.  
    "int16_t"   - 16 bit signed number. Hexadecimal if it starts with "0x" 
                else decimal  
    "uint16_t"  - 16 bit unsigned number. Hexadecimal if it starts 
				with "0x" else decimal  
    "int32_t"   - 32 bit signed number. Hexadecimal if it starts with "0x" 
                else decimal  
    "uint32_t"  - 32 bit unsigned number. Hexadecimal if it starts 
				with "0x" else decimal  
    "int64_t"   - 64 bit signed number. Hexadecimal if it starts with "0x" 
                else decimal  
    "uint64_t"  - 64 bit unsigned number. Hexadecimal if it starts 
				with "0x" else decimal  
    "float"	 - Data is coded as a IEEE-754 1985 floating point value
				That is a total of 32-bits. The most significant byte is 
                stored first. 
    "double"	- IEEE-754, 64 Bits, double precision. 
				That is a total of 64-bits. The most significant byte is 
                stored first.
    "date"      - Must be passed in the format dd-mm-yyyy and mapped to 
                "yy yy mm dd" that is four bytes, MSB->LSB
    "time"      - Must be passed in the format hh:mm:ss where hh is 24 hour 
                clock and mapped to "hh mm ss" MSB->LSBthat is four bytes.
    "guid"	  - Holds the 16 bytes of a GUID. Stored on the form 
                11:22:33:... MSB->LSB 

    synonyms
 1. -------
    "char"      - Is the same as "int8_t".
    "byte"      - Is the same as "uint8_t".
    "short"	 - Is the same as "int16_t".
    "integer"   - Is the same as "int16_t".
    "long"	  - Is the same as "int32_t".

    index storage
 2. ------------
    This type of storage takes up two bytes in register space. The first byte
    is the index into the second.
    
    index8_int16_t
    index8_uint16_t
    index8_int32_t
    index8_uint32_t
    index8_int64_t
    index8_uint64_t
    index8_float
    index8_double
    index8_date
    index8_time
    index8_guid
    index8_string   - String stored as [width, string]. Width tells how long the strings are. 
					If any of them are shorter then this value it should be zero terminated.
	
-->   

`<!-- General section -->`     
`<vscp>` 

	<!-- one or many. First one is used -->
	<redirect mdf-path="url" />

	<module>  <!-- one file can contain one or several modules -->      
		
		<name lang="en">aaaaaaaa</name>    
		<model>bbbbb</model>    
		<version>cccccc</version>
		<description lang = "en">yyyyyyyyyyyyyyyyyyyyyyyyyyyy</description>    
		
		<!-- Site with info about the product -->    
		<infourl>http://www.somewhere.com</infourl>    
		
		<!-- Max package size a node can receive -->    
		<buffersize></buffersize>    
		
		<manufacturer>        
			<name lang="en">tttttttttttttttttttt</name>  
      	  `<!-- One or many -->`
			<address lang="en">              
				<street>ttttttttttttt</street>            
				<town>llllllllll</town>            
				<city>London</city>            
				<postcode>HH1234</postcode>            
				<!-- Use region or state -->            
				<state></state>            
				<region></region>            
				<country>ttttt</country>        
			</address>        
			
			<!-- One or many -->        
			<telephone>            
				<number>123456789</number>            
				<description lang="en" >Main Reception</description>        
			</telephone>        
		
			<!-- One or many -->        
			<fax>            
				<number>1234567879</number>            
				<description lang="en">Main Fax Number</description>        
			</fax>        

			<!-- One or many -->        
			<email>            
				<address>someone@somwhere.com</description>            
				<description> lang="en">Main email address</description>        
			</email>        
		
			<!-- One or many -->        
			<web>            
				<address>www.somewhere.com</address>            
				<description lang="en">Main web address</description>        
			</web>     
		</manufacturer>
    
		<!-- Available Drivers   
				[id] is a manufacturer defined ID for the driver   
				[type] is "canal" or "vscp"   
				[os] is "linux-generic", "mac-generic", "windows-generic", 
						"windows-nt", "windows-xp", "windows-vista"   
				[osver] is os version 
		--> 
		<driver id="xxx", type="yyy" os="zzz" osver="123">   
			<description lang="en">Main email address</description>   
			<location>Where the driver can be fetched from 
                      (one or many)`</location>` 
		</driver>

		<!-- Picture of device --> 	
		<picture path="url where picture can be found"  		
			format="bmp | jpg | png | ....... " 		
			height="heigh for picture in pixels"
			width="width of picture in pixels"  	
			size="size of picture file in bytes" >
			<description lang="en">Description of picture</description> 	
		</picture>

		<!-- Firmware for the device (can be several) -->
		<firmware path="url where firmware can be found" 
				format="intelhex8|intelhex16"
				size="Optional size in bytes for firmware file (not image)"
				date="ISO date year-month-day when released."
				version_major="x"
				version_minor="y"
				version_subminor="z">
				<description lang="en" >Firmware description</description> 
		</firmware>

		<!-- Full documentation for the device (can be several) -->
		<manual path="url where manual can be found" 	
				lang="Two digit iso code for language"
				format="txt | rtf | doc | pdf | html">
    			`<description lang="en" >`Firmware description`</description>`
		</manual>
<!-- 
	Settings Section  Types are defined here. An abstraction is something 
	that maps to a register which is  specified by page/offset and is of a 
	predefined type  The ID is the tag that can be used in Level II 
	configuration events. 
-->   

	<abstractions>       
	<!--	The abstract variable "somename" is defined as a boolean type 
			which can have a value 0 or 1 (system also recognize false/true). 
			This variable is located at page=0, offset=1 at bit=0. As this is 
            a boolean the system knows it ocupies one bit. Other types may 
			need "width" to be defined also. The variable can be read and 
			written. Note that the name of the "variable" can be set to 
			different thing depending on locale. Note the difference between 
			"id" and "name". "id" is the same for a certain abstraction for all 
			languages and what is used internally by system software. "name" is 
			what is presented to the user.     
	-->     
	<abstraction id="somename" 
					type="bool" 
					default="false" 
					page = "0" 
					offset = "1" 
					bit="0" > 
		<name lang="en">tttt</name>     
		<description lang="en">yyy</description>         
		<help type="text/url"  lang="en">tttt</help>     
		<access>rw</access>     
	</abstraction>
	
	<!--	The abstract variable "alsoaname" is just defined as a short. 
			That is a 16-bit signed integer. It has a default value of 182 
			and is located at page=0 offset=15 and 16 (big-endian). The variable 
			can be read and written.    
	-->    
	<abstraction id="alsoaname" type="short" default="182" 
					page = "0" offset = "15" indexed="false" >         
		<name lang="en">tttt</name>     
		<description lang="en">yyy</description>         
		<help type="text/url"  lang="en">tttt</help>     
		<access>rw</access>    
	</abstraction>      

	<!--	Here a abstract variable "adescriptivename" of type string is 
			defined. A width is needed here and the string is stored in 
			page=0 at offset=20-21. Read write access is possible    
	-->    
	
	<abstraction id="adescriptivename" type="string" width="12" default="" 
					page = "0" offset = "20" indexed="false" >
		<name lang="en">tttt</name>     
		<description lang="en">yyy</description>         
		<help type="text/url"  lang="en">tttt</help>     
		<access>rw</access>    
	</abstraction>      
	<!--	This example shows a value list stored in an integer. This is 
			typically presented to the user as a list-box or a combo-box 
			with values to choose from. If register space is limited it 
			can be more efficient to use a bitfield for the options.    
	-->    
	<abstraction id="namedlist" type="integer" default="" page = "0" offset = "100" >        
		<name lang="en">tttt</name>     
		<description lang="en">yyy</description>         
		<help type="text/url"  lang="en">tttt</help>     
		<access>r</access>     
		<valuelist>               
			<item value = "0x0">                 
				<name lang="en">item0</name>                 
				<description lang="en">item0_description</description>                
			</item>                
			<item value = "0x1">                 
				<name lang="en">item1</name>                 
				<description lang="en">item1_description</description>                
			</item>                
			<item value = "0x2">                 
				<name lang="en">item2</name>                 
				<description lang="en">item2_description</description>                
			</item>                
			<item value = "0x3">                 
				<name lang="en">item3</name>                 
				<description lang="en">item3_description</description>                
			</item>                
			<item value = "0x4">                 
				<name lang="en">"item4</name>                 
				<description lang="en">item4_description</description>                
			</item>                
			<item value = "0x5">                 
				<name lang="en">item5</name>                 
				<description lang="en">item5_description</description>                
			</item>                
			<item value = "0x6">                 
				<name lang="en">item6</name>                 
				<description lang="en">item6_description</description>                
			</item>                
			<item value = "0x7">                 
				<name lang="en">item7</name>                 
				<description lang="en">item7_description</description>                
			</item>                  
			<item  value = "0x8">             
				<name lang="en">item8</name>                 
				<description lang="en">item8_description</description>                
			</item>         
		</valuelist>       
	</abstraction>   

	<abstraction id="Calibrations" type="index8_int16_t"
                          page = "0" offset = "116" size="6" > 			

		<name lang="en">Indexed array of values</name> 			
		<description lang="en"> 				
			This is an array of six 16-bit integers. Register 116 is the index
			inte the array which is at 117. So setting register 116 to 0 will 
			put the MSB of the first integer into register 117 ans so on.
		</description> 			
		<access>rw</access> 		
	</abstraction>


`</abstractions>`     




`<!-- Register section -->`   

`<registers>`       

<!-- 	The following is abstraction "alsoaname"     
		described in register space by two reg items.     
-->     
`<reg page="0" offset="15" default="0" >`         
	<name lang="en">alsoaname_msb</name>         
	<description lang="en">MSB of alsoaname</description>         
	<help type="text/url"  lang="en">tttt</help>         
	<access>rw</access>     
`</reg>`     

`<reg page="0" offset="16" >`         
	<help type="text/url"  lang="en">tttt</help>         
	<name lang="en">alsoaname_lsb</name>         
	<description lang="en">LSB of alsoaname</description>         
	<access>rw</access>     
`</reg>`       

<!--	The following is abstraction "adescriptivename"     
		described in register space. Note the use of "width"     
		which can be used to tell how many registers an abstraction     
		see instead of having many register defines. Default width     
		is one byte.     
-->     
`<reg page="0" offset="15" width="12" >`         
	<help type="text/url"  lang="en">tttt</help>         
	<name lang="en">abcdefghih</name>         
	<description lang="en">The string adescriptivename</description>         
	<access>rw</access>     
`</reg>`       

<!--	This example shows how individual bits in a register is defined. 
		Note that each bit can be named. Note also at pos 4 
		(a bit position) where a bit field has been defined which is four 
		bits wide. Here a valuelist also could have been defined describing 
		the possible values. All eight bites in register at page=0, 
		offset=1 is described here.     
-->     
`<reg page="0" offset="1" >`           
	<help type="text/url"  lang="en">tttt</help>         
	<name lang="en">tttt</name>         
	<description lang="en">yyy</description>         
	<access>rw</access>           
	<bit pos="0" default="false" >               
		<name lang="en">tttt</name>               
		<description lang="en">yyy</description>             
		<help type="text/url"  lang="en">tttt</help>         
	</bit>           
	<bit pos="1">             
		<name lang="en">tttt</name>             
		<description lang="en">yyy</description>             
		<help type="text/url"  lang="en">tttt</help>         
	</bit>           
	<bit pos="2">             
		<name lang="en">tttt</name>             
		<description lang="en">yyy</description>             
		<help type="text/url"  lang="en">tttt</help>         
	</bit>           
	<bit pos="3">             
		<name lang="en">tttt</name>             
		<description lang="en">yyy</description>             
		<help type="text/url"  lang="en">tttt</help>         
	</bit>   
	<!-- example for bit groups -->       
	<bit pos="4" width="4">     
		<name lang="en">tttt</name>             
		<description lang="en">yyy</description>             
		<help type="text/url"  lang="en">tttt</help>     
	</bit>     
`</reg>`       

<!--	Here a bitfield with width of six bits has been defined. 
		Note the access rights for the field. If access rights 
		is not given read+write access is presumed. The register 
		itself is not give a name here just the bit field.     
-->     
`<reg page="0" offset="2">`           
	<bit pos="2" width="6">               
		<name lang="en">tttt</name>             
		<description lang="en">yyy</description>             
		<help type="text/url"  lang="en">tttt</help>             
		<access>rw</access>               
		<valuelist>                   
			<item value = "0x0">                   
				<name lang="en">undefined</name>                     
					<description lang="en">yyy</description>                     
					<help type="text/url"  lang="en">tttt</help>                    
			</item>                
			<item value = "0x1">                     
				<name lang="en">Normal</name>                     
				<description lang="en">yyy</description>                     
				<help type="text/url"  lang="en">tttt</help>                
			</item>                
			<item value = "0x2">                  
				<name lang="en">Error</name>                   
				<description lang="en">yyy</description>                     
				<help type="text/url"  lang="en">tttt</help>                
			</item>                
			<item value = "0x3">                  
				<name lang="en">Disabled</name>                     
				<description lang="en">yyy</description>                     
				<help type="text/url"  lang="en">tttt</help>                
			</item>                
			<item value = "0x4">                  
				<name lang="en">"Test</name>                    
				<description lang="en">yyy</description>                     
				<help type="text/url"  lang="en">tttt</help>                
			</item>                
			<item value = "0x5">                  
				<name lang="en">Disposed</name>                     
				<description lang="en">yyy</description>                     
				<help type="text/url"  lang="en">tttt</help>                
			</item>                
			<item value = "0x6">                  
				<name lang="en">PowerSaving</name>                     
				<description lang="en">yyy</description>                     
				<help type="text/url"  lang="en">tttt</help>                
			</item>                
			<item value = "0x7">                  
				<name lang="en">Stopped</name>                     
				<description lang="en">yyy</description>                     
				<help type="text/url"  lang="en">tttt</help>                
			</item>                
			<item  value = "0x8">                  
				<name lang="en">Paused</name>                     
				<description lang="en">yyy</description>                     
				<help type="text/url"  lang="en">tttt</help>                
			</item>             
		</valuelist>         
	</bit>     
`</reg>`       

`<!--	Here all bits of a register is used as a value list which is only readable. -->`     
`<reg page = "0" offset = "88">`         
	<name lang="en">tttt</name>         
	<description lang="en">yyy</description>         
	<help type="text/url"  lang="en">tttt</help>         
	<access>r</access>         
	<valuelist>               
		<item value = "0x0">                 
			<name lang="en">undefined</name>              
			<description lang="en">yyy</description>                 
			<help type="text/url"  lang="en">tttt</help>                
		</item>                
		<item value = "0x1">                 
			<name lang="en">Normal</name>                 
			<description lang="en">yyy</description>                 
			<help type="text/url"  lang="en">tttt</help>                
		</item>                
		<item value = "0x2">                
			<name lang="en">Error</name>                 
			<description lang="en">yyy</description>                 
			<help type="text/url"  lang="en">tttt</help>                
		</item>                
		<item value = "0x3">                 
			<name lang="en">Disabled</name>                 
			<description lang="en">yyy</description>                 
			<help type="text/url"  lang="en">tttt</help>                
		</item>                
		<item value = "0x4">                 
			<name lang="en">"Test</name>                 
			<description lang="en">yyy</description>                 
			<help type="text/url"  lang="en">tttt</help>                
		</item>                
		<item value = "0x5">                 
			<name lang="en">Disposed</name>                 
			<description lang="en">yyy</description>                 
			<help type="text/url"  lang="en">tttt</help>                
		</item>                
		<item value = "0x6">                 
			<name lang="en">PowerSaving</name>               
			<description lang="en">yyy</description>                 
			<help type="text/url"  lang="en">tttt</help>                
		</item>                
		<item value = "0x7">                 
			<name lang="en">Stopped</name>                 
			<description lang="en">yyy</description>                 
			<help type="text/url"  lang="en">tttt</help>                
		</item>                
		<item  value = "0x8">                 
			<name lang="en">Paused</name>                 
			<description lang="en">yyy</description>                 
			<help type="text/url"  lang="en">tttt</help>                
		</item>         
	</valuelist>     
`</reg>`       

`<!-- Example where min/max is used -->`     
`<reg page = "0" offset = "88" min="8" max="32">`         
	<name lang="en">Trust</name>         
	<description lang="en">yyy</description>         
	<help type="text/url"  lang="en">tttt</help>     
`</reg>`   

`</registers>`         

`<!-- Decision matrix -->` 

`<dmatrix>`       
	<help type="text/url"  lang="en">tttt</help> 
     
	<!-- Can currently be 1 or 2 -->     
	<level>1</level>     

	<!-- Where is matrix located -->     
	<start page="0" offset="1" indexed="true|false"/>  
	<!-- If the matrix is placed at location 126 (Level I) it will
		automatically be set to indexed --> 

	<!-- # of rows in matrix -->     
	<rowcnt>10</rowcnt>     

	<!-- Size in bytes for one row - only for level II. 
			Always 8 for Level I. Defaults to 8. -->     
	<rowsize>8</rowsize>    

	<!-- Code for action -->     
	<action code="0x0">         
		<name lang="en"></name>         
		<description lang="en"></description>         
		<help type="text/url"  lang="en">tttt</help>         
		<!-- Descriptions of parameters - one or many -->         
		<param>               
			<name lang="en"></name>               
			<description lang="en"></description>             
			<help type="text/url"  lang="en">tttt</help>               
			<!-- Just one pos for Level I -->               
			<data offset="1" >                
				<name lang="en">tttt</name>               
				<description lang="en">yyy</description>                 
				<help type="text/url"  lang="en">tttt</help>               
				<bit pos="0">                   
					<name lang="en">tttt</name>                   
					<description lang="en">yyy</description>                     
					<help type="text/url"  lang="en">tttt</help>               
				</bit>               
				<!-- valuelist could also be used in bit groups and for hole byte -->         
			</data>         
		</param>     
	</action> 

`</dmatrix>`     

`<!-- Events this module can generate (or receive) -->` 
`<!-- Normally you only describe events the module is capable to send out -->`
`<!-- here. In this case direction="out" which is the default and  -->`
`<!-- what is used if direction is not given. Sometimes some events can  -->`
`<!-- have special meaning to the module. A typical is the CONTROL.SYNC event -->`
`<!-- if a module understands this the event can be described here with  -->`
`<!-- direction="in". -->`

`<events>`     
	<event class="0" type="10" direction="in | out" >           
		<help type="text/url"  lang="en">tttt</help>           
		<!-- Optional: user event name -->     
		<name lang="en"></name>     
		<!-- Why and when event is sent -->     
		<description lang="en">yyyy</description>         
		<help type="text/url"  lang="en">tttt</help>     
		<!-- Optional: What priority it will be sent as -->     
		<priority>3</priority>     
		<!-- Information about event data -->     
		<data offset="1" >            
			<name lang="en">tttt</name>               
			<description lang="en">yyy</description>             
			<help type="text/url"  lang="en">tttt</help>               
			<bit pos="0">                   
				<name lang="en">tttt</name>               
				<description lang="en">yyy</description>                 
				<help type="text/url"  lang="en">tttt</help>               
			</bit>     
		</data>     
	</event> 
`</events>`   

`<!-- A valuelist can be used here as well -->`     
 
`<!-- Description/specification for alarm bits -->` 

`<alarm>`     
	<bit pos="1">         
		<name lang="en">tttt</name>         
		<description lang="en">yyy</description>         
		<help type="text/url"  lang="en">tttt</help>     
	</bit> 
`</alarm>`     

`<!-- bootlader information -->` 

`<boot>`     `<!-- bootloader algorithm that can be used on this module -->`     
	<algorithm>1</algorithm>     
	<!-- Size of boot block/sector -->     
	<blocksize>20</blocksize>     
	<!-- Number of available boot blocks/sectors -->     
	<blockcount>66</blockcount> 
`</boot>`   

`</module>` 

`</vscp>`


`</code>`


Valid abstraction types are [here](http://www.vscp.org/docs/vscpspec/doku.php?id=register_abstraction_model#abstractions).

## Creating a new MDF file

 1.  Add contact and company information.
 2.  Include name and a description about the module and pointers to full descriptions if available.
 3.  Add descriptions to registers if the module have extra registers besides the standard ones.
 4.  Add information about any boot loader supported.
 5.  Add abstractions for complex registers. A complex register can be two registers that together form a 16-bit number.
 6.  If the module can issue alarms add alarm section.
 7.  If the modules got a decision matrix add information about it.
 8.  If the module send out events or can send out events add information about them.

### Relations between registers and abstractions

Registers are always eight bits. This is the only way a VSCP unit can be interfaced to. Everything it exports of its black box functionality must be broken down into eight bit registers. The common denominator between devices in short.

For user applications this may be inconvenient as a higher level application wants to look at parameters in a smarter way. A string should be a string instead of a sequence of registers. An integer a numerical value instead of two consecutive registers with a high and a low part. To overcome this abstractions can be defined in the MDF file that tells which registers make up a string and which register makes up an integer. This can then be presented to the user and the software can handle the actual register abstraction model. 

Lets look at an example. The reference model for the Ethernet based Nova module have a protection timer. O the unit this timer takes up two consecutive registers for each output channel it protects. The first byte is as it should be the most significant byte of the timer and the second byte is the least significant byte. Thus the actual timer value is byte0 * 256 + byte1. In the MDF file for Nova this is written as

`<code="xml">`
`<reg page="0" offset="26" >` 			
	<name lang="en">Output protection timer 0 MSB</name> 			
	<description lang="en"> 				
		This is the most significant byte for the output protection timer.  				
		An output will be inactivated if not written to before this time  				
		has elapsed. 				
		Set to zero to disable (default). The max time is 65535 seconds 
		which is about 18 hours. 				
		The registers can be as an example be used as a security feature 
		to ensure that an output  				
		is deactivated after a preset time even if the controlling device 
		failed to deactivate the relay.   			
	</description> 			
	<access>rw</access> 	
`</reg>`
	
`<reg page="0" offset="27" >` 			
	<name lang="en">Output protection timer 0 LSB</name> 			
	<description lang="en"> 				
		This is the least significant byte for the output protection timer.  				
		An output will be inactivated if not written to before this time  				
		has elapsed. 				
		Set to zero to disable (default). The max time is 65535 seconds 
		which is about 18 hours. 				
		The registers can be as an example be used as a security feature 
		to ensure that an output  				
		is deactivated after a preset time even if the controlling device 
		failed to deactivate the relay.   			
	</description> 			
	<access>rw</access> 		
`</reg>`
`</code>`

As seen the register at position 26 and 27 is used. Both on page 0. A user that gets this information presented for him/here needs to do some calculations to actually set the value. To make it possible to preset this to a user in a more user friendly way and abstraction is defines.

`<code="xml">`
`<abstraction id="Protectiontimer0" type="uint16_t" default="0" page = "0" offset = "26" >`
	<name lang="en">Output protection timer 0</name>      			
	<description lang="en"> 				
		This is the least significant byte for the output protection timer.  				
		An output will be inactivated if not written to before this time  				
		has elapsed.\n 				
		Set to zero to disable (default). The max time is 65535 seconds 
		which is about 18 hours. 				
		The registers can be as an example be used as a security feature 
		to ensure that an output  				
		is deactivated after a preset time even if the controlling device 
		failed to deactivate the relay.   			
	</description>          			
	<help type="url"  lang="en">
		http://www.vscp.org/wiki/doku.php/modules/nova#output_protection_time_registers
	</help>      	
	<access>rw</access>     		
`</abstraction>`
`</code>`

Now the two registers instead is presented as an unsigned 16 bit integer in a way a user expect it to be. He/she just set the value in seconds for the protection timer and the control system knowing that an unsigned integer needs two bytes can write or read the value from the register pair 26/27.

Also here an URL pointing to formatted help information is set. This URL could have been set for the registers as well of course.

User software first try to present information to users using the definitions in the abstraction section and only use registers if no abstraction covers that register. 


## reg

### name tag

    `<name lang="en">`register name`</name>`
    
The name tag names the register. This is how the register will be named by handling software. The name tag can have the usual **lang** attribute and there can be one name tag for each supported language.

### description tag

    `<description lang="en">`register name`</description>`
    
The description tag describes the register and its use. The description tag can have the usual **lang** attribute and there can be one description tag for each supported language. "\n" can be inserted in text as a new line marker.

### help tag

    `<help type="text/html/url"  lang="en">`tttt`</help>`
The help tag gives help about the register and its use. The help tag can have the usual **lang** attribute and there can be one help tag for each supported language. The type can be **text** for general inline text help, **html** for inline html help or **url** for an external web page.
    
### access tag

    `<access>`rw`</access>`

The access tag is used to tell if a cell is readable or writable or both. **r** is readable and **w** is writable. 
    
### Attributes

 | Name        | Description                                                                                                                                                                                                        | 
 | ----        | -----------                                                                                                                                                                                                        | 
 | **offset**  | Offset (Level I: 0-127) on page this  register is located on.                                                                                                                                                      | 
 | **page**    | The page the register is located on. 0-65535 can be set. Default is 0.                                                                                                                                             | 
 | **width**   | Width expressed as number of bits for register, 0-8. Default is 8.                                                                                                                                                 | 
 | **default** | Default value for register. Default is 0.                                                                                                                                                                          | 
 | **min**     | Minimum value for register. Default is 0.                                                                                                                                                                          | 
 | **max**     | Maximum value for register. Default is 255.                                                                                                                                                                        | 
 | **type**    | See [register types](http://www.vscp.org/docs/vscpspec/doku.php?id=module_description_file&#register_types) below.                                                                                                 | 
 | **size**    | Size (number of registers) for certain types. Default=1.                                                                                                                                                           | 
 | **fgcolor** | Foreground color for the location this register is presented in. Default is black. Format is **0x//rrggbb//** where **rr** is red value, **gg** is green value, **bb** is blue value or equivalent decimal number. | 
 | **bgcolor** | Background color for the location this register is presented in. Default is white. Format is **0x//rrggbb//** where **rr** is red value, **gg** is green value, **bb** is blue value or equivalent decimal number. | 

### Register types

For a register tag it is possible to define an optional type attribute. Current possible types is listed in the table below

 | Type         | Description                                                                                                                                                                                                                                                                                                                                                            | 
 | ----         | -----------                                                                                                                                                                                                                                                                                                                                                            | 
 | **std**      | This is a standard register byte. If a type attribute is not present this is what the type will be set as.                                                                                                                                                                                                                                                             | 
 | **dmatrix1** | This is a level I decision matrix defined a register space. A size attribute is needed which should be set to a value dividable by eight which is the number of rows the decision matrix consist of. *Bitfields and value lists will be ignored.* Se sample below.                                                                                                   | 
 | **block**    | This is a block of registers. A size attribute is needed that specifies the size of the block in bytes. When read a block should be interpreted as **size** register defines with names starting with **name0** to **namen** where n is size-1. The entire block should fit on the same register page. *Bitfields and value lists will be ignored.* Se sample below. | 
 
#### Decision matrix

    type="dmatrix1" size="number of dm rows * 8"
Instead of defining a decision matrix with a register entry for each of its bytes it is possible to define it in a single registry entry. This is done by specifying a type attribute for it set to **dmatrix1**. The registers that build up the decision matrix will be automatically named.

The example 

`<code="xml">`
    <reg page="0" offset="32" type="dmatrix1" size="64" 
                  oddfg="0xrrggbb" evenfg="0xrrggbb" oddbg="0xrrggbb" evenbg="0xrrggbb" >
    `<name lang="en">`Decision matrix`</name>`
    `<description lang="en">`Decision matrix for Odessa`</description>` 
    `<reg>`
`</code>`

will generate 64 register entries for a decision matrix that consist of eight rows (64/8) and name them automatically. 



#### Register blocks

    type="block" size="size of block"
A register block is a consecutive area of registers that is located on the same page. Naming is done automatically with the register name as a base.

The example 

`<code="xml">`
    <reg page="0" offset="4" type="block" size="8"
                oddfg="rrggbb" evenfg="rrggbb" oddbg="rrggbb" evenbg="rrggbb" >
    `<name lang="en">`Reserved`</name>`
    `<description lang="en">`Reserved for future use.`</description>` 
    `<reg>`
`</code>`
    
will generate eight register defines as

 | Name      | page | offset | Description              | 
 | ----      | ---- | ------ | -----------              | 
 | Reserved0 | 0    | 4      | Reserved for future use. | 
 | Reserved1 | 0    | 5      | Reserved for future use. | 
 | Reserved2 | 0    | 6      | Reserved for future use. | 
 | Reserved3 | 0    | 7      | Reserved for future use. | 
 | Reserved4 | 0    | 8      | Reserved for future use. | 
 | Reserved5 | 0    | 9      | Reserved for future use. | 
 | Reserved6 | 0    | 10     | Reserved for future use. | 
 | Reserved7 | 0    | 11     | Reserved for future use. | 

\\ 
    
## Setup recipes

**Preliminary**

Setup recipes are stored sequences that can be used to setup a specific device in a certain way. They can just set up a device according to some rules or they can interact with a user
and setup a device from user input or just guide a user through a specific setup.  

This is functionality that will be extended heavily in the future.

A sample can look like this

`<code="xml">`
`<setup>`
    `<recipe>`
        `<name>`Blink-channel0`</name>`
        `<description lang="en">`
        Set channel 0 to output and blink with 10 Hz.
        `</description>`
        `<!-- Set channel as output -->`
        `<write-bit-in-reg pos="3" page="0" offset="2" value="false" />`
        `<write-register page="0" offset="0" value="0" />`
        `<!-- Read frequency from user -->`
        `<messagebox>`
            `<function>`input`</function>`
            `<name lang="en">`Beijing I/O node`</name>`
            `<description lang="en">`With what frequency should channel blink?`</description>`
            `<variable type="byte" name="frequency" />`
        `</messagebox>`
        `<!-- Write frequency to abstraction register -->`
        `<write-abstraction name="blink-frequency0" value="$frequency" />`
    `</recipe>`
`</setup>`
`</code>`
    
The recipe has a name which is not multilingual and a description which is multilingual. From this description we see that this recipe will blink channel 0. Names of a recipe can be referenced from other recipes. A name containing spaces will have the spaces replaced by underscores. The description is some informative text for a user.

Allowed tags are

    `<write-bit-in-reg>`
This sets a bit in a specified register. 

Allowed attributes are

 | Attributes | Description                                                                                                                                                                                                     | 
 | ---------- | -----------                                                                                                                                                                                                     | 
 | pos        | Position in register from low to high (0-7)                                                                                                                                                                     | 
 | page       | Page where register is located                                                                                                                                                                                  | 
 | offset     | Offset in page where register is located                                                                                                                                                                        | 
 | width      | Number of bits if this is a bit array. Default = 1 no bitarray.                                                                                                                                                 | 
 | value      | Value for bit. Can either be true/false or 0/1. The value can also be a variable and if so should be preceded with a dollar sign '$'. If width > 1 the value can have a numerical value that fits in width ^ 2. | 

    `<write-bit-in-abstraction>`

This sets a bit in a specified abstraction
 
Allowed attributes are

 | Attributes | Description                                                                                                                           | 
 | ---------- | -----------                                                                                                                           | 
 | name       | Name of abstraction                                                                                                                   | 
 | pos        | Position in register from low to high.                                                                                                | 
 | width      | Number of bits if this is a bit array. Default = 1 no bitarray.                                                                       | 
 | value      | Value for bit. Can either be true/false or 0/1. The value can also be a variable and if so should be preceded with a dollar sign '$'. | 

    `<write-register>`
    
This sets a value in a register

 | Attributes | Description                                                                                                                           | 
 | ---------- | -----------                                                                                                                           | 
 | page       | Page where register is located                                                                                                        | 
 | offset     | Offset in page where register is located                                                                                              | 
 | value      | Value for bit. Can either be true/false or 0/1. The value can also be a variable and if so should be preceded with a dollar sign '$'. | 

    `<write-abstraction>`
    
This sets a value of an abstraction

 | Attributes | Description                                                                                                                                | 
 | ---------- | -----------                                                                                                                                | 
 | name       | Name of abstraction                                                                                                                        | 
 | value      | Value that is valid for the type of the abstraction. The value can also be a variable and if so should be preceded with a dollar sign '$'. | 

    `<messagebox>`
    
This displays a message box which can be of several types. It can be used to inform a user about different things and it can be used to input information from a user.  

The following messagebox types are defined.

 | Type        | function textual identifier | function numerical identifier | Description                                                                                                                                                      | 
 | ----        | --------------------------- | ----------------------------- | -----------                                                                                                                                                      | 
 | Information | "info"                      | 0                             | Give some textual information with an OK button                                                                                                                  | 
 | Input       | "input"                     | 1                             | Input a string into a variable                                                                                                                                   | 
 | Valuelist   | "list"                      | 2                             | Let a user selects an item from a list setting a variable to a value related to the list item                                                                    | 
 | Checkbox    | "checkbox"                  | 3                             | Let the user select among a couple of options in check boxes and returns named variables that are set or not set for each option. Many can be selected.          | 
 | Radiobox    | "radiobox"                  | 4                             | Let the user select among a couple of options in radio boxes and returns one named variable that have a value specified by the option. Only one can be selected. | 

 | Attributes  | Description                                                                                                                                                                       | 
 | ----------  | -----------                                                                                                                                                                       | 
 | function    | Either a textual function or a numerical function identifier which selects what messagebox to display                                                                             | 
 | head        | Text to display in header of message box. Can have **lang** attribute to specify language.                                                                                        | 
 | description | Text to display as description in message box. \n can be used as a new line. Can have **lang** attribute to specify language.                                                     | 
 | icon        | Select icon to be used                                                                                                                                                            | 
 | variable    | Select a variablename that is coupled to messagebox and which will receve input. Can have a **type** attribute and value checking will occure if so. A string is always returned. | 

## Setup screens

**Preliminary** 

This is just preliminary information about a future UI element that can be used to configure and/or control a module. There are two types of this type of interfaces

### Live setup screens

A live setup screen is a pointer to a web page that can be used to setup/control the VSCP module that is described in the MDF file. The module can either a module that is attached to a VSCP daemon interfaces or a full Level II module. It is the users responsibility to point the setup code to the right interface with the help of discovery procedures. There can be as many pointers to ui setup interfaces as needed.

The format for the tag is

`<code="xml">`
    `<setup-ui type="live" url="path to interface">`
     `<description lang="en">`Bla. bla. bla. bla.`</description>`
     `<payload>`If url is empty base64 encoded ui content here`</payload>`
    `</setup-ui>`
`</code>`

or 

`<code="xml">`
    `<setup-ui type="live-list" format="JSONP|JSON|XML" url="path to list of setup interfaces">`
     `<description lang="en">`Bla. bla. bla. bla.`</description>`
    `</setup-ui>`
`</code>`  

where the later points to a list with entries of the former type.

### Package setup screens

This type is a package in a zip file with JavaScript code/HTML5/CSS that defines a setup UI. The package should have a structure in the zip file that is the same as it should have on disc. A manifest in the file in XML format specify the content.

The format for the tag is

`<code="xml">`
    `<setup-ui type="package" url="path to package">`
     `<description lang="en">`Bla. bla. bla. bla.`</description>`
     `<payload>`If url is empty base64 encoded content here`</payload>`
    `</setup-ui>`
`</code>`

or 

`<code="xml">`
    `<setup-ui type="package-list" ptype="zip" format="JSONP|JSON|XML" url="path to list of packages">`
     `<description lang="en">`Bla. bla. bla. bla.`</description>`
    `</setup-ui>`
`</code>`

where the later points to a list with entries of the former type.

the `<payload>` tag is for devices that have the capability to have large information on-board, and in this case the ui packet is delivered inside the mdf.

\\ 
----
{{  ::copyright.png?400  |}}

`<HTML>``<p style="color:red;text-align:center;">``<a href="http://www.paradiseofthefrog.com">`Paradise of the Frog AB`</a>``</p>``</HTML>`

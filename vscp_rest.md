# VSCP REST

## VSCP REST Interface

The REST interface is popular among many developers today as it makes it easy to communicate using JavaScript and other web oriented languages over the Internet, and using standard web techniques. The VSCP Daemon has a REST interface that has much of the same functionality of the TCP/IP interface.

The commands that are available are described on this page.

### Where to find the REST interface

The web interface is available at

    http://host:port/vscp/rest

or for a SSL connection

    https://host:port/vscp/rest

for simplicity we only show the non SSL URL's in this documentation.

### Format for HTTP Requests

You can use **GET** or **POST** HTTP requests. They differ a little in format as the **POST** version send authentication information in the header, but in all other senses they are the same. 

#### Example of GET HTTP REQUEST

    http://localhost:8884/vscp/rest?vscpuser=admin&vscpsecret=secret&op=open&format=plain

#### Example of POST HTTP REQUEST

    curl -X POST "http://host:port/vscp/rest" \
    -H "vscpuser: user" \
    -H "vscpsecret: password" \
    -H "vscpsession: session" \
    -d "vscpuser=admin&vscpsecret=secret&\
        op=open&format=plain"
        
### Life of a REST session

A REST session normally lives between **open** and **close** HTTP requests. If for some reason a rest session is not closed and not accessed within ten minutes the system will regard it as an orphan and close it. To issue a *status* HTTP request from time to time is a good way to hold a session open. But any other of the HTTP requests that need the session value also will do.

### JSONP

If you are using JavaScript in a web browser to retrieve data, then you might be interested in using the JSONP format. JSONP allows you to make to requests from a server from a different domain, which is normally not possible because of the same-origin policy.

Unlike all of the other methods, JSONP responses will always be sent with the HTTP 200 success code. We respond this way for the JSONP format because browsers will not parse the response body when the server replies with a HTTP error code.


## VSCP REST Protocol Description

This page describes the protocol and HTTP requests available for the VSCP REST protocol.

The format here uses some special characters that may need some extra explanation.


*  **'\'** is a sign that indicates that the current line continues on the next line.

*  **'|'** is **or**. It is often written on the form *type=option|option2|optionm3|option4* and means you can select one of the options.

### HTTP Request Parameters

 | Parameter | Example | description |    
 | --------- | ------- | ----------- |    
 | **vscpuser**    | vscpuser=admin  | Sets the username |  
 | **vscpsecret**  | vscpsecret=d50c3180375c27927c22e42a379c3f67  | Set password. The password is made up of the md5 hash of *username:auth-domain:realtextpassword*. The **mkpasswd** tool that comes with VSCP & Friends can be used to generate the hash or one can use any of the on-line resources available. |    
| **vscpsession** | vscpsession=d1c13eb83f52f319f14d167962048521 | This is a key that is received from the server after the **open** command. It is used as a parameter for all other parameters to identify the client session and reuse it |    
 | **format**      | format=plain \| csv \| xml \| json \| jsonp   | Sets the format responses should be delivered on. See format table below for possible values. |   
 | **op**          | op=open                                      | Operation to perform. op can have a token or a numerical value. |    

### Supported output formats 

The currently available formats are

 | Format    | Description                                    | 
 | ------    | -----------                                    | 
 | **plain** | Plain text format                              | 
 | **csv**   | Comma Separated Values                         | 
 | **xml**   | XML format                                     | 
 | **json**  | JSON format popular in Javascript              | 
 | **jsonp** | JSONP format popular in Javascript crossdomain | 


### Operations

The available operations currently are

 | operation token  | Code | Description | 
 | --------------- | :----: | ----------- | 
 | [status](rest_interface_status.md) | 0    | Gives status for session | 
 | [open](rest_interface_open.md)     | 1    | Open a new session session | 
 | [close](rest_interface_close.md)   | 2    | Close a session | 
 | [sendevent](rest_interface_sendevent.md)  | 3 | Send VSCP Event | 
 | [readevent](rest_interface_readevent.md)  | 4 | Read VSCP Event | 
 | [setfilter](rest_interface_setfilter.md)  | 5 | Set filter for this session | 
 | [clearqueue](rest_interface_clearinqueue.md) | 6 | Clear input queue for this session | 
 | [listvar](rest_interface_listvar.md) | 12 | List variables variable | 
 | [readvar](rest_interface_readvar.md) | 7 | Read the value of a variable | 
 | [writevar](rest_interface_writevar.md) | 8 | Write the value of a variable | 
 | [createvar](rest_interface_createvar.md) | 9 | Create a variable | 
 | [measurement](rest_interface_measurement.md) | 10 | Send a measurement | 
 | [table](rest_interface_table.md) | 11 | Read a table | 

### Errors

#### General - Error = -1

This error is received as a general error message.

#### Invalid session - Error = -2

The login session is invalid or have timeout because of inactivity. An Open call is needed before most commands can be used.

###### Error code format=plain

```css
0 -2 Invalid session 

The session must be opened with 'open' before a session command can be used. It may also be possible that the session has timed out.
```

###### Error code format=csv

```css
success-code,error-code,message,description\r\n0,-2,Invalid session,The session must be opened with 'open' before a session command can be used. It may also be possible that the session has timed out.
```


###### Error code format=xml

```xml
<vscp-rest success="false" 
    code="-2" 
    message="Invalid session" 
    description="The session must be opened with 'open' before a session command can be used. It may also be possible that the session has timed out."/>
```

###### Error code format=json

```javascript
{\"success\":false,\"code\":-2,\"message\":\"Invalid session\",\"description\":\"The session must be opened with 'open' before a session command can be used. It may also be possible that the session has timed out.\"}
```

###### Error code format=jsonp

```javascript
typeof handler === 'function' && handler(("{\"success\":false,\"code\":-2,\"message\":\"Invalid session\",\"description\":\"The session must be opened with 'open' before a session command can be used. It may also be possible that the session has timed out.\"});
```

#### Unsupported format - Error = -3

This error is received because the format of the call is not valid.

#### Unable to create session - Error = -4

The system was unable to create the session.

#### Missing data/parameter - Error = -5

Needed data or a parameter to a call is missing. 

#### Input queue empty - Error = -6

There is no events to read from the input queue.

#### Variable not found - Error = -7

A requested variable can't be found and is probably undefined.

#### Variable could not be created - Error = -8

A variable could not be created. This can be a memory or a naming problem.

## Get Status

```css
    op=0 or op=STATUS
```  

Check status. Can be used to hold the session active but also to check how many event are waiting in the input queue. **Requires a valid session parameter**

**General format:**

```css
http://server:port/rest?
    vscpsession=key&
    format='plain|csv|xml|json|jsonp'&
    op='0|status'
```

**Arguments:**


*  **op** - Set to 0|status

*  **format** - can be 0|plain, 1|csv, 2|xml, 3|json or 4|jsonp.

*  **vscpsession** - A valid session key received from the open method.

### HTTP Request with GET

```css
http://demo.vscp.org:8884/vscp/rest?vscpsession=d1c13eb83f52f319f14d167962048521 &format=plain|csv|xml|json|jsonp&op=0|status    
```

to test this with **curl** use the following format

```css
curl -X GET "http://host:port/vscp/rest? \
    vscpsession=d1c13eb83f52f319f14d167962048521 & \
    format=plain|csv|xml|json|jsonp& \
    op=0|status"
```

### Examples

###### example GET HTTP request

```css
    http://localhost:8884/vscp/rest?  
              vscpsession=d1c13eb83f52f319f14d167962048521&
              format=plain&
              op=0
```  


###  HTTP Request with POST

```css
curl -X POST "http://localhost:8884/vscp/rest" \
    -H "vscpsession: d1c13eb83f52f319f14d167962048521" \ 
    -d "op=status&format=plain"     
```

### Demo

There is a [demo app.](https://github.com/grodansparadis/vscp-ux/tree/master/rest) in the source tree, that demonstrates this functionality using JavaScript.

#### JavaScript Request with JSONP

```javascript
//////////////////////////////////////////////////////////////////
// do_status
//
		
var do_status = function() {
			
if ( VscpSessionKey.length > 0 ) {	
   $.ajax({
       url: VscpServer + '/vscp/rest?vscpsession=' + VscpSessionKey + '&format=jsonp&op=status',
       type : "GET",
       jsonpCallback: 'handler',
       cache: true,
       dataType: 'jsonp',
       success: function(response) {
           // response will be a JavaScript
           // array of objects
           console.log("-----------------------------------------------------------");
           console.log("                         do_status");
           console.log("-----------------------------------------------------------");
           console.log("Success = " + response.success );
           console.log("Code = " + response.code );
           console.log("Message = " + response.message );
           console.log("Description = " + response.description );
           console.log("Number of events = " + response.nEvents );   
           		
           if (  response.success ) {
               VscpEventCount = response.nEvents;
               $("#nevents").html("`<b>`Number of events in queue`</b>`: " + response.nEvents );
           }					
       },
       error: function( xhr, status, error ) {
           console.log( "Close:" + error + " Status:" + status );
       }
});
}
else {
    alert("Interface is not open!");
}
};
```

### Responses

#### Plain

	
	1 1 Success 
	
	Everything is fine.
	vscpsession=b3c85bb85aa38ecaf25b15a5865178f2 nEvents=14


#### CSV

	
	success-code,error-code,message,description,vscpsession,nEvents
	1,1,Success,Success. 1,1,Success,Sucess,b3c85bb85aa38ecaf25b15a5865178f2,84


#### XML

```xml
<vscp-rest success="true" code="1" message="Success." description="Success.">
    <vscpsession>`b3c85bb85aa38ecaf25b15a5865178f2`</vscpsession>
    <nEvents>`46`</nEvents>
</vscp-rest>
```

#### JSON

```css
{"success":true,"code":1,"message":"success","description":"Success","vscpsession":"b3c85bb85aa38ecaf25b15a5865178f2","nEvents":59}
```

#### JSONP

```javascript
typeof handler === 'function' && handler({"success":true,"code":1,"message":"success","description":"Success","vscpsession":"b3c85bb85aa38ecaf25b15a5865178f2","nEvents":69});
```


## Open

```css
    op=1 or op=OPEN
```
    
This HTTP request open a new session with the server. This should be the first operation you do when you want to work with the VSCP REST interface. If all goes well you will be handed a session key and you should use this session key in further calls.

For GET requests you put the key in the request URL just as any other value 

    vscpsession=d1c13eb83f52f319f14d167962048521 

and for PUT HTTP requests you place the key in the header as

    vscpsession: d1c13eb83f52f319f14d167962048521 

If you do not use this session key within five minutes it will be invalid and you have to do a new open HTTP request.

**General format:**

```css
http://host:port/vscp/rest?
    vscpuser=username&
    vscpsecret=password&
    format=plain|csv|xml|json|jsonp&
    op=1|open     
```

**Arguments:**


*  **op** - Set to 1|open

*  **format** - Can be 0|plain, 1|csv, 2|xml, 3|json or 4|jsonp.

*  **vscpuser** - A valid username.

*  **vscpuser** - A valid password.


**note** the *vscpsecret* has been changed from a md5 password to a clear text password from version 1.12.14.12.

### HTTP Request with GET

```css
http://host:port/vscp/rest?vscpuser=username&vscpsecret=password&format=plain|csv|xml|json|jsonp&op=1|open     
```
    
You can interact with the vscp demo server right now by plugging this into your browser.

```css
http://demo.vscp.org:/vscp/rest?vscpuser=admin&vscpsecret=secret&format=plain&op=1
```

See "Read Event" section of REST Interface documentation for more details.  

###  CURL HTTP Request with GET

```bash
    curl -X GET "http://localhost:8884/vscp/rest?vscpuser=admin&vscpsecret=secret&format=plain&op=open"
```

you should get a response with something like

	
	1 1 Success vscpsession=8fa1052598a988ad5166bc9c65f0a167 nEvents=0


where *8fa1052598a988ad5166bc9c65f0a167* is the session id to use for further calls.



###  CURL HTTP Request with POST

```bash
curl -X POST "http://localhost:8884/vscp/rest" \
    -H "vscpuser: admin" \
    -H "vscpsecret: d50c3180375c27927c22e42a379c3f67" \ 
    -d "op=open&format=plain"     
```

### Demo

There is a a [demo app](https://github.com/grodansparadis/vscp-ux/tree/master/rest) in the source tree, that demonstrates this functionality using JavaScript.

#### Bash sample

The following bash script fetches a session ID and automatically uses it to read VSCP events in plain format.

```bash
#!/bin/bash

# Angus Galloway
# fetch a session ID from the daemon, it is valid for 5 minutes.

# option -s for silent
# option -X for specifying request cmd

curl -s -X GET "http://demo.vscp.org:8884/vscp/rest?vscpuser=admin&vscpsecret=secret&format=plain&op=1" > temp_file

awk '{ split($4,arr,"="); print "curl -X GET \"http://demo.vscp.org:8884/vscp/rest?session="arr[2]"&format=plain&op=4\""; }' temp_file

# execute result

awk '{ split($4,arr,"="); print "curl -X GET \"http://demo.vscp.org:8884/vscp/rest?session="arr[2]"&format=plain&op=4\"" | "bash"; }' temp_file
```

#### JavaScript Request with JSONP

```javascript
$.ajax({
    url: 'http://demo.vscp.org:8884/vscp/rest?vscpuser=admin&vscpsecret=secret&format=jsonp&op=1',
    type : "GET",
    jsonpCallback: 'handler',
    cache: true,
    dataType: 'jsonp',
    success: function(response) {
        // response will be a JavaScript
        // array of objects
        console.log("Success = " + response.success );
        console.log("Code = " + response.code );
        console.log("Message = " + response.message );
        console.log("Description = " + response.description );					
        console.log("Sessionkey = " + response.vscpsession );
        console.log("nEvents = " + response.nEvents );
					
        if (  response.success ) {
            console.log("Session key assigned to global object " + typeof( response.success) );
            gVscpSessionKey = response.vscpsession;
        }
    },
    error: function( xhr, status, error ) {
        console.log( error + " Status:" + status );
    }
});
```

Use the returned vscpsession key for all other calls.

### Responses

With the format parameter you set the format your want the response represented as. The following shows the positive outcome of the Open HTTP request for all formats available.

###### Response for format=plain

```css
1 1 Success vscpsession=d1c13eb83f52f319f14d167962048521 nEvents=0
```

###### Response for format=csv

```css
success_code,error-code,message,description,vscpsession,nEvents
1,1,Success,Success. 1,1,Success,Success,d1c13eb83f52f319f14d167962048521 
```

###### response for format=xml

```xml
<vscp-rest success="true" 
       code="1" 
       message="Success." 
       description="Success.">
    <vscpsession>d1c13eb83f52f319f14d167962048521 </vscpsession>
    <nEvents>0</nEvents>
</vscp-rest>
```

###### response for format=json

```css
{"success":true,"code":1,"message":"success","description":"Success","vscpsession":"d1c13eb83f52f319f14d167962048521 ","nEvents":0}
```

###### response for format=jsonp

```css
typeof handler === 'function' && handler({"success":true,"code":1,"message":"success","description":"Success","vscpsession":"d1c13eb83f52f319f14d167962048521 ","nEvents":0});
```


# Close

```css
    op=2 or op=CLOSE
```

Close a session with the server. **Requires a valid session parameter**

**General format:**
```css
http://host:port/vscp/rest?
    vscpsession=session-key&
    format=plain|csv|xml|json|jsonp&
    op=2|close    
```

**Arguments:**


*  **op** - Set to 2|close

*  **format** - can be 0|plain, 1|csv, 2|xml, 3|json or 4|jsonp.

*  **vscpsession** - A valid session key received from the open method.

### HTTP Request with GET

```css
http://demo.vscp.org:8884/vscp/rest?vscpsession=d1c13eb83f52f319f14d167962048521 &format=plain|csv|xml|json|jsonp&op=2|close    
```

To test this with **curl** use the following format

```css
curl -X GET "http://demo.vscp.org:8884/vscp/rest? \
    vscpsession=d1c13eb83f52f319f14d167962048521 & \
    format=plain|csv|xml|json|jsonp& \
    op=2|close"
```

### Examples

###### example GET HTTP request

```css
    http://localhost:8884/vscp/rest?  
              vscpsession=d1c13eb83f52f319f14d167962048521&
              format=plain&
              op=2
```  

###  HTTP Request with POST

```css
curl -X POST "http://localhost:8884/vscp/rest" \
    -H "vscpsession: d1c13eb83f52f319f14d167962048521" \ 
    -d "op=close&format=plain"     
```

### Demo

There is a [demo app](https://github.com/grodansparadis/vscp-ux/tree/master/rest) in the source tree, that demonstrates this functionality using JavaScript.

#### JavaScript Request with JSONP

```javascript
///////////////////////////////////////////////////////////////////
// do_close
//
		
var do_close = function() {
			
    if ( VscpSessionKey.length > 0 ) {	
        $.ajax({
            url: VscpServer + '/vscp/rest?vscpsession=' + VscpSessionKey + '&format=jsonp&op=2',
            type : "GET",
            jsonpCallback: 'handler',
            cache: true,
            dataType: 'jsonp',
            success: function(response) {
                // response will be a JavaScript
		// array of objects
		console.log("-----------------------------------------------------------");
		console.log("                         do_close");
		console.log("-----------------------------------------------------------");
		console.log("Success = " + response.success );
		console.log("Code = " + response.code );
		console.log("Message = " + response.message );
		console.log("Description = " + response.description );
		
	        if (  response.success ) {
                    console.log("Sessionkey cleared"  );
                    VscpSessionKey = "";
                    $("#sessionkey").html("`<b>`Sessionkey`</b>`: " );
                    $("#nevents").html(" " );
                }					
					
            },
            error: function( xhr, status, error ) {
                console.log( "Close:" + error + " Status:" + status );
           }
    });
    }
    else {
        alert("Interface is not open!");
    }
};
```

### Responses

#### Plain

	
	1 1 Success 
	
	Everything is fine.


#### CSV

	
	success-code,error-code,message,description
	1,1,Success,Success.


#### XML

```xml
<vscp-rest success="true" code="1" message="Success" description="Success."/>
```

#### JSON

```css
{"success":true,"code":1,"message":"success","description":"Success"}
```

#### JSONP

```javascript
typeof handler === 'function' && handler({"success":true,"code":1,"message":"success","description":"Success"});
```


## Send Event

```css
    op=3 or op=SENDEVENT
```  
    
Send a VSCP Event. The event should be given in string form "head,vscp-class,vscp-type,obid,datetime,timestamp,guid,data1,data2,data2..." **Requires a valid session parameter**

**Important note** datetime is introduced in version 1.12.20.0

**General format:**

```css
http://server:port/rest?
    vscpsession=session-key&
    format=plain|csv|xml|json|jsonp&
    op=3|sendevent&
    vscpevent=event-in-string-form
```

Arguments:


*  **op** - Set to 3|sendevent

*  **format** - can be 0|plain, 1|csv, 2|xml, 3|json or 4|jsonp.

*  **vscpsession** - A valid session key received from the open method.

*  **vscpevent** - Event in string form. That is *head,class,type,obid,time-stamp,GUID,data1,data2,data3.... * for example *0,20,3,0,,0,0:1:2:3:4:5:6:7:8:9:10:11:12:13:14:15,0,1,35* to send [CLASS1.INFORMATION TYPE=3 ON event](http://docs.vscp.org/spec/latest/#/./class1.information?id=type3-0x03-on), for zone=1, sub-zone=35. Can also be sent as *0,20,3,0,0,-,0,1,35* which will use the GUID of the interface.

### HTTP Request with GET

```css
http://demo.vscp.org:8884/vscp/rest?vscpsession=d1c13eb83f52f319f14d167962048521 &format=plain|csv|xml|json|jsonp&op=3|sendevent&vscpevent=0,10,6,0,,,-,138,0,255    
```

to test this with **curl** use the following format

```css
curl -X GET "http://host:port/vscp/rest? \
    vscpsession=d1c13eb83f52f319f14d167962048521 & \
    format=plain|csv|xml|json|jsonp& \
    op=3|sendevent&vscpevent=0,10,6,0,,,-,138,0,255"
```


###Examples

###### example GET HTTP request

```css
    http://localhost:8884/vscp/rest?  
              vscpsession=d1c13eb83f52f319f14d167962048521&
              format=plain&
              op=3&
              vscpevent=event-in-string-form
```  


###  HTTP Request with POST

```css
curl -X POST "http://localhost:8884/vscp/rest" \
    -H "vscpsession: d1c13eb83f52f319f14d167962048521" \ 
    -d "op=sendevent&format=plain&vscpevent=0,10,6,0,,,-,138,0,255"     
```

### Demo

There is a a [demo app.](https://github.com/grodansparadis/vscp-ux/tree/master/rest) in the source tree, that demonstrates this functionality using JavaScript.

#### JavaScript Request with JSONP

```javascript
//////////////////////////////////////////////////////////////////
// do_sendEvent
//
		
var do_sendEvent = function() {
			
    if ( VscpSessionKey.length > 0 ) {	
        $.ajax({
            url: VscpServer + '/vscp/rest?vscpsession=' + VscpSessionKey + '&format=jsonp&op=sendevent&vscpevent=' + txtSendEvent,
            type : "GET",
            jsonpCallback: 'handler',
            cache: true,
            dataType: 'jsonp',
            success: function(response) {
                // response will be a javascript
                // array of objects
                console.log("-----------------------------------------------------------");
                console.log("                         do_sendEvent");
                console.log("-----------------------------------------------------------");
                console.log("Success = " + response.success );
                console.log("Code = " + response.code );
                console.log("Message = " + response.message );
                console.log("Description = " + response.description);
                console.log("Info = " + response.info );
					
                if ( response.success ) {
                    $("#events").html( "event sent" );
                }					
					
            },
            error: function( xhr, status, error ) {
                console.log( "Close:" + error + " Status:" + status );
            }
        });
    }
    else {
        alert("Interface is not open!");
    }
};
```

### Responses

#### Plain

	
	1 1 Success 
	
	Everything is fine.


#### CSV

	
	success-code,error-code,message,description
	1,1,Success,Success.


#### XML

```xml
<vscp-rest success="true" code="1" message="Success" description="Success."/>
```

#### JSON

```css
{"success":true,"code":1,"message":"success","description":"Success"}
```

#### JSONP

```javascript
typeof handler === 'function' && handler({"success":true,"code":1,"message":"success","description":"Success"});
```


## Read Event

```css
    op=4 or op=READEVENT
```  

Read one or more VSCP Event(s). 

**Requires a valid session parameter**

**General format:**

```css
http://server:port/rest?
    vscpsession=session-key&
    format=plain|csv|xml|json|jsonp&
    op=4|readevent
    [&count=n]
```

so to read a maximum of four events in plain format use

```css
http://server:port/rest?vscpsession=session-key&
    format=plain&
    op=4&
    count=4
```

**Arguments:**


*  **op** - Set to 4|readevent

*  **format** - Can be 0|plain, 1|csv, 2|xml, 3|json or 4|jsonp.

*  **vscpsession** - A valid session key received from the open method.

*  **count** is an optional parameter and will, if not set, default to one.

### HTTP Request with GET

```css
http://host:port/vscp/rest?vscpsession=d1c13eb83f52f319f14d167962048521 &format=plain|csv|xml|json|jsonp&op=4&readevent[&count=n]    
```

to test this with **curl** use the following format

```css
curl -X GET "http://host:port/vscp/rest? \
    vscpsession=d1c13eb83f52f319f14d167962048521 & \
    format=plain|csv|xml|json|jsonp& \
    op=4|readevent[&count=n]"
```

or against the demo server in your browser

```css
http://demo.vscp.org:8884/vscp/rest?vscpsession=98608c27b1ca33ceb6c7f003688c7095&format=plain&op=readevent&count=2
```

replacing the session key (98608c27b1ca33ceb6c7f003688c7095) with the key you received in the open call.

The result you get should be something like

    1 1 Success 
    2 events requested of 201 available (unfiltered) 2 will be retrieved
    - 96,10,6,1,2003-11-02T12:01:01,1917354301,FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00,0x8A,0x81,0x00,0xE9/r/n
    - 96,10,6,1,Important note datetime is introduced in version 1.12.20.0,2003-11-02T12:01:01,1917354551,FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00,0x8A,0x81,0x00,0xE7/r/n


### Examples

###### example GET HTTP request

```css
    http://localhost:8884/vscp/rest?  
              vscpsession=d1c13eb83f52f319f14d167962048521&
              format=plain&
              op=4
```  


### HTTP Request with POST

```css
curl -X POST "http://localhost:8884/vscp/rest" \
    -H "vscpsession: d1c13eb83f52f319f14d167962048521" \ 
    -d "op=readevent&format=plain&count=5"     
```

### Demo

There is a a [demo app.](https://github.com/grodansparadis/vscp-ux/tree/master/rest) in the source tree, that demonstrates this functionality using JavaScript.

#### JavaScript Request with JSONP

```javascript
//////////////////////////////////////////////////////////////////
// do_readEventOne
//
		
var do_readEventOne = function() {
			
    if ( VscpSessionKey.length > 0 ) {	
        $.ajax({
            url: VscpServer + '/vscp/rest?vscpsession=' + VscpSessionKey + '&format=jsonp&op=readevent&count=1',
            type : "GET",
            jsonpCallback: 'handler',
            cache: true,
            dataType: 'jsonp',
            success: function(response) {
                // response will be a JavaScript
                // array of objects
                console.log("-----------------------------------------------------------");
                console.log("                         do_readEventOne");
                console.log("-----------------------------------------------------------");
                console.log("Success = " + response.success );
                console.log("Code = " + response.code );
                console.log("Message = " + response.message );
                console.log("Description = " + response.description );
                console.log("Info = " + response.info );
                console.log("Count = " + response.count );
                console.log("Filtered = " + response.filtered );
                console.log("Errors = " + response.errors );
					
                if (  response.success && ( 1 == response.count ) ) {
                    $("#events").html( printEventData( response.event[0] ) );
                }					
					
            },
            error: function( xhr, status, error ) {
                console.log( "Close:" + error + " Status:" + status );
            }
        });
        }
        else {
            alert("Interface is not open!");
        }
};
```

If you want to read all events in the queue just set count to a very (insanely) high value.

### Responses

**Important note:** The datetime field was introduced in version 1.12.20.0
#### Plain

```css
1 1 Success 
10 events requested of 16 available (unfiltered) 10 will be retrieved
- 96,10,6,3,2003-11-02T12:01:01,55055109,FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00,0x8A,0x81,0x01,0x32
- 96,10,6,3,2003-11-02T12:01:01,55057140,FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00,0x8A,0x82,0x0B,0xE5
- 96,10,6,3,2003-11-02T12:01:01,55059156,FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00,0x8A,0x82,0x0B,0xEE
- 96,10,6,3,2003-11-02T12:01:01,55061171,FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00,0x8A,0x82,0x0B,0xD9
- 96,10,6,3,2003-11-02T12:01:01,55063203,FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00,0x8A,0x82,0x0B,0xE4
- 96,10,6,3,2003-11-02T12:01:01,55065234,FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00,0x8A,0x82,0x0B,0xDF
- 96,10,6,3,2003-11-02T12:01:01,55067281,FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00,0x8A,0x81,0x01,0x2E
- 96,20,9,3,2003-11-02T12:01:01,55068312,FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00,0x00,0x01,0x02
- 96,10,6,3,2003-11-02T12:01:01,55069343,FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00,0x8A,0x82,0x0B,0xB0
- 96,10,6,3,2003-11-02T12:01:01,55071343,FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00,0x8A,0x82,0x0B,0xAF
```

#### CSV

```csv
success-code,error-code,message,description,Event
1,1,Success,Success.,NULL
1,2,Info,10 events requested of 14 available (unfiltered) 10 will be retrieved,NULL
1,4,Count,10,NULL
1,3,Data,Event,96,10,6,3,2003-11-02T12:01:01,55036906,FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00,0x8A,0x82,0x0A,0x4D
1,3,Data,Event,96,20,9,3,2003-11-02T12:01:01,55037906,FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00,0x00,0x01,0x02
1,3,Data,Event,96,10,6,3,2003-11-02T12:01:01,55038906,FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00,0x8A,0x82,0x0A,0xE3
1,3,Data,Event,96,10,6,3,2003-11-02T12:01:01,55040921,FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00,0x8A,0x82,0x0B,0x81
1,3,Data,Event,96,10,6,3,2003-11-02T12:01:01,55042937,FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00,0x8A,0x82,0x0B,0x8D
1,3,Data,Event,96,10,6,3,2003-11-02T12:01:01,55044953,FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00,0x8A,0x82,0x0B,0xAF
1,3,Data,Event,96,10,6,3,2003-11-02T12:01:01,55046968,FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00,0x8A,0x82,0x0B,0xCE
1,3,Data,Event,96,10,6,3,2003-11-02T12:01:01,55049000,FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00,0x8A,0x82,0x0B,0xD9
1,3,Data,Event,96,10,6,3,2003-11-02T12:01:01,55051015,FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00,0x8A,0x82,0x0B,0xEE
1,3,Data,Event,96,10,6,3,2003-11-02T12:01:01,55053062,FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00,0x8A,0x82,0x0B,0xFB
```


*  Row starting with 1,1 is header

*  Row starting with 1,2 is info

*  Row starting with 1,3 is Event

*  Row starting with 1,4 is Event count returned.

#### XML

```xml
<vscp-rest success="true" code="1" message="Success" description="Success.">
<info>
10 events requested of 5 available (unfiltered) 5 will be retrieved
</info>
<count>5</count>
<event>
    <head>96</head>
    <vscpclass>10</vscpclass>
    <vscptype>6</type>
    <timestamp>54997984</timestamp>
    <obid>3</obid>
    <guid>FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00</guid>
    <sizedata>4</sizedata>
    <data>0x8A,0x81,0x00,0xCE</data>
    <raw>
        96,10,6,3,2003-11-02T12:01:01,54997984,FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00,0x8A,0x81,0x00,0xCE
    </raw>
</event>

<event>
    <head>96</head>
    <vscpclass>10</vscpclass>
    <vscptype>6</type>
    <obid>3</obid>
    <datetime>2003-11-02T12:01:01</datetime>
    <timestamp>55000015</timestamp>
    <obid>3</obid>
    <guid>FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00</guid>
    <sizedata>4</sizedata>
    <data>0x8A,0x81,0x00,0xD0</data>
    <raw>
        96,10,6,3,2003-11-02T12:01:01,55000015,FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00,0x8A,0x81,0x00,0xD0
    </raw>
</event>

<event>
    <head>96</head>
    <vscpclass>10</vscpclass>
    <vscptype>6</type>
    <obid>3</obid>
    <datetime>2003-11-02T12:01:01</datetime>
    <timestamp>55002078</timestamp>
    <obid>3</obid>`
    <guid>FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00</guid>
    <sizedata>3</sizedata>
    <data0x8A,0x80,0x15</data>
    <raw>
        96,10,6,3,2003-11-02T12:01:01,55002078,FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00,0x8A,0x80,0x15
    </raw>
</event>

<event>
    <head>96</head>
    <vscpclass>10</vscpclass>
    <vscptype>6</type>
    <obid>3</obid>
    <datetime>2003-11-02T12:01:01</datetime>
    <timestamp>55004109</timestamp>
    <obid>3</obid>
    <guid>FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00</guid>
    <sizedata>4</sizedata>
    <data>0x8A,0x81,0x00,0xD5</data>
    <raw>
        96,10,6,3,2003-11-02T12:01:01,55004109,FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00,0x8A,0x81,0x00,0xD5
    </raw>
</event>

<event>
    <head96</head>
    <vscpclass>10</vcpclass>
    <vscptype>6</type>
    <obid>3</obid>
    <datetime>2003-11-02T12:01:01</datetime>
    <timestamp55006125</timestamp>
    <obid>3</obid>
    <guid>FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00</guid>
    <sizedata>4</sizedata>
    <data>0x8A,0x81,0x00,0xD8</data>
    <raw>
        96,10,6,3,2003-11-02T12:01:01,55006125,FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00,0x8A,0x81,0x00,0xD8
    </raw>
</event>

`<filtered>`0`</filtered>`
`<errors>`0`</errors>`

`</vscp-rest>`

```

####  JSON 

```javascript
{
    "success":true,
    "code":1,
    "message":"success",
    "description":"Success",
    "info":"10 events requested of 10 available (unfiltered) 10 will be retrieved",
    "event":   
    [
        { 
            "head":96,
            "vscpclass":10,
            "vscptype":6,
            "datetime":"2003-11-02T12:01:01,"
            "timestamp":58712468,
            "obid":3,
            "guid":"FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00",
            "sizedata":4,
            "data":[138,129,0,204]
        },
        {
            "head":96,
            "vscpclass":10,
            "vscptype":6,
            "datetime":"2003-11-02T12:01:01"
            "timestamp":58714468,            
            "obid":3,
            "guid":"FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00",
            "sizedata":4,
            "data":[138,129,0,206]
       },
       {
            "head":96,
            "vscpclass":10,
            "vscptype":6,
            "datetime":"2003-11-02T12:01:01"
            "timestamp":58716531,
            "obid":3,
            "guid":"FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00",
            "sizedata":4,
            "data":[138,129,0,205]
       },
       {
            "head":96,
            "vscpclass":10,
            "vscptype":6,
            "datetime":"2003-11-02T12:01:01"
            "timestamp":58718546,
            "obid":3,
            "guid":"FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00",
            "sizedata":4,
            "data":[138,129,0,206,]
       },
       {
            "head":96,
            "vscpclass":10,
            "vscptype":6,
            "datetime":"2003-11-02T12:01:01"
            "timestamp":58720625,
            "obid":3,
            "guid":"FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00",
            "sizedata":4,
            "data":[138,129,0,208]
       },
       {
            "head":96,
            "vscpclass":10,
            "vscptype":6,
            "datetime":"2003-11-02T12:01:01"
            "timestamp":58722859,
            "obid":3,
            "guid":"FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00",
            "sizedata":3,
            "data":[138,128,21]
       },
       {
            "head":96,
            "vscpclass":10,
            "vscptype":6,
            "datetime":"2003-11-02T12:01:01"
            "timestamp":58724906,
            "obid":3,
            "guid":"FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00",
            "sizedata":4,
            "data":[138,129,0,213]
       },
       {
            "head":96,
            "vscpclass":10,
            "vscptype":6,
            "datetime":"2003-11-02T12:01:01"
            "timestamp":58726937,
            "obid":3,
            "guid":"FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00",
            "sizedata":4,
            "data":[138,129,0,216]
      },
      {
           "head":96,
           "vscpclass":20,
           "vscptype":9,
           "datetime":"2003-11-02T12:01:01"
           "timestamp":58728000,
           "obid":3,
           "guid":"FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00",
           "sizedata":3,
           "data":[0,1,2]
      },
      {
          "head":96,
          "vscpclass":10,
          "vscptype":6,
          "datetime":"2003-11-02T12:01:01"
          "timestamp":58729046,
          "obid":3,
          "guid":"FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00",
          "sizedata":4,
          "data":[138,129,0,215]
       }
   ],
   "count":10,
   "filtered":0,
   "errors":0
}
```

####  JSONP 

```javascript
typeof handler === 'function' && handler(
{
    "success":true,
    "code":1,
    "message":"success",
    "description":"Success",
    "info":"10 events requested of 10 available (unfiltered) 10 will be retrieved",
    "event":   
    [
        { 
            "head":96,
            "vscpclass":10,
            "vscptype":6,
            "datetime":"2003-11-02T12:01:01"
            "timestamp":58712468,
            "obid":3,
            "guid":"FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00",
            "sizedata":4,
            "data":[138,129,0,204]
        },
        {
            "head":96,
            "vscpclass":10,
            "vscptype":6,
            "datetime":"2003-11-02T12:01:01"
            "timestamp":58714468,
            "obid":3,
            "guid":"FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00",
            "sizedata":4,
            "data":[138,129,0,206]
       },
       {
            "head":96,
            "vscpclass":10,
            "vscptype":6,
            "datetime":"2003-11-02T12:01:01"
            "timestamp":58716531,
            "obid":3,
            "guid":"FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00",
            "sizedata":4,
            "data":[138,129,0,205]
       },
       {
            "head":96,
            "vscpclass":10,
            "vscptype":6,
            "datetime":"2003-11-02T12:01:01"
            "timestamp":58718546,
            "obid":3,
            "guid":"FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00",
            "sizedata":4,
            "data":[138,129,0,206,]
       },
       {
            "head":96,
            "vscpclass":10,
            "vscptype":6,
            "datetime":"2003-11-02T12:01:01"
            "timestamp":58720625,
            "obid":3,
            "guid":"FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00",
            "sizedata":4,
            "data":[138,129,0,208]
       },
       {
            "head":96,
            "vscpclass":10,
            "vscptype":6,
            "datetime":"2003-11-02T12:01:01"
            "timestamp":58722859,
            "obid":3,
            "guid":"FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00",
            "sizedata":3,
            "data":[138,128,21]
       },
       {
            "head":96,
            "vscpclass":10,
            "vscptype":6,
            "datetime":"2003-11-02T12:01:01"
            "timestamp":58724906,
            "obid":3,
            "guid":"FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00",
            "sizedata":4,
            "data":[138,129,0,213]
       },
       {
            "head":96,
            "vscpclass":10,
            "vscptype":6,
            "datetime":"2003-11-02T12:01:01"
            "timestamp":58726937,
            "obid":3,
            "guid":"FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00",
            "sizedata":4,
            "data":[138,129,0,216]
      },
      {
           "head":96,
           "vscpclass":20,
           "vscptype":9,
           "datetime":"2003-11-02T12:01:01"
           "timestamp":58728000,
           "obid":3,
           "guid":"FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00",
           "sizedata":3,
           "data":[0,1,2]
      },
      {
          "head":96,
          "vscpclass":10,
          "vscptype":6,
          "datetime":"2003-11-02T12:01:01"
          "timestamp":58729046,
          "obid":3,
          "guid":"FF:FF:FF:FF:FF:FF:FF:F7:03:00:00:00:00:00:00:00",
          "sizedata":4,
          "data":[138,129,0,215]
       }
   ],
   "count":10
   "filtered":0,
   "errors":0
} );
```


## Set Filter

```css
    op=5 or op=SETFILTER
```  
    
Set read filter. Requires a valid **session parameter** and **vscfilter** and **vscpmask** where 

**General format:**
```css
http://server:port/rest?
    vscpsession=session-key&
    format=plain|csv|xml|json|jsonp&
    op=5|setfilter&
    vscpfilter=filter&
    vscpmask=mask
```

**Arguments:**


*  **op** - Set to 5|setfilter

*  **format** - can be 2|xml, 3|json or 4|jsonp (0|plain and 1|csv returns error).

*  **vscpsession** - A valid session key received from the open method.

*  **vscpfilter** - Filter as described above.

*  **vscpmask** - Mask as described above.

**vscpfilter** should be given as

    priority,class,type,GUID
    
and **vscpmask** as

    priority,class,type,GUID

It is possible to leave out parameters as long as they are left out at the end.

To rest the filter (let all events through) set booth stings to

    "0,0,0,00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00"

### HTTP Request with GET

```css
http://host:port/vscp/rest?
    vscpsession=d1c13eb83f52f319f14d167962048521&
    format=plain|csv|xml|json|jsonp&
    op=5|setfilter&vscpfilter=filter&vscpmask=mask    
```

to test this with **curl** use the following format

```css
curl -X GET "http://host:port/vscp/rest? \
    vscpsession=d1c13eb83f52f319f14d167962048521 & \
    format=plain|csv|xml|json|jsonp& \
    op=5|setfilter" & \
    vscpfilter=filter & \
    vscpmask=mask
```


### Examples

###### example GET HTTP request

```css
    http://localhost:8884/vscp/rest?  
              vscpsession=d1c13eb83f52f319f14d167962048521&
              format=plain&
              op=5&
              vscpfilter=filter&
              vscpmask=mask
```  


### HTTP Request with POST

```css
curl -X POST "http://localhost:8884/vscp/rest" \
    -H "vscpsession: d1c13eb83f52f319f14d167962048521" \ 
    -d "op=setfilter&format=plain&vscpfilter=filter&vscpmask=mask"     
```

### Demo

There is a a [demo app.](https://github.com/grodansparadis/vscp-ux/tree/master/rest) in the source tree, that demonstrates this functionality using JavaScript.

#### JavaScript Request with JSONP

```javascript
//////////////////////////////////////////////////////////////////
// do_setFilter
//
		
var do_setFilter = function() {

    // Filter/Mask to filter just to receive heart beats CLASS1.INFORMATION, Type=9 Node heartbeat
    // both are "priority,class,type,guid"
    var txtVscpFilter = "0x0000,0x14,0x09,00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00";
    var txtVscpMask = "0x0000,0xffff,0xffff,00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00";
			
    if ( VscpSessionKey.length > 0 ) {	
        $.ajax({
             url: VscpServer + '/vscp/rest?vscpsession=' + VscpSessionKey + '&format=jsonp&op=setfilter&vscpfilter=' + txtVscpFilter + '&vscpmask=' + txtVscpMask,
             type : "GET",
             jsonpCallback: 'handler',
             cache: true,
             dataType: 'jsonp',
             success: function(response) {
                 // response will be a JavaScript
                 // array of objects
	         console.log("-----------------------------------------------------------");
                 console.log("                         do_setFilter");
                 console.log("-----------------------------------------------------------");
                 console.log("Success = " + response.success );
                 console.log("Code = " + response.code );
                 console.log("Message = " + response.message );
                 console.log("Description = " + response.description );		
                 console.log("Info = " + response.info );
					
                 if ( response.success ) {
                     $("#events").html( "Mask set" );
                 }					
					
             },
             error: function( xhr, status, error ) {
                 console.log( "Close:" + error + " Status:" + status );
             }
         });
    }
    else {
        alert("Interface is not open!");
    }

};
```

or clearing the filter

```javascript
//////////////////////////////////////////////////////////////////
// do_clrFilter
//
		
var do_clrFilter = function() {
			
    if ( VscpSessionKey.length > 0 ) {	
        $.ajax({
            url: VscpServer + '/vscp/rest?vscpsession=' + VscpSessionKey + 
                '&format=jsonp&op=setfilter&vscpfilter=' + 
                "0,0,0,00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00" + 
                '&vscpmask=' + 
                "0,0,0,00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00",
           type : "GET",
           jsonpCallback: 'handler',
           cache: true,
           dataType: 'jsonp',
           success: function(response) {
               // response will be a JavaScript
               // array of objects
               console.log("-----------------------------------------------------------");
               console.log("                         do_clrFilter");
               console.log("-----------------------------------------------------------");
               console.log("Success = " + response.success );
               console.log("Code = " + response.code );
               console.log("Message = " + response.message );
               console.log("Description = " + response.description );
               console.log("Info = " + response.info );
					
               if ( response.success ) {
                   $("#events").html( "Mask set" );
               }					
					
           },
           error: function( xhr, status, error ) {
               console.log( "Close:" + error + " Status:" + status );
           }
       });
    }
    else {
        alert("Interface is not open!");
    }

};
```

###  Responses
	
####  Plain
	`<code>`
	1 1 Success 
	
	Everything is fine.


#### CSV

	
	success-code,error-code,message,description
	1,1,Success,Success.


#### XML

```xml
<vscp-rest success="true" code="1" message="Success" description="Success."/>
```

#### JSON

```css
{"success":true,"code":1,"message":"success","description":"Success"}
```

#### JSONP

```javascript
typeof handler === 'function' && handler({"success":true,"code":1,"message":"success","description":"Success"});
```

## Clear Input queue

```css
    op=6 or op=CLEARQUEUE
```  

Clear the input queue for this clients session. **Requires a valid session parameter**

**General format:**

```css
http://server:port/rest?
    vscpsession=session-key&
    format=plain|csv|xml|json|jsonp&
    op=6|clearqueue
```

**Arguments:**


*  **op** - Set to 6|clearqueue

*  **format** - can be 2|xml, 3|json or 4|jsonp (0|plain and 1|csv returns error).

*  **vscpsession** - A valid session key received from the open method.

### HTTP Request with GET

```css
http://demo.vscp.org:8884/vscp/rest?vscpsession=d1c13eb83f52f319f14d167962048521 &format=plain|csv|xml|json|jsonp&op=6|clearqueue    
```

to test this with **curl** use the following format

```bash
curl -X GET "http://host:port/vscp/rest? \
    vscpsession=d1c13eb83f52f319f14d167962048521 & \
    format=plain|csv|xml|json|jsonp& \
    op=6|clearqueue"
```


### Examples

###### example GET HTTP request

```css
    http://localhost:8884/vscp/rest?  
              vscpsession=d1c13eb83f52f319f14d167962048521&
              format=plain&
              op=6
```  


### HTTP Request with POST

```bash
curl -X POST "http://localhost:8884/vscp/rest" \
    -H "vscpsession: d1c13eb83f52f319f14d167962048521" \ 
    -d "op=clearqueue&format=plain"     
```

### Demo

There is a a [demo app.](https://github.com/grodansparadis/vscp-ux/tree/master/rest) in the source tree, that demonstrates this functionality using JavaScript.

#### JavaScript Request with JSONP

```javascript
//////////////////////////////////////////////////////////////////
// do_clrQueue
//
		
var do_clrQueue = function() {
			
    if ( VscpSessionKey.length > 0 ) {	
        $.ajax({
            url: VscpServer + '/vscp/rest?vscpsession=' + VscpSessionKey + 
                '&format=jsonp&op=clearqueue',
            type : "GET",
            jsonpCallback: 'handler',
            cache: true,
            dataType: 'jsonp',
            success: function(response) {
                // response will be a JavaScript
                // array of objects
                console.log("-----------------------------------------------------------");
                console.log("                         do_clrQueue");
                console.log("-----------------------------------------------------------");
                console.log("Success = " + response.success );
                console.log("Code = " + response.code );
                console.log("Message = " + response.message );
                console.log("Description = " + response.description );
                console.log("Info = " + response.info );
					
                if ( response.success ) {
                    $("#events").html( "Mask set" );
                }					
					
            },
            error: function( xhr, status, error ) {
                console.log( "Close:" + error + " Status:" + status );
            }
        });
    }
    else {
        alert("Interface is not open!");
    }

};
```

### Responses

#### Plain

	
	1 1 Success 
	
	Everything is fine.


#### CSV

	
	success-code,error-code,message,description
	1,1,Success,Success.


#### XML

```xml
<vscp-rest success="true" code="1" message="Success" description="Success."/>
```

#### JSON

```css
{"success":true,"code":1,"message":"success","description":"Success"}
```

#### JSONP

```javascript
typeof handler === 'function' && handler({"success":true,"code":1,"message":"success","description":"Success"});
```


## List variables

```css
    op=12 or op=LISTVAR
```  
    
List variables selected with a regular expression. 

**Requires a valid session parameter**

**General format:**

```css
http://host:port/vscp/rest?
    vscpsession=session-key&
    format=plain|csv|xml|json|jsonp&
    op=12|listvar&
    [listlong=true|false]
    [regex=regular-expression]   
```

**Arguments:**


*  **op** - Set to 12|listvar

*  **format** - can be 2|xml, 3|json or 4|jsonp (0|plain and 1|csv returns error).

*  **vscpsession** - A valid session key received from the open method.

*  **listlong** - Optional setting that defaults to false. When false the variable list dos not include __value__ and __note__. If set to true __value__ and __note__ is included. The setting should be used with caution as both __value__ and __note__ can be very large. It is often a better alternative to list variables with **listvar** and then use **readvar** to retrieve full data for specific variables of interest.

*  **regex** - Optional regular expression to select variables to list. If not given or empty all variables will be listed.

### HTTP Request with GET

```css
   http://host:port/vscp/rest?vscpsession=sessionkey
      &format=plain|csv|xml|json|jsonp&op=7|listvar[&listlong=true][&regex=`<regular expression>`]   
```

### Examples

#### Example HTTP GET request

```css
    http://localhost:8884/vscp/rest?  
              vscpsession=d1c13eb83f52f319f14d167962048521&
              format=plain&
              op=12&
              regex=SIM1
```  

#### Example Curl HTTP Request with GET

```css
curl -X GET "http://localhost:8884/vscp/rest?vscpsession=d1c13eb83f52f319f14d167962048521&op=12&format=plain&regex=SIM1"     
```

#### Example Curl HTTP Request with POST

```css
curl -X POST "http://localhost:8884/vscp/rest" \
    -H "vscpsession: d1c13eb83f52f319f14d167962048521" \ 
    -d "op=listvar&format=plain&regex=SIM"     
```

### Demo

There is a a [demo app.](https://github.com/grodansparadis/vscp-ux/tree/master/rest) in the source tree, that demonstrates this functionality using JavaScript.

#### JavaScript Request with JSONP

```javascript
//////////////////////////////////////////////////////////////////
// printVariableData
//

var printVariableData = function( variable, bLong ) {

    var vartxt = "`<b>`Variable`</b>`: `<b>`Name`</b>`:" + variable.varname +	
       "  `<b>`Type`</b>`:" + variable.vartype + " `<b>`Typecode`</b>`:" + 
       variable.vartypecode + " `<b>`Persistence`</b>`:" + variable.varpersistence +
       " `<b>`User`</b>`:" + variable.varuser + " `<b>`Access-rights`</b>`:" + 
       variable.varaccessright + " `<b>`Last-change`</b>`:" + variable.varlastchange;

    if ( true === bLong ) {
        vartxt += "`<br>``<b>`Value`</b>`:" + variable.varvalue;
        vartxt += "`<br>``<b>`Note`</b>`:" + variable.varnote;
        vartxt += "`<br>`-----------------------------------------------------------------------------";	
    }

    return vartxt;
}

//////////////////////////////////////////////////////////////////
// do_listVariables
//

var do_listVariables = function() {

    if ( VscpSessionKey.length > 0 ) {	

        $("#events").html( "" );
	var txtRegEx = window.prompt("Regular expression (leave blank to select all):","");
        if ( null == txtRegEx ) txtRegEx = "(.*)";

            $.ajax({
                url: VscpServer + '/vscp/rest?vscpsession=' + VscpSessionKey + 
                  '&format=jsonp&op=listvar&listlong=false&regex=' + encodeURIComponent( txtRegEx ),                  
                type : "GET",
                jsonpCallback: 'handler',
                cache: true,
                dataType: 'jsonp',
                success: function(response) {
                    // response will be a JavaScript
                    // array of objects		
                    console.log("-----------------------------------------------------------");
                    console.log("                     do_listVariables");
                    console.log("-----------------------------------------------------------");
                    console.log("Success = " + response.success );
                    console.log("Code = " + response.code );
                    console.log("Message = " + response.message );
                    console.log("Description = " + response.description );
                    console.log("Info = " + response.info );
                    console.log("Count = " + response.count );
                    console.log("Errors = " + response.errors );
                    
                    if ( response.success ) {
                        if ( response.count > 0 ) {
                            var eventtxt = "";
                            for (var i=0; i<response.count; i++ ) {
                                eventtxt += printVariableData( response.variable[i], false ) + "`<br>`";
                            }
			    $("#events").html( eventtxt );
                         }
                         else {
                             $("#events").html( " " );
                             $("#nevents").html( "It looks like there is no variables to read." 
                         );
                     };
                 }
					
             },
             error: function( xhr, status, error ) {
                 console.log( "do_listVariable:" + error + " Status:" + status );
             }
         });
    }
    else {
        alert("Interface is not open!");
    }

};
```

### Responses



**note** Response format has changed from version 1.12.14.12 and now include *user*, *access-rights*, *last-change*. Also all note data is always BASE64 encoded and this is true also for 'string-type' values.

With the format parameter you set the format your want the response represented as. The following shows the positive outcome of the Open HTTP request for all formats available.

###### Response for format=plain

```css
curl -X POST "http://localhost:8884/vscp/rest" -H "vscpsession:6c77f7bb681cf4c252984550f0dd3c22" -d "op=listvar&format=plain&regex=SIM"

1 1 Success 
name=SIM1_BLEVEL20 type=2 user=0 access-right=000 last-change='2016-10-06T18:15:38' persistent=false
name=SIM1_CODING0 type=3 user=0 access-right=000 last-change='2016-10-06T18:15:38' persistent=false
name=SIM1_DECISIONMATRIX0 type=1 user=0 access-right=700 last-change='2016-10-06T18:15:38' persistent=false
name=SIM1_GUID0 type=8 user=0 access-right=700 last-change='2016-10-06T18:15:38' persistent=false
name=SIM1_INDEX0 type=3 user=0 access-right=700 last-change='2016-10-06T18:15:38' persistent=false
name=SIM1_INTERVAL0 type=3 user=0 access-right=700 last-change='2016-10-06T18:15:38' persistent=false
name=SIM1_MEASUREMENTCLASS0 type=4 user=0 access-right=700 last-change='2016-10-06T18:15:38' persistent=false
name=SIM1_MEASUREMENTTYPE0 type=4 user=0 access-right=700 last-change='2016-10-06T18:15:38' persistent=false
name=SIM1_NUMBEROFNODES type=3 user=0 access-right=700 last-change='2016-10-06T18:15:38' persistent=false
name=SIM1_PATH0 type=1 user=0 access-right=700 last-change='2016-10-06T18:15:38' persistent=false
name=SIM1_SUBZONE0 type=3 user=0 access-right=700 last-change='2016-10-06T18:15:38' persistent=false
name=SIM1_UNIT0 type=3 user=0 access-right=700 last-change='2016-10-06T18:15:38' persistent=false
name=SIM1_ZONE0 type=3 user=0 access-right=700 last-change='2016-10-06T18:15:38' persistent=false 
```

###### Response for format=csv

```css
curl -X POST "http://localhost:8884/vscp/rest" -H "vscpsession: 6c77f7bb681cf4c252984550f0dd3c22" -d "op=listvar&format=1&regex=SIM"

success-code,error-code,message,description,Variable
1,1,Success,Success.,NULL
1,2,Info,13 variables found,NULL
1,5,Count,13,NULL
1,3,Data,Variable,SIM1_BLEVEL20;2;0;700;false;2016-10-06T18:15:38
1,3,Data,Variable,SIM1_CODING0;3;0;700;false;2016-10-06T18:15:38
1,3,Data,Variable,SIM1_DECISIONMATRIX0;1;0;700;false;2016-10-06T18:15:38
1,3,Data,Variable,SIM1_GUID0;8;0;700;false;2016-10-06T18:15:38
1,3,Data,Variable,SIM1_INDEX0;3;0;700;false;2016-10-06T18:15:38
1,3,Data,Variable,SIM1_INTERVAL0;3;0;700;false;2016-10-06T18:15:38
1,3,Data,Variable,SIM1_MEASUREMENTCLASS0;4;0;700;false;2016-10-06T18:15:38
1,3,Data,Variable,SIM1_MEASUREMENTTYPE0;4;0;700;false;2016-10-06T18:15:38
1,3,Data,Variable,SIM1_NUMBEROFNODES;3;0;700;false;2016-10-06T18:15:38
1,3,Data,Variable,SIM1_PATH0;1;0;700;false;2016-10-06T18:15:38
1,3,Data,Variable,SIM1_SUBZONE0;3;0;700;false;2016-10-06T18:15:38
1,3,Data,Variable,SIM1_UNIT0;3;0;700;false;2016-10-06T18:15:38
1,3,Data,Variable,SIM1_ZONE0;3;0;700;false;2016-10-06T18:15:38
```

###### response for format=xml

```css
curl -X POST "http://localhost:8884/vscp/rest" -H "vscpsession: 6c77f7bb681cf4c252984550f0dd3c22" -d "op=listvar&format=2&regex=SIM"
```

```xml
<?xml version = "1.0" encoding = "UTF-8" ?>
<vscp-rest success = "true" code = "1" message = "Success" description = "Success." >
<variable name="SIM1_BLEVEL20" 
    typecode="2" 
    type="Boolean" 
    user="0" 
    access-right="700" 
    persistent="false" 
    last-change="2016-10-06T18:15:38" >

<variable name="SIM1_CODING0" 
    typecode="3" 
    type="Integer" 
    user="0" 
    access-right="700" 
    persistent="false" 
    last-change="2016-10-06T18:15:38" >

<variable name="SIM1_DECISIONMATRIX0" 
    typecode="1" 
    type="String" 
    user="0" 
    access-right="700" 
    persistent="false" 
    last-change="2016-10-06T18:15:38" >

<variable name="SIM1_GUID0" 
    typecode="8" 
    type="VscpGuid" 
    user="0" access-right="700" 
    persistent="false" 
    last-change="2016-10-06T18:15:38" >
    
<variable name="SIM1_INDEX0" 
    typecode="3" 
    type="Integer" 
    user="0" 
    access-right="700" 
    persistent="false" 
    last-change="2016-10-06T18:15:38" >
    
<variable name="SIM1_INTERVAL0" 
    typecode="3" 
    type="Integer" 
    user="0" 
    access-right="700" 
    persistent="false" 
    last-change="2016-10-06T18:15:38" >
    
<variable name="SIM1_MEASUREMENTCLASS0" 
    typecode="4" 
    type="Long" 
    user="0" 
    access-right="700" 
    persistent="false" 
    last-change="2016-10-06T18:15:38" >
    
<variable name="SIM1_MEASUREMENTTYPE0" 
    typecode="4" 
    type="Long" 
    user="0" 
    access-right="700" 
    persistent="false" 
    last-change="2016-10-06T18:15:38" >
    
<variable name="SIM1_NUMBEROFNODES" 
    typecode="3" 
    type="Integer" 
    user="0" 
    access-right="700" 
    persistent="false" 
    last-change="2016-10-06T18:15:38" >
    
<variable name="SIM1_PATH0" 
    typecode="1" 
    type="String" 
    user="0" 
    access-right="700" 
    persistent="false" 
    last-change="2016-10-06T18:15:38" >
    
<variable name="SIM1_SUBZONE0" 
    typecode="3" 
    type="Integer" 
    user="0" 
    access-right="700" 
    persistent="false" 
    last-change="2016-10-06T18:15:38" >
    
<variable name="SIM1_UNIT0" 
    typecode="3" 
    type="Integer" 
    user="0" 
    access-right="700" 
    persistent="false" 
    last-change="2016-10-06T18:15:38" >
    
<variable name="SIM1_ZONE0" 
    typecode="3" 
    type="Integer" 
    user="0" 
    access-right="700" 
    persistent="false" 
    last-change="2016-10-06T18:15:38" >
    
</variable>

</vscp-rest>
```

###### response for format=json

```css
curl -X POST "http://localhost:8884/vscp/rest"3&regex=SIM"ion: 6c77f7bb681cf4c252984550f0dd3c22" -d "op=listvar&format=2

{"success":true,"code":1,"message":"success","description":"Success","info":"13 variables will be retrieved","variable":
[{"varname":"SIM1_BLEVEL20","vartype":"Boolean","vartypecode":2,"varuser":0,"varaccessright":700,"varpersistence":"false","varlastchange":"2016-10-06T18:15:38",},
{"varname":"SIM1_CODING0","vartype":"Integer","vartypecode":3,"varuser":0,"varaccessright":700,"varpersistence":"false","varlastchange":"2016-10-06T18:15:38",},
{"varname":"SIM1_DECISIONMATRIX0","vartype":"String","vartypecode":1,"varuser":0,"varaccessright":700,"varpersistence":"false","varlastchange":"2016-10-06T18:15:38",},
{"varname":"SIM1_GUID0","vartype":"VscpGuid","vartypecode":8,"varuser":0,"varaccessright":700,"varpersistence":"false","varlastchange":"2016-10-06T18:15:38",},
{"varname":"SIM1_INDEX0","vartype":"Integer","vartypecode":3,"varuser":0,"varaccessright":700,"varpersistence":"false","varlastchange":"2016-10-06T18:15:38",},
{"varname":"SIM1_INTERVAL0","vartype":"Integer","vartypecode":3,"varuser":0,"varaccessright":700,"varpersistence":"false","varlastchange":"2016-10-06T18:15:38",},
{"varname":"SIM1_MEASUREMENTCLASS0","vartype":"Long","vartypecode":4,"varuser":0,"varaccessright":700,"varpersistence":"false","varlastchange":"2016-10-06T18:15:38",},
{"varname":"SIM1_MEASUREMENTTYPE0","vartype":"Long","vartypecode":4,"varuser":0,"varaccessright":700,"varpersistence":"false","varlastchange":"2016-10-06T18:15:38",},
{"varname":"SIM1_NUMBEROFNODES","vartype":"Integer","vartypecode":3,"varuser":0,"varaccessright":700,"varpersistence":"false","varlastchange":"2016-10-06T18:15:38",},
{"varname":"SIM1_PATH0","vartype":"String","vartypecode":1,"varuser":0,"varaccessright":700,"varpersistence":"false","varlastchange":"2016-10-06T18:15:38",},
{"varname":"SIM1_SUBZONE0","vartype":"Integer","vartypecode":3,"varuser":0,"varaccessright":700,"varpersistence":"false","varlastchange":"2016-10-06T18:15:38",},
{"varname":"SIM1_UNIT0","vartype":"Integer","vartypecode":3,"varuser":0,"varaccessright":700,"varpersistence":"false","varlastchange":"2016-10-06T18:15:38",},
{"varname":"SIM1_ZONE0","vartype":"Integer","vartypecode":3,"varuser":0,"varaccessright":700,"varpersistence":"false","varlastchange":"2016-10-06T18:15:38",}],"count":13,"errors":0}

```

###### response for format=jsonp

```javascript
curl -X POST "http://localhost:8884/vscp/rest" -H "vscpsession: 6c77f7bb681cf4c252984550f0dd34&regex=SIM"istvar&format=3

typeof handler === 'function' && 
handler({"success":true,"code":1,"message":"success","description":"Success","info":"13 variables will be retrieved","variable":
[{"varname":"SIM1_BLEVEL20","vartype":"Boolean","vartypecode":2,"varuser":0,"varaccessright":0,"varpersistence":"false","varlastchange":"2016-10-06T18:15:38",},
{"varname":"SIM1_CODING0","vartype":"Integer","vartypecode":3,"varuser":0,"varaccessright":0,"varpersistence":"false","varlastchange":"2016-10-06T18:15:38",},
{"varname":"SIM1_DECISIONMATRIX0","vartype":"String","vartypecode":1,"varuser":0,"varaccessright":0,"varpersistence":"false","varlastchange":"2016-10-06T18:15:38",},
{"varname":"SIM1_GUID0","vartype":"VscpGuid","vartypecode":8,"varuser":0,"varaccessright":0,"varpersistence":"false","varlastchange":"2016-10-06T18:15:38",},
{"varname":"SIM1_INDEX0","vartype":"Integer","vartypecode":3,"varuser":0,"varaccessright":0,"varpersistence":"false","varlastchange":"2016-10-06T18:15:38",},
{"varname":"SIM1_INTERVAL0","vartype":"Integer","vartypecode":3,"varuser":0,"varaccessright":0,"varpersistence":"false","varlastchange":"2016-10-06T18:15:38",},
{"varname":"SIM1_MEASUREMENTCLASS0","vartype":"Long","vartypecode":4,"varuser":0,"varaccessright":0,"varpersistence":"false","varlastchange":"2016-10-06T18:15:38",},
{"varname":"SIM1_MEASUREMENTTYPE0","vartype":"Long","vartypecode":4,"varuser":0,"varaccessright":0,"varpersistence":"false","varlastchange":"2016-10-06T18:15:38",},
{"varname":"SIM1_NUMBEROFNODES","vartype":"Integer","vartypecode":3,"varuser":0,"varaccessright":0,"varpersistence":"false","varlastchange":"2016-10-06T18:15:38",},
{"varname":"SIM1_PATH0","vartype":"String","vartypecode":1,"varuser":0,"varaccessright":0,"varpersistence":"false","varlastchange":"2016-10-06T18:15:38",},
{"varname":"SIM1_SUBZONE0","vartype":"Integer","vartypecode":3,"varuser":0,"varaccessright":0,"varpersistence":"false","varlastchange":"2016-10-06T18:15:38",},
{"varname":"SIM1_UNIT0","vartype":"Integer","vartypecode":3,"varuser":0,"varaccessright":0,"varpersistence":"false","varlastchange":"2016-10-06T18:15:38",},
{"varname":"SIM1_ZONE0","vartype":"Integer","vartypecode":3,"varuser":0,"varaccessright":0,"varpersistence":"false","varlastchange":"2016-10-06T18:15:38",}],"count":13,"errors":0});

```


## Read variable

```css
    op=7 or op=READVAR
```  
    
Read the value of a server variable. **Requires a valid session parameter**

**General format:**

```css
http://host:port/vscp/rest?
    vscpsession=session-key&
    format=plain|csv|xml|json|jsonp&
    op=7|readvar&
    variable=variable-name   
```

**Arguments:**


*  **op** - Set to 7|readvar

*  **format** - can be 2|xml, 3|json or 4|jsonp (0|plain and 1|csv returns error).

*  **vscpsession** - A valid session key received from the open method.

*  **variable** - Name of variable.

### HTTP Request with GET

```css
http://host:port/vscp/rest?vscpsession=d1c13eb83f52f319f14d167962048521 &format=plain|csv|xml|json|jsonp&op=7|readvar &variable=`<variable_name>`   
```



to test this with **curl** use the following format

```css
curl -X GET "http://host:port/vscp/rest? \
    vscpsession=d1c13eb83f52f319f14d167962048521 & \
    format=plain|csv|xml|json|jsonp& \
    op=7|readvar \
    variable=`<variable_name>`"
```


### Examples

###### example GET HTTP request

```css
    http://localhost:8884/vscp/rest?  
              vscpsession=d1c13eb83f52f319f14d167962048521&
              format=plain&
              op=7&
              variable=SIM1_ZONE0
```  
### HTTP Request with POST

```css
curl -X POST "http://localhost:8884/vscp/rest" \
    -H "vscpsession: d1c13eb83f52f319f14d167962048521" \ 
    -d "op=readvar&format=plain"     
```
### Demo

There is a a [demo app.](https://github.com/grodansparadis/vscp-ux/tree/master/rest) in the source tree, that demonstrates this functionality using JavaScript.

#### JavaScript Request with JSONP

```javascript
//////////////////////////////////////////////////////////////////
// do_readVariable
//
		
var do_readVariable = function() {
			
    if ( VscpSessionKey.length > 0 ) {

        var txtVariableName = window.prompt("Name of variable to read:","test");
				
        $.ajax({
            url: VscpServer + '/vscp/rest?vscpsession=' + VscpSessionKey + 
                 '&format=jsonp&op=readvar&variable=' + txtVariableName,
            type : "GET",
            jsonpCallback: 'handler',
            cache: true,
            dataType: 'jsonp',
            success: function(response) {
                // response will be a javaScript
                // array of objects
                console.log("-----------------------------------------------------------");
                console.log("                     do_readVariable");
                console.log("-----------------------------------------------------------");
                console.log("Success = " + response.success );
                console.log("Code = " + response.code );
                console.log("Message = " + response.message );
                console.log("Description = " + response.description );
                console.log("Info = " + response.info );
                console.log("Variable name = " + response.varname );                
                console.log("Variable type = " + response.vartype );
                console.log("Variable type code = " + response.vartypecode );
                console.log("Variable percistence = " + response.varpersistence );
                console.log("Variable user = " + response.varuser );
                console.log("Variable access-rights = " + response.varaccessright );
                console.log("Variable last-change = " + response.varlastchange );
                console.log("Variable value = " + response.varvalue );
                console.log("Variable note = " + response.varnote );
					
                if ( response.success ) {
                    $("#log").html( response.varname + " = " + response.varvalue + 
                           "`<br>`Type = " + response.vartype + 
                           "`<br>`Typecode = " + response.vartypecode + 
                           "`<br>`Peristence = " + response.varpersistence +
                           "`<br>`User = " + response.varuser +
                           "`<br>`Access-rights = " + response.varaccessright.toString(16) +
                           "`<br>`Last-change = " + response.varlastchange +
                           "`<br>`Note = " + response.varnote );
                }
                else {
                    $("#log").html( "Unable to read variable" );
                }
					
            },
            error: function( xhr, status, error ) {
                console.log( "do_readVariable:" + error + " Status:" + status );
            }
        });
    }
    else {
	alert("Interface is not open!");
    }
};
```

### Responses

**note** Response format has changed from version 1.12.14.12 and now include *user*, *access-rights*, *last-change*. Also all note data is always BASE64 encoded and this is true also for 'string-type' values.

With the format parameter you set the format your want the response represented as. The following shows the positive outcome of the Open HTTP request for all formats available.

###### Response for format=plain

```css
1 1 Success 
name=TEST type=1 user=0 access-rights=777 persistent=true last-change=2016-09-29T11:36:11 value='VGhpcyBpcyBhIHRlc3Q=' note='U3RheSBodW5ncnksIHN0YXkgZm9vbGlzaA=='
```

where 

```javascript
"VGhpcyBpcyBhIHRlc3Q=" = BASE64("This is a test")\\
"U3RheSBodW5ncnksIHN0YXkgZm9vbGlzaA==" = BASE64("Stay hungry, stay foolish") 
```
###### Response for format=csv

```css
success-code,error-code,message,description,Variable,Type,Persistent,Value,Note
1,1,Success,Success.,test,1,0,777,true,2016-09-29T11:36:11'VGhpcyBpcyBhIHRlc3Q=','U3RheSBodW5ncnksIHN0YXkgZm9vbGlzaA=='
```

###### response for format=xml

```xml
<vscp-rest success="true" 
            code="1" 
            message="Success"    
            description="Success.">
    <variable type="1(String)" persistent="true">
        <name>TEST</name>
        <value>VGhpcyBpcyBhIHRlc3Q</value>
        <note>U3RheSBodW5ncnksIHN0YXkgZm9vbGlzaA==</note>
    </variable>
</vscp-rest>
```

###### response for format=json

```css
{"success":true,"code":1,"message":"success","description":"Success","varname":"TEST","vartype":"String","vartypecode":1,"varpersistence":"true","varvalue":"VGhpcyBpcyBhIHRlc3Q","varnote":"U3RheSBodW5ncnksIHN0YXkgZm9vbGlzaA=="}
```

###### response for format=jsonp

```javascript
typeof handler === 'function' && handler({"success":true,"code":1,"message":"success","description":"Success","varname":"TEST","vartype":"String","vartypecode":1,"varpersistence":"true","varvalue":"VGhpcyBpcyBhIHRlc3Q","varnote":"U3RheSBodW5ncnksIHN0YXkgZm9vbGlzaA=="});
```


## Write variable

```css
    op=8 or op=WRITEVAR
```  
    
Write/change a remote variable value. If you want to change other parameters then the value of a variable use [create Variable](./rest_interface_createvar.md).

**Requires a valid session parameter**

**General form:**
http://host:port/vscp/rest?
    vscpsession=session-key&
    format=plain|csv|xml|json|jsonp&
    op=8|writevar&
    variable=name&
    value=value

**Arguments:**


*  **op** - Set to 8|writevar

*  **format** - can be 2|xml, 3|json or 4|jsonp (0|plain and 1|csv returns error).

*  **vscpsession** - A valid session key received from the open method.

*  **variable** - Name of variable.

*  **value** - Value for variable.

### HTTP Request with GET

```css
http://demo.vscp.org:8884/vscp/rest?vscpsession=d1c13eb83f52f319f14d167962048521 &format=plain|csv|xml|json|jsonp&op=8|writevar&variable=name&value=value    
```

to test this with **curl** use the following format

```css
curl -X GET "http://host:port/vscp/rest? \
    vscpsession=d1c13eb83f52f319f14d167962048521 & \
    format=plain|csv|xml|json|jsonp& \
    op=8|writevar"
```


### Examples

###### example GET HTTP request

```css
    http://localhost:8884/vscp/rest?  
              vscpsession=d1c13eb83f52f319f14d167962048521&
              format=plain&
              op=8
```  

### Curl example HTTP Request with POST

```css
curl -X POST "http://localhost:8884/vscp/rest" \
    -H "vscpsession: d1c13eb83f52f319f14d167962048521" \ 
    -d "op=writevar&format=plain"     
```

### Demo

There is a a [demo app.](https://github.com/grodansparadis/vscp-ux/tree/master/rest) in the source tree, that demonstrates this functionality using JavaScript.

#### JavaScript Request with JSONP

```javascript
//////////////////////////////////////////////////////////////////
// do_writeVariable
//
		
var do_writeVariable = function() {
			
    if ( VscpSessionKey.length > 0 ) {

        var txtVariableName = window.prompt("Name of variable to write:","test");
        var txtVariableValue = window.prompt("New value (BASE64 encoded for string types):","");
				
        $.ajax({
            url: VscpServer + '/vscp/rest?vscpsession=' + VscpSessionKey + 
                    '&format=jsonp&op=writevar&variable=' + txtVariableName +
                    '&value=' + encodeURIComponent( txtVariableValue ),
                    type : "GET",
            jsonpCallback: 'handler',
            cache: true,
            dataType: 'jsonp',
            success: function(response) {
                // response will be a javascript
                // array of objects
                console.log("-----------------------------------------------------------");
                console.log("                   do_writeVariable");
                console.log("-----------------------------------------------------------");
                console.log("Success = " + response.success );
                console.log("Code = " + response.code );
                console.log("Message = " + response.message );
                console.log("Description = " + response.description );
                console.log("Info = " + response.info );
                if ( response.success ) {
                    $("#events").html( "OK Variable written" );
                }								
            },
            error: function( xhr, status, error ) {
                console.log( "Close:" + error + " Status:" + status );
            }
        });
    }
    else {
        alert("Interface is not open!");
    }

};
```

### Responses

#### Plain

	
	1 1 Success 
	
	Everything is fine.


#### CSV

	success-code,error-code,message,description
	1,1,Success,Success.


#### XML

```xml
`<vscp-rest success="true" code="1" message="Success" description="Success."/>`
```

#### JSON

```css
{"success":true,"code":1,"message":"success","description":"Success"}
```

#### JSONP

```javascript
typeof handler === 'function' && handler({"success":true,"code":1,"message":"success","description":"Success"});
```

## Create variable

```css
    op=9 or op=CREATEVAR
```  
    
Create a remote variable. If the remote variable already exists the supplied parameters is updated in the existing variable.

**Requires a valid session parameter**

**General form:**

```css
http://host:port/vscp/rest?
    vscpsession=session-key& 
    format=plain|csv|xml|json|jsonp&
    op=9|createvar&
    variable=name&
    value=value&
    type=type&
    [persistent=true|false]&
    [accessright=0x777]&
    [note=Optional base64 encoded note about variable.]    
```

**Arguments:**


*  **op** - Set to 9|createvar

*  **format** - can be 2|xml, 3|json or 4|jsonp (0|plain and 1|csv returns error).

*  **vscpsession** - A valid session key received from the open method.

*  **variable** - Name of variable.

*  **value** - Value for variable ([string-types encoded in BASE64](http://www.vscp.org/docs/vscpd/doku.php?id=remote_variables#variable_types)).

*  **note** - Textual note about variable (always encoded in BASE64).

*  **type** - Type of variable to create.

*  **persistent** - Optional variable that should be set to true to make the variable persistent.

*  **accessright** - Acess-rights for this variable (For example "0x777" all rights to everyone). Number can be given in hexadecimal ( preceded by "0x" ) or in decimal. Default is 0x700 (all rights for owner, no rights for everyone else).

The owner of the variable will be the current logged in user.

### HTTP Request with GET

```css
http://demo.vscp.org:8884/vscp/rest?vscpsession=d1c13eb83f52f319f14d167962048521& 
    format=plain|csv|xml|json|jsonp&
    op=9|createvar&
    variable=name&
    value=value&
    type=type&
    [persistent=true|false]    
```


*  **type** is a variable type on [numerical form](./remote_variables#variable_types). Default is string.

*  **persistent** tells if variable should be persistent. That is saved to disk and loaded when the VSCP daemon is restarted. Default = false, not persistent.

to test this with **curl** use the following format

```css
curl -X GET "http://host:port/vscp/rest? \
    vscpsession=d1c13eb83f52f319f14d167962048521 & \
    format=plain|csv|xml|json|jsonp& \
    op=9|createvar"
```


### Examples

###### example GET HTTP request

```css
    http://localhost:8884/vscp/rest?  
              vscpsession=d1c13eb83f52f319f14d167962048521&
              format=plain&
              op=9
```  

### HTTP Request with POST

```css
curl -X POST "http://localhost:8884/vscp/rest" \
    -H "vscpsession: d1c13eb83f52f319f14d167962048521" \ 
    -d "op=createvar&format=plain"     
```

### Demo

There is a a [demo app.](https://github.com/grodansparadis/vscp-ux/tree/master/rest) in the source tree, that demonstrates this functionality using JavaScript.

#### JavaScript Request with JSONP

```javascript
//////////////////////////////////////////////////////////////////
// do_createVariable
//
		
var do_createVariable = function() {
						
    if ( VscpSessionKey.length > 0 ) {

        var txtVariableName = window.prompt("Name of variable to create:","test");
        if ( null == txtVariableName ) return;
        var txtVariableType = window.prompt("Type:","string");
        if ( null == txtVariableType ) return;
        var txtVariableValue = window.prompt("Value:","This is a new string");
        if ( null == txtVariableValue ) return;
        var txtVariableNote = window.prompt("Note:","A base64 encoded note about this variable.");
        if ( null == txtVariableNote ) return;
        var txtVariableAccessRight = window.prompt("Access-rights:","777");
        if ( null == txtVariableAccessRight ) return;
        var txtVariablePersistent = window.prompt("Persistent (true/false):","false");
        if ( null == txtVariablePersistent ) return;
			
        // The value should be base64 encoded for 'string-types'
        if ( ( txtVariableType.toUpperCase() == "STRING" ) ||
            ( txtVariableType == "1" ) ||
            ( txtVariableType.toUpperCase() == "BLOB" ) ||
            ( txtVariableType == "16" ) ||
            ( txtVariableType.toUpperCase() == "MIME" ) ||
            ( txtVariableType == "100" ) ||
            ( txtVariableType.toUpperCase() == "HTML" ) ||
            ( txtVariableType == "101" ) ||
            ( txtVariableType.toUpperCase() == "JAVASCRIPT" ) ||
            ( txtVariableType == "102" ) ||
            ( txtVariableType.toUpperCase() == "JSON" ) ||
            ( txtVariableType == "103" ) ||
            ( txtVariableType.toUpperCase() == "XML" ) ||
            ( txtVariableType == "104" ) ||
            ( txtVariableType.toUpperCase() == "SQL" ) ||
            ( txtVariableType == "105" ) ||
            ( txtVariableType.toUpperCase() == "LUA" ) ||
            ( txtVariableType == "201" ) ||
            ( txtVariableType.toUpperCase() == "LUARES" ) ||
            ( txtVariableType == "202" ) ||
            ( txtVariableType.toUpperCase() == "UXTYPE1" ) ||
            ( txtVariableType == "300" )  ) { 
                txtVariableValue = vscp.b64EncodeUnicode( txtVariableValue );
        } 
                				
        $.ajax({
                url: VscpServer + '/vscp/rest?vscpsession=' + VscpSessionKey + 
                           '&format=jsonp&op=createvar&variable=' + txtVariableName +
                           '&value=' + txtVariableValue +
                           '&type=' + txtVariableType +
                           '&note=' + vscp.b64EncodeUnicode( txtVariableNote ) +
                           '&accessright=' + txtVariableAccessRight +
                           '&persistent=' + txtVariablePersistent,
                type : "GET",
                jsonpCallback: 'handler',
                cache: true,
                dataType: 'jsonp',
                success: function(response) {
                   // response will be a javaScript                        
                   // array of objects
                   console.log("-----------------------------------------------------------");
                   console.log("                     do_createVariable");
                   console.log("-----------------------------------------------------------");
                   console.log("Success = " + response.success );
                   console.log("Code = " + response.code );
                   console.log("Message = " + response.message );
                   console.log("Description = " + response.description );
                   console.log("Info = " + response.info );
                   if ( response.success ) {
                       $("#events").html( "OK Variable written" );
                   }					
					
                },
                error: function( xhr, status, error ) {
                    console.log( "Close:" + error + " Status:" + status );
                }
        });
    }
    else {
       alert("Interface is not open!");
    }

};
```

### Responses

#### Plain

#### CSV

#### XML

```xml

```

#### JSON

```css

```

#### JSONP

```javascript

```


## Send a measurement

```css
    op=10 or op=MEASUREMENT
```  
    
Sends a VSCP measurement event on a high level. **Requires a valid session parameter**

**General form:**

```javascript
http://host:port/vscp/rest?
    vscpsession=d1c13eb83f52f319f14d167962048521&
    format=plain|csv|xml|json|jsonp&
    op=10|measurement&
    guid=00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:01
    type=valid VSCP measurement type
    eventformat=string|float&
    value=floating point value&
    [level=2]&
    [sensorindex]=0-7|255&
    [unit=(0-3)|255]&
    [zone=(0-255)]&
    [subzone=0-255]
```

**Arguments:**


*  **guid** is the GUID for the event. If not given it defaults to all zeros.

*  **type** is the [VSCP type value](http://docs.vscp.org/spec/latest/#/./class1.measurement) specifying which type of measurement this is. Mandatory.

*  **eventformat** is optional and can be *string* or *float* to generate a string based or a float based event. If not give the default value, float, will be used.

*  **value** is a floating point value for the measurement.

*  **level** VSCP level (Level I or Level II) to send event as. Can be 1 or 2 and defaults to 2.

*  **sensorindex** is the index for the sensor for the unit. Can be in the range 0-7 for a Level I event and 0-255 for a Level II event. Defaults to zero.

*  **unit** is the measurement unit for this type of measurement. An be in the range 0-3 for a Level I event and 0-255 for a Level II event. Defaults to zero.

*  **zone** zone value for Level II events. Defaults to zero.

*  **subzone** zone value for Level II events. Defaults to zero.

### HTTP Request with GET

```javascript
http://demo.vscp.org:8884/vscp/rest?vscpsession=d1c13eb83f52f319f14d167962048521&
    format=plain|csv|xml|json|jsonp&
    op=10|measurement&
    guid=00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:01
    type=6&
    value=floating point value&
    [level=2]&
    [sensorindex]=0-7|255&
    [unit=0-3|255]&
    [zone=0-255]&
    [subzone=0-255]&
```

to test this with **curl** use the following format

```css
curl -X GET "http://host:port/vscp/rest? \
    vscpsession=d1c13eb83f52f319f14d167962048521 & \
    format=plain|csv|xml|json|jsonp& \
    op=10|measurement"
```

###### example GET HTTP request

```css
    http://localhost:8884/vscp/rest?  
              vscpsession=d1c13eb83f52f319f14d167962048521&
              format=plain&
              op=10
```  

### HTTP Request with POST

```css
curl -X POST "http://localhost:8884/vscp/rest" \
    -H "vscpsession: d1c13eb83f52f319f14d167962048521" \ 
    -d "op=measurement&format=plain"     
```

### Demo

There is a a [demo app](https://github.com/grodansparadis/vscp-ux/tree/master/rest) in the source tree, that demonstrates this functionality using JavaScript.

#### Javascript Request with JSONP

### Responses

#### Plain

	
	


#### CSV

	
	


#### XML

```xml

```

#### JSON

```css

```

#### JSONP

```javascript

```

**note** The table functionality is broken in the head version. This is because it is being rewritten at the moment. 


## Read Table

Tables is a feature of the daemon that makes it easy to collect time + value data, typically measurements from a sensor. It is a feature of the decision matrix of the VSCP daemon and is described [here](./decision_matrix.md#write_table). 

```css
    op=11 or op=TABLE
```  
    
Read data from a server defined table. **Requires a valid session parameter**

**General Format**
```css
http://host:port/vscp/rest?
    vscpsession=session-key&
    format=plain|csv|xml|json|jsonp&
    op=11|table&
    name=name-of-table&
    from=from-date-time&
    to=from-date-time  
```

**Arguments:**


*  **op** - Set to 11|gettable

*  **format** - can be 0|plain, 1|csv, 2|xml, 3|json or 4|jsonp.

*  **vscpsession** - A valid session key received from the open method.

*  **name** - Name of table to fetch data from.

*  **from** - Time on the form YY-MM-DD HH:MM:SS to start show values from.

*  **to** - Time on the form YY-MM-DD HH:MM:SS to show values to.

### HTTP Request with GET

```css
http://host:port/vscp/rest?vscpsession=d1c13eb83f52f319f14d167962048521 &format=plain|csv|xml|json|jsonp&op=11|table    
```

to test this with **curl** use the following format

```css
curl -X GET "http://host:port/vscp/rest? \
    vscpsession=d1c13eb83f52f319f14d167962048521 & \
    format=plain|csv|xml|json|jsonp& \
    op=11|table"
```

###### example GET HTTP request

```css
    http://localhost:8884/vscp/rest?  
              vscpsession=d1c13eb83f52f319f14d167962048521&
              format=plain&
              op=11
```  

### HTTP Request with POST

```css
curl -X POST "http://localhost:8884/vscp/rest" \
    -H "vscpsession: d1c13eb83f52f319f14d167962048521" \ 
    -d "op=table&format=plain"     
```

### Demo

There is a a [demo app](https://github.com/grodansparadis/vscp-ux/tree/master/rest) in the source tree, that demonstrates this functionality using JavaScript.

#### Javascript Request with JSONP

### Responses

#### Plain

#### CSV

#### XML

```xml

```

#### JSON

```css

```

#### JSONP

```javascript

```

## Get MDF

```css
    op=11 or op=mdf
```  
    
Get and display MDF for a device. **Requires a valid session parameter**

Intended for devices that can't download the MDF by themselves. Building a web-app. around this functionality is usually a bad idea. It is much better to use the functionality in the [VSCP JavaScript library](https://docs.vscp.org/#development). This is because the VSCP daemon can not always be expected to be available in every setup (typically wireless and Ethernet setups). If that is the case for you (it is available all the time) use this functionality by all means.

**General Format:**

```javascript
http://host:port/vscp/rest?vscpsession=session-key&
    format=xml|json|jsonp&
    op=11|mdf&
    url=http://www.eurosource.se/beijing_2.xml
```

**Arguments:**


*  **op** - Can be 11|mdf

*  **format** - can be 2|xml, 3|json or 4|jsonp (0|plain and 1|csv returns error).

*  **vscpsession** - A valid session key received from the open method.

*  **url** - the url to the MDF file. 

### HTTP Request with GET

```javascript
http://demo.vscp.org:8884/vscp/rest?vscpsession=d1c13eb83f52f319f14d167962048521&
    format=xml|json|jsonp&
    op=11|mdf&
    url=http://www.eurosource.se/beijing_2.xml
```

to test this with **curl** use the following format

```css
curl -X GET "http://host:port/vscp/rest? 
    vscpsession=d1c13eb83f52f319f14d167962048521 & 
    format=xml|json|jsonp&
    op=11|mdf"&
    url=http://www.eurosource.se/beijing_2.xml
```

### HTTP Request with POST

```css
curl -X POST "http://host:8884/vscp/rest" \
    -H "vscpsession: d1c13eb83f52f319f14d167962048521" \ 
    -d "op=11|mdf&format=xml|json|jsonp&url=http://www.eurosource.se/beijing_2.xml"     
```

### Demo

There is a a [demo app.](https://github.com/grodansparadis/vscp-ux/tree/master/rest) in the source tree, that demonstrates this functionality using JavaScript.

```javascript
http://demo.vscp.org:8884/vscp/rest?vscpuser=admin&vscpsecret=d50c3180375c27927c22e42a379c3f67&format=plain&op=1
```

and you will get a reply

	
	1 1 Success vscpsession=2a280db0de5d7c698faaee0e44a94314 nEvents=0


and now you use the returned VSCP sesson-key 

	
	2a280db0de5d7c698faaee0e44a94314 


in new calls. In this case

```javascript
http://localhost:8884/vscp/rest?vscpsession=b6d6e355124504cef7da7a6e97c09872&format=xml&op=mdf&url=http://www.eurosource.se/beijing_2.xml
```

to get the MDF file for the [Beijing node](http://www.grodansparadis.com/beijing/beijing.html).

### Responses

#### Format=plain

Not supported.

	
	0 -1 Failure 
	
	General failure.


#### Format=csv

Not supported.

	
	success-code,error-code,message,description
	0,-1,Failure,General failure.


#### Format=xml

```xml
<!--  Ake Hedman, Grodans Paradis AB  -->
<vscp>
    <module>
        <name>Beijing IO controller</name>
        <model>B</model>
        <version>1.0.4</version>
        <changed>2015-07-07</changed>
        
        .... bla bla bla bla
        
    </module>
</vscp>
```

#### Format=json

```json
{"vscp":
    {"module":{"name":"Beijing IO controller","model":"B","version":"1.0.4","changed":"2015-07-07",
    
    .... bla bla bla bla
    
        frequency0","@value":"$frequency"}}}}
    }
}
```

#### Format=jsonp

```json
typeof handler === 'function' && handler({"vscp":
    {"module":{"name":"Beijing IO controller","model":"B","version":"1.0.4","changed":"2015-07-07",
    
    .... bla bla bla bla
    
        frequency0","@value":"$frequency"}}}}
    }
});
```

[filename](./bottom_copyright.md ':include')

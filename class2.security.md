# Class=1034 (0x040A) - Level II Security

    CLASS2.SECURITY

# Description

Level II security related events.



## Type=0 (0x00) - General event :id=type0
```
VSCP2_TYPE_SECURITY_GENERAL
```
General Event.
----

## Type=1 (0x01) - Set key :id=type1
```
VSCP2_TYPE_SECURITY_SETKEY
```
Set encryption key for a node. The payload data is encrypted from byte 1 to the payload length. The first first byte holds the encryption code as of the definition in the VSCP specification (and vscp.h).

Encrypted content is encrypted with AES128/AES192/AES256 CBC. The encrypted content is sent with a 16-byte IV appended to it meaning that the actual payload can be max 479 bytes (512-16 (GUID)-1 (type)-16 (IV)).

##### Payload content 

 | Byte   | Description |
 | :----: | ----------- |
 | 0 | Encryption code in low nibble. High nibble is reserved for future use. |
 | 1 | Reserved for future use. |
 | 2-17  | GUID for node that the key is intended for.  (All zero GUID is all nodes.) |
 | 18-511 | Key (any length) + (16 byte) iv. |

Note that key length is application/protocol dependent.

##### Encryption (bits 3,2,1,0)

 | Code   | Description |
 | :----: | ----------- |
 | 0 | No encryption |
 | 1 | AES-128 |
 | 2 | AES-192 |
 | 3 | AES-256 |
 | 4-254 | Reserved |
 | 255 | User defined encryption |
----

[filename](./bottom_copyright.md ':include')
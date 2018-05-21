# Dumb nodes

Normally a node have registers as specified by the VSCP standard and it also have a pointer to a MDF (Module Description File) that describes the noe it self and it's uses. There is however something that is called a **dumb node** which is a Level II node that only can send (yes possibly also receive) events. This type can not do anything else. It is defined by a full GUID and is marked with a dumb node bit in the header (see [vscp.h](https///github.com/grodansparadis/vscp/blob/master/src/vscp/common/vscp.h)).

{% include "./bottom_copyright.md" %}
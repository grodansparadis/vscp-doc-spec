# Super low bandwidth

Sometimes you have a very low bandwidth between nodes. In this case you can use VSCP in a very compact way. You can have links where a low end device just sends a number from the source to a receiver. You can do this if the other information about the event is already known and/or can be obtained in other ways. Imagine a node that sends a temperature. There is one node. You therefore know its GUID beforehand. You know that it sends a measurement and that that the measurement is a temperature. You can pack this into an event on the receiving side as a measurement of your choice. You can set the timestamp to the current time or leave it at zero to let the receiver set the timestamp. Thus you have a full event with only a single number sent over the link. This is very compact and can be used in low bandwidth links. You can also use this approach for other types of events, such as status events or control events. The key is to have a predefined schema for the events that allows you to reconstruct the full event on the receiving side with minimal information sent over the link. 

If you instead send different value types over the link you need to code and provide the type also and still very little extra information is added to the event. 

If you have several nodes on a segment you can use nicknames schema as in the CAN4VSCP schema. You can then use a nickname to identify the source node. The receiver can then use the nickname to construct the full GUID for the node. 

For each extra variable you have to add more data to the link to distinguish between the different variables. If you have a lot of variables you can use a more complex schema and use the full event.

MQTT has a topic structure that can be used to encode the source and type of the event. You can then use the payload to send the value. This allows for a very compact representation of the event on the MQTT link and you have all the information needed in the topic to reconstruct the full event on the receiving side.

To summarise, there is no need to send redundant information over the link if the receiver can reconstruct the full event with minimal information sent over the link. This allows for a very efficient use of bandwidth and can be used in scenarios where bandwidth is limited.
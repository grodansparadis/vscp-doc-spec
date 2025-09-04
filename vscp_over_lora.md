# VSCP over LoRa

Generally LoRa nodes will be dumb nodes. They simply send and receive data without any VSCP processing or intelligence. They can have registers and a decision matrix but the configuration of a node will be very slow. Still there will be a need to configure a LoRa node. Other communication methods can be used for that (like a serial line) but it would also be possible to setup VSCP registers if a node need to be configured also in the field. The only thing it needs to implement for this tp work is the read/write events of the VSCP protocol. The configuring application must then take care not to take up to much bandwidth with it's operations and use delays between read/write operations.

Communication parameters, such as region, spread factor, and transmit power and the encryption key is an example of parameters that needs to be set for nodes.

LoRa nodes should send VSCP heartbeats at regular intervals to indicate they are alive. It is recommended that the heartbeat is sent unencrypted.

## LoRa transparent mode

**preliminary**

Transparent mode works just like a serial link One just send data out the line and it is received on the other end as a serial stream. Packaging is this hidden. It is still possible to address nodes etc.See documentation for modules like the [DX-LR02](http://en.szdx-smart.com/m/EN/zlxz/LORAmk/Lora1/514.html) for information about the meaning of the transparent mode.

In LoRa transparent mode, a serial connection is established between the VSCP device and the LoRa gateway or other LoRa devices. The VSCP frames are sent on the same format as VSCP frames are sent over a serial line. Typically there are three distinct cases 

1. **Transparent**: A single VSCP frame is sent to a specific destination device specified by it's  channel. Typically this device can be a LoRA gateway/bridge.
2. **Fixed point**: A VSCP frame is sent to a specific device on the LoRa network where the device is specified by its 16-bit MAC address and it's channel. Typically this device can be a LoRA gateway/bridge.
3. **Broadcast**: A VSCP frame is sent to all devices on the same channel on the LoRa network.

A big advantage with the transparent mode is it's ease of use. All that is needed is a serial channel and then the VSCP frames can be sent without any additional packaging or processing.

### Frame format
The same frame format as used for VSCP over serial is used for VSCP over LoRa. See [VSCP over serial]() (vscp_over_serial.md) for more information. It is recommended that AES-128 CBC encryption is used for all LoRa transmissions. **Channel** in the serial frame format refers to the logical channel used for communication. The LoRA MAC address is in GUID byte 14 (MSB) and 15 (LSB)

#### Using CANAL to save frame space

The [CANAL frame](https://grodansparadis.github.io/vscp-doc-spec/#/./vscp_over_a_serial_channel_rs-232?id=frame-type2-canal-message) can be used to save frame space by utilizing a more compact representation of the data. In this format max eight bytes of data is allowed (Level I) and the id of the node, VSCP type, VSCP class is coded into the CAN id as of below

 | Bits | Description                |
 | --------- | -----------                |
 | 0-7       | Node ID                    |
 | 8-15      | VSCP Type                  |
 | 16-24     | VSCP Class                 |
 | 25-31     | Set to zero                |

This adds 14 bytes to the frame payload and 18 bytes with timestamp. The format without timestamp is well suited for AES-128 CBC encryption if padded with two bytes. The minimum payload in this case i 32 bytes (16 bytes for padded data and 16 bytes for IV). This gives 42 bytes for a full frame. Sending the same frame using VSCP frame without timestamp, which is 22 bytes plus data would with 10 bytes of data give a frame that is minimum 48 bytes. So using CANAL can save 6 bytes in this case. The advantage with the VSCP frame as payload is full level II support.

Obviously it is important to consider the impact of these additional bytes on the overall frame size and transmission efficiency. If you receive a specific type if data from a node x you already know it's address and also VSCP type and VSCP class, sensor index, coding etc and in that case it makes sense just to send the value. And also for different values in this context precede it with VSCP class and VSCP type. The receiver can then create the correct VSCP frame for the rest of the system (whish does not have this extra known information) to use.

#### Dumb or smart
Due to the nature of LoRa communication, devices can be classified as either "dumb" or "smart". Dumb devices simply send and receive data without any processing or intelligence, while smart devices can register and respond to events, making them more versatile in a networked environment. In any case a smart LoRa device must limit its register space to ensure efficient communication and avoid overwhelming the network. 

## LoRa block/frame mode

**preliminary**

In block or frame mode we send the frames in binary format. A frame should fit in one block of LoRA data. That means a maximum theoretical frame size of 256 bytes. The frame is sent as is without any additional packaging.  It is recommended that **AES-128**/192/256 CBC encryption is used for all LoRa transmissions but it can be sent unencrypted also. In any case 16-bytes is perfect for the VSCP part and if encrypted with AES-128/192/256 CBC, the total frame size would be 32 bytes (16 bytes for the encrypted data and 16 bytes for the IV).

## Frame format 

| Byte | Description |
| ---- | ----------- |
| 0 | Frame type & encryption settings. (**never encrypted**)|
| 1* | Flags |
| 2* | Sequence counter, increased with one for each sent frame |
| 3* | Originating node id (radio id) MSB |
| 4* | Originating node id (radio id)  LSB |
| 5* | VSCP class |
| 6* | VSCP type |
| 7* | VSCP data length (without zero padding) |
| 8-16* | VSCP frame data (padding with zero to always make 8 bytes) |
| 17-32| AES-128/192/256 CBC IV (16 bytes) |

Bytes marked with '*' are encrypted when the frame is encrypted forming a 16-byte block.

Radio id equal to 0 and radio id equal to 0xffff (65535) is broadcast and should not be originating id's.

### Definition of frame type

The byte is never encrypted.

| Bits | Description |
| ---- | ----------- |
| 7,6,5,4 | Packet type. Currently always zero. |
| 3,2,1,0 | Encryption. |

### Frame and encryption types
| Code | Description |
| 0 | No encryption |
| 1 | AES128 CBC encryption. 16-byte IV is appended to each frame. |
| 2 | AES192 CBC encryption. 16-byte IV is appended to each frame. |
| 3 | AES256 CBC encryption. 16-byte IV is appended to each frame. |
| 4-15 | Reserved |

### Definition of flags

| Bits | Description |
| ---- | ----------- |
| 7 | If set this is a dumb node.  |
| 6,5,4,3,2,1,0 | Reserved |

# Reference
  * LoRA docs - https://lora.readthedocs.io/en/latest/
  * LoRa & LoRaWAN Explained! - https://www.youtube.com/watch?v=XvrVjpQBSL0
  * Example of transparent and fixed modes - https://www.youtube.com/watch?v=JvBC7cEgI0E

# Manufacturers
  * SHEN ZHEN DX-SMART TECHNOL OGY CO.，LTD. - http://en.szdx-smart.com/m/EN/zlxz/LORAmk/Lora1/514.html
  * Ebyte - https://www.cdebyte.com/?gad_source=1&gad_campaignid=22838789706&gclid=Cj0KCQjwzt_FBhCEARIsAJGFWVmOa9puKMdUa4mIVf4j5-rR9xQ3IBpDvBQPUHLFWPznaOESgbKq38IaAuVYEALw_wcB

[filename](./bottom_copyright.md ':include')

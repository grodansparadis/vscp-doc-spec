# VSCP over LoRa

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

t.b.d



[filename](./bottom_copyright.md ':include')

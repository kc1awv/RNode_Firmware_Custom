# RNode Custom Firmware by KC1AWV 

This is a customized version of the [RNode](https://unsigned.ip/rnode) firmware, designed for use using the [Moteino MEGA](https://lowpowerlab.com/guide/moteino/) by LowPowerLab, with the RFM95 LoRa Module.

## Changes made:

- Config.h pinouts for the RFM95 module installed on the Moteino MEGA
- Refactor .ino code to .cpp (developing using VSCode / PlatformIO)
- ROM.h added custom model E4 (0xE4) for Moteino MEGA board with RFM95 LoRa module
- RNode-Custom.cpp & ROM.h removed references to Mark Qvist's model A4 and A9 due to pin changes and to prevent bad flashes onto real RNodes

## Caveat:

Writing this firmware requires an additional step using rnodeconfigutil, as flashing the firmware to the Moteino MEGA will not write the EEPROM data needed by the device. In addition, rnodeconf.py will need the following modifications for the custom node model:

- git clone [rnodeconfigutil](https://github.com/markqvist/rnodeconfigutil)
- Edit rnodeconf/rnodeconf.py
- Change line 43: `ranges = { 0xA4: [410000000, 525000000, 14], 0xA9: [820000000, 1020000000, 17], 0xE4: [410000000, 525000000, 23] }`
- Change line 44: `firmware_update_url = "https://github.com/markqvist/RNode_Firmware/raw/master/Precompiled/rnode_firmware_latest.hex"`
- Add line 120: `    MODEL_E4       = 0xE4`
- Add line 933: `                    if args.model == "e4":`
- Add line 934: `                        model = ROM.MODEL_E4`
- Change line 1074: `                    if args.txp != None and (args.txp >= 0 and args.txp <= 23):`

# RNode Firmware

This is the firmware for [RNode](https://unsigned.io/rnode), a very flexible LoRa-based communication device. RNode can functions as a:

- A general purpose long-range data radio
- Network adapter for [RNS](https://github.com/markqvist/Reticulum)
- LoRa interface for your computer (or any device with a USB or serial port)
- Generic [LoRa-based network adapter](https://unsigned.io/15-kilometre-ssh-link-with-rnode/) for your Linux devices
- [Packet sniffer](https://github.com/markqvist/LoRaMon) for LoRa networks
- LoRa development board
- A LoRa-based KISS-compatible TNC
- A flexible platform for experiementing with LoRa technology

RNode is controlled by a powerful ATmega1284p MCU, and is fully Arduino compatible. You can use this firmware, or it can be programmed any way you like, either from the Arduino IDE, or using any of the available tools for AVR development. This firmware can also be edited and compiled directly from the Arduino IDE.

For adding RNode to your Arduino environment, please see [this post](https://unsigned.io/board-support-in-arduino-ide/).

For configuring an RNode with this firmware, please have a look at the [RNode Config Utility](https://github.com/markqvist/rnodeconfigutil).

## Current Status
The RNode firmware can be considered stable at this point. If you do find a bug or discover unintended behaviour, please report it as an issue here, so I can fix it!

## Operating Modes
RNode can operate in two modes, host-controlled (default) and TNC mode:

- When RNode is in host-controlled mode, it will stay in standby when powered on, until the host specifies frequency, bandwidth, transmit power and other required parameters. This mode can be enabled by using the -N option of this utility. In host-controlled mode, promiscuous mode can be activated to sniff any LoRa frames.

- When RNode is in TNC mode, it will configure itself on powerup and enable the radio immediately. This mode can be enabled by using the -T option of this utility (the utility will guide you through the settings if you don't specify them directly).

## USB and Serial Protocol
You can communicate with RNode either via the on-board USB connector, or using the serial pins on the board (labeled RX0 and TX0). RNode uses a standard FTDI USB chip, so it works out of the box without additional drivers in most operating systems.

All communications to and from the board uses [KISS framing](https://en.wikipedia.org/wiki/KISS_(TNC)) with a custom command set. RNode also does not use HDLC ports in the command byte, and as such uses the full 8 bits of the command byte is available for the actual command. Please see table below for supported commands.

| Command          | Byte | Description
| -----------------|------| -----------------------------------------------
| Data frame       | 0x00 | A data packet to or from the device
| Frequency        | 0x01 | Sets or queries the frequency
| Bandwidth        | 0x02 | Sets or queries the bandwidth
| TX Power         | 0x03 | Sets or queries the TX power
| Spreading Factor | 0x04 | Sets or queries the spreading factor
| Coding Rate      | 0x05 | Sets or queries the coding rate
| Radio State      | 0x06 | Sets or queries radio state
| Radio Lock       | 0x07 | Sets or queries the radio lock
| Device Detect    | 0x08 | Probe command for device detection
| Promiscuous      | 0x0E | Sets or queries promiscuous mode
| RX Stats         | 0x21 | Queries received bytes
| TX Stats         | 0x22 | Queries transmitted bytes
| Last RSSI        | 0x23 | Indicates RSSI of last packet received
| Blink            | 0x30 | Blinks LEDs
| Random           | 0x40 | Queries for a random number
| Firmware Version | 0x50 | Queries for installed firmware version
| ROM Read         | 0x51 | Read EEPROM byte
| ROM Write        | 0x52 | Write EEPROM byte
| TNC Mode         | 0x53 | Enables TNC mode
| Normal Mode      | 0x54 | Enables host-controlled mode
| ROM Erase        | 0x59 | Completely erases EEPROM
| Error            | 0x90 | Indicates an error

## Programming Libraries
Have a look in the "Libraries" folder for includes to let you easily use RNode in your own software.

Here's a Python example:

```python
from RNode import RNodeInterface

def gotPacket(data, rnode):
	print "Received a packet: "+data

rnode = RNodeInterface(
	callback = gotPacket,
	name = "My RNode",
	port = "/dev/ttyUSB0",
	frequency = 868000000,
	bandwidth = 125000,
	txpower = 2,
	sf = 7,
	cr = 5,
	loglevel = RNodeInterface.LOG_DEBUG)

rnode.send("Hello World!")
```

## Promiscuous Mode and LoRa Sniffing
RNode can be put into LoRa promiscuous mode, which will dump raw LoRa frames to the host. Raw LoRa frames can also be sent in this mode, and have the standard LoRa payload size of 255 bytes. To enable promiscuous mode send the "Promiscuous" command to the board, or use one of the programming libraries. You can also use the example program [LoRaMon](https://github.com/markqvist/LoRaMon) for an easy to use LoRa packet sniffer.
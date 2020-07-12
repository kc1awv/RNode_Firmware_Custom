#include <stdint.h>
#include <stdio.h>

#ifndef FRAMING_H
	#define FRAMING_H

	#define FEND				0xC0
	#define FESC				0xDB
	#define TFEND				0xDC
	#define TFESC				0xDD

	#define CMD_UNKNOWN			0xFE
	#define CMD_DATA			0x00
	#define CMD_FREQUENCY		0x01
	#define CMD_BANDWIDTH		0x02
	#define CMD_TXPOWER			0x03
	#define CMD_SF				0x04
	#define CMD_CR				0x05
	#define CMD_RADIO_STATE		0x06
	#define CMD_RADIO_LOCK		0x07
	#define CMD_DETECT			0x08
	#define CMD_PROMISC			0x0E
	#define CMD_READY			0x0F

	#define CMD_STAT_RX			0x21
	#define CMD_STAT_TX			0x22
	#define CMD_STAT_RSSI		0x23
	#define CMD_STAT_SNR		0x24
	#define CMD_BLINK			0x30
	#define CMD_RANDOM			0x40

	#define CMD_FW_VERSION		0x50
	#define CMD_ROM_READ		0x51
	#define CMD_ROM_WRITE		0x52
	#define CMD_CONF_SAVE		0x53
	#define CMD_CONF_DELETE		0x54
	#define CMD_UNLOCK_ROM		0x59
	#define ROM_UNLOCK_BYTE		0xF8

	#define DETECT_REQ			0x73
	#define DETECT_RESP			0x46

	#define RADIO_STATE_OFF		0x00
	#define RADIO_STATE_ON		0x01

	#define NIBBLE_SEQ			0xF0
	#define NIBBLE_FLAGS		0x0F
	#define FLAG_SPLIT			0x01
	#define SEQ_UNSET			0xFF

	#define CMD_ERROR			0x90
	#define ERROR_INITRADIO		0x01
	#define ERROR_TXFAILED		0x02
	#define ERROR_EEPROM_LOCKED	0x03
	#define ERROR_QUEUE_FULL	0x04

	// Serial framing variables
	size_t frame_len;
	bool IN_FRAME = false;
	bool ESCAPE = false;
	uint8_t command = CMD_UNKNOWN;

#endif

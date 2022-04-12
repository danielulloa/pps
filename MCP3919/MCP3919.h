#ifndef MCP3919_H
#define MCP3919_H

#include <Arduino.h>

/*
 * MCP3919 Library
 * Daniel Ulloa
 * 4/2022
 *
 * based from
 * MCP3903 Library
 * Kerry D. Wong
 * http://www.kerrywong.com
 * 5/2014
 */

class MCP3919 {
public:
	// control byte
	// the first byte transmitted to the MCP3919 in any
	// communication is always the control byte
	// bit 7-6 : Device Address A[6:5] = 01
	// bit 5-1 : A[4:0] = Register Address
	// bit 0 : R/W
	// 0b01000000 = 0x40
	// control_byte = DEVICE_ADDR | REGISTER_ADDR | R/W
	static const byte DEVICE_ADDR = 0x40;

	//***** register map *****

	// **** CHANNELn ****
	// readonly channel registers
	// 24bit MSB first, left justified
	static const byte REG_CH_0 = 0x00;
	static const byte REG_CH_1 = 0x01;
	static const byte REG_CH_2 = 0x02;

	// **** MOD ****
	// Delta-sigma modulators output value 24bit
	// bit 11-8  COMPn_CH2
	// bit 7-4   COMPn_CH1
	// bit 3-0   COMPn_CH0
	// Do not write to this register to ensure
	// the accuracy of each ADC
	// static const byte REG_MOD = 0x08;

	// **** PHASE ****
	// phase delay config register 24bit
	// phase delay between channels
	// bits delay = phaseb[11:0] decimal code/DMCLK
	// bit 23-12 CH2 relative to CH1 phase delay
	// bit 11-0  CH0 relative to CH1 phase delay
	static const byte REG_PHASE = 0x0A;

	// **** GAIN ****
	// gain config register 24bit
	// bit 8-6  PGA_CH2
	// bit 5-3  PGA_CH1
	// bit 2-0  PGA_CH0
	//
	// Channel Gain
	// 111 (reserved, gain = 1)
	// 110 (reserved, gain = 1)
	// 101 gain = 32
	// 100 gain = 16
	// 011 gain = 8
	// 010 gain = 4
	// 001 gain = 2
	// 000 gain = 1 (default)
	static const byte REG_GAIN = 0x0B;
	static const byte GAIN_1 = 0x0;
	static const byte GAIN_2 = 0x1;
	static const byte GAIN_4 = 0x2;
	static const byte GAIN_8 = 0x3;
	static const byte GAIN_16 = 0x4;
	static const byte GAIN_32 = 0x5;

	// **** STATUSCOM ****
	// status/communication register 24bit
	// 0b101000010000000000000111 = 0xA10007
	// DEFAULT: 0xA10007
	// bit 23-22: Address Loop Setting
	// 11 = cycle through entire reg map
	// 10 = loop through reg TYPES (default)
	// 01 = loop through reg GROUPS
	// 00 = continue read single reg (not incremented)
	//
	// bit 21: Address Counter Increment Setting
	// 1 = address counter auto-increments and loops on writtable part of
	// the register map (default)
	// 0 = address not incremented, continually writes to the same register address
	//
	// bit 20: DR_HIZ data ready pin inactive state control for DRA, DRB and DRC
	// 1 = the default state is a logic high when data is NOT ready
	// 0 = the default state is a high impedance when data is not ready (default)
	//
	// bit 19: DR_LINK (data ready link control
	// 1 = data ready link on, all channels linked and data ready pulses from the most lagging ADC
	//	are present on each DR pin
	// 0 = Data ready link off, each ADC produces ready pulse (default)
	//
	// bit 18: WIDTH_CRC
	// 1 = 32 bit 
	// 0 = 16 bit (default)
	//
	// bit 17-16: WIDTH_DATA
	// 11 = 32 bit sign extension
	// 10 = 32 bit with zeros padding
	// 01 = 24 bit (default)
	// 00 = 16 bit rounding
	//
	// bit 15: EN_CRCCOM CRC checksum
	// 1 = CRC-16 checksum
	// 0 = disabled (default)
	//
	// bit 14: EN_INT CRCREG interrupt flag CRCREG checksum
	// 1 = enabled
	// 0 = disabled (default)
	//
	// bit 13-12: Reserved
	// 0 = keep equal to '0' at all times
	//
	// bit 11-3: Unimplemented
	// read as '0'
	//
	// bit 2-0 DRSTATUS[n] individual ADC Ch Data Ready status bit
	// 1 = channel CHn data are not ready (default)
	// 0 = channel CHn data are ready

	static const byte REG_STATUS_COMM = 0x0C;

	// **** CONFIG0 ****
	// CONFIG0 register 24bit
	// 0b001110000110000001010000
	// DEFAULT: 0x386050

	// bit 23: EN_OFFCAL offset calibration on all channels
	// 1 = enabled
	// 0 = disabled (default)
	//
	// bit 22: EN_GAINCAL gain calibration on all channels
	// 1 = enabled
	// 0 = disabled (default)
	//
	// bit 21-22 : DITHER 
	// 11 = Dithering on, Strenght = Maximum (default)
	// 10 = Dithering on, Strenght = Medium
	// 01 = Dithering on, Strenght = Minimum
	// 00 = Dithering off
	//
	// bit 19-18 : BOOST
	// 11 = x2
	// 10 = x1 (default)
	// 01 = x0.66
	// 00 = x0.5
	//
	// bit 17-16 : PRESCALE
	// 11 = AMCLK = MCLK/8
	// 10 = AMCLK = MCLK/4
	// 01 = AMCLK = MCLK/2
	// 00 = AMCLK = MCLK (default)
	//
	// bit 15-13 : OSR (over sampling ratio)
	// 111 = 4096
	// 110 = 2048
	// 101 = 1024
	// 100 = 512
	// 011 = 256 (default)
	// 010 = 128
	// 001 = 64
	// 000 = 32
	//
	// bit 12-8 : Unimplemented
	//
	// bit 7-0 : VREFCAL
	// 0x50 default

	static const byte REG_CONFIG0 = 0x0D;

	// **** CONFIG1 ****
	// CONFIG1 register 24 bit
	// 0b000000000000000000000000
	// DEFAULT: 0x0

	// bit 23-19 : Unimplemented
	//
	// bit 18-16 : RESET individual ADC soft reset
	// RESET[n] = 1 : channel is in soft reset mode
	// RESET[n] = 0 : channel is not in soft reset mode
	//
	// bit 15-11 : Unimplemented
	//
	// bit 10-8 : SHUTDOWN
	// SHUTDOWN[n] = 1 : channel is in shutdown mode
	// SHUTDOWN[n] = 0 : channel is not in shutdown mode
	//
	// bit 7 : VREFEXT (internal reference shutdown control)
	// 1 = internal Vref disabled
	// 0 = internal Vref enabled (default)
	//
	// bit 6 : CLKEXT (clock mode)
	// 1 = CLOCK mode (internal osc disabled) (default)
	// 0 = XT mode (crystal between OSC1/OSC2)
	//
	// bit 5-0 : Unimplemented

	static const byte REG_CONFIG1 = 0x0E;

	// **** OFFCAL_CH0 ****
	// !TODO!
	static const byte REG_OFFCAL_CH0 = 0x0F;
	// **** GAINCAL_CH0 ****
	// !TODO!
	static const byte REG_GAINCAL_CH0 = 0x10;
	// **** OFFCAL_CH1 ****
	// !TODO!
	static const byte REG_OFFCAL_CH1 = 0x11;
	// **** GAINCAL_CH1 ****
	// !TODO!
	static const byte REG_GAINCAL_CH1 = 0x12;
	// **** OFFCAL_CH2 ****
	// !TODO!
	static const byte REG_OFFCAL_CH2 = 0x13;
	// **** GAINCAL_CH2 ****
	// !TODO!
	static const byte REG_GAINCAL_CH2 = 0x14;
	// **** CRC ****
	// !TODO!
	static const byte REG_CRC = 0x1F;
	//***************************

	//loop chn0/1, chn2/3, chn4/5
	// MOD/PHASE/GAIN, STAT/CONFIG
	static const byte READ_OPTION_GROUP = 0x01;

	// loop chn0-5, MOD/PHASE/GAIN/STAT/CONFIG
	static const byte READ_OPTION_TYPE = 0x10;
	
	//loop through entire reg map
	static const byte READ_OPTION_ALL = 0x11;

	static const byte OSR_32 = 0x0;
	static const byte OSR_64 = 0x1;
	static const byte OSR_128 = 0x2;
	static const byte OSR_256 = 0x3;
	static const byte OSR_512 = 0x4;
	static const byte OSR_1024 = 0x5;
	static const byte OSR_2048 = 0x6;
	static const byte OSR_4096 = 0x7;	

	MCP3919();
	void reset();
	void reset(byte osr);
	unsigned long readRegister(byte reg);
	void writeRegister(byte reg, unsigned long data);
	unsigned long readControlRegister();
	unsigned long readStatusCommRegister();
	double readADC(byte channel);
	void setGain(byte channel, byte gain);
	void setGain(byte channel, byte gain, byte boost);
private:
    static const int pinMOSI = 11; //MOSI
    static const int pinMISO = 12; //MISO
    static const int pinSPIClock = 13; //SCK
    static const int pinCS = 10; //CS
};
#endif

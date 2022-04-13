/*
 * MCP3919 Library
 * Daniel Ulloa
 * 4/2022
 *
 * MCP3903 Library
 * Kerry D. Wong
 * http://www.kerrywong.com
 * 5/2014
 */

#include "MCP3919.h"
#include <SPI.h>

MCP3919::MCP3919()
{
    pinMode(pinMOSI, OUTPUT);
    pinMode(pinMISO, INPUT);
    pinMode(pinSPIClock, OUTPUT);
    pinMode(pinCS, OUTPUT);
	digitalWrite(pinCS, HIGH);
	pinMode(pinRST, OUTPUT);
	digitalWrite(pinRST,HIGH);
    
}


//set to 24 bit mode
void MCP3919::reset()
{
	digitalWrite(pinRST,LOW);
	delay(1);
	digitalWrite(pinRST,HIGH);
	unsigned long cmd1 = 0x386050;
	unsigned long cmd2 = 0x000000
	writeRegister(REG_CONFIG0, cmd1);
	writeRegister(REG_CONFIG1, cmd2);
}


//read from specified register
//returns 24 bit data
unsigned long MCP3919::readRegister(byte reg)
{
	byte cmdByte = DEVICE_ADDR | reg <<1 | 1;
	unsigned long r = 0;

	digitalWrite(pinCS, LOW);
	SPI.transfer(cmdByte);
	r = (unsigned long) SPI.transfer(0x0) << 16;
	r |= (unsigned long) SPI.transfer(0x0) << 8;
	r |= (unsigned long) SPI.transfer(0x0);
	digitalWrite(pinCS, HIGH);

	return r;
}

//write 24 bit data to register
void MCP3919::writeRegister(byte reg, unsigned long data)
{
	byte cmdByte = DEVICE_ADDR | reg <<1;
	
	byte b2 = (data & 0xff0000) >> 16;
	byte b1 = (data & 0x00ff00) >> 8;
	byte b0 = data & 0x0000ff;

	digitalWrite(pinCS, LOW);
	SPI.transfer(cmdByte);
	SPI.transfer(b2);
	SPI.transfer(b1);
	SPI.transfer(b0);
	digitalWrite(pinCS, HIGH);	
}

//read from ADC channel (0-2)
double MCP3919::readADC(byte channel)
{
	long r = (long) readRegister(channel);

	if (r > 8388607l) r -= 16777216l;
	
	return (double) r / 8388608.0 /3.0;
}

//set channel gain
//channel (0-2)
//valid gain settings:
//GAIN_1
//GAIN_2
//GAIN_4
//GAIN_8
//GAIN_16
//GAIN_32
void MCP3919::setGain(byte channel, byte gain) 
{
	setGain(channel, gain, 0);
}

//overloaded setGain
//the boost parameter indicates the current boost setting for channel
void MCP3919::setGain(byte channel, byte gain, byte boost)
{
	// !TODO!
	unsigned long r = readRegister(REG_GAIN);

	byte idx = channel * 4;
	unsigned long chGain = 0;

	if (channel % 2 == 0) //0, 2, 4
	{
		chGain = (boost << 3) | gain;
	}
	else //1, 3, 5 
	{
		chGain = boost | (gain << 1);
	}
	
	r &= ~(0xf << idx);
	r |= chGain << idx;

	writeRegister(REG_GAIN, r);
}

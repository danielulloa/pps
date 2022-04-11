#!/usr/bin/env python3

# source: https://gist.github.com/RandomInsano/937536cee9dc363cdbd3e27d5f0afdf2

import serial
import binascii

PUERTO = '/dev/ttyUSB0'
BAUDRATE = 9600

ser = serial.Serial(port=PUERTO,baudrate=BAUDRATE,timeout=0.005)


def read_serial(ser):
    ''' Read any output it might have produced'''
    output = bytearray()
    while True:
        inp = ser.read(size=1) #read a byte
        output += inp

        if len(inp) < 1:
            return bytearray(output)


def send_command(command):
    ''' Push out a command to the serial port, get data back '''
    output = bytearray()
    for byte in command:
        ser.write([byte])
        output += read_serial(ser)

    return output


def increment(counter):
    carry = 0
    for i in range(len(counter)):
        byte = counter[i]

        if byte == 255:
            byte = 0
            carry = 1
        elif carry == 1:
            byte += carry
            carry = 0
        else:
            byte += 1

        counter[i] = byte

        if carry is not 1:
            break

    return counter

counter = [0, 0]
print()
while True:
    message = bytearray(counter)
    print("\rSending:  {0} ".format(binascii.hexlify(message)), end='')
    response = send_command(message)
    if len(response) > 0:
        print("\nReceived: {0}\n".format(binascii.hexlify(response)))

    counter = increment(counter)



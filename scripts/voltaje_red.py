#!/usr/bin/env python3

# source: https://learn.sparkfun.com/tutorials/graph-sensor-data-with-python-and-matplotlib/update-a-graph-in-real-time

import pymodbus
from pymodbus.pdu import ModbusRequest
from pymodbus.client.sync import ModbusSerialClient as ModbusClient
from pymodbus.transaction import ModbusRtuFramer
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
import datetime as dt

client = ModbusClient(method="rtu", port="/dev/ttyUSB0", baudrate=19200, parity="E", timeout=0.1)
connection = client.connect()

# Create figure for plotting
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
xs = []
ys = []

# This function is called periodically from FuncAnimation
def animate(i, xs, ys):
    read = client.read_holding_registers(3207,1,unit=1)
    voltaje = read.registers[0]/10
    xs.append(dt.datetime.now().strftime('%H:%M:%S.%f'))
    ys.append(voltaje)

    # Limit x and y lists to 20 items
    xs = xs[-20:]
    ys = ys[-20:]

    # Draw x and y lists
    ax.clear()
    ax.plot(xs, ys)

    # Format plot
    plt.xticks(rotation=45, ha='right')
    plt.subplots_adjust(bottom=0.30)
    plt.title('Voltaje de red')
    plt.ylabel('Voltaje [V]')

# Set up plot to call animate() function periodically
ani = animation.FuncAnimation(fig, animate, fargs=(xs, ys), interval=1000)
plt.show()

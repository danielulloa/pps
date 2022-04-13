import machine

# 23 CS - va a gpio7
# 18 DR - va a gpio5
# 24 SCK - va a gpio2
# 25 SDO -> va a gpio4
# 26 SDI -> va a gpio3
# 27 RST - va a gpio8

spi_sck = machine.Pin(2)
spi_tx = machine.Pin(3)
spi_rx = machine.Pin(4)
cs = machine.Pin(7, machine.Pin.OUT, value=1)
rst = machine.Pin(8, machine.Pin.OUT, value=1)

cs.value(0)
spi = machine.SPI(0,baudrate=1000000, polarity=0, phase=0, bits=8, firstbit=machine.SPI.MSB, sck=spi_sck, mosi=spi_tx, miso=spi_rx)
# escribo en config0
#spi.write('\x5A')
# configuro con 0x386050
spi.write('\x5A386050')
#spi.write('\x60')
#spi.write('\x50')
# escribo en config1
spi.write('\x5C000000')
# configuro con 0x0
#spi.write('\x00')
#spi.write('\x00')
#spi.write('\x00')
# leer statuscom
temp = bytearray(1)
data = bytearray(3)
spi.readinto(temp, 0x59)
spi.readinto(data, 0x59)
cs.value(1)
print(data)
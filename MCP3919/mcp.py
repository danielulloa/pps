import machine
import utime
import ustruct
import sys

###############################################################################
# Constants
CONFIG0 = 0x386050
CONFIG1 = 0x000000

# Registers
REG_CONFIG0 = 0x0D
REG_CONFIG1 = 0x0E
REG_CH_0 = 0x00
REG_CH_1 = 0x00
BASE_ADDR = 0x40


###############################################################################
# Settings

# Assign chip select (CS) pin (and start it high)
cs = machine.Pin(7, machine.Pin.OUT)
rst = machine.Pin(8, machine.Pin.OUT)

# Initialize SPI
spi = machine.SPI(0,
                  baudrate=1000000,
                  polarity=0,
                  phase=0,
                  bits=8,
                  firstbit=machine.SPI.MSB,
                  sck=machine.Pin(2),
                  mosi=machine.Pin(3),
                  miso=machine.Pin(4))

###############################################################################
# Functions

def reg_write(spi, cs, reg, data):
    """
    Write n bytes to the specified register.
    """
    
    # Construct message (set ~W bit low, MB bit low)
    msg = bytearray()
    msg.append(BASE_ADDR | reg << 1)
    msg.append(data)
    
    # Send out SPI message
    cs.value(0)
    spi.write(msg)
    cs.value(1)
    
def reg_read(spi, cs, reg, nbytes=3):
    """
    Read byte(s) from specified register.
    """
    
    # Construct message (set ~W bit high)
    msg = bytearray()
    msg.append(BASE_ADDR | reg <<1 | 1)
    
    # Send out SPI message and read
    cs.value(0)
    spi.write(msg)
    data = spi.read(nbytes)
    cs.value(1)
    
    return data

###############################################################################
# Main
# Start CS pin high
cs.value(1)

# Wait before taking measurements
utime.sleep(2.0)

reg_write(spi, cs, REG_CONFIG0, CONFIG0)
reg_write(spi, cs, REG_CONFIG1, CONFIG1)
reads=0
# Run forever
while reads<10:
    
    # Read X, Y, and Z values from registers (16 bits each)
    data = reg_read(spi, cs, REG_CH_1, 3)
    print(data)
    #print(ustruct.unpack_from("<h", data, 0)[0])
    utime.sleep(0.1)
    reads+=1
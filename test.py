#!/usr/bin/env python
import serial
import time
import struct

serialPort = 'COM20'
serialBaud = 921600
bytecount = 0
bRun = True

# Connect to serial port
print('Trying to connect to ' + str(serialPort) +
      ' at ' + str(serialBaud) + ' BAUD.')
try:
    s = serial.Serial(serialPort, serialBaud, timeout=4)
    print('Connected!')
except:
    print("Failed to connect with " + str(serialPort) +
          ' at ' + str(serialBaud) + ' BAUD.')

file = open("sample.jpg", "wb")
s.reset_input_buffer()  # flush input buffer
while(bRun):
    #time.sleep(0.2)
    # read n bytes into array
    rawData = s.read(128)
    bytecount = bytecount + len(rawData)
    file.write(rawData)
    if bytecount>60000:
        bRun=False

file.close()

    
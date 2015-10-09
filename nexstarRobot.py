#! /usr/bin/env python

import pyduino
import sys
import time

def usage():
    print """Usage: ./nexstarRobot.py port action
Example port /dev/cu.usbserial-AL01C9IS
Available actions: 1 - hibernate
                 2 - wake
                 3 - power off
                 4 - power on"""

if __name__ == "__main__":
	try:
        	arduino = pyduino.Arduino(sys.argv[1])
        	action = int(sys.argv[2])
    	except IndexError, ValueError:
        	usage()
        	sys.exit()	
	arduino.iterate()
	try:
		if action == 1:
			arduino.digital[2].set_active(1)
			arduino.digital[2].set_mode(pyduino.DIGITAL_OUTPUT)
			arduino.digital[2].write(1)    #Turn output high
			arduino.digital[2].write(0)
		if action == 2:
			arduino.digital[3].set_active(1)
       		        arduino.digital[3].set_mode(pyduino.DIGITAL_OUTPUT)
       	       		arduino.digital[3].write(1)    #Turn output high
			arduino.digital[3].write(0)
	        if action == 3:
			arduino.digital[4].set_active(1)
                	arduino.digital[4].set_mode(pyduino.DIGITAL_OUTPUT)
           		arduino.digital[4].write(1)    #Turn output high
			arduino.digital[4].write(0)
		if action == 4:
                	arduino.digital[5].set_active(1)
                	arduino.digital[5].set_mode(pyduino.DIGITAL_OUTPUT)
                	arduino.digital[5].write(1)    #Turn output high
			arduino.digital[5].write(0)
	except KeyboardInterrupt:
            arduino.exit()

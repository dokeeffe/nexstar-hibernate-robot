#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <iostream>

#include "firmata.h"

/**
 * Simple command to send data to an arduino board with the HibernateRobot firmware installed. 
 * Asks to set pins on/off using firmata protocol which the firmware will interpret as one of 4 commands.
 * Ask firmata: pin 5 on = powerOn the scope. Switch on relay
 * Ask firmata: pin 4 on = powerOff the scope. Switch off the relay
 * Ask firmata: pin 3 on = wake. Press the enter button on handset using servo
 * Ask firmata: pin 2 on = hibernate. Press the sequence of buttons to enter hibernate.
 
**/
int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Usage: nxhibernate [hibernate wake poweron poweroff]\n");
        return 1;
    }

    Firmata* sf;
    //iterate over the first 10 ttyUSBxx USB devices and see if we can find the HibernateRobot
    for( int a = 0; a < 10; a = a + 1 )
    {
    	string usbPort = "/dev/ttyUSB" +  std::to_string(a);
    	printf("Attempting connection\n");
        sf = new Firmata(usbPort.c_str());
        if (sf->portOpen && strstr(sf->firmata_name, "HibernateRobot.ino-2.4")) {
    	    printf("ARDUINO BOARD CONNECTED.\n");
	        printf("FIRMATA VERSION:%s\n",sf->firmata_name);
		for (int i = 1; i < argc; ++i) {
                    sf->reportDigitalPorts(1);
		
		    if (strstr(argv[i], "poweron")) {
                        printf("Powering on\n");
      		        sf->writeDigitalPin(5,ARDUINO_HIGH);
		        sf->writeDigitalPin(5,ARDUINO_LOW);
                        sleep(5); //5 sec delay built into firmware so we should wait too.
		    }
		    if (strstr(argv[i], "poweroff")) {
                        printf("Powering off\n");
                        sf->writeDigitalPin(4,ARDUINO_HIGH);
                        sf->writeDigitalPin(4,ARDUINO_LOW);
                        sleep(5); //5 sec delay built into firmware so we should wait too.
                    }
		    if (strstr(argv[i], "wake")) {
                        printf("Waking from hibernation\n");
                        sf->writeDigitalPin(3,ARDUINO_HIGH);
                        sf->writeDigitalPin(3,ARDUINO_LOW);
                        sleep(1); //takes 1 sec to do this button press
                    }
		    if (strstr(argv[i], "hibernate")) {
                        printf("Hibernating\n");
                        sf->writeDigitalPin(2,ARDUINO_HIGH);
                        sf->writeDigitalPin(2,ARDUINO_LOW);
                        sleep(5); //Takes about 5 sec to get through button presses
                    }
		}
	        return 0;
        } else {
            printf("FIRMATA VERSION:%s",sf->firmata_name);
            printf("Failed, trying next port.\n");
        }
    }
    printf(" Failed to connect to arduino board\n");
    delete sf;
    return 1;
}


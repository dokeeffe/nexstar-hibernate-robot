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
 * 
 **/
int main(int argc, char* argv[])
{
    if (argc < 3) {
        printf("Usage: nxhibernate /dev/ttyUSB0 [hibernate wake poweron poweroff]\nWhere /dev/ttyUSB0 is the arduino device\n");
        return 1;
    }
    
    Firmata* sf;
    //connect to device specified in param 1
    string usbPort = argv[1];
    printf("Attempting connection\n");
    sf = new Firmata(usbPort.c_str());
    if (sf->portOpen && strstr(sf->firmata_name, "HibernateRobot.ino-2.4")) {
        printf("ARDUINO BOARD CONNECTED.\n");
        printf("FIRMATA VERSION:%s\n",sf->firmata_name);
        for (int i = 2; i < argc; ++i) {
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
        printf("Failed to connect, is the device correct?\n");
    }
    
    printf(" Failed to connect to arduino board\n");
    delete sf;
    return 1;
}


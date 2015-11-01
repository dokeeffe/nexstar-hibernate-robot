/*
 * 
 *
 * http://firmata.org/wiki/Download
 */
#include <Servo.h>
#include <Firmata.h> 
 
Servo menuUpButtonServo;  // create servo object to control a servo. The servo placed over the menu and up buttons on the controller
Servo enterAlignButtonServo;  // create servo object to control a servo. The servo placed over the enter and align buttons on the controller

const int buttonMenuTravel = 40;
const int buttonUpTravel = 40;
const int buttonEnterTravel = 50;
const int telescopePowerRelayPin = 6;
const int menuUpButtonServoPin = 2;
const int enterAlignButtonServoPin = 4;

byte previousPIN[TOTAL_PORTS];  
byte previousPORT[TOTAL_PORTS];

/**
 * Setup servos and firmata
 */
void setup() 
{ 
  Firmata.setFirmwareVersion(FIRMATA_MAJOR_VERSION, FIRMATA_MINOR_VERSION);
  Firmata.attach(DIGITAL_MESSAGE, digitalWriteCallback);
  Firmata.attach(SET_PIN_MODE, setPinModeCallback);
  Firmata.begin(57600);
  menuUpButtonServo.attach(menuUpButtonServoPin);
  enterAlignButtonServo.attach(enterAlignButtonServoPin);
  menuUpButtonServo.write(90);
  enterAlignButtonServo.write(90);
  pinMode(telescopePowerRelayPin, OUTPUT); //relay to control the scope's 12v supply
} 
 
void loop() 
{ 
  while (Firmata.available()) {
    Firmata.processInput();
  }
}

/**
 * Empty pinmode callback
 */
void setPinModeCallback(byte pin, int mode) {
 //do nothing, not needed as we are just using pin signals from clients as messages/commands. However if we have no callback for SET_PIN_MODE there is a wierd bug where first commands (after power on) to firmware from clients will fail.
}

/**
 * Firmata callback. Handles requests from client
 */
void digitalWriteCallback(byte port, int value)
{
  byte i;
  byte currentPinValue, previousPinValue;

  if (port < TOTAL_PORTS && value != previousPORT[port]) {
    for (i = 0; i < 8; i++) {
      currentPinValue = (byte) value & (1 << i);
      previousPinValue = previousPORT[port] & (1 << i);
      int pin = i + (port * 8);
      if (pin == 2 && currentPinValue > 0) {
        hibernate();
      } else if (pin == 3 && currentPinValue > 0) {
        wake();
      } else if (pin == 4 && currentPinValue > 0) {
        powerOff();
      } else if (pin == 5 && currentPinValue > 0) {
        powerOn();
      }
    }
    previousPORT[port] = value;
  }
}

/**
 * Power off the scope
 */
void powerOff() {
  delay(5000);//wait 5 sec before powering off. TODO: add a buzzer or some sort of feedback
  digitalWrite(telescopePowerRelayPin, LOW); 
}

/**
 * Power on the scope
 */
void powerOn() {
  digitalWrite(telescopePowerRelayPin, HIGH); 
  delay(5000);//wait 5 sec just in case it takes time before 'wake' is available
}

/**
 * Press the sequence of buttons to enter hibernation mode.
 */
void hibernate() {
  buttonMenu(1);
  buttonUp(6);
  buttonEnter(1);
  buttonUp(6);
  buttonEnter(1);
}

/**
 * Press the sequence of buttons to wake from hibernation (only works if already in hibernation mode and powed on)
 */
void wake() {
 buttonEnter(1); 
}


/**
 * Press the menu button
 */
void buttonMenu(int presses) {
  menuUpButtonServo.write(90);
  delay(100);  
  menuUpButtonServo.write(90-buttonMenuTravel);
  delay(300);
  menuUpButtonServo.write(90);
  delay(100);
}

/**
 * Press the up button
 */
void buttonUp(int presses) {
  for(int i=0; i<presses; i++) {
    menuUpButtonServo.write(90);
    delay(100);  
    menuUpButtonServo.write(90+buttonUpTravel);
    delay(300);
    menuUpButtonServo.write(90);
    delay(100);    
  }
}

/**
 * Press the enter button
 */
void buttonEnter(int presses) {
  enterAlignButtonServo.write(90);
  delay(100);  
  enterAlignButtonServo.write(90+buttonEnterTravel);
  delay(200);
  enterAlignButtonServo.write(90);
  delay(100);
}



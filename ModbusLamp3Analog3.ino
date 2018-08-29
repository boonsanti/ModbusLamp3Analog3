/*
  ModbusLamp3Analog3
  Example code by Boonsanti Tungisarawuttigul
*************************************************  
  Library (Modbus Serial)
  Copyright by André Sarmento Barbosa
  http://github.com/andresarmento/modbus-arduino
*/
 
#include <Modbus.h>
#include <ModbusSerial.h>

// Modbus Registers Offsets (0-9999)
const int LAMP1_COIL0 = 0x4800;
const int LAMP1_COIL1 = 0x4801;
const int LAMP1_COIL2 = 0x4802;

const int ANALOG_HREG0 = 0x0;
const int ANALOG_HREG1 = 0x1;
const int ANALOG_HREG2 = 0x2;

// Used Pins
const int led1 = 2;
const int led2 = 3;
const int led3 = 4;

const int sensor0 = A0;
const int sensor1 = A1;
const int sensor2 = A2;

// ModbusSerial object
ModbusSerial mb;

void setup() {
    // Config Modbus Serial (port, speed, byte format) 
    mb.config(&Serial, 9600, SERIAL_8N1);
    // Set the Slave ID (1-247)
    mb.setSlaveId(1);  
    
    // Set ledPin mode
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);

    mb.addCoil(LAMP1_COIL0);
    mb.addCoil(LAMP1_COIL1);
    mb.addCoil(LAMP1_COIL2);

    mb.addHreg(ANALOG_HREG0);
    mb.addHreg(ANALOG_HREG1);
    mb.addHreg(ANALOG_HREG2);
}

void loop() {
   // Call once inside loop() - all magic here
   mb.task();
   
   digitalWrite(led1, !mb.Coil(LAMP1_COIL0));
   digitalWrite(led2, !mb.Coil(LAMP1_COIL1));
   digitalWrite(led3, !mb.Coil(LAMP1_COIL2));

   mb.Hreg(ANALOG_HREG0, analogRead(sensor0));
   mb.Hreg(ANALOG_HREG1, analogRead(sensor1));
   mb.Hreg(ANALOG_HREG2, analogRead(sensor2));
}

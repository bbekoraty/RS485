#include "MyModbusSensor.h"

//Serial Configuration
/*SERIAL_5N1
SERIAL_6N1
SERIAL_7N1
SERIAL_8N1 (the default)
SERIAL_5N2
SERIAL_6N2
SERIAL_7N2
SERIAL_8N2
SERIAL_5E1: even parity
SERIAL_6E1
SERIAL_7E1
SERIAL_8E1
SERIAL_5E2
SERIAL_6E2
SERIAL_7E2
SERIAL_8E2
SERIAL_5O1: odd parity
SERIAL_6O1
SERIAL_7O1
SERIAL_8O1
SERIAL_5O2
SERIAL_6O2
SERIAL_7O2
SERIAL_8O2*/


//MyModbusSensor objectname(dir pin,rxPin,txPin,slaveID,Buadrate)
MyModbusSensor conductivity(4, 16, 17, 1, 9600);

void setup()
{
  conductivity.initial(SERIAL_8N2);
  Serial.begin(9600);
}

void loop()
{
  conductivity.readSensorValues(0, 2); //objectname.readsensor(startbit,quantity)
  conductivity.readSensorValues(2, 2); //objectname.readsensor(startbit,quantity)
  conductivity.displayConductivity(); //Display
  conductivity.displayTemperature();
  Serial.println("/////END VALUE/////");
  delay(1000);
}

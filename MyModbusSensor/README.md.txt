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
MyModbusSensor Digital_conductivity(4, 16, 17, 1, 9600);
MyModbusSensor Analog_conductivity(4, 16, 17, 1, 9600);
MyModbusSensor Analog_pH(4, 16, 17, 1, 9600);

/*coden >> 0 conduct_digi
           1 conduct
           2 pH
*/

void setup()
{
  conductivity.initial(SERIAL_8N2);
  Serial.begin(9600);
}

void loop()
{
  /////////////////////Read and display function ///////////////////////////////////
                     // Digital probe conductivity//
  Digital_conductivity.readSensorValues(0, 2, 4, 0); //objectname.readsensor(startbit,quantity,readMode(3,4),coden(0,1,2))
  Digital_conductivity.displayConductivity(); //Display conductivity
  Digital_conductivity.readSensorValues(0, 2, 4, 0); //objectname.readsensor(startbit,quantity,readMode(3,4),coden(0,1,2))
  Digital_conductivity.displayTemperature();//Display Temperature

                     // Anolog probe conductivity//
  Analog_conductivity.readSensorValues(0, 2, 3, 1); //objectname.readsensor(startbit,quantity,readMode(3,4),coden(0,1,2))
  Analog_conductivity.displayConductivity(); //Display conductivity
  Analog_conductivity.readSensorValues(0, 2, 3, 1); //objectname.readsensor(startbit,quantity,readMode(3,4),coden(0,1,2))
  Analog_conductivity.displayTemperature();//Display Temperature

                    // Analog probe pH//
  Analog_pH.readSensorValues(0, 2, 3, 2); //objectname.readsensor(startbit,quantity,readMode(3,4),coden(0,1,2))
  Analog_pH.displayConductivity(); //Display conductivity
  Analog_pH.readSensorValues(0, 2, 3, 2); //objectname.readsensor(startbit,quantity,readMode(3,4),coden(0,1,2))
  Analog_pH.displayTemperature();//Display Temperature
  
/////////////////////Read and display function END /////////////////////////////////

//////////////////////getter function /////////////////////////////////////
    // get slaveID//
 //object name.getSlaveID
  int slaveID = conductivity.getSlaveID();

  // get conductivity as variable//
 //object name.getConductivityValue()
 float conductivityValue = conductivity.getConductivityValue(); 
  Serial.print("Conductivity Value: ");
  Serial.println(conductivityValue, 6);


    // get temperature as variable//
 //object name.getTemperatureValue()
 float conductivityValue = conductivity.getTemperatureValue(); 
  Serial.print("Conductivity Value: ");
  Serial.println(conductivityValue, 6);

      // get pH as variable//
 //object name.getpHValue()
 float pHValue = Analog_pH.getpHValue(); 
  Serial.print("pH Value: ");
  Serial.println(pH, 3);
  
//////////////////////getter function END /////////////////////////////////////

  delay(1000);
}
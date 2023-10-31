#include "MyModbusSensor.h"

ModbusMaster MyModbusSensor::_node;
uint8_t MyModbusSensor::_dirPin;
uint8_t MyModbusSensor::_staticDirPin = 0;

//constructure
MyModbusSensor::MyModbusSensor(uint8_t dirPin, uint8_t rxPin, uint8_t txPin, uint8_t slaveID, unsigned long baudRate)
{
  _dirPin = dirPin;
  _staticDirPin = dirPin;  // Initialize _staticDirPin to dirPin
  _rxPin = rxPin;
  _txPin = txPin;
  _slaveID = slaveID;
  _serialBaudRate = baudRate;
}

void MyModbusSensor::setDirPin(uint8_t dirPin)
{
  _staticDirPin = dirPin;                                                                                                                                                                                       
}

void MyModbusSensor::staticModbusPostTransmission()
{
  digitalWrite(_staticDirPin, LOW);
  delay(100);
}

void MyModbusSensor::staticModbusPreTransmission()
{
  delay(100);
  digitalWrite(_staticDirPin, HIGH);
}

void MyModbusSensor::initial(SerialConfig mySerialConfig)
{
  Serial.begin(9600);
  pinMode(_dirPin, OUTPUT);
  digitalWrite(_dirPin, LOW);

  Serial2.begin(_serialBaudRate, mySerialConfig, _rxPin, _txPin);
  Serial2.setTimeout(250);

  setDirPin(_staticDirPin);

  _node.begin(_slaveID, Serial2);
  _node.postTransmission(staticModbusPostTransmission);
  _node.preTransmission(staticModbusPreTransmission);
}


void MyModbusSensor::readSensorValues(uint8_t startAddress, uint8_t numRegisters ,uint8_t mode,uint8_t coden)
{
  uint8_t result;
  
  //------------------DIGITAL PROBE CONDUCTIVITY VALUE------------------//

  if (startAddress == 0&&numRegisters == 2&&mode == 4&&coden==0)//Conductivity Address (Digital Probe)
  {
    Serial.println("In CD digi");
    result = _node.readInputRegisters(startAddress, numRegisters);
    if (result == _node.ku8MBSuccess)
    {
      uint32_t sensorValue = 0;
      for (int i = 0; i < numRegisters; i++)
      {
        sensorValue |= _node.getResponseBuffer(i) << (i * 16);
      }
      _conductivityValue = *(float *)&sensorValue;
    }
    else
    {
      Serial.print("Error reading Conductivity registers! Error code: ");
      Serial.println(result, HEX);
    }
  }

   //******************* END *******************//
   //------------------DIGITAL PROBE TEMP VALUE------------------//

  else if (startAddress == 2&&numRegisters == 2&&mode == 4&&coden==0)//Temperature Address
  {
    Serial.println("In CD digi");
    result = _node.readInputRegisters(startAddress, numRegisters);
    if (result == _node.ku8MBSuccess)
    {
      uint32_t sensorValue = 0;
      for (int i = 0; i < numRegisters; i++)
      {
        sensorValue |= _node.getResponseBuffer(i) << (i * 16);
      }
      _temperatureValue = *(float *)&sensorValue;
    }
    else
    {
      Serial.print("Error reading Temperature registers! Error code: ");
      Serial.println(result, HEX);
    }
  }
   //******************* END *******************//
   //------------------ANALOG PROBE CONDUCTIVITY VALUE------------------//
  else if (startAddress == 0&&numRegisters == 2&&mode == 3&&coden==1)//Conductivity Address (Analog Probe)
  {
    Serial.println("In CD ");
    result = _node.readHoldingRegisters(startAddress, numRegisters);
    if (result == _node.ku8MBSuccess)
    {
      uint32_t sensorValue = 0;
      for (int i = 0; i < numRegisters; i++)
      {
        sensorValue |= _node.getResponseBuffer(i) << (i * 16);
      }
      _conductivityValue = *(float *)&sensorValue;
    }
    else
    {
      Serial.print("Error reading Conductivity registers! Error code: ");
      Serial.println(result, HEX);
    }
  }
     //******************* END *******************//
   //------------------ANALOG PROBE TEMP VALUE------------------//
    else if (startAddress == 2&&numRegisters == 2&&mode == 3&&coden==1)//Temperature Address (Analog Probe)
  {
    Serial.println("In CD ");
    result = _node.readHoldingRegisters(startAddress, numRegisters);
    if (result == _node.ku8MBSuccess)
    {
      uint32_t sensorValue = 0;
      for (int i = 0; i < numRegisters; i++)
      {
        sensorValue |= _node.getResponseBuffer(i) << (i * 16);
      }
      _temperatureValue = *(float *)&sensorValue;
    }
    else
    {
      Serial.print("Error reading Temperature registers! Error code: ");
      Serial.println(result, HEX);
    }
  }
  //******************* END *******************//
  //------------------pH VALUE------------------//
    else if (startAddress == 0&&numRegisters == 2&&mode == 3&&coden==2)
  {
    Serial.println("In pH");
    result = _node.readHoldingRegisters(startAddress, numRegisters);
    if (result == _node.ku8MBSuccess)
    {
      uint32_t sensorValue = 0;
      for (int i = 0; i < numRegisters; i++)
      {
        sensorValue |= _node.getResponseBuffer(i) << (i * 16);
      }
      _pHValue = *(float *)&sensorValue;
    }
    else
    {
      Serial.print("Error reading pH registers! Error code: ");
      Serial.println(result, HEX);
    }
  }
  //******************* END *******************//
  //------------------pH Temp VALUE------------------//
    else if (startAddress == 2&&numRegisters == 2&&mode == 3&&coden==2)//Temperature Address (Analog Probe)
  {
    Serial.println("In pH");
    result = _node.readHoldingRegisters(startAddress, numRegisters);
    if (result == _node.ku8MBSuccess)
    {
      uint32_t sensorValue = 0;
      for (int i = 0; i < numRegisters; i++)
      {
        sensorValue |= _node.getResponseBuffer(i) << (i * 16);
      }
      _temperatureValue = *(float *)&sensorValue;
    }
    else
    {
      Serial.print("Error reading Temperature registers! Error code: ");
      Serial.println(result, HEX);
    }
  }
  //******************* END *******************//
}

//*********************Display Part******************//
void MyModbusSensor::displayConductivity()
{
  Serial.println("---CONDUCTIVITY--- ");
  Serial.print(_conductivityValue, 6);
  Serial.println(" ms/cm");
}
void MyModbusSensor::displayTemperature()
{
  Serial.println("---TEMPERATURE--- ");
  Serial.print(_temperatureValue, 6);
  Serial.println(" C");
}
void MyModbusSensor::displaypH()
{
  Serial.println("---pH--- ");
  Serial.print(_pHValue, 6);
  Serial.println(" ");
}

#ifndef MyModbusSensor_h
#define MyModbusSensor_h

#include <Arduino.h>
#include <ModbusMaster.h>

class MyModbusSensor
{
private:
  uint8_t _rxPin;
  uint8_t _txPin;
  uint8_t _slaveID;
  unsigned long _serialBaudRate;
  float _conductivityValue;
  float _temperatureValue;
  static uint8_t _dirPin;
  static uint8_t _staticDirPin;
  static ModbusMaster _node;

public:
  MyModbusSensor(uint8_t dirPin, uint8_t rxPin, uint8_t txPin, uint8_t slaveID, unsigned long baudRate);
  void initial(SerialConfig mySerialConfig);
  void readSensorValues(uint8_t startAddress, uint8_t numRegisters);
  void displayConductivity();
  void displayTemperature();

  static void setDirPin(uint8_t dirPin);
  static void staticModbusPostTransmission();
  static void staticModbusPreTransmission();

    float getConductivityValue() const {
    return _conductivityValue;
  }

      float getTemperatureValue() const {
    return _temperatureValue;
  }

      int getSlaveID() const {
  return _slaveID;
  }

};

#endif

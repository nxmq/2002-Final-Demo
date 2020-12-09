#include <Romi32U4.h>
#include "IR_sensor.h"

void IRsensor::Init(void)
{
    pinMode(pin_IR, INPUT);
}

float IRsensor::PrintData(void)
{
    Serial.println(ReadData(), 4);
}

float IRsensor::ReadData(void)
{
  //assignment 1.1
  //read out and calibrate your IR sensor, to convert readouts to distance in [cm]
  int adc = analogRead(pin_IR);
  float voltage = (5/1024.0)*adc;
  float distance = (20/voltage);
  //return voltage;
  return distance;
}
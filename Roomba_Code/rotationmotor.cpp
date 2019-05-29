#include "rotationmotor.h"
#include <iostream>

int16_t rotationMotor :: getRPM() const
{
  return rpm;
}

void rotationMotor :: incRPM()
{
  rpm += incValue;
  if(rpm >= maxRPM)
    {
      std::cout<<"maxRPM reached"<<std::endl;
      rpm = maxRPM;
    }

}

void rotationMotor :: decRPM()
{
  rpm -= decValue;
  if(rpm <= minRPM)
    {
      std::cout<<"minRPM reached"<<std::endl;
      rpm = minRPM;
    }
}

int16_t rotationMotor :: getincValue()const
{
  return incValue;
}

int16_t rotationMotor :: getdecValue()const
{
  return decValue;
}

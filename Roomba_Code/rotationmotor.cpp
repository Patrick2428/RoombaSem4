#include "rotationmotor.h"
#include <iostream>
///Implementation of member functions of rotatioMotor class

///Get RPM
int16_t rotationMotor :: getRPM() const
{
  return rpm;
}

///Increments rpm with data member incValue 
void rotationMotor :: incRPM()
{
  rpm += incValue;
  if(rpm >= maxRPM)
    {
      std::cout<<"maxRPM reached"<<std::endl;
      rpm = maxRPM;
    }

}

///Decrements rpm with data member decValue
void rotationMotor :: decRPM()
{
  rpm -= decValue;
  if(rpm <= minRPM)
    {
      std::cout<<"minRPM reached"<<std::endl;
      rpm = minRPM;
    }
}

///Get inc/dec values
int16_t rotationMotor :: getincValue()const
{
  return incValue;
}

int16_t rotationMotor :: getdecValue()const
{
  return decValue;
}

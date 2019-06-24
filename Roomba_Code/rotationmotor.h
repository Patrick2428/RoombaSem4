/** @file */
///\brief rotation motor class init for controlling roomba rotation motors
#ifndef ROTATIONMOTOR_H_
#define ROTATIONMOTOR_H_
#include <cstdint>

///Rotation Motor class to control the Speed of the Roomba motors
class rotationMotor
{

 public:
  ///Constructor to initialise the RPM and the inc/dec values
 rotationMotor(int16_t defaultRPM, int16_t inc = 50, int16_t dec = 50) : rpm(defaultRPM), incValue(inc), decValue(dec) {}
  ///returns the value of the current rpm
  int16_t getRPM()const;
  ///returns the increment value used
  int16_t getincValue()const;
  ///returns the decrement value used
  int16_t getdecValue()const; 
  ///Increments the rpm value
  void incRPM();
  ///Decrements the rpm value
  void decRPM();  

 private:
  ///Data members of type int16_t
  ///rpm data members
  int16_t rpm, incValue, decValue;
  ///max rpm data member
  int16_t maxRPM = 500;
  ///min rpm data member
  int16_t minRPM = -500; 

};

#endif

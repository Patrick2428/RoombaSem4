#ifndef ROTATIONMOTOR_H_
#define ROTATIONMOTOR_H_
#include <cstdint>

///Rotation Motor class to control the Speed of the Roomba motors
class rotationMotor
{

 public:
  ///Constructor to initialise the RPM and the inc/dec values
 rotationMotor(int16_t defaultRPM, int16_t inc = 50, int16_t dec = 50) : rpm(defaultRPM), incValue(inc), decValue(dec) {}
  ///Getters and setters for RPM and inc/dec values
  int16_t getRPM()const;
  int16_t getincValue()const;
  int16_t getdecValue()const;

  ///member functions to increment and decrement the rotation of the motors with initialised values
  void incRPM();
  void decRPM();

 private:
  ///Data members of type int16_t 
  int16_t rpm, incValue, decValue;
  int16_t maxRPM = 500;
  int16_t minRPM = -500;

};

#endif

#ifndef ROTATIONMOTOR_H_
#define ROTATIONMOTOR_H_
#include <cstdint>

class rotationMotor
{

 public:
 rotationMotor(int16_t defaultRPM, int16_t inc = 50, int16_t dec = 50) : rpm(defaultRPM), incValue(inc), decValue(dec) {}
  int16_t getRPM()const;
  int16_t getincValue()const;
  int16_t getdecValue()const;
  void incRPM();
  void decRPM();

 private:
  int16_t rpm, incValue, decValue;
  int16_t maxRPM = 250;
  int16_t minRPM = -250;

};

#endif

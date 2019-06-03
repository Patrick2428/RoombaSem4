#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_
#include <string>
#include "SerialLink.h"
#include "rotationmotor.h"
#include "CommandProcessor.h"
///initialising statemachine function
void sendsignal(const std::string &signalp, SerialLink &slp, int &Modep);

#endif

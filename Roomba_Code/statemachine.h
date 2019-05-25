#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_
#include <string>
#include "SerialLink.h"

void sendsignal(const std::string &signal, SerialLink &sl,bool driveMode);

#endif

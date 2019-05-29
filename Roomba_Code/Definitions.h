#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#include "AppInfo.h"
#include "Config.h"
#include "MQTTDataHandler.h"
#include "OpenInterfaceConfig.h"
#include "SerialLink.h"
#include "statemachine.h"
#include "rotationmotor.h"
#include "CommandProcessor.h"

#include <iostream>
#include <csignal>
#include <string>
#include <chrono>
#include <thread>
#include <vector>

void addCommands (CommandProcessor &cmdp, SerialLink &sl, rotationMotor &lm, rotationMotor &rm,int &RoombaMode );

#endif


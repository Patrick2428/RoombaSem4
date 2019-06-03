#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

///Include file with Command function definitions 

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
#include <stdio.h>
#include <sstream>


void addCommands (CommandProcessor &cmdp, SerialLink &sl, rotationMotor &lm, rotationMotor &rm,int &RoombaMode, MQTTDataHandler &MQTTData);

void addDriveCommands(CommandProcessor &cmdp, SerialLink &sl, rotationMotor &lm, rotationMotor &rm, MQTTDataHandler &MQTTData);

void removeDriveCommands(CommandProcessor &cmdp);
  

#endif


/** @file */
///\brief Include file with Command function definitions 
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
#include <stdio.h>
#include <sstream>

///Init addCommand function
void addCommands (CommandProcessor &cmdp, SerialLink &sl, rotationMotor &lm, rotationMotor &rm,int &RoombaMode, MQTTDataHandler &MQTTData);
///Init addDriveCommand function
void addDriveCommands(CommandProcessor &cmdp, SerialLink &sl, rotationMotor &lm, rotationMotor &rm, MQTTDataHandler &MQTTData);
///Init removeDriveCommand function
void removeDriveCommands(CommandProcessor &cmdp);
  

#endif


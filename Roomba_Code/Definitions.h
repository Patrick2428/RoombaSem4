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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/resource.h>

///Init addCommand function
void addCommands (CommandProcessor &cmdp, SerialLink &sl, rotationMotor &lm, rotationMotor &rm,int &RoombaMode, MQTTDataHandler &MQTTData);
///Init addDriveCommand function
void addDriveCommands(CommandProcessor &cmdp, SerialLink &sl, rotationMotor &lm, rotationMotor &rm, MQTTDataHandler &MQTTData);
///Init removeDriveCommand function
void removeDriveCommands(CommandProcessor &cmdp);
///Function that forks the process and calls the Sense hat python code using execlp()
void printOnSenseHat(MQTTDataHandler &MQTTData);
  

#endif


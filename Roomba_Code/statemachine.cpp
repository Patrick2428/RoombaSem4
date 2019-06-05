#include "statemachine.h"
#include "OpenInterfaceConfig.h"
#include "SerialLink.h"
#include "CommandProcessor.h"

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>

using namespace std::chrono_literals;
///statemachine function handeling events/commands from the Command Processor
///Most actions of the roomba are handled by the CommandProcessor
///Events not linked to MQTT commands are executed here
void sendsignal(const std::string &signalp, SerialLink &slp, int &Modep)
{
  switch(Modep)
    {
    case 0:  
      ///help mode --displayes a message of all available commands
      ///see definitions.cpp
      break;
      
    case 1:
      ///drive mode --enables manual driving of roomba
      ///see definitions.cpp
      break;

    case 2:
      ///reset mode --resets the roomba into safe mode
      slp.write(driveDirect(0, 0));
      slp.write(startSafe());
      break;

    case 3:
      ///cleaning mode --sends cleaning command
      slp.write(clean());
      break;

    case 4:
      ///docking mode -- sends docking command
      slp.write(dock());
      break;

    case 5:
      ///battle mode -- plays the final countdown on the roomba
      slp.write(playSong(0));
      std::this_thread::sleep_for(3.65s);
      slp.write(playSong(1));
      std::this_thread::sleep_for(3.3s);
      slp.write(playSong(2));
      std::this_thread::sleep_for(3s);     
      break;

    default:
      ///No applicable 
      std::cerr<<"wrong mode"<<std::endl;
      exit(1);
      
    }
  

  
}

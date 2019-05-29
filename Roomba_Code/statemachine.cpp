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

void sendsignal(const std::string &signalp, SerialLink &slp, int &Modep, const CommandProcessor &cmdpp )
{
  switch(Modep)
    {
    case 0:
      //start-up mode
      break;
      
    case 1:
      //drive mode
       break;

    case 2:
      //reset mode
      slp.write(driveDirect(0, 0));
      slp.write(startSafe());
      break;

    case 3:
      //cleaning mode
      slp.write(clean());
      break;

    case 4:
      //docking mode
      slp.write(dock());
      break;

    case 5:
      //battle mode
      slp.write(drive(500,10));
      std::this_thread::sleep_for(0.5s);
      slp.write(playSong(0));
      std::this_thread::sleep_for(5.0s);
      slp.write(drive(500,-10));
      std::this_thread::sleep_for(0.5s);
      slp.write(playSong(1));
      std::this_thread::sleep_for(3s);
      
      break;

    default:
      std::cerr<<"wrong mode"<<std::endl;
      exit(1);
      
    }
  

  
}

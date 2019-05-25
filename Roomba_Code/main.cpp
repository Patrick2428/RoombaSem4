#include "AppInfo.h"
#include "Config.h"
#include "MQTTDataHandler.h"
#include "OpenInterfaceConfig.h"
#include "SerialLink.h"
#include "statemachine.h"

#include <iostream>
#include <csignal>
#include <string>
#include <chrono>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

volatile sig_atomic_t receivedSIGINT{false};

void handleSIGINT(int /* s */)
{
  receivedSIGINT = true;
}

int main(int argc, char *argv[])
{
  std::string mqttBroker{MQTT_LOCAL_BROKER};
  int mqttBrokerPort{MQTT_LOCAL_BROKER_PORT};
  int major = 0;
  int minor = 0;
  int revision = 0;
  bool driveMode = false;
  std::string idleData = "idle";
  //Initialising serial connection
  SerialLink sl {"/dev/ttyUSB0",
      static_cast<unsigned int>(Baud::ROOMBA_DEFAULT)};
  
  std::cout << "The application started" << std::endl;
  std::cout << "Version: " << VERSION <<std::endl;
  std::cout << "Authors: " << AUTHORS <<std::endl;

  signal(SIGINT,handleSIGINT);

  mosqpp::lib_init();
  mosqpp::lib_version(&major, &minor, &revision);
  std::cout << "MQTT version: " << major << '.' << minor << '.'
       << revision <<std:: endl;

  MQTTDataHandler MQTTData("RoombaController", "MQTTData", mqttBroker, mqttBrokerPort);

  sl.write(startSafe());

  //loop receiving signals  
  while (!receivedSIGINT)
    {
      int rc{MQTTData.loop()};

      if(MQTTData.getData() == "drive")
	{
	  driveMode = true;
	  std::cout << "Driving mode selected" <<std::endl;
	  std::cout << "Enter driving direction" << std::endl;	  
	}
      else if(MQTTData.getData() == "stop")
	{
	  driveMode = false;
	  std::cout << "device Stopped" <<std::endl;
	}

      sendsignal(MQTTData.getData(), sl ,driveMode);

      //reseting datastring value
      MQTTData.resetData();
	
      if(rc) {
      std::cerr<<"--Reconnecting MQTT rc--" << rc << std::endl;
      MQTTData.reconnect();

    }
  }

  std::cout << "The application ended" <<std::endl;

  mosqpp::lib_cleanup();
  return 0;
}

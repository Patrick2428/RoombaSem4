#include "AppInfo.h"
#include "Config.h"
#include "MQTTDataHandler.h"
#include "OpenInterfaceConfig.h"
#include "SerialLink.h"

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
	  std::cout << "Driving mode selected" <<std::endl;
	  sl.write(driveDirect(100, 100));
	  std::this_thread::sleep_for(3s);

	  sl.write(driveDirect(0, -100));
	  std::this_thread::sleep_for(3s);

	  sl.write(driveDirect(-100, -100));
	  std::this_thread::sleep_for(3s);
      
	  sl.write(driveDirect(100, 0));
	  std::this_thread::sleep_for(3s);
	}
      if(MQTTData.getData() == "stop")
	{
	  std::cout << "device Stopped" <<std::endl;
	  sl.write(driveDirect(0 , 0));
	  sl.write(startSafe());
		   
	}

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

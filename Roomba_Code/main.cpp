#include "AppInfo.h"
#include "Config.h"
#include "MQTTDataHandler.h"

#include <iostream>
#include <csignal>
#include <string>

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
  
  std::cout << "The application started" << std::endl;
  std::cout << "Version: " << VERSION <<std::endl;
  std::cout << "Authors: " << AUTHORS <<std::endl;

  signal(SIGINT,handleSIGINT);

  mosqpp::lib_init();
  mosqpp::lib_version(&major, &minor, &revision);
  std::cout << "MQTT version: " << major << '.' << minor << '.'
       << revision <<std:: endl;

  MQTTDataHandler MQTTData("RoombaController", "MQTTData", mqttBroker, mqttBrokerPort);

  while (!receivedSIGINT){
    int rc{MQTTData.loop()};
    if(rc) {
      std::cerr<<"--Reconnecting MQTT rc--" << rc << std::endl;
      MQTTData.reconnect();
    }
  }

  std::cout << "The application ended" <<std::endl;

  mosqpp::lib_cleanup();
  return 0;
}

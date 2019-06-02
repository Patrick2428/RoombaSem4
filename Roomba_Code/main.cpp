#include "Definitions.h"

using namespace std::chrono_literals;

volatile sig_atomic_t receivedSIGINT{false};

void handleSIGINT(int /* s */)
{
  receivedSIGINT = true;
}

int main(int argc, char *argv[])
{
  //definitions
  std::string mqttBroker{MQTT_LOCAL_BROKER};
  std::string message , command;
  int mqttBrokerPort{MQTT_LOCAL_BROKER_PORT};
  int major = 0;
  int minor = 0;
  int revision = 0;
  int RoombaMode = 0;
  CommandProcessor cmdp;
  rotationMotor lm(50,20,20),rm(50,20,20);
  
  //Initialising serial connection
  SerialLink sl {"/dev/ttyUSB0",
      static_cast<unsigned int>(Baud::ROOMBA_DEFAULT)};
  //Initialising MQTT connection
  MQTTDataHandler MQTTData("idle","RoombaController", "MQTTData", mqttBroker, mqttBrokerPort);
  
  std::cout << "The application started" << std::endl;
  std::cout << "Version: " << VERSION <<std::endl;
  std::cout << "Authors: " << AUTHORS <<std::endl;

  signal(SIGINT,handleSIGINT);

  mosqpp::lib_init();
  mosqpp::lib_version(&major, &minor, &revision);
  std::cout << "MQTT version: " << major << '.' << minor << '.'
       << revision << std:: endl;

  sl.write(startSafe());
  sl.write(addSong(2));
  
  
  //Initialising Commands
  addCommands(cmdp, sl, lm, rm, RoombaMode,MQTTData);
  MQTTData.sendMessage( "Choose a mode: drive, clean, dock, battle or reset");
  cmdp.executeCommand(MQTTData.getData());
  MQTTData.sendMessage(MQTTData.getMessage());

  //loop receiving signals  
  while (!receivedSIGINT)
    {
      int rc{MQTTData.loop()};
      
      if(MQTTData.getData() != "idle")
	{
	  cmdp.executeCommand(MQTTData.getData());
	  MQTTData.sendMessage(MQTTData.getMessage());
	  
	  if(RoombaMode == 1)
	    {
	      addDriveCommands(cmdp, sl, lm, rm, MQTTData);
	      sendsignal(MQTTData.getData(), sl, RoombaMode);	      
	    }
	  else
	    {
	      removeDriveCommands(cmdp);
	      sendsignal(MQTTData.getData(), sl, RoombaMode);
	    }
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


/** @file */
///\brief Main cpp file in which objects get initialised and main control is handled

#include "Definitions.h"

using namespace std::chrono_literals;

volatile sig_atomic_t receivedSIGINT{false};

void handleSIGINT(int /* s */)
{
  receivedSIGINT = true;
}

int main(int argc, char *argv[])
{
  //Initialisation
  std::string mqttBroker{MQTT_LOCAL_BROKER};
  std::string message , command;
  int mqttBrokerPort{MQTT_LOCAL_BROKER_PORT};
  int major = 0;
  int minor = 0;
  int revision = 0;
  int RoombaMode = 0;
  CommandProcessor cmdp;
  rotationMotor lm(50,20,20), rm(50,20,20);
  
  ///Initialising serial connection
  SerialLink sl {"/dev/ttyUSB0",
      static_cast<unsigned int>(Baud::ROOMBA_DEFAULT)};
  ///Initialising MQTT connection
  MQTTDataHandler MQTTData("idle","RoombaController", "MQTTData", mqttBroker, mqttBrokerPort);
  
  std::cout << "The application started" << std::endl;
  std::cout << "Version: " << VERSION <<std::endl;
  std::cout << "Authors: " << AUTHORS <<std::endl;

  signal(SIGINT,handleSIGINT);

  mosqpp::lib_init();
  mosqpp::lib_version(&major, &minor, &revision);
  std::cout << "MQTT version: " << major << '.' << minor << '.'
       << revision << std:: endl;
  ///Set roomba into safe mode
  sl.write(startSafe());
  
  ///Initialising Commands
  addCommands(cmdp, sl, lm, rm, RoombaMode,MQTTData);
  MQTTData.sendMessage( "Choose a mode from the button selection");
  ///Executes first command - getData was set to idle
  cmdp.executeCommand(MQTTData.getData());
  MQTTData.sendMessage(MQTTData.getMessage());

  ///loop receiving signals and executing commands
  while (!receivedSIGINT)
    {
      int rc{MQTTData.loop()};
      ///Once getData changes from idle to something else events can occur
      if(MQTTData.getData() != "idle")
	{
	  cmdp.executeCommand(MQTTData.getData());
	  MQTTData.sendMessage(MQTTData.getMessage());
	  printOnSenseHat(MQTTData);
	  ///When roomba is in drive state driveCommands are added and ready for execution
	  if(RoombaMode == 1)
	    {
	      addDriveCommands(cmdp, sl, lm, rm, MQTTData);
	      sendsignal(MQTTData.getData(), sl, RoombaMode);	      
	    }
	  ///Once roomba leaves drive mode the driveCommands are removed
	  else
	    {
	      removeDriveCommands(cmdp);
	      sendsignal(MQTTData.getData(), sl, RoombaMode);
	    }
	}	
      ///reseting datastring value to idle waiting for next command
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


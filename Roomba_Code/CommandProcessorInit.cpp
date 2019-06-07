/** @file */
///\brief Functions adding commands to CommandProcessor class
#include "Definitions.h"

///Events linked to MQTT messages/commands are executed here
using namespace std::chrono_literals;
void addCommands(CommandProcessor &cmdp, SerialLink &sl, rotationMotor &lm, rotationMotor &rm, int &RoombaMode, MQTTDataHandler &MQTTData)
{
 
 ///Commands definitions with lambda function implementations
  cmdp.addCommand("help", [&MQTTData, &RoombaMode](){   ///addition of help command
      RoombaMode = 0;
      MQTTData.setMessage("MODES: drive, clean, reset, dock, battle"); });
    
  cmdp.addCommand("idle", [&MQTTData](){    ///addition of idle command
      std::cout<<"Waiting for command"<<std::endl;
      MQTTData.setMessage("Idle mode: waiting for command");});
  
  cmdp.addCommand("drive", [&RoombaMode,&MQTTData](){RoombaMode = 1; ///addition of drive command
      std::cout << "Driving mode selected" <<std::endl;
      std::cout << "Enter driving direction" << std::endl;
      MQTTData.setMessage("Driving mode: waiting for direction");});
 
  cmdp.addCommand("reset", [&RoombaMode,&MQTTData](){RoombaMode = 2; ///addition of reset command
      std::cout << "device in reset mode" <<std::endl;
      MQTTData.setMessage("Reset mode: Resetting Roomba");});
  
  cmdp.addCommand("clean", [&RoombaMode,&MQTTData](){RoombaMode = 3; ///addition of clean command
      std::cout<<"device in clean mode" <<std::endl;
      MQTTData.setMessage("Clean mode: Cleaning dust");});
  
  cmdp.addCommand("dock", [&RoombaMode, &MQTTData](){RoombaMode = 4; ///addition of dock command
      std::cout<<"device in dock mode" <<std::endl;
      MQTTData.setMessage("Dock mode: searching for docking station");});

  ///When playing and storing songs on the roomba some process time has to be implement before executing other commands
  cmdp.addCommand("battle", [&RoombaMode, &sl,&MQTTData](){RoombaMode = 5; ///addition of battle command
      std::this_thread::sleep_for(0.2s);
      sl.write(addSong(0)); ///write song nr 1 to roomba
      std::this_thread::sleep_for(0.2s); 
      sl.write(addSong(1)); ///write song nr 2 to roomba
      std::this_thread::sleep_for(0.2s);
      sl.write(addSong(2)); ///write song nr 3 to roomba
      std::this_thread::sleep_for(0.2s);
      sl.write(addSong(3));
      std::this_thread::sleep_for(0.2s);
      std::cout<<"device in battle mode" <<std::endl;
      MQTTData.setMessage("Battle mode: A Lannister always pays his debts");});
  
  cmdp.addCommand("stop", [&sl,&lm,&rm,&MQTTData](){ ///addition of stop command
      std::cout<<"stopped"<<std::endl;
      sl.write(driveDirect(0, 0));
      MQTTData.setMessage("Stopping");});
  
  cmdp.addCommand("incrpm",[&sl,&lm,&rm,&MQTTData]{lm.incRPM(); ///addition of incrpm command
      rm.incRPM();
      std::cout<<"rpm incremented by: " <<lm.getincValue()<<std::endl;
      std::cout<<"rpm values: " <<lm.getRPM() << ", "<<rm.getRPM() << std::endl;      
      MQTTData.setMessage("Speed set to: ");
      MQTTData.appendMessage(std::to_string(lm.getRPM()));});
  
  cmdp.addCommand("decrpm",[&sl,&lm,&rm,&MQTTData]{ ///addition of decrpm command
      lm.decRPM();
      rm.decRPM();
      std::cout<<"rpm decremented by: " <<lm.getdecValue()<<std::endl;
      std::cout<<"rpm value: " <<lm.getRPM() << ", "<<rm.getRPM() <<
	std::endl;
      MQTTData.setMessage("Speed set to:");
      MQTTData.appendMessage(std::to_string(lm.getRPM()));});

}

///Drive commands added when in drive mode 
void addDriveCommands(CommandProcessor &cmdp, SerialLink &sl, rotationMotor &lm, rotationMotor &rm, MQTTDataHandler &MQTTData)
{
  cmdp.addCommand("straight", [&sl,&lm,&rm,&MQTTData](){ ///addition of straight command
      std::cout <<"Going straight" <<std::endl;
      MQTTData.setMessage("Driving straight");
      sl.write(driveDirect(lm.getRPM(),rm.getRPM()));});

  cmdp.addCommand("left", [&sl,&lm,&rm,&MQTTData](){    ///addition of left command
      std::cout <<"Going left" <<std::endl;
      MQTTData.setMessage("Turning left");
      sl.write(drive(lm.getRPM(),10));});
  
  cmdp.addCommand("right", [&sl,&lm,&rm,&MQTTData](){   ///addition of right command
      std::cout <<"Going right" <<std::endl;
      MQTTData.setMessage("Turning right");
      sl.write(drive(rm.getRPM(),-10));});
  
  cmdp.addCommand("reverse", [&sl,&lm,&rm,&MQTTData](){ ///addition of reverse command
      std::cout<<"Going backwards" <<std::endl;
      MQTTData.setMessage("Driving backwards");
      sl.write(driveDirect(-lm.getRPM(),-rm.getRPM()));});

}

///calls the remove command class member function
void removeDriveCommands(CommandProcessor &cmdp)
{
  std::string message;
  cmdp.removeCommand(message = "straight");
  cmdp.removeCommand(message = "left");
  cmdp.removeCommand(message = "right");
  cmdp.removeCommand(message = "reverse");

}

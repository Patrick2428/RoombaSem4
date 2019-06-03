#include "Definitions.h"

///Functions adding commands to CommandProcessor class
///Events linked to MQTT messages/commands are executed here
using namespace std::chrono_literals;
void addCommands(CommandProcessor &cmdp, SerialLink &sl, rotationMotor &lm, rotationMotor &rm, int &RoombaMode, MQTTDataHandler &MQTTData)
{
 
 ///Commands definitions with lambda function implementations
  cmdp.addCommand("help", [&MQTTData, &RoombaMode](){
      RoombaMode = 0;
      MQTTData.setMessage("MODES: drive, clean, reset, dock, battle"); });
    
  cmdp.addCommand("idle", [&MQTTData](){
      std::cout<<"Waiting for command"<<std::endl;
      MQTTData.setMessage("Idle mode: waiting for command");});
  
  cmdp.addCommand("drive", [&RoombaMode,&MQTTData](){RoombaMode = 1;
      std::cout << "Driving mode selected" <<std::endl;
      std::cout << "Enter driving direction" << std::endl;
      MQTTData.setMessage("Driving mode: waiting for direction");});
 
  cmdp.addCommand("reset", [&RoombaMode,&MQTTData](){RoombaMode = 2;
      std::cout << "device in reset mode" <<std::endl;
      MQTTData.setMessage("Reset mode: Resetting Roomba");});
  
  cmdp.addCommand("clean", [&RoombaMode,&MQTTData](){RoombaMode = 3;
      std::cout<<"device in clean mode" <<std::endl;
      MQTTData.setMessage("Clean mode: Cleaning dust");});
  
  cmdp.addCommand("dock", [&RoombaMode, &MQTTData](){RoombaMode = 4;
      std::cout<<"device in dock mode" <<std::endl;
      MQTTData.setMessage("Dock mode: searching for docking station");});

  ///When playing and storing songs on the roomba some process time has to be implement before executing other commands
  cmdp.addCommand("battle", [&RoombaMode, &sl,&MQTTData](){RoombaMode = 5;
      sl.write(addSong(0));
      std::this_thread::sleep_for(0.2s);
      sl.write(addSong(1));
      std::this_thread::sleep_for(0.2s);
      sl.write(addSong(2));
      std::this_thread::sleep_for(0.2s);
      std::cout<<"device in battle mode" <<std::endl;
      MQTTData.setMessage("Battle mode: get ready for destruction");});
  
  cmdp.addCommand("stop", [&sl,&lm,&rm,&MQTTData](){
      std::cout<<"stopped"<<std::endl;
      sl.write(driveDirect(0, 0));
      MQTTData.setMessage("Stopping");});
  
  cmdp.addCommand("incrpm",[&sl,&lm,&rm,&MQTTData]{lm.incRPM();
      rm.incRPM();
      std::cout<<"rpm incremented by: " <<lm.getincValue()<<std::endl;
      std::cout<<"rpm values: " <<lm.getRPM() << ", "<<rm.getRPM() << std::endl;      
      MQTTData.setMessage("Speed set to: ");
      MQTTData.appendMessage(std::to_string(lm.getRPM()));});
  
  cmdp.addCommand("decrpm",[&sl,&lm,&rm,&MQTTData]{
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
  cmdp.addCommand("straight", [&sl,&lm,&rm,&MQTTData](){
      std::cout <<"Going straight" <<std::endl;
      MQTTData.setMessage("Driving straight");
      sl.write(driveDirect(lm.getRPM(),rm.getRPM()));});

  cmdp.addCommand("left", [&sl,&lm,&rm,&MQTTData](){
      std::cout <<"Going left" <<std::endl;
      MQTTData.setMessage("Turning left");
      sl.write(drive(lm.getRPM(),10));});
  
  cmdp.addCommand("right", [&sl,&lm,&rm,&MQTTData](){
      std::cout <<"Going right" <<std::endl;
      MQTTData.setMessage("Turning right");
      sl.write(drive(rm.getRPM(),-10));});
  
  cmdp.addCommand("reverse", [&sl,&lm,&rm,&MQTTData](){
      std::cout<<"Going backwards" <<std::endl;
      MQTTData.setMessage("Driving backwards");
      sl.write(driveDirect(-lm.getRPM(),-rm.getRPM()));});

}

void removeDriveCommands(CommandProcessor &cmdp)
{
  std::string message;
  cmdp.removeCommand(message = "straight");
  cmdp.removeCommand(message = "left");
  cmdp.removeCommand(message = "right");
  cmdp.removeCommand(message = "reverse");

}

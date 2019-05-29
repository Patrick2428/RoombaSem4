#include "Definitions.h"

using namespace std::chrono_literals;
void addCommands(CommandProcessor &cmdp, SerialLink &sl, rotationMotor &lm, rotationMotor &rm, int &RoombaMode)
{
 //Commands definitions
  cmdp.addCommand("idle", [](){
      std::cout<<"Waiting for command"<<std::endl;});
  cmdp.addCommand("drive", [&RoombaMode,&sl](){RoombaMode = 1;
      std::cout << "Driving mode selected" <<std::endl;
      sl.write(playSong(2));
      std::this_thread::sleep_for(2s);
      std::cout << "Enter driving direction" << std::endl;});
  cmdp.addCommand("reset", [&RoombaMode](){RoombaMode = 2;
      std::cout << "device in reset mode" <<std::endl;});
  cmdp.addCommand("clean", [&RoombaMode](){RoombaMode = 3;
      std::cout<<"device in clean mode" <<std::endl;});
  cmdp.addCommand("dock", [&RoombaMode](){RoombaMode = 4;
      std::cout<<"device in dock mode" <<std::endl;});
  cmdp.addCommand("battle", [&RoombaMode, &sl](){RoombaMode = 5;
      sl.write(addSong(0));
      std::this_thread::sleep_for(0.5s);
      sl.write(addSong(1));
      std::this_thread::sleep_for(0.5s);
      std::cout<<"device in battle mode" <<std::endl;});
  cmdp.addCommand("straight", [&sl,&lm,&rm](){
      std::cout <<"Going straight" <<std::endl;
      sl.write(driveDirect(lm.getRPM(),rm.getRPM()));});
  cmdp.addCommand("left", [&sl,&lm,&rm](){
      std::cout <<"Going left" <<std::endl;
      sl.write(drive(lm.getRPM(),10));});
  cmdp.addCommand("right", [&sl,&lm,&rm](){
      std::cout <<"Going right" <<std::endl;
      sl.write(drive(rm.getRPM(),-10));});
  cmdp.addCommand("reverse", [&sl,&lm,&rm](){
      std::cout<<"Going backwards" <<std::endl;
      sl.write(driveDirect(-lm.getRPM(),-rm.getRPM()));});
  cmdp.addCommand("stop", [&sl,&lm,&rm](){
      std::cout<<"stopped"<<std::endl;
      sl.write(driveDirect(0, 0));});
  cmdp.addCommand("incrpm",[&sl,&lm,&rm]{lm.incRPM();
      rm.incRPM();
      std::cout<<"rpm incremented by: " <<lm.getincValue()<<std::endl;
      std::cout<<"rpm values: " <<lm.getRPM() << ", "<<rm.getRPM() <<
      std::endl;});
  cmdp.addCommand("decrpm",[&sl,&lm,&rm]{
      lm.decRPM();
      rm.decRPM();
      std::cout<<"rpm decremented by: " <<lm.getdecValue()<<std::endl;
      std::cout<<"rpm value: " <<lm.getRPM() << ", "<<rm.getRPM() <<
      std::endl;});

}

#include "statemachine.h"
#include "OpenInterfaceConfig.h"
#include "SerialLink.h"

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>

using namespace std::chrono_literals;

void sendsignal(const std::string &signal, SerialLink &sl, bool driveMode)
{
  
  if(driveMode)
    {
       if(signal == "straight")
	 {
	   std::cout <<"Going straight" <<std::endl;
	   sl.write(driveDirect(50,50));
	 }
       else if(signal == "right")
	 {
	   std::cout <<"Going right" <<std::endl;
	   sl.write(driveDirect(0,50));
	 }
       else if(signal == "left")
	 {
	   std::cout <<"Going left" <<std::endl;
	   sl.write(driveDirect(50,0));
	 }
       else if(signal == "reverse")
	 {
	   std::cout<<"Going backwards" <<std::endl;
	   sl.write(driveDirect(-50,-50));
	 }
    }
  else
    {     
	  sl.write(driveDirect(0, 0));
    }
  
}

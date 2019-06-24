/** @file */
///\brief Sensehat function
///Executes the sense hat python codes by forking and using execlp()
#include "Definitions.h"

void printOnSenseHat(MQTTDataHandler &MQTTData)
{
  pid_t Child;

  Child = fork();

  switch(Child){
  case -1:
    printf("Can't fork the parent process");
    exit(1);
    break;
  case 0:
    execlp("/usr/bin/python", "/home/pi/examples/python-sense-hat/commands.py", "/home/pi/examples/python-sense-hat/commands.py",MQTTData.getData(), NULL);
    printf("test\n");
    exit(1);
    break;
  default:
    break;
  }
  
  wait(NULL);
  printf("All children have finished\n\n");


}


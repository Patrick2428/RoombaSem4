/** @file */
///\brief CommandProcessor class initialisiation for handeling commands and link them to serial Interface

#ifndef COMMANDPROCESSOR_H_
#define COMMANDPROCESSOR_H_

#include <map>
#include <iostream>
#include <functional>
#include <iterator>
#include <algorithm>
#include <string>
#include "MQTTDataHandler.h"

class CommandProcessor
{
 public:
  ///Constructor and Destructor
  CommandProcessor();

  ///template commandfunction_t for functional function
  using commandfunction_t = std::function<void()>;

  
  void addCommand(const std::string &command,CommandProcessor::commandfunction_t cf);///add command function, to insert a new map command
  void executeCommand(const std::string &command); ///execute command function found in the map
  void removeCommand(const std::string &command);  ///remove command function from the map

 private:
  std::map <std::string, commandfunction_t> commands_;///map data member
  
 

};

#endif 

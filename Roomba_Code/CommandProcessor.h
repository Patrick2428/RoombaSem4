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
  //Constructor and Destructor
  CommandProcessor();

  //template commandfunction_t for functional function
  using commandfunction_t = std::function<void()>;

  //memberfunctions
  void addCommand(const std::string &command,CommandProcessor::commandfunction_t cf);
  void executeCommand(const std::string &command);
  void removeCommand(const std::string &command);

 private:
  std::map <std::string, commandfunction_t> commands_;
  
 

};

#endif 

#include <iostream>
#include "CommandProcessor.h"

///CommandProcessor class member functions to handle commands 

CommandProcessor::CommandProcessor()
{
}

void CommandProcessor::addCommand(const std::string &command,CommandProcessor::commandfunction_t cf)
{
  auto p = commands_.find(command);
  if (p == end(commands_))
    {
      commands_[command] = cf;
    }
  else
    {
      //If a command already exists it shouldn't be added
    }
}

void CommandProcessor::executeCommand(const std::string &command)
{
// p is an iterator
auto p = commands_.find(command);
if (p != end(commands_))
{
auto commandfunc = (*p).second;
commandfunc();
}
else
{
    std::cout<<"Error: command could not be found"<<std::endl;
}

}

void CommandProcessor::removeCommand(const std::string &command)
{
  auto p = commands_.find(command);
  if( p != end(commands_))
    {
      commands_.erase(p);
    }
}

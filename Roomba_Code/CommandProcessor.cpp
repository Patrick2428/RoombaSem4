/** @file */
///\brief CommandProcessor class member functions to handle commands 
#include <iostream>
#include "CommandProcessor.h"

CommandProcessor::CommandProcessor()
{
}

///Adds a command to the map using an iterator to move to the end of the map
void CommandProcessor::addCommand(const std::string &command,CommandProcessor::commandfunction_t cf)
{
  auto p = commands_.find(command);
  if (p == end(commands_))
    {
      commands_[command] = cf;
    }
  else
    {
      ///If a command already exists it shouldn't be added
    }
}

///executes the lambda function linked to the specific command 
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
  ///will not execute if no link is found
    std::cout<<"Error: command could not be found"<<std::endl;
}

}

///removes specific commands from the map. 
void CommandProcessor::removeCommand(const std::string &command)
{
  auto p = commands_.find(command);
  if( p != end(commands_))
    {
      commands_.erase(p);
    }
}

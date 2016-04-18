#include "Command.h"
#include <iostream>

Command::Command(const std::string &name) : redirect(0), name(name)
{

}

Command::~Command()
{
  //If there is a pointer to redirect, delete it
  if(redirect){
    delete redirect;
  }
}

void Command::addArgument(const std::string& arg)
{
  args.push_back(arg);
}


void Command::setInput(const std::string& in)
{
  this->input = in;
}

void Command::setOutput(const std::string& out)
{
  this->output = out;
}

void Command::setRedirect(Command *redirect)
{
  this->redirect = redirect;
}

void Command::setAppend(bool append)
{
  this->append = append;
}


std::ostream& operator<<(std::ostream& out, const Command& cmd)
{
  out << cmd.name;
  out << "";
  for(auto i = cmd.args.begin(); i != cmd.args.end(); i++){
    out << " ";

    out << "\"" << *i << "\"";
  }

  if(cmd.hasOutput()){
    out << " >";
    if(cmd.getAppend()){
      out << ">";
    }
    out << " " << cmd.output;
  }

  if(cmd.hasInput()){
    out << " < ";
    out << cmd.input;
  }

  if(cmd.hasRedirect()){
    out << " | " << *(cmd.redirect);
  }

  return out;
}

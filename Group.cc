#include "Group.h"

Group::Group()
{
  //Nothing :D
}

Group::~Group()
{
  for(auto i = commands.begin(); i != commands.end(); i++){
    Command *p = *i;

    delete p;
  }
}

void Group::addCommand(Command *cmd)
{
  commands.push_back(cmd);
}

std::ostream& operator<<(std::ostream &out, const Group& group)
{
  for(auto i = group.commands.begin(); i != group.commands.end(); i++){
    if(i != group.commands.begin())
      out << " & ";
    Command *cmd = *i;
    out << *cmd;
  }

  return out;
}

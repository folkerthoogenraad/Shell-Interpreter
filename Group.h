#ifndef GROUP_H
#define GROUP_H

#include <vector>
#include <iostream>
#include "Command.h"

/*
 * Group represents a group of commands that can be executed simultaneously. Examples are:
 * ls -all & echo "Some Text!"
 * cat aardappel.txt > output.txt & curl www.google.nl
 *
 * A Group can have 0 or more Commands.
*/
class Group
{
private:
  std::vector<Command*> commands;

public:
  Group();
  ~Group();

  void addCommand(Command*);

  friend std::ostream& operator<<(std::ostream&, const Group&);
  friend class Executer;
};

#endif

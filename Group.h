#ifndef GROUP_H
#define GROUP_H

#include <vector>
#include <iostream>
#include "Command.h"

/*
 * Executes a group of commands simultaniously
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
};

#endif

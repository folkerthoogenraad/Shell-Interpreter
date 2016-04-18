#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <vector>
#include "Group.h"

/*
 * Executes a group of commands simultaniously
*/
class Sequence
{
private:
  std::vector<Group*> groups;

public:
  Sequence();
  ~Sequence();

  void addGroup(Group*);

  friend std::ostream& operator<<(std::ostream&, const Sequence&);
};

#endif

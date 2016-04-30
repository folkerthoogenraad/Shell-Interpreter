#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <vector>
#include "Group.h"

/*
 * Sequence represents a list of Groups that can be executed in order.
 * Examples are:
 * ls -all; cat output.txt
 * echo "Text is cool!" > file.txt ; cat file.txt
 *
 * A Sequence can have 0 or more groups.
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
  friend class Executer;
};

#endif

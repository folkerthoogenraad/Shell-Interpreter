#include "Sequence.h"

Sequence::Sequence()
{

}

Sequence::~Sequence()
{
  for(auto i = groups.begin(); i != groups.end(); i++){
    Group *g = *i;

    delete g;
  }
}

void Sequence::addGroup(Group *g)
{
  groups.push_back(g);
}

std::ostream& operator<<(std::ostream &out, const Sequence& sequence)
{
  for(auto i = sequence.groups.begin(); i != sequence.groups.end(); i++){
    if(i != sequence.groups.begin())
      out << " ; ";
    Group *g = *i;
    out << *g;
  }

  return out;
}

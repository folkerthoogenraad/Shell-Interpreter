#ifndef EXECUTER_H
#define EXECUTER_H

class Sequence;
class Group;
class Command;

/**
 * Executer class is responseable for executing Commands, Groups and Sequences.
*/
class Executer
{
public:
  Executer();
  ~Executer();

  void execute(Sequence *sequence);
  void execute(Group *group);
  void execute(Command *cmd);

private:
  void executeRaw(Command *cmd);
};

#endif

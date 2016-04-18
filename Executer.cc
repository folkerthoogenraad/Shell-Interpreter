#include "Executer.h"

#include "Sequence.h"
#include "Group.h"
#include "Command.h"

#include <unistd.h>
#include <sys/wait.h>

#define EXECUTION_ERROR(STATUS) std::cerr << "Process ended with status " << STATUS << std::endl
#define FORK_ERROR() std::cerr << "Failed to fork process" << std::endl;

Executer::Executer()
{

}

Executer::~Executer()
{

}

/**
  * Executes a sequence of groups, in succession
*/
void Executer::execute(Sequence *sequence)
{
  std::cout << "Executing: " << *sequence << std::endl;

  for(auto i = sequence->groups.begin(); i != sequence->groups.end(); i++){
    Group *group = *i;
    execute(group);
  }
}

/**
  * Executes a group of commands simultaneously
*/
void Executer::execute(Group *group)
{
  std::cout << "Executing group " << *group << std::endl;

  std::vector<int> pids;

  for(auto i = group->commands.begin(); i != group->commands.end(); i++){
    Command *cmd = *i;

    int pid = fork();

    //Child process
    if(pid == 0){
      execute(cmd);
      exit(0);
    }

    //Parent process
    else if(pid > 0){
      //Save this pid to wait for later
      pids.push_back(pid);
    }

    //Fork error
    else{
      FORK_ERROR();
    }
  }

  //Wait for all the created child processes to die :) WHY WON'T THEY DIE
  for(auto i = pids.begin(); i != pids.end(); i++){
    int status;

    //Wait for the created process to end
    waitpid(*i, &status, 0);
    if(status != 0){
      EXECUTION_ERROR(status);
    }
  }
}

/**
  * Executes a command (with redirecting in and output for this command)
*/
void Executer::execute(Command *cmd)
{
  std::cout << "Executing command " << *cmd << std::endl;
}

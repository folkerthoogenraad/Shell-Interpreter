#include "Executer.h"

#include "Sequence.h"
#include "Group.h"
#include "Command.h"

#include <unistd.h>
#include <sys/wait.h> //for waitpid
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define EXECUTION_ERROR(STATUS) std::cerr << "Process ended with status " << STATUS << std::endl
#define FORK_ERROR() std::cerr << "Failed to fork process" << std::endl;
#define PIPE_ERROR() std::cerr << "Failed to create pipe" << std::endl;
#define OPEN_ERROR(MESSAGE) std::cerr << "File error: " << MESSAGE << std::endl;

/*
 * Open a file with the given permissions
*/
// int openFile(const char *file, mode_t permission)
// {
//   int fd = open(file, permission);
//   if(fd < 0){
//     fd = creat(file, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
//     close(fd);
//     fd = open(file, permission);
//   }
//
//   if(fd < 0){
//     OPEN_ERROR("Invalid file " << file);
//   }
//   return fd;
// }

char *const* toCharPP(const std::vector<std::string> &source)
{
  //TODO check this for memory issues, I think this leaks
  std::vector<char*> *cstrings = new std::vector<char*>();

  for(size_t i = 0; i < source.size(); ++i){
    cstrings->push_back(const_cast<char*>(source[i].c_str()));
  }

  cstrings->push_back(0);

  return &(*cstrings)[0];
}

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
  std::vector<int> pids;

  for(auto i = group->commands.begin(); i != group->commands.end(); i++){
    Command *cmd = *i;

    int pid = fork();

    //Child process
    if(pid == 0){
      executeRaw(cmd);
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
  int pid = fork();

  //Child process
  if(pid == 0){
    executeRaw(cmd);
  }

  //Parent process
  else if(pid > 0){
    int status;

    waitpid(pid, &status, 0);

    if(status != 0){
      EXECUTION_ERROR(status);
    }
  }

  //Error
  else{
    FORK_ERROR();
  }
}

/*
 * Executes Command on this process
*/
void Executer::executeRaw(Command *cmd)
{
  //Get the input from file
  if(cmd->hasInput()){
    int fd = open(cmd->input.c_str(), O_RDONLY);

    if(fd < 0){
      OPEN_ERROR(cmd->input);
      return;
    }

    dup2(fd, STDIN_FILENO);
    close(fd);
  }

  //Write the output to file
  if(cmd->hasOutput()){
    mode_t per = O_WRONLY | O_CREAT | O_TRUNC;
    if(cmd->getAppend()){
      per |= O_APPEND;
    }

    int fd = open(cmd->output.c_str(), per, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    if(fd < 0){
      OPEN_ERROR(cmd->output);
      return;
    }

    dup2(fd, STDOUT_FILENO);
    close(fd);
  }

  //Write the output to other process
  //TODO let the redirection be done by an overhead (for example, the group or something. I'm not sure where yet, but currently the gandchild sometimes isn't finished when teh parent is, and thus the output will not be correct)
  if(cmd->hasRedirect()){
    int p[2];
    int status = pipe(p);

    if(status == -1){
      PIPE_ERROR();
      return;
    }

    int pid = fork();

    if(pid < 0){
      FORK_ERROR();
      return;
    }

    //Execute order 66
    if(pid == 0){
      dup2(p[0], STDIN_FILENO);
      close(p[0]);
      close(p[1]);
      //TODO maybe seround this by forks?
      executeRaw(cmd->redirect);
    }

    else{
      dup2(p[1], STDOUT_FILENO);
      close(p[0]);
      close(p[1]);
    }
  }

  //Execute itself
  //Maybe seround this by forks? Wait for newly created pid afterwards?
  execvp(cmd->name.c_str(), toCharPP(cmd->args));
}

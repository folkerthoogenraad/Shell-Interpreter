#include <iostream>
#include <sstream>

#include "Lexer.h"
#include "Parser.h"
#include "Group.h"
#include "Executer.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#include <unistd.h>
#include <signal.h>

void interupt_signal(int sig)
{
  std::cout << std::endl << ANSI_COLOR_GREEN << "..> " << ANSI_COLOR_RESET;
  std::cout.flush();
}

/*

self notes:

a b c       execute a with arguments b and c
a & b       executes a and b at the same time
a ; b       executes a and b in succession
a | b       sends output from a to b
a > b       executes a and writes output to file b
a < b       executes a and reads input from file b

*/

void execute(std::string line);

int main(int argc, char **argv){

  signal(SIGINT, interupt_signal);

  std::cerr << ANSI_COLOR_RED;

  std::cout << ANSI_COLOR_CYAN << "Apryx Shell XP [Version 1.0.0000]" << std::endl;
  std::cout << "(C) Copyright 2016-2016 Apryx Corp." << std::endl;
  std::cout << "Type :help for help with commands" << std::endl;
  std::cout << ANSI_COLOR_RESET << std::endl;

  // execute("echo hans | grep an > output.txt ; cat output.txt");

  bool running = true;
  char cwd[1024];
  while(running){
    getcwd(cwd, 1024);
    std::cout << ANSI_COLOR_GREEN << "C:" << cwd << "> " << ANSI_COLOR_RESET;

    std::string line;
    getline(std::cin, line);

    if(line == ":quit"){
      exit(0);
    }

    else if(line == ":help"){
      std::cout << ":help - for help" << std::endl;
      std::cout << ":reboot - to reboot the terminal (if you remake and stuff)" << std::endl;
      std::cout << ":quit - to shut down the terminal" << std::endl;
    }

    else if(line == ":reboot"){
      execvp(argv[0], argv);
    }

    else{
      execute(line);
    }
  }
}

void execute(std::string line)
{
  std::stringstream stream(line);

  Lexer lexer(&stream);
  lexer.setIgnoreWhitespace(true);

  Parser parser(&lexer);

  Sequence *sequence = parser.parse();

  if(lexer.hasError()){
    std::cout << "Lexical error occurred. Please check your spelling" << std::endl;
    return;
  }

  if(parser.hasError()){
    std::cout << "Parsing error occurred. Please check your grammar" << std::endl;
    delete sequence;
    return;
  }

  Executer executer;

  executer.execute(sequence);

  //Don't forget to clean up!
  delete sequence;
}

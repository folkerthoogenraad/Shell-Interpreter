#include <iostream>
#include <sstream>

#include "Lexer.h"
#include "Parser.h"
#include "Group.h"
#include "Executer.h"

#include <unistd.h>

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
  std::cout << "Apryx Shell XP [Version 1.0.0000]" << std::endl;
  std::cout << "(C) Copyright 2016-2016 Apryx Corp." << std::endl;
  std::cout << std::endl;

  execute("echo hans | grep an > output.txt ; cat output.txt");

  bool running = true;
  while(running){
    std::cout << "C:/> ";

    std::string line;
    getline(std::cin, line);

    if(line == ":quit"){
      exit(0);
    }

    else if(line == ":help"){
      std::cout << "This is very helpful, isn't it?" << std::endl;
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

  Executer executer;

  executer.execute(sequence);

  //Don't forget to clean up!
  delete sequence;
}

#include <iostream>
#include <sstream>

#include "Lexer.h"
#include "Parser.h"

/*

self notes:

a b c       execute a with arguments b and c
a & b       executes a and b at the same time
a ; b       executes a and b in succession
a | b       sends output from a to b



*/


int main(){
  std::stringstream stream("ls -all -f -v | hans.txt");

  Lexer lexer(&stream);
  lexer.setIgnoreWhitespace(true);

  Parser parser(&lexer);

  parser.parse();

}

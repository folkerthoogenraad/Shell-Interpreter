#include <iostream>
#include <sstream>

#include "Lexer.h"
#include "Parser.h"
#include "Group.h"

/*

self notes:

a b c       execute a with arguments b and c
a & b       executes a and b at the same time
a ; b       executes a and b in succession
a | b       sends output from a to b
a > b       executes a and writes output to file b
a < b       executes a and reads input from file b

*/


int main(){
  std::stringstream stream("echo \"This is some random text\" > hans.txt ; Pizza is nice <3");

  Lexer lexer(&stream);
  lexer.setIgnoreWhitespace(true);

  Parser parser(&lexer);

  Sequence *sequence = parser.parse();

  std::cout << *sequence << std::endl;

}

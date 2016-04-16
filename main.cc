#include <iostream>
#include <sstream>

#include "Lexer.h"


int main(){
  std::stringstream stream("token > token2 >> token3 < token a b > token b | c");

  Lexer lexer(&stream);
  lexer.setIgnoreWhitespace(true);

  while(!lexer.isDone()){
    Token *t = lexer.next();

    if(t != 0){
      std::cout << *t << std::endl;
      delete t;
    }

  }
}

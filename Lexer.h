#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include "Token.h"

class Lexer
{
private:
  //Lexer will NOT clean these pointers!
  std::istream *in; //Input to read from
  Token* c;         //current token, will be consumed with next!

  char currentCharacter;
  int line = 1; //Stupid humans start couning at one
  int charIndex = 0;

  bool ignoreWhitespace = true;

  bool done;
  bool error = false;

public:
  Lexer(std::istream *in);
  ~Lexer();

  //Lexer will not clean up these tokens
  Token *next();
  Token *current();

  inline char currentChar();
  inline char nextChar();
  inline int  currentLine();
  inline bool hasError(){return error;}

  inline void setIgnoreWhitespace(bool w){ignoreWhitespace = w;}

  bool isDone();

};

#endif

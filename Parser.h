#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"

class Parser
{
private:
  Lexer *lexer;

public:
  Parser(Lexer *lex);
  ~Parser();
};

#endif

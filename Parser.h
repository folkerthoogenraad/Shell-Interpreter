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

  inline void setLexer(Lexer *lex){
    lexer = lex;
  }

  inline Lexer *getLexer(){
    return lexer;
  }

  void parse();

private:
  void parseExpression();
};

#endif

#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"
#include "Command.h"

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

  Command* parse();

private:
  Command* parseCommand();
  Command* parseSequence();
};

#endif

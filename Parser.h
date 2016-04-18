#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"
#include "Command.h"
#include "Group.h"
#include "Sequence.h"

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

  Sequence* parse();

private:
  Sequence* parseSequence();
  Group* parseGroup();
  Command* parseChain();
  Command* parseCommand();
};

#endif

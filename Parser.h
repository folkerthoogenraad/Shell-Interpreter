#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"
#include "Command.h"
#include "Group.h"
#include "Sequence.h"

/**
 * The parser parses input from the lexer. It generates the abstract syntax
 * tree. The AST in this case is the Sequence, Group and Command.
*/
class Parser
{
private:
  Lexer *lexer;
  bool error = false;

public:
  Parser(Lexer *lex);
  ~Parser();

  inline void setLexer(Lexer *lex){
    lexer = lex;
  }

  inline Lexer *getLexer(){
    return lexer;
  }

  inline bool hasError(){return error;}

  Sequence* parse();

private:
  Sequence* parseSequence();
  Group* parseGroup();
  Command* parseChain();
  Command* parseCommand();
};

#endif

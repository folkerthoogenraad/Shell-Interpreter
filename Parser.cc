#include "Parser.h"
#include <vector>

#define UNEXPECTED_TOKEN(GOT, EXPECTED) std::cerr << "Unexpected token : " << GOT << ". Expected token of type " << EXPECTED << std::endl
#define SYNTAX_ERROR(ERROR) std::cerr << "Syntax error: " << ERROR << std::endl

Parser::Parser(Lexer *lex)
  : lexer(lex)
{
  //Set up the lexer, that the current == the first token (AKA -1 to 0)
  lexer->next();
}

Parser::~Parser()
{
  //Do nothing again
}

Sequence* Parser::parse()
{
  return parseSequence();
}

Sequence* Parser::parseSequence()
{
  Sequence *s = new Sequence();

  while(true){
    Group *p = parseGroup();

    if(p == 0)
      break;

    s->addGroup(p);

    Token *token = lexer->current();

    if(token->getType() == Token::SEMICOLON){
      delete token;
      lexer->next();
    }else{
      break;
    }
  }

  return s;
}

Group* Parser::parseGroup()
{
  Group *g = new Group();

  while(true){
    Command *cmd = parseChain();

    if(cmd == 0)
      break;

    g->addCommand(cmd);

    Token *token = lexer->current();

    if(token->getType() == Token::AND){
      delete token;
      lexer->next();
    }else{
      break;
    }
  }

  return g;
}

Command *Parser::parseChain()
{
  Command *lhs = parseCommand();

  Token *token = lexer->current();

  if(token == 0)
    return lhs;

  if(token->getType() == Token::INPUT){

    //Get the token after stuff
    Token *file = lexer->next();

    //If its not a file name
    if(file->getType() != Token::LITERAL){
      UNEXPECTED_TOKEN(*token, Token::LITERAL);
      return 0;
    }

    lhs->setInput(file->getData());

    delete token;
    delete file;

    //Consume
    token = lexer->next();
  }

  if(token == 0)
    return lhs;

  if(token->getType() == Token::PIPE){
    delete token;

    lexer->next();

    Command *rhs = parseChain();

    if(!rhs){
      SYNTAX_ERROR("Unconnected Pipe!");
      return 0;
    }

    lhs->setRedirect(rhs);
  }

  else if(token->getType() == Token::OUTPUT || token->getType() == Token::APPEND){
    Token *file = lexer->next();

    if(file->getType() != Token::LITERAL){
      UNEXPECTED_TOKEN(*token, Token::LITERAL);
      return 0;
    }

    lhs->setOutput(file->getData());
    lhs->setAppend(token->getType() == Token::APPEND);

    delete token;
    delete file;

    //Consume
    lexer->next();
  }

  return lhs;
}

Command *Parser::parseCommand()
{
  Token *token = lexer->current();

  if(token->getType() != Token::LITERAL){
    UNEXPECTED_TOKEN(*token, Token::LITERAL);
    delete token;
    return 0;
  }

  Command *cmd = new Command(token->getData());

  //Clean up the current token
  delete token;

  while((token = lexer->next()) && token->getType() == Token::LITERAL){
    cmd->addArgument(token->getData());

    //Clean up the argument
    delete token;
  }

  return cmd;
}
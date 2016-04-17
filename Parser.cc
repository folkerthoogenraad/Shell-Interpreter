#include "Parser.h"
#include <vector>

#define UNEXPECTED_TOKEN(GOT, EXPECTED) std::cerr << "Unexpected token : " << GOT << ". Expected token of type " << EXPECTED << std::endl;

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

void Parser::parse()
{
  //Right hand side
  parseExpression();

  Token *token = lexer->current();

  if(token == 0)
    return;

  if(token->getType() == Token::PIPE){
    std::cout << "Pipe this to: " << std::endl;
    lexer->next();
    parseExpression();
  }
  else if(token->getType() == Token::OUTPUT){
    std::cout << "Output to : " << std::endl;
    Token *file = lexer->next();

    if(file->getType() != Token::LITERAL){
      UNEXPECTED_TOKEN(*token, Token::LITERAL);
      return;
    }

    std::cout << file->getData() << std::endl;

    lexer->next();

  }
}

void Parser::parseExpression()
{
  Token *token = lexer->current();

  if(token->getType() != Token::LITERAL){
    UNEXPECTED_TOKEN(*token, Token::LITERAL);
    return;
  }

  std::string name = token->getData();

  std::vector<std::string> arguments;

  while((token = lexer->next()) && token->getType() == Token::LITERAL){
    arguments.push_back(token->getData());
  }

  std::cout << "Executing " << name << " with arguments ";
  for(auto i = arguments.begin(); i != arguments.end(); i++){
    std::cout << *i << ", ";
  }

  std::cout << std::endl;
}

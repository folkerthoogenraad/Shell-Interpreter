#include "Token.h"
#include <iostream>

Token::Token(TokenType type, int line, int charIndex, std::string data)
  : charIndex(charIndex), line(line), type(type), data(data)
{
  //Do nothing
}

Token::~Token()
{
  //Do nothing
}


std::ostream& operator<<(std::ostream& out, const Token& token)
{
  //Should also print other stuff, but what ever
  return out << token.type << "\t("<< token.line << ':' << token.charIndex << ")\t" << token.data;
}

std::ostream& operator<<(std::ostream& out, const Token::TokenType &type)
{
  switch(type){
  case Token::LITERAL:
    out << "LITERAL";
    break;
  case Token::PIPE:
    out << "PIPE";
    break;
  case Token::INPUT:
    out << "INPUT";
    break;
  case Token::OUTPUT:
    out << "OUTPUT";
    break;
  case Token::APPEND:
    out << "APPEND";
    break;
  case Token::WHITESPACE:
    out << "WHITESPACE";
    break;
  default:
    out << "UNKNOWN";
    break;
  }
  return out;
}

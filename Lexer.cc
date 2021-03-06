#include "Lexer.h"
#include <sstream>

inline bool isCharacter(char c)
{
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

inline bool isDigit(char c)
{
  return c >= '0' && c <= '9';
}

inline bool isSpecial(char c)
{
  return c == '?' || c == '#' || c == '/' || c == '-' || c == '.' || c == '*' || c == '@' || c == ':'
  || c == '%' || c == '!' || c == '^' || c == ',' || c == '+' || c == '(' || c == ')' || c == '`' || c == '\''
  || c == '[' || c == ']' || c == '{' || c == '}' || c == '=' || c == '$' || c == '_' || c == '~';
}

inline bool isLiteral(char c)
{
  return isDigit(c) || isCharacter(c) || isSpecial(c);
}

inline bool isAnd(char c)
{
  return c == '&';
}

inline bool isSemicolon(char c)
{
  return c == ';';
}

inline bool isWhitespace(char c)
{
  return c == '\n' || c == '\r' || c == '\t' || c == ' ';
}

inline bool isQuotation(char c)
{
  return c == '"';
}

inline bool isPipe(char c)
{
  return c == '|';
}

inline bool isInput(char c)
{
  return c == '<';
}

inline bool isOutput(char c)
{
  return c == '>';
}

inline bool isEscape(char c)
{
  return c == '\\';
}

Lexer::Lexer(std::istream *in) : in(in), c(0), currentCharacter(0), done(false)
{
  //Set up to read the first char ready
  nextChar();
}

Lexer::~Lexer()
{
  //Do nothing :)
}

char Lexer::currentChar()
{
  return currentCharacter;
}

char Lexer::nextChar()
{
  std::istream &input = *in;

  if(currentCharacter == '\n'){
    line++;
    charIndex = 0;
  }

  //Tell it we need the next char
  charIndex++;

  if(input){
    currentCharacter = input.get();

    if(!input){
      done = true;
    }
  }else{
    currentCharacter = 0;
    done = true;
  }

  return currentChar();
}

int Lexer::currentLine()
{
  return line;
}

Token *Lexer::next()
{
  //if we are done
  if(done){
    return 0;
  }

  //Get the current character

  if(isLiteral(currentChar()) || isEscape(currentChar())){
    std::stringstream output;

    //TODO test this
    if(isEscape(currentChar())){
      nextChar();

      if(done){
        c = 0;
        return 0;
      }
    }

    output << currentChar();

    //Last character in the stream is by definition not literal (0-9 A-z)
    while(isLiteral(nextChar()) || isEscape(currentChar())){
      if(isEscape(currentChar())){
        nextChar();
        if(done){
          break;
        }
      }
      output << currentChar();
    }

    c = new Token(Token::LITERAL, line, charIndex, output.str());

    return c;
  }

  //If it serounded by quotations
  else if(isQuotation(currentChar())){
    std::stringstream output;

    //while it does not find the quotation, and the input is ready to read
    //and the while
    while(!isQuotation(nextChar()) && !done){
      if(isEscape(currentChar())){

        nextChar();
        if(!done){
          if(isQuotation(currentChar())){
            //Append " only
            output << '"';
          }else{
            //Append both
            output << '\\' << currentChar();
          }
        }else{
          //Append this last char anyway, it doesn't really matter
          output << '\\';
        }
      }else{
        output << currentChar();
      }
    }

    //Consume the "

    nextChar();

    //Create the token
    c = new Token(Token::LITERAL, line, charIndex, output.str());

    //Return the token
    return c;
  }

  else if(isWhitespace(currentChar())){
    std::stringstream output;
    output << currentChar();

    //Last character in the stream is by definition not literal (0-9 A-z)
    while(isWhitespace(nextChar())){
      output << currentChar();
    }

    c = new Token(Token::WHITESPACE, line, charIndex, output.str());

    if(ignoreWhitespace){
      return next();
    }else{
      return c;
    }
  }

  else if(isInput(currentChar())){
    std::stringstream output;
    output << currentChar();

    //Consume token
    nextChar();

    c = new Token(Token::INPUT, line, charIndex, output.str());
    return c;
  }

  else if(isOutput(currentChar())){
    std::stringstream output;
    output << currentChar();

    //Check if the next is >, for >>
    if(isOutput(nextChar())){
      output << currentChar();
      nextChar(); //Consume the rest of append
      c = new Token(Token::APPEND, line, charIndex, output.str());
    }else{
      c = new Token(Token::OUTPUT, line, charIndex, output.str());
    }

    return c;
  }

  else if(isPipe(currentChar())){
    std::stringstream output;
    output << currentChar();

    //Consume token
    nextChar();

    c = new Token(Token::PIPE, line, charIndex, output.str());
    return c;
  }

  else if(isSemicolon(currentChar())){
    std::stringstream output;
    output << currentChar();

    //Consume token
    nextChar();

    c = new Token(Token::SEMICOLON, line, charIndex, output.str());
    return c;
  }

  else if(isAnd(currentChar())){
    std::stringstream output;
    output << currentChar();

    //Consume token
    nextChar();

    c = new Token(Token::AND, line, charIndex, output.str());
    return c;
  }


  else{
    error = true;
    std::cout << "Unknown character '" << currentChar() << "' at " << line << ":" << charIndex << std::endl;
    nextChar();
    c = 0;
    return c;
  }
}

Token *Lexer::current(){
  return c;
}

bool Lexer::isDone(){
  return done;
}

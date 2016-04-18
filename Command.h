#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>
#include "Token.h"

class Command
{
private:
  std::string input;
  std::string output;
  Command *redirect;
  bool append;

  std::string name;
  std::vector<std::string> args;

public:
  Command(const std::string&);

  void addArgument(const std::string&);
  void setInput(const std::string&);
  void setOutput(const std::string&);
  void setRedirect(Command *redirect);
  void setAppend(bool append);

  inline bool getAppend() const {return append;}
  inline bool hasOutput() const {return output.length() > 0;}
  inline bool hasInput() const {return input.length() > 0;}
  inline bool hasRedirect() const {return redirect != 0;}

  ~Command();

  friend std::ostream& operator<<(std::ostream&, const Command&);
  friend class Executer;
};

#endif

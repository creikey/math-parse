#ifndef HPP_TOKENIZER
#define HPP_TOKENIZER

#include "common.hpp"
#include <vector>
#include <string>

enum class TokenType { SYMBOL, NUMBER };

class Token {
public:
  virtual std::string getString() = 0;
  virtual cmn::pos getPos() = 0;
  virtual TokenType getType() = 0;
};

class Tokenizer {
public:
  Tokenizer();
  ~Tokenizer();
  std::vector<Token> Tokenize(std::string);
private:
  cmn::pos curPos;
};

#endif

#ifndef HPP_TOKENIZER
#define HPP_TOKENIZER

#include "common.hpp"
#include <array>
#include <cstring>
#include <string>
#include <vector>

enum class TokenType { Symbol, Number };

class Token {
public:
  virtual std::string getString() = 0;
  virtual cmn::pos getPos() = 0;
  virtual TokenType getType() = 0;
  static Token *parseToken(cmn::pos, std::string);
};

class NumberToken : public Token {
public:
  std::string getString();
  cmn::pos getPos();
  TokenType getType();
  NumberToken();
  NumberToken(cmn::pos *, int);
  NumberToken(cmn::pos *, std::string);
  static bool isNumber(char);

private:
  int val;
  cmn::pos myPos;
  std::string myString;
  static int numDigits(int32_t x);
  const TokenType myType = TokenType::Number;
};

class SymbolToken : public Token {
public:
  enum class SymbolType { RightShift, LeftShift, Plus, Empty, Unknown };
  std::string getString();
  cmn::pos getPos();
  TokenType getType();
  SymbolToken();
  SymbolToken(cmn::pos *, SymbolType);
  SymbolToken(cmn::pos *, std::string);
  SymbolType getSymbolType();
  static bool isSymbol(char);
  static const constexpr std::array<const char *, 4> symbolNames{
      {[(int)SymbolType::RightShift] = ">>",
       [(int)SymbolType::LeftShift] = "<<", [(int)SymbolType::Plus] = "+",
       [(int)SymbolType::Empty] = ""}};
  // TODO use compile time expression for this hacky var
  const static int maxNameLen =
      strlen(SymbolToken::symbolNames[(int)SymbolType::RightShift]);

private:
  cmn::pos myPos;
  SymbolType mySymbolType;
  const TokenType myType = TokenType::Symbol;
};

class Tokenizer {
public:
  Tokenizer();
  ~Tokenizer();
  std::vector<Token *> Tokenize(std::string);
  void setPos(cmn::pos);

private:
  cmn::pos curPos;
};

#endif

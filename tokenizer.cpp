#include "tokenizer.hpp"
#include <cstring>
#include <limits.h>

Token *Token::parseToken(cmn::pos inPos, std::string inString) {
  Token *toReturn;
  for (auto i = inString.begin() + inPos.column; i < inString.end(); i++) {
    if (NumberToken::isNumber(*i)) {
      toReturn = new NumberToken(&inPos, inString);
    } else if (SymbolToken::isSymbol(*i)) {
      toReturn = new SymbolToken(&inPos, inString);
    }
  }
  return toReturn;
};

std::string NumberToken::getString() { return this->myString; };

cmn::pos NumberToken::getPos() { return this->myPos; };

TokenType NumberToken::getType() { return this->myType; };

NumberToken::NumberToken() {
  this->val = 0;
  this->myPos = cmn::pos();
  this->myString = "0";
};

NumberToken::NumberToken(cmn::pos *inPos, std::string inString) {
  std::string toSet = "";
  for (auto i = inString.begin() + inPos->column;
       i != inString.end() && NumberToken::isNumber(*i); i++) {
    toSet.append(1, *i);
  }
  // Set the current numbers position for errors
  this->myPos = *inPos;
  // Move over the tokenizer's position by the length of the number
  inPos->column += toSet.size();
  // Set this numbertoken's value from the string that was found
  this->val = stoi(toSet);
  this->myString = toSet;
};

NumberToken::NumberToken(cmn::pos *inPos, int inInt) {
  // Set the current numbers position for errors
  this->myPos = *inPos;
  // set the number to the input number
  this->val = inInt;
  // set the string to cache stoi output
  this->myString = std::to_string(inInt);
  // shift over the input position by the number of digits
  inPos->column += NumberToken::numDigits(inInt);
};

bool NumberToken::isNumber(char inChar) {
  if (inChar > '0' && inChar < '9') {
    return true;
  }
  return false;
};

// Code by @Vitali on stackoverflow.com
// partial specialization optimization for 32-bit numbers
int NumberToken::numDigits(int32_t x) {
  if (x == INT_MIN)
    return 10 + 1;
  if (x < 0)
    return numDigits(-x) + 1;

  if (x >= 10000) {
    if (x >= 10000000) {
      if (x >= 100000000) {
        if (x >= 1000000000)
          return 10;
        return 9;
      }
      return 8;
    }
    if (x >= 100000) {
      if (x >= 1000000)
        return 7;
      return 6;
    }
    return 5;
  }
  if (x >= 100) {
    if (x >= 1000)
      return 4;
    return 3;
  }
  if (x >= 10)
    return 2;
  return 1;
};

std::string SymbolToken::getString() {
  return this->symbolNames[(int)this->mySymbolType];
};

cmn::pos SymbolToken::getPos() { return this->myPos; };

TokenType SymbolToken::getType() { return this->myType; };

SymbolToken::SymbolToken() {
  this->myPos = cmn::pos();
  this->mySymbolType = SymbolType::Empty;
}

SymbolToken::SymbolToken(cmn::pos *inPos, SymbolType inType) {
  this->mySymbolType = inType;
  this->myPos = *inPos;
  inPos->column += strlen(this->symbolNames[(int)inType]);
}

SymbolToken::SymbolToken(cmn::pos *inPos, std::string inString) {
  std::string buff = "";
  SymbolToken::SymbolType getType = SymbolToken::SymbolType::Unknown;
  while (buff.size() <= SymbolToken::maxNameLen) {

    char toAppend = inString[inPos->column + buff.size()];
    if (SymbolToken::isSymbol(toAppend)) {
      buff.append(1, toAppend);
      for (auto i = SymbolToken::symbolNames.begin();
           i != SymbolToken::symbolNames.end(); i++) {
        if (*i == buff) {
          getType =
              (SymbolToken::SymbolType)(i - SymbolToken::symbolNames.begin());
          break;
        }
      }
    } else {
    }
  }
}

SymbolToken::SymbolType SymbolToken::getSymbolType() {
  return this->mySymbolType;
};

bool SymbolToken::isSymbol(char inChar) {
  for (auto i = SymbolToken::symbolNames.begin();
       i != SymbolToken::symbolNames.end(); i++) {
    if (*i[0] == inChar) {
      return true;
    }
  }
  return false;
};

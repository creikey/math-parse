#ifndef HPP_PARSER
#define HPP_PARSER

#include <iostream>
#include "tokenizer.hpp"

class Parser {
public:
  Parser(std::istream&);
  Parser();
  ~Parser();
  void setTokenizer(Tokenizer);
private:
  Tokenizer tokzer;
  std::istream& stream;
};


#endif

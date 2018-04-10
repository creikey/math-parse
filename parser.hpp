#ifndef HPP_PARSER
#define HPP_PARSER

#include "tokenizer.hpp"
#include <iostream>

class Parser {
public:
  Parser(std::istream *, std::ostream *);
  Parser();
  ~Parser();
  void readln();
  void setTokenizer(Tokenizer);

private:
  Tokenizer tokzer;
  std::istream *stream;
  std::ostream *out;
  cmn::pos cur;
};

#endif

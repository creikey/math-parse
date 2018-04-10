#include "parser.hpp"
#include <iostream>
#include <vector>

Parser::Parser(std::istream *inStream, std::ostream *outStream)
    : stream(inStream), out(outStream){};

Parser::Parser() {
  this->stream = &std::cin;
  this->out = &std::cout;
};

Parser::~Parser(){};

void Parser::readln() {
  std::string curLine;
  *this->stream >> curLine;
  *this->out << "Parsing line: " << curLine << std::endl;
  std::vector<Token *> toks;
}

void Parser::setTokenizer(Tokenizer inTokzer) { this->tokzer = inTokzer; };

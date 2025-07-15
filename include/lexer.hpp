#ifndef _LEXER
#define _LEXER

#include "token.hpp"
#include <fstream>
#include <vector>

class Lexer {
private:
    std::istream& input_stream;

public:
    Lexer(std::istream& is);
    ~Lexer();

    std::vector<Token> produce();
};

#endif
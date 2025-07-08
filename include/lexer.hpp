#ifndef _LEXER
#define _LEXER

#include "token.hpp"
#include <fstream>
#include <vector>

class Lexer {
private:
    std::ifstream& input_stream;

public:
    Lexer(std::ifstream& ifs);
    ~Lexer();

    std::vector<Token> produce();
};

#endif
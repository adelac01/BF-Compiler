#ifndef _LEXER
#define _LEXER

#include "token.hpp"
#include <istream>
#include <vector>

class Lexer {
private:
    std::istream& input_stream;
    Token get_token(char c);

public:
    Lexer(std::istream& is);
    ~Lexer();

    std::vector<Token> produce();
};

#endif
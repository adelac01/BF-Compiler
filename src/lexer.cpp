#include "../include/lexer.hpp"
#include <iostream>

Lexer::Lexer(std::istream& is) : input_stream(is) { }

Lexer::~Lexer() { }

std::vector<Token> Lexer::produce() {

    std::vector<Token> token_stream;
    char c;

    while(input_stream >> c) {
        switch(c) {
            case '>':
                token_stream.push_back(MOVE_RIGHT);
            break;
            case '<':
                token_stream.push_back(MOVE_LEFT);
            break;
            case '+':
                token_stream.push_back(INCREMENT);
            break;
            case '-':
                token_stream.push_back(DECREMENT);
            break;
            case '.':
                token_stream.push_back(OUTPUT);
            break;
            case ',':
                token_stream.push_back(INPUT);
            break;
            case '[':
                token_stream.push_back(JUMP_PAST);
            break;
            case ']':
                token_stream.push_back(JUMP_BACK);
            break;
            default:
                // do nothing
            break;
        }
    }

    return token_stream;
}
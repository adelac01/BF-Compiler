#include "../include/lexer.hpp"
#include <iostream>

Lexer::Lexer(std::istream& is) : input_stream(is) { }

Lexer::~Lexer() { }

Token Lexer::get_token(char c) {

    Token result = Token::COMMENT_CHAR;

    switch(c) {
        case '>':
            result = Token::MOVE_RIGHT;
        break;
        case '<':
            result = Token::MOVE_LEFT;
        break;
        case '+':
            result = Token::INCREMENT;
        break;
        case '-':
            result = Token::DECREMENT;
        break;
        case '.':
            result = Token::OUTPUT;
        break;
        case ',':
            result = Token::INPUT;
        break;
        case '[':
            result = Token::JUMP_PAST;
        break;
        case ']':
            result = Token::JUMP_BACK;
        break;
    }

    return result;
}

std::vector<Token> Lexer::produce() {

    std::vector<Token> token_stream;
    char c;

    while(input_stream >> c) {
        Token t = this->get_token(c);

        if(t != Token::COMMENT_CHAR) {
            token_stream.push_back(t);
        }
    }

    return token_stream;
}
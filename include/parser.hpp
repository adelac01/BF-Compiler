#ifndef _PARSER
#define _PARSER

#include "token.hpp"
#include "ast.hpp"
#include <vector>

class Parser {
private:
    std::vector<Token> token_stream;
    unsigned int stream_ptr;
    Op *head;

    unsigned int consume_token();
    void clear_memory(Op *node);

public:
    Parser(std::vector<Token> token_stream);
    ~Parser();

    Op* gen_ast();
};

#endif
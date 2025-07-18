#ifndef _PARSER
#define _PARSER

#include "token.hpp"
#include "ast.hpp"
#include "metadata.hpp"
#include <vector>
#include <memory>

class Parser {
private:
    std::vector<Token> token_stream;
    unsigned int stream_ptr;
    Program *program;

    unsigned int consume_token();
    void clear_memory(Op *program);

public:
    Parser(std::vector<Token> token_stream);
    ~Parser();

    // void set_metadata();
    Program *gen_ast(struct metadata &md);
};

#endif
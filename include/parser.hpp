#ifndef _PARSER
#define _PARSER

#include "token.hpp"
#include "ast.hpp"
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

    Program *gen_ast(unsigned int array_size, unsigned int cell_size, unsigned int ptr_offset);
};

#endif
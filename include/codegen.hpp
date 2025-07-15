#ifndef _CODEGEN
#define _CODEGEN

#include "ast.hpp"
#include <sstream>
#include <fstream>
#include <stack>

class Codegen {
private:
    Program* program;
    std::string filename;
    std::ofstream assembly;
    unsigned int label_num;
    std::stack<unsigned int> unclosed_labels;

    // prepare assembly file
    void initialize_stream();
    void finalize_stream();
    void walk_ast(Op *curr);

    // generate code specific to received ast node
    void gen_right();
    void gen_left();
    void gen_inc();
    void gen_dec();
    void gen_out();
    void gen_in();
    void gen_past();
    void gen_back();

public:
    Codegen(Program* program, std::string filename);
    ~Codegen();

    void generate();
};

#endif
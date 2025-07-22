#ifndef _ANALYZER
#define _ANALYZER

#include "ast.hpp"
#include <stack>
#include <cstdint>

// Error codes
#define OK 0
#define UNKNOWN_SYMBOL 1
#define UNCLOSED_BRACKET 2

class Analyzer {
private:

    Program *program;
    uint8_t flags;
    int ptr_pos;
    std::stack<Op *> unclosed_brackets;

    void report_error(int error_code); 


    int semantic_analysis(); 
    int apply_optimizations();

    // int constant_folding();
    // int deadcode_elimiation();
    // int repeat_inout_reduction();
    // int loop_unrolling();

public:
    Analyzer(Program *p, uint8_t flags);
    ~Analyzer();
    int analyze_program();
};

#endif
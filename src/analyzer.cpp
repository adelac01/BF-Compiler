#include "../include/analyzer.hpp"
#include "../include/flags.hpp"
#include <iostream>

Analyzer::Analyzer(Program *p, uint8_t flags) : program(p), flags(flags) {
    ptr_pos = p->md.starting_offset;
}

Analyzer::~Analyzer() { }

void Analyzer::report_error(int error_code) {

    switch(error_code) {
        case UNKNOWN_SYMBOL:
            std::cout << "Error: Unknown Symbol" << std::endl; 
        break;
        case UNCLOSED_BRACKET:
            std::cout << "Error: Unclosed Brackets" << std::endl; 
        break;
    }
}

int Analyzer::analyze_program() {
    int error_code = this->semantic_analysis();

    if(error_code) {
        report_error(error_code);
        return error_code;
    }

    if(this->flags & ENABLE_OPTIMIZATIONS) {
        this->apply_optimizations();
    }

    return error_code;
}

int Analyzer::semantic_analysis() {

    Op *curr = this->program->head;

    while(curr != nullptr) {
        switch(curr->type) {
            case PAST:
                this->unclosed_brackets.push(curr);
            break;
            case BACK:
                this->unclosed_brackets.pop();
            break;
            case UNDEF:
                return UNKNOWN_SYMBOL;
            break;

        }
        curr = curr->next;
    }

    if(!this->unclosed_brackets.empty()) {
        return UNCLOSED_BRACKET;
    }

    return OK;
}


int Analyzer::apply_optimizations() {
    int error_code = 0;

    return error_code;
}
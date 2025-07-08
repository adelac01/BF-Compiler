#include "../include/codegen.hpp"
#include <iostream>

Codegen::Codegen(Op* head) : head(head) {
    this->label_num = 0;
    this->assembly = std::ofstream("asm.s");
 }

Codegen::~Codegen() { }

void Codegen::initialize_stream() {
    this->assembly << ".intel_syntax noprefix\n\n";
    this->assembly << ".section .bss\n";
    this->assembly << "tape:\n";
    this->assembly << "\t.space 30000\n\n";
    this->assembly << ".section .text\n";
    this->assembly << ".global main\n";
    this->assembly << "main:\n";
    this->assembly << "\tmov rbx, 0\n";
}

void Codegen::finalize_stream() {
    this->assembly << "\tmov rax, 60\n";
    this->assembly << "\tmov rdi, 0\n";
    this->assembly << "\tsyscall\n";
}

void Codegen::gen_right() {
    this->assembly << "\tinc rbx\n";

}

void Codegen::gen_left() {
    this->assembly << "\tdec rbx\n";
}

void Codegen::gen_inc() {
    this->assembly << "\tinc BYTE PTR[tape + rbx]\n";
}

void Codegen::gen_dec() {
    this->assembly << "\tdec BYTE PTR[tape + rbx]\n";
}

void Codegen::gen_out() {
    this->assembly << "\tmov rax, 1\n";
    this->assembly << "\tmov rdi, 1\n";
    this->assembly << "\tlea rsi, BYTE PTR[tape + rbx]\n";
    this->assembly << "\tmov rdx, 1\n";
    this->assembly << "\tsyscall\n";
}

void Codegen::gen_in() {
    this->assembly << "\tmov rax, 0\n";
    this->assembly << "\tmov rdi, 0\n";
    this->assembly << "\tlea rsi, BYTE PTR[tape + rbx]\n";
    this->assembly << "\tmov rdx, 1\n";
    this->assembly << "\tsyscall\n";
}

void Codegen::gen_past() {
    this->assembly << "\tcmp BYTE PTR[tape + rbx], 0\n";
    this->assembly << "\tjz e" << this->label_num << "\n";
    this->assembly << "\nl" << this->label_num << ":\n";
    this->unclosed_labels.push(this->label_num);
    this->label_num++;
}

void Codegen::gen_back() {
    unsigned int label = this->unclosed_labels.top();
    this->unclosed_labels.pop();

    this->assembly << "\tcmp BYTE PTR[tape + rbx], 0\n";
    this->assembly << "\tjnz l" << label << "\n";
    this->assembly << "\ne" << label << ":\n";
}

void Codegen::walk_ast(Op *curr) {

    if(curr == nullptr) {
        return;
    }

    switch(curr->type) {
        case RIGHT:
            gen_right();
        break;
        case LEFT:
            gen_left();
        break;
        case INC:
            gen_inc();
        break;
        case DEC:
            gen_dec();
        break;
        case OUT:
            gen_out();
        break;
        case IN:
            gen_in();
        break;
        case PAST:
            gen_past();
        break;
        case BACK:
            gen_back();
        break;

    }

    walk_ast(curr->next);

}

void Codegen::generate() {
    initialize_stream();
    walk_ast(this->head);
    finalize_stream();
    // std::cout << this->assembly.str() << std::endl;
}
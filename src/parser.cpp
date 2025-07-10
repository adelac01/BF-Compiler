#include "../include/parser.hpp"

Parser::Parser(std::vector<Token> token_stream) : token_stream(token_stream) {
    this->stream_ptr = 0;
    this->program = new Program();
}

Parser::~Parser() { 
    clear_memory(this->program->head);
    delete this->program;
}

void Parser::clear_memory(Op *node) {
    if(node == nullptr) {
        return;
    }

    clear_memory(node->next);
    delete node;
}

unsigned int Parser::consume_token() {
    unsigned int type;
    switch(token_stream[this->stream_ptr]) {
        case MOVE_RIGHT:
            type = RIGHT;
        break;
        case MOVE_LEFT:
            type = LEFT;
        break;
        case INCREMENT:
            type = INC;
        break;
        case DECREMENT:
            type = DEC;
        break;
        case OUTPUT:
            type = OUT;
        break;
        case INPUT:
            type = IN;
        break;
        case JUMP_PAST:
            type = PAST;
        break;
        case JUMP_BACK:
            type = BACK;
        break;
    }

    this->stream_ptr++;
    return type;
}

// pass in program metadata 
Program *Parser::gen_ast(unsigned int array_size, unsigned int cell_size, unsigned int ptr_offset) {

    // if(this->token_stream.size() == 0) {
    //     return nullptr;
    // }

    this->program->array_size = array_size;
    this->program->cell_size = cell_size;
    this->program->ptr_offset = ptr_offset;
    this->program->head = new Op(consume_token());
    Op *curr = this->program->head;

    for(unsigned int i = 0; i < this->token_stream.size(); i++) {
        curr->next = new Op(consume_token()); 
        curr = curr->next;
    }

    curr->next = nullptr;
    return this->program;
}
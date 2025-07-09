#include "../include/parser.hpp"

Parser::Parser(std::vector<Token> token_stream) : token_stream(token_stream) {
    this->stream_ptr = 0;
    this->head = nullptr;
}

Parser::~Parser() { 
    clear_memory(this->head);
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

Op* Parser::gen_ast() {

    if(this->token_stream.size() == 0) {
        return nullptr;
    }

    Op *curr;
    this->head = new Op(consume_token());
    curr = this->head;

    for(unsigned int i = 1; i < this->token_stream.size(); i++) {
        curr->next = new Op(consume_token()); 
        curr = curr->next;
    }

    curr->next = nullptr;

    return this->head;
}
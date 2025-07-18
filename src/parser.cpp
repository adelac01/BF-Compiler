#include "../include/parser.hpp"

Parser::Parser(std::vector<Token> token_stream) : token_stream(token_stream) {
    this->stream_ptr = 0;
    this->program = new Program();
}

Parser::~Parser() { 
    if(this->program == nullptr) {
        return;
    }

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

    if(this->token_stream.size() == 0) {
        return UNDEF;
    }

    unsigned int type;
    switch(token_stream[this->stream_ptr]) {
        case Token::MOVE_RIGHT:
            type = RIGHT;
        break;
        case Token::MOVE_LEFT:
            type = LEFT;
        break;
        case Token::INCREMENT:
            type = INC;
        break;
        case Token::DECREMENT:
            type = DEC;
        break;
        case Token::OUTPUT:
            type = OUT;
        break;
        case Token::INPUT:
            type = IN;
        break;
        case Token::JUMP_PAST:
            type = PAST;
        break;
        case Token::JUMP_BACK:
            type = BACK;
        break;
    }

    this->stream_ptr++;
    return type;
}

// pass in program metadata 
Program *Parser::gen_ast(struct metadata &md) {

    this->program->md = md;
    this->program->head = new Op(consume_token());
    Op *curr = this->program->head;

    while(this->stream_ptr < this->token_stream.size()) {
        curr->next = new Op(consume_token()); 
        curr = curr->next;
    }

    curr->next = nullptr;
    return this->program;
}
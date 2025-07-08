#include "../include/parser.hpp"

Parser::Parser(std::vector<Token> token_stream) : token_stream(token_stream) {}

Parser::~Parser() { 
    Op *node = this->head;
    clear_memory(node);

}

void Parser::clear_memory(Op *node) {
    if(node == nullptr) {
        return;
    }

    clear_memory(node->next);
    delete node;
}

Op* Parser::O(unsigned int i) {
    if(i >= this->token_stream.size()) {
        return nullptr;
    }

    unsigned int type;
    switch(token_stream[i]) {
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

    Op *curr_node = new Op(type);
    curr_node->next = this->O(i + 1);

    return curr_node;
}

Op* Parser::gen_ast() {
    this->head = this->O(0);
    return this->head;
}
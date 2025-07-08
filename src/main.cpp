#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../include/lexer.hpp"
#include "../include/parser.hpp"
#include "../include/codegen.hpp"

int main(int argc, char **argv) {

    if(argc != 2) {
        std::cout << "Usage: <filename>.bf" << std::endl;
        return 1;
    }

    std::ifstream ifs(argv[1]);

    Lexer lexer(ifs);
    std::vector<Token> token_stream = lexer.produce();

    // for(int i = 0; i < token_stream.size(); i++) {
    //     std::cout << token_stream[i] << std::endl;
    // }

    Parser parser(token_stream);
    Op *head = parser.gen_ast();

    // while(head != nullptr) {

    //     std::string type;
    //     switch(head->type) {
    //         case RIGHT:
    //             type = "RIGHT";
    //         break;
    //         case LEFT:
    //             type = "LEFT";
    //         break;
    //         case INC:
    //             type = "INC";
    //         break;
    //         case DEC:
    //             type = "DEC";
    //         break;
    //         case OUT:
    //             type = "OUT";
    //         break;
    //         case IN:
    //             type = "IN";
    //         break;
    //         case PAST:
    //             type = "PAST";
    //         break;
    //         case BACK:
    //             type = "BACK";
    //         break;
    //     }
    //     std::cout << type << std::endl;
    //     head = head->next;
    // }

    Codegen codegen(head);
    codegen.generate();

    return 0;
}
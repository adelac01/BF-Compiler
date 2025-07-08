#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdint>
#include "../include/lexer.hpp"
#include "../include/parser.hpp"
#include "../include/codegen.hpp"

int main(int argc, char **argv) {
    uint8_t flags = 0;

    if(argc != 2) {
        std::cout << "Usage: <flags> <filename>.bf" << std::endl;
        return 1;
    }

    std::ifstream ifs(argv[1]);

    Lexer lexer(ifs);
    std::vector<Token> token_stream = lexer.produce();

    Parser parser(token_stream);
    Op *head = parser.gen_ast();

    Codegen codegen(head);
    codegen.generate();

    return 0;
}
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdint>
#include <format>
#include "../include/lexer.hpp"
#include "../include/parser.hpp"
#include "../include/codegen.hpp"

int main(int argc, char **argv) {

    /**
     * What does each bit do?
     * bit 0: set output name
     * bit 1: only output assembly
     * bit 2: set array size
     * bit 3: set cell size
     * bit 4: enable some optimizations 
     * bit 5: unused
     * bit 6: unused
     * bit 7: unused
     */
    uint8_t flags = 0;
    std::string filename = "a.out";
    std::string command, assemble, link, clean;

    if(argc < 2) {
        std::cout << "Usage: <flags> <filename>.bf" << std::endl;
        return 1;
    }

    // Lexer stage
    std::ifstream ifs(argv[1]);
    Lexer lexer(ifs);
    std::vector<Token> token_stream = lexer.produce();
    ifs.close();

    // Parsing stage
    Parser parser(token_stream);
    Op *head = parser.gen_ast();

    // Codegen stage
    Codegen codegen(head, filename);
    codegen.generate();

    // assembly and linking stage
    command = std::format("as -o /tmp/{}.o /tmp/{}.s && ld -o {} /tmp/{}.o && rm /tmp/{}*", filename, filename, filename, filename, filename);
    system(command.c_str());

    return 0;
}
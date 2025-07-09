#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdint>
#include <format>
#include "../include/lexer.hpp"
#include "../include/parser.hpp"
#include "../include/codegen.hpp"

void print_help() {
    std::string help_string = "\
Usage: bf [flags] filename\n\
flags:\n\
    -o <file>              Name output the specified file name.\n\
    -S                     Only perform compilation. Generates assembly file.\n\
    -a=<number>            Set array size of program.\n\
    -c=<number>            Set cell size of an array entry.\n\
    -O                     Enable optimizations\n\
    --help                 Print help message\n\
";

    std::cout << help_string << std::endl;
}

void set_flags(uint8_t &flags, unsigned int &o_flag_index, int &i, char **argv) {
    std::string arg = argv[i];
    if(arg == "-o") {
        flags |= 0x01;
        o_flag_index = i + 1;
        i += 1;
    } else if(arg == "-S") {
        flags |= 0x02;
    } else if(arg == "-a") {
        flags |= 0x04;
    } else if(arg == "-c") {
        flags |= 0x08;
    } else if(arg == "-O") {
        flags |= 0x10;
    } else if(arg == "-help") {
        flags |= 0x20;
    } else {
        flags |= 0x80;
    }
}

int main(int argc, char **argv) {

    /**
     * What does each bit do?
     * bit 0: set output name
     * bit 1: only output assembly
     * bit 2: set array size
     * bit 3: set cell size
     * bit 4: enable some optimizations 
     * bit 5: help 
     * bit 6: unused
     * bit 7: unrecognized flag 
     */
    uint8_t flags = 0;
    unsigned int o_flag_index;
    std::string output_file = "a.out";
    std::string input_file = ""; 
    std::string command;

    if(argc < 2) {
        std::cout << "Usage: [flags] <filename>.bf" << std::endl;
        return 1;
    } else {
        for(int i = 1; i < argc; i++) {
            if(argv[i][0] == '-') {
                set_flags(flags, o_flag_index, i, argv);
            } else {
                input_file = argv[i];
            }
        }
    }

    // Walk through the different flags
    if(flags & 0x80) {
        std::cout << "Error: Unrecognized flag." << std::endl;
        return 1;
    }

    if(flags & 0x20) {
        print_help();
        return 0;
    }

    if(flags & 0x01) {
        output_file = argv[o_flag_index];
    }

    // Lexer stage
    std::ifstream ifs(input_file);
    if(!ifs.is_open()) {
        std::cout << "Error: Could not find input file." << std::endl;
        return 1;
    }
    Lexer lexer(ifs);
    std::vector<Token> token_stream = lexer.produce();
    ifs.close();

    // Parsing stage
    Parser parser(token_stream);
    Op *head = parser.gen_ast();

    // Codegen stage
    Codegen codegen(head, output_file);
    codegen.generate();

    if(flags & 0x02) {
        // move file from tmp if only doing compliation
        command = std::format("mv /tmp/{}.s ./", output_file);
    } else {
        // assembly and linking stage
        command = std::format("as -o /tmp/{}.o /tmp/{}.s && ld -o {} /tmp/{}.o; rm /tmp/{}*", output_file, output_file, output_file, output_file, output_file);
    }

    system(command.c_str());

    return 0;
}
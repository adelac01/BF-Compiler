#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdint>
#include <format>
#include <memory>
#include "../include/lexer.hpp"
#include "../include/parser.hpp"
#include "../include/codegen.hpp"
#include "../include/metadata.hpp"

#define SET_OUTPUT 0x01
#define COMPILE_ONLY 0x02
#define SET_ARRAY_SIZE 0x04
#define SET_CELL_SIZE 0x08
#define ENABLE_OPTIMIZATIONS 0x10
#define PRINT_HELP 0x20
#define SET_OFFSET 0x40
#define FLAG_UNKNOWN 0x80

void print_help() {
    std::string help_string = "\
Usage: bf [flags] filename\n\
flags:\n\
    -o <file>              Name output file the name specified in <file>.\n\
    -S                     Only perform compilation. Generates assembly file.\n\
    -a <number>            Set array size of program. Default array size is 30000\n\
    -c <number>            Specify cell size of an array entry by number of bytes. Number used must be valid. A list of valid numbers is given below.\n\
                           Valid options: {1, 2, 4, 8}\n\
    -n <number>            Set initial starting index of the array.\n\
    -O                     Enable optimizations\n\
    --help                 Print help message\
";

    std::cout << help_string << std::endl;
}

void set_flags(uint8_t &flags, struct metadata &md, int &i, char **argv) {
    std::string arg = argv[i];
    if(arg == "-o") {
        flags |= SET_OUTPUT;
        md.output_file = argv[i + 1];
        i += 1;
    } else if(arg == "-S") {
        flags |= COMPILE_ONLY;
    } else if(arg == "-a") {
        flags |= SET_ARRAY_SIZE;
        md.array_size= std::stoi(argv[i + 1]);
        i += 1;
    } else if(arg == "-c") {
        flags |= SET_CELL_SIZE;
        md.cell_size = std::stoi(argv[i + 1]);
        i += 1;
    } else if(arg == "-O") {
        flags |= ENABLE_OPTIMIZATIONS;
    } else if(arg == "--help") {
        flags |= PRINT_HELP;
    } else if(arg == "-n") {
        flags |= SET_OFFSET;
        md.starting_offset = std::stoi(argv[i + 1]);
        i += 1;
    } else {
        flags |= FLAG_UNKNOWN;
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
    std::string command; 

    struct metadata md;
    md.array_size = DEFAULT_ARRAY_SIZE;
    md.cell_size = DEFAULT_CELL_SIZE;
    md.starting_offset = DEFAULT_OFFSET;

    md.output_file = DEFAULT_OUTFILENAME;


    if(argc < 2) {
        std::cout << "Usage: [flags] <filename>.bf" << std::endl;
        return 1;
    } else {
        for(int i = 1; i < argc; i++) {
            if(argv[i][0] == '-') {
                set_flags(flags, md, i, argv);
            } else {
                md.input_file = argv[i];
            }
        }
    }

    // Walk through the different flags
    if(flags & FLAG_UNKNOWN) {
        std::cout << "Error: Unrecognized flag." << std::endl;
        return 1;
    }

    if(flags & PRINT_HELP) {
        print_help();
        return 0;
    }

    // Lexer stage
    std::ifstream ifs(md.input_file);
    if(!ifs.is_open()) {
        std::cout << "Error: Could not find input file." << std::endl;
        return 1;
    }
    Lexer lexer(ifs);
    std::vector<Token> token_stream = lexer.produce();
    ifs.close();

    // Parsing stage
    Parser parser(token_stream);
    Program *program = parser.gen_ast(md);

    // Codegen stage
    Codegen codegen(program);
    codegen.generate();

    // Assembly and linking stage
    if(flags & COMPILE_ONLY) {
        // move file from tmp if only doing compliation
        command = std::format("mv /tmp/{}.s ./", md.output_file);
    } else {
        // assembly and linking stage
        command = std::format("as -o /tmp/{}.o /tmp/{}.s && ld -o {} /tmp/{}.o; rm /tmp/{}*", md.output_file, md.output_file, md.output_file, md.output_file, md.output_file);
    }

    system(command.c_str());

    return 0;
}
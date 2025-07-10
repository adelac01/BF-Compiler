#ifndef _AST 
#define _AST

#define RIGHT 0
#define LEFT 1
#define INC 2
#define DEC 3
#define OUT 4
#define IN 5
#define PAST 6
#define BACK 7
#define UNDEF 8

#include <string>

typedef struct operation {
    unsigned int type;
    struct operation *next;
    operation(unsigned int type) : type(type) { }
} Op;

// hold meta data
typedef struct program {
    unsigned int array_size;
    unsigned int cell_size;
    unsigned int starting_offset;
    std::string program_name;
    Op *head;
} Program;

#endif
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
#include <memory>
#include "metadata.hpp"

typedef struct operation {
    unsigned int type;
    unsigned int occurence;
    std::unique_ptr<struct operation> next;
    operation() { }
    operation(unsigned int type) : type(type) { 
        occurence = 1;
    }
} Op;

// hold meta data
typedef struct program {
    struct metadata md;
    std::unique_ptr<Op> head;
} Program;

#endif
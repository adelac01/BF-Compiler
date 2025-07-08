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

typedef struct operation {
    unsigned int type;
    struct operation *next;
    operation(int type) : type(type) { }
} Op;

#endif
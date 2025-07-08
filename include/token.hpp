#ifndef _TOKEN
#define _TOKEN

typedef enum {
    MOVE_RIGHT,
    MOVE_LEFT,
    INCREMENT,
    DECREMENT,
    OUTPUT,
    INPUT,
    JUMP_PAST,
    JUMP_BACK
} Token;

#endif
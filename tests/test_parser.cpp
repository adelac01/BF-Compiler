#include <gtest/gtest.h>
#include <vector>
#include <memory>
#include <iostream>
#include "lexer.hpp"
#include "parser.hpp"
#include "token.hpp"
#include "ast.hpp"

// Unit tests
TEST(ParserTest, AllValidTokens) {
    using enum Token;

    unsigned int array_size = 30000;
    unsigned int cell_size = 1;
    unsigned int starting_offset = 0;
    std::string program_name = "program";

    unsigned int expected_num_op = 8;
    unsigned int actual_num_op = 0;

    std::vector<Token> token_stream = {
        JUMP_PAST,
        INPUT,
        INCREMENT,
        DECREMENT,
        MOVE_LEFT,
        MOVE_RIGHT,
        OUTPUT,
        JUMP_BACK
    }; 

    Program p;
    Program *expected = &p;
    expected->array_size = 30000;
    expected->cell_size = 1;
    expected->starting_offset = 0;

    Op node0(PAST);
    Op node1(IN);
    Op node2(INC);
    Op node3(DEC);
    Op node4(LEFT);
    Op node5(RIGHT);
    Op node6(OUT);
    Op node7(BACK);

    node0.next = &node1;
    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node4.next = &node5;
    node5.next = &node6;
    node6.next = &node7;
    node7.next = nullptr;

    expected->head = &node0;

    Parser parser(token_stream);
    Program *actual = parser.gen_ast(array_size, cell_size, starting_offset);

    // Check metadata if they match
    ASSERT_EQ(expected->array_size, actual->array_size);
    ASSERT_EQ(expected->cell_size, actual->cell_size);
    ASSERT_EQ(expected->starting_offset, actual->starting_offset);

    // Check linked list if they match
    Op *e_curr = expected->head;
    Op *a_curr = actual->head;

    while(a_curr != nullptr) {
        ASSERT_EQ(e_curr->type, a_curr->type);
        e_curr = e_curr->next;
        a_curr = a_curr->next;
        actual_num_op++;
    }

    ASSERT_EQ(actual_num_op, expected_num_op);
}


TEST(ParserTest, EmptyFile) {
    unsigned int array_size = 30000;
    unsigned int cell_size = 1;
    unsigned int starting_offset = 0;

    Program p;
    Program *expected = &p;
    expected->array_size = 30000;
    expected->cell_size = 1;
    expected->starting_offset = 0;

    Op node0(UNDEF);
    expected->head = &node0;

    std::vector<Token> token_stream;
    Parser parser(token_stream);
    Program *actual = parser.gen_ast(array_size, cell_size, starting_offset); 

    // check metadata
    ASSERT_EQ(expected->array_size, actual->array_size);
    ASSERT_EQ(expected->cell_size, actual->cell_size);
    ASSERT_EQ(expected->starting_offset, actual->starting_offset);
    ASSERT_EQ(expected->head->type, actual->head->type);
}

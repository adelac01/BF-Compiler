#include <gtest/gtest.h>
#include <cstdint>
#include "analyzer.hpp"
#include "ast.hpp"

TEST(AnalyzerTest, ValidProgram) {

    int actual_status;
    int expected_status = 0; 
    uint8_t flags = 0;

    Program p;
    Program *test;
    test->md.array_size = 30000;
    test->md.cell_size = 1;
    test->md.starting_offset = 0;
    test->md.output_file = "a.out";

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

    test->head = &node0;

    Analyzer analyzer(test, flags);
    actual_status = analyzer.analyze_program();

    ASSERT_EQ(actual_status, expected_status);
}

TEST(AnalyzerTest, UnknownSymbol) {

    int actual_status;
    int expected_status = 1; 
    uint8_t flags = 0;

    Program p;
    Program *test;
    test->md.array_size = 30000;
    test->md.cell_size = 1;
    test->md.starting_offset = 0;
    test->md.output_file = "a.out";

    Op node0(PAST);
    Op node1(IN);
    Op node2(INC);
    Op node3(DEC);
    Op node4(LEFT);
    Op node5(UNDEF);
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

    test->head = &node0;

    Analyzer analyzer(test, flags);
    actual_status = analyzer.analyze_program();

    ASSERT_EQ(actual_status, expected_status);

}

TEST(AnalyzerTest, UnclosedBracket) {

    int actual_status;
    int expected_status = 2; 
    uint8_t flags = 0;

    Program p;
    Program *test;
    test->md.array_size = 30000;
    test->md.cell_size = 1;
    test->md.starting_offset = 0;
    test->md.output_file = "a.out";

    Op node0(PAST);
    Op node1(IN);
    Op node2(INC);
    Op node3(DEC);
    Op node4(LEFT);
    Op node5(LEFT);
    Op node6(OUT);

    node0.next = &node1;
    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node4.next = &node5;
    node5.next = &node6;
    node6.next = nullptr;

    test->head = &node0;

    Analyzer analyzer(test, flags);
    actual_status = analyzer.analyze_program();

    ASSERT_EQ(actual_status, expected_status);
}

TEST(AnalyzerTest, EmptyFile) {

    int actual_status;
    int expected_status = 0; 
    uint8_t flags = 0;

    Program p;
    Program *test;
    test->md.array_size = 30000;
    test->md.cell_size = 1;
    test->md.starting_offset = 0;
    test->md.output_file = "a.out";

    Analyzer analyzer(test, flags);
    actual_status = analyzer.analyze_program();

    ASSERT_EQ(actual_status, expected_status);
}
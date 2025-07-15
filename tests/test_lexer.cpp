#include <gtest/gtest.h>
#include <sstream>
#include "lexer.hpp"
#include "token.hpp"

TEST(LexerTest, ParsePlus) {

    std::string test_string = "+";
    std::istringstream iss(test_string);
    Lexer lexer(iss);
    std::vector<Token> token_stream = lexer.produce();


    ASSERT_EQ(token_stream.size(), test_string.size());
    ASSERT_EQ(token_stream[0], Token::INCREMENT);
}
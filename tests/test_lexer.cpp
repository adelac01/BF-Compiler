#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include "lexer.hpp"
#include "token.hpp"

TEST(LexerTest, ScanAllDefinedSymbols) {
    using enum Token;

    std::string test_string = "[,+><-.]";
    std::vector<Token> expected = {
        JUMP_PAST, 
        INPUT, 
        INCREMENT, 
        MOVE_RIGHT,
        MOVE_LEFT,
        DECREMENT,
        OUTPUT,
        JUMP_BACK
    };

    std::istringstream iss(test_string);
    Lexer lexer(iss);
    std::vector<Token> token_stream = lexer.produce();

    ASSERT_EQ(token_stream.size(), expected.size());

    for(int i = 0; i < token_stream.size(); i++) {
        ASSERT_EQ(token_stream[i], expected[i]);
    }
}

TEST(LexerTest, ScanUndefinedSymbols) {
    using enum Token;

    std::string test_string = "++adsf++324+ +asdf++ fafv 3-Set Cl, 8 [ %%";
    std::vector<Token> expected = {
        INCREMENT,
        INCREMENT,
        INCREMENT,
        INCREMENT,
        INCREMENT,
        INCREMENT,
        INCREMENT,
        INCREMENT,
        DECREMENT,
        INPUT,
        JUMP_PAST
    };

    std::istringstream iss(test_string);
    Lexer lexer(iss);
    std::vector<Token> token_stream = lexer.produce();

    ASSERT_EQ(token_stream.size(), expected.size());

    for(int i = 0; i < token_stream.size(); i++) {
       ASSERT_EQ(token_stream[i], expected[i]);
    }

}
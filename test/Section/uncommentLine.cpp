#include <gtest/gtest.h>

#include "Section.hpp"

using namespace ES;

TEST(uncommentLine, empty) {
    std::string s = EMPTY_STRING;
    ASSERT_NO_THROW(uncommentLine(s));
    ASSERT_EQ(uncommentLine(s), EMPTY_STRING);
}

TEST(uncommentLine, noNeed) {
    std::string s = "no need in uncommenting";
    ASSERT_EQ(uncommentLine(s), "no need in uncommenting");
}

TEST(uncommentLine, commentSharpReturnEmpty) {
    std::string s = "#some text after comment";
    ASSERT_EQ(uncommentLine(s), EMPTY_STRING);
}

TEST(uncommentLine, commentSharpReturnText) {
    std::string s = "some text# comment";
    ASSERT_EQ(uncommentLine(s), "some text");
}

TEST(uncommentLine, commentSemicolonReturnEmpty) {
    std::string s = ";some text after comment";
    ASSERT_EQ(uncommentLine(s), EMPTY_STRING);
}

TEST(uncommentLine, commentSemicolonReturnText) {
    std::string s = "some text; comment";
    ASSERT_EQ(uncommentLine(s), "some text");
}

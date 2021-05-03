#include <gtest/gtest.h>

#include "Section.hpp"

using namespace ES;

TEST(beautifyPrefix, empty) {
    std::string s = EMPTY_STRING;
    ASSERT_NO_THROW(beautifyPrefix(s));
    ASSERT_EQ(beautifyPrefix(s), EMPTY_STRING);
}

TEST(beautifyPrefix, returnEmpty) {
    std::string s = "\n \r    \r\n \r";
    ASSERT_EQ(beautifyPrefix(s), EMPTY_STRING);
}

TEST(beautifyPrefix, noNeed) {
    std::string s = "test";
    ASSERT_EQ(beautifyPrefix(s), "test");
}

TEST(beautifyPrefix, CRsNLsSpaces) {
    std::string s = "\r  \n\r \r \n\n   test";
    ASSERT_EQ(beautifyPrefix(s), "test");
}

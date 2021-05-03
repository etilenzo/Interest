#include <gtest/gtest.h>

#include "Section.hpp"

using namespace ES;

TEST(beautifySuffix, empty) {
    std::string s = EMPTY_STRING;
    ASSERT_NO_THROW(beautifySuffix(s));
    ASSERT_EQ(beautifySuffix(s), EMPTY_STRING);
}

TEST(beautifySuffix, returnEmpty) {
    std::string s = "\n \r    \r\n \r";
    ASSERT_EQ(beautifySuffix(s), EMPTY_STRING);
}

TEST(beautifySuffix, noNeed) {
    std::string s = "test";
    ASSERT_EQ(beautifySuffix(s), "test");
}

TEST(beautifySuffix, CRsNLsSpaces) {
    std::string s = "test\r  \n\r \r \n\n   ";
    ASSERT_EQ(beautifySuffix(s), "test");
}

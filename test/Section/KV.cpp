#include <gtest/gtest.h>

#include "Section.hpp"

using namespace ES;

TEST(KV, simpleDeclaration) {
    ASSERT_NO_THROW(KV k);
    KV k;
    ASSERT_NO_THROW(k.key = "1");
    k.key = "1";
    ASSERT_NO_THROW(k.value = "2");
    k.value = "2";
    ASSERT_EQ(k.key, "1");
    ASSERT_EQ(k.value, "2");
}

TEST(KV, constructorDeclaration) {
    ASSERT_NO_THROW(KV k("1", "2"));
    KV k("1", "2");
    ASSERT_EQ(k.key, "1");
    ASSERT_EQ(k.value, "2");
}

TEST(KV, fromString) {
    KV k;
    ASSERT_NO_THROW(k.fromString("me=you"));
    ASSERT_EQ(k.key, "me");
    ASSERT_EQ(k.value, "you");
}

TEST(KV, fromStringEmpty) {
    KV k;
    ASSERT_ANY_THROW(k.fromString(EMPTY_STRING));
}

TEST(KV, fromStringUgly) {
    KV k;
    ASSERT_NO_THROW(k.fromString("me=you  \r"));
    ASSERT_EQ(k.key, "me");
    ASSERT_EQ(k.value, "you");
}

TEST(KV, fromStringWithSpaces) {
    KV k;
    ASSERT_NO_THROW(k.fromString("me = you  \r"));
    ASSERT_EQ(k.key, "me");
    ASSERT_EQ(k.value, "you");
}

TEST(KV, fromStringAbsolutelyWrong) {
    KV k;
    ASSERT_ANY_THROW(k.fromString("word"));
}

TEST(KV, fromStringEmptyKey) {
    KV k;
    ASSERT_ANY_THROW(k.fromString("=you"));
}

TEST(KV, fromStringWrongKey) {
    KV k;
    ASSERT_ANY_THROW(k.fromString(" =you"));
}

TEST(KV, fromStringEmptyValue) {
    KV k;
    ASSERT_NO_THROW(k.fromString("1="));
    k.fromString("1=  \r");
    ASSERT_EQ(k.key, "1");
    ASSERT_EQ(k.value, EMPTY_STRING);
}

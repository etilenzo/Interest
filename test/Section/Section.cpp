#include <gtest/gtest.h>

#include "Section.hpp"

using namespace ES;

TEST(Section, simpleDeclaration) {
    ASSERT_NO_THROW(Section s);
    Section s;
    ASSERT_NO_THROW(s.name = "me");
    s.name = "me";
    ASSERT_NO_THROW(s.options = std::vector<KV>());
    s.options = std::vector<KV>();
    ASSERT_EQ(s.name, "me");
    ASSERT_TRUE(s.options.empty());
}

TEST(Section, constructorDeclaration) {
    ASSERT_NO_THROW(Section s("me", std::vector<KV>()));
    Section s("me", std::vector<KV>());
    ASSERT_EQ(s.name, "me");
    ASSERT_TRUE(s.options.empty());
}

TEST(Section, insert) {
    Section s("me", std::vector<KV>());
    ASSERT_NO_THROW(s.insert("hi"));
    s.insert("hi");
    ASSERT_FALSE(s.options.empty());
    ASSERT_EQ(s.options[0].m_key, "hi");
    ASSERT_EQ(s.options[0].m_value, EMPTY_STRING);
}

TEST(Section, insertEmpty) {
    Section s("me", std::vector<KV>());
    ASSERT_ANY_THROW(s.insert(EMPTY_STRING));
}

TEST(Section, SBinsert) {
    Section s("me", std::vector<KV>());
    ASSERT_NO_THROW(s["hi"]);
    s["hi"];
    ASSERT_EQ(s.options[0].m_key, "hi");
    ASSERT_EQ(s.options[0].m_value, EMPTY_STRING);
}

TEST(Section, SBinsertEmpty) {
    Section s("me", std::vector<KV>());
    ASSERT_ANY_THROW(s[EMPTY_STRING]);
}

TEST(Section, SBinsertWithInit) {
    Section s("me", std::vector<KV>());
    ASSERT_NO_THROW(s["hi"] = "world");
    s["hi"] = "world";
    ASSERT_EQ(s.options[0].m_key, "hi");
    ASSERT_EQ(s.options[0].m_value, "world");
}

TEST(Section, SBinsertWithSearch) {
    Section s("me", std::vector<KV>());
    ASSERT_NO_THROW(s["hi"] = "world");
    s["hi"] = "world";
    ASSERT_EQ(s["hi"], "world");
}

TEST(Section, SBinsertMultiple) {
    Section s("me", std::vector<KV>());
    ASSERT_NO_THROW(s["hi"] = "world");
    s["hi"] = "world";
    ASSERT_NO_THROW(s["one"] = "two");
    s["one"] = "two";
    ASSERT_EQ(s["hi"], "world");
}

TEST(Section, SBinsertRewrite) {
    Section s("me", std::vector<KV>());
    ASSERT_NO_THROW(s["hi"] = "world");
    s["hi"] = "world";
    ASSERT_EQ(s["hi"], "world");
    ASSERT_NO_THROW(s["hi"] = "two");
    s["one"] = "two";
    ASSERT_EQ(s["hi"], "two");
}

TEST(Section, SBinsertRewriteMultiple) {
    Section s("me", std::vector<KV>());
    ASSERT_NO_THROW(s["hi"] = "world");
    s["hi"] = "world";
    ASSERT_EQ(s["hi"], "world");
    ASSERT_NO_THROW(s["one"] = "two");
    s["hi"] = "two";
    ASSERT_EQ(s["one"], "two");
    s["one"] = "two";
    ASSERT_NO_THROW(s["hi"] = "three");
    s["hi"] = "three";
    ASSERT_EQ(s["hi"], "three");
}

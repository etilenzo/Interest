/**
 * @file
 * @brief This file contains tests of KV class
 * @author Evilenzo
 * @version 0.2
 */

#include <sstream>

#include "doctest/doctest.h"

#include "KV.hpp"

using namespace ES;

using std::operator""s;

TEST_CASE("KV") {
    SUBCASE("Empty constructor") { REQUIRE_NOTHROW(KV kv); }

    SUBCASE("Key-Value constructor") {
        REQUIRE_NOTHROW(KV kv("Key", "Value"));
        KV kv("Key", "Value");
        REQUIRE(kv.m_key == "Key");
        REQUIRE(kv.m_value == "Value");
    }

    SUBCASE("L-value constructor fromString") {
        std::string s = "Key=Value";
        REQUIRE_NOTHROW(KV kv(s));
        s = "Key=Value";
        KV kv(s);
        REQUIRE(kv.m_key == "Key");
        REQUIRE(kv.m_value == "Value");
    }

    SUBCASE("R-value constructor fromString") {
        REQUIRE_NOTHROW(KV kv("Key=Value"));
        KV kv("Key=Value");
        REQUIRE(kv.m_key == "Key");
        REQUIRE(kv.m_value == "Value");
    }

    SUBCASE("Copy constructor") {
        KV kv1("Key=Value");
        REQUIRE_NOTHROW(KV kv2(kv1));
        KV kv2(kv1);
        REQUIRE(kv1.m_key == "Key");
        REQUIRE(kv1.m_value == "Value");
        REQUIRE(kv2.m_key == "Key");
        REQUIRE(kv2.m_value == "Value");
    }

    SUBCASE("Move constructor") {
        KV kv1("Key=Value");
        REQUIRE_NOTHROW(KV kv2(std::move(kv1)));
        KV kv2("Key=Value");
        KV kv3(std::move(kv2));
        REQUIRE(kv2.m_key == "");
        REQUIRE(kv2.m_value == "");
        REQUIRE(kv3.m_key == "Key");
        REQUIRE(kv3.m_value == "Value");
    }

    SUBCASE("Copy assignment operator") {
        KV kv1("Key=Value");
        REQUIRE_NOTHROW(KV kv2 = kv1);
        KV kv2 = kv1;
        REQUIRE(kv1.m_key == "Key");
        REQUIRE(kv1.m_value == "Value");
        REQUIRE(kv2.m_key == "Key");
        REQUIRE(kv2.m_value == "Value");
    }

    SUBCASE("Move assignment operator") {
        KV kv1("Key=Value");
        KV kv2;
        REQUIRE_NOTHROW(kv2 = std::move(kv1));
        KV kv3("Key=Value");
        KV kv4;
        kv4 = std::move(kv3);
        REQUIRE(kv3.m_key == "");
        REQUIRE(kv3.m_value == "");
        REQUIRE(kv4.m_key == "Key");
        REQUIRE(kv4.m_value == "Value");
    }

    SUBCASE("Empty value") { REQUIRE(KV("Key= ").m_value == ""); }

    SUBCASE("Ostream operator overload") {
        KV kv("Key=Value");
        std::stringstream os;
        os << kv;
        std::string line;
        getline(os, line);
        REQUIRE(line == "Key=Value"s);
    }

    // TODO: fromString() tests
}

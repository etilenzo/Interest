/**
 * @file
 * @brief This file contains tests of KV class
 * @author Evilenzo
 * @version 0.3
 */

#include <sstream>

#include "doctest/doctest.h"

#include "KV.hpp"

using namespace ES;

void checkValues(KV& kv) {
    REQUIRE(kv.m_key == "Key");
    REQUIRE(kv.m_value == "Value");
}

TEST_CASE("KV") {
    SUBCASE("Empty constructor") {
        REQUIRE_NOTHROW(KV kv);
        KV kv;
        REQUIRE(kv.wrong());
    }

    SUBCASE("Key-Value constructor") {
        REQUIRE_NOTHROW(KV kv("Key", "Value"));
        KV kv("Key", "Value");
        checkValues(kv);
    }

    SUBCASE("L-value constructor fromString") {
        std::string s = "Key=Value";
        REQUIRE_NOTHROW(KV kv(s));
        s = "Key=Value";
        KV kv(s);
        checkValues(kv);
    }

    SUBCASE("R-value constructor fromString") {
        REQUIRE_NOTHROW(KV kv("Key=Value"));
        KV kv("Key=Value");
        checkValues(kv);
    }

    SUBCASE("Copy constructor") {
        KV kv1("Key=Value");
        REQUIRE_NOTHROW(KV kv2(kv1));
        KV kv2(kv1);
        checkValues(kv1);
        checkValues(kv2);
    }

    SUBCASE("Move constructor") {
        KV kv1("Key=Value");
        REQUIRE_NOTHROW(KV kv2(std::move(kv1)));
        KV kv2("Key=Value");
        KV kv3(std::move(kv2));
        REQUIRE(kv2.wrong());
        checkValues(kv3);
    }

    SUBCASE("Copy assignment operator") {
        KV kv1("Key=Value");
        REQUIRE_NOTHROW(KV kv2 = kv1);
        KV kv2 = kv1;
        checkValues(kv1);
        checkValues(kv2);
    }

    SUBCASE("Move assignment operator") {
        KV kv1("Key=Value");
        KV kv2;
        REQUIRE_NOTHROW(kv2 = std::move(kv1));
        KV kv3("Key=Value");
        KV kv4;
        kv4 = std::move(kv3);
        REQUIRE(kv3.wrong());
        checkValues(kv4);
    }

    SUBCASE("Empty value") { REQUIRE(KV("Key= ").m_value == ""); }

    SUBCASE("Ostream operator overload") {
        KV kv("Key=Value");
        std::stringstream os;
        os << kv;
        std::string line;
        getline(os, line);
        REQUIRE(line == "Key=Value");
    }

    // TODO: fromString() tests
}

/**
 * @file
 * @brief This file contains tests of Ini class
 * @author Evilenzo
 * @version 0.1
 */

#include "doctest/doctest.h"

#include "Ini.hpp"

using namespace ES;

TEST_CASE("Ini") {
    SUBCASE("Test standard") {
        std::ifstream is("./ini/test_standard.ini");
        Ini ini;
        boost::optional<Error> error = ini.parseFromStream(is);
        REQUIRE(!error);
        REQUIRE(ini["Test"]["a"] == "b");
        REQUIRE(ini["Test"]["b"] == "c");
        REQUIRE(ini["Test"]["c"] == "D");
        REQUIRE(ini["Test 1"]["a"] == "b");
    }

    SUBCASE("Test Missing First") {
        std::ifstream is("./ini/test_missing_first.ini");
        Ini ini;
        boost::optional<Error> error = ini.parseFromStream(is);
        REQUIRE(error->code == Code::MISSING_FIRST_SECTION);
    }

    SUBCASE("Test Wrong Line") {
        std::ifstream is("./ini/test_wrong_line.ini");
        Ini ini;
        boost::optional<Error> error = ini.parseFromStream(is);
        REQUIRE(error->code == Code::WRONG_LINE);
    }

    SUBCASE("Test Empty Section") {
        std::ifstream is("./ini/test_empty_section.ini");
        Ini ini;
        boost::optional<Error> error = ini.parseFromStream(is);
        REQUIRE(!error);
        REQUIRE(ini["Test"].empty());
        REQUIRE(ini["Test 1"]["a"] == "b");
    }

    SUBCASE("Test Empty Value") {
        std::ifstream is("./ini/test_empty_value.ini");
        Ini ini;
        boost::optional<Error> error = ini.parseFromStream(is);
        REQUIRE(!error);
        REQUIRE(ini["Test"]["key"] == EMPTY_STRING);
    }

    SUBCASE("Common test") {
        std::ifstream is("test_stream.ini");
        Ini ini;
        boost::optional<Error> error = ini.parseFromStream(is);
        REQUIRE(!error);
        REQUIRE(ini["SessionKey.UsePotionMP"]["Key1.Offset"] == "72");
    }
}

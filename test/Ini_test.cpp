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
        bool i = ini.parseFromStream(is)->code == Code::WRONG_STRING;
        std::cout << i << std::endl;

        REQUIRE(ini["Test"]["a"] == "b");
        REQUIRE(ini["Test"]["b"] == "c");
        REQUIRE(ini["Test"]["c"] == "D");
        REQUIRE(ini["Test 1"]["a"] == "b");
    }
    SUBCASE("Common test") {
        std::ifstream is("test_stream.ini");
        Ini ini;
        ini.parseFromStream(is);
        bool result = ini["SessionKey.UsePotionMP"]["Key1.Offset"] == "72";
        REQUIRE(result);
    }
}

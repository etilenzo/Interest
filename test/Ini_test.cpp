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
    SUBCASE("Common test") {
        std::ifstream is("test_stream.ini");
        Ini ini;
        ini.parseFromStream(is);
        bool result = ini["SessionKey.UsePotionMP"]["Key1.Offset"] == "72";
        REQUIRE(result);
    }
}

#include "doctest/doctest.h"

#include "Section.hpp"

using namespace ES;

TEST_CASE("uncommentLine") {
    SUBCASE("Empty string") {
        std::string s = EMPTY_STRING;
        REQUIRE_NOTHROW(uncommentLine(s));
        REQUIRE(s == EMPTY_STRING);
    }
    SUBCASE("No need in uncommenting") {
        std::string s = "Hi! I am pretty string!";
        REQUIRE_NOTHROW(uncommentLine(s));
        REQUIRE(s == "Hi! I am pretty string!");
    }
    SUBCASE("Empty string after uncommenting") {
        std::string s = "#very useful comment";
        REQUIRE_NOTHROW(uncommentLine(s));
        REQUIRE(s == EMPTY_STRING);
    }
    SUBCASE("Uncomment #") {
        std::string s = "text#comment";
        REQUIRE_NOTHROW(uncommentLine(s));
        REQUIRE(s == "text");
    }
    SUBCASE("Uncomment ;") {
        std::string s = "text;comment";
        REQUIRE_NOTHROW(uncommentLine(s));
        REQUIRE(s == "text");
    }
    SUBCASE("Uncomment messy string") {
        std::string s = "text;comment1#comment2#comment3";
        REQUIRE_NOTHROW(uncommentLine(s));
        REQUIRE(s == "text");
    }
}

/**
 * @file
 * @brief This file contains tests of string beautify functions
 * @author Evilenzo
 * @version 0.1
 */

#include "doctest/doctest.h"

#include "Beautifiers.hpp"

using namespace ES;

TEST_CASE("Beautifiers") {
    SUBCASE("uncommentLine") {
        SUBCASE("Empty string") {
            std::string s;
            REQUIRE_NOTHROW(uncommentLine(s));
            REQUIRE(s.empty());
        }
        SUBCASE("No need in uncommenting") {
            std::string s = "Hi! I am pretty string!";
            REQUIRE_NOTHROW(uncommentLine(s));
            REQUIRE(s == "Hi! I am pretty string!");
        }
        SUBCASE("Empty string after uncommenting") {
            std::string s = "#very useful comment";
            REQUIRE_NOTHROW(uncommentLine(s));
            REQUIRE(s.empty());
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
        SUBCASE("Nasty string") {
            std::string s = "text;comment1#comment2#comment3";
            REQUIRE_NOTHROW(uncommentLine(s));
            REQUIRE(s == "text");
        }
    }

    SUBCASE("beautifyPrefix") {
        SUBCASE("Empty string") {
            std::string s = EMPTY_STRING;
            REQUIRE_NOTHROW(beautifyPrefix(s));
            REQUIRE(s == EMPTY_STRING);
        }
        SUBCASE("Empty string after beautifiing") {
            std::string s = "\n \r    \r\n \r";
            REQUIRE_NOTHROW(beautifyPrefix(s));
            REQUIRE(s == EMPTY_STRING);
        }
        SUBCASE("No need in beautifiing") {
            std::string s = "text";
            REQUIRE_NOTHROW(beautifyPrefix(s));
            REQUIRE(s == "text");
        }
        SUBCASE("Nasty string") {
            std::string s = "\r  \n\r \r \n\n   text";
            REQUIRE_NOTHROW(beautifyPrefix(s));
            REQUIRE(s == "text");
        }
    }

    SUBCASE("beautifySuffix") {
        SUBCASE("Empty string") {
            std::string s = EMPTY_STRING;
            REQUIRE_NOTHROW(beautifySuffix(s));
            REQUIRE(s == EMPTY_STRING);
        }
        SUBCASE("Empty string after beautifiing") {
            std::string s = "\n \r    \r\n \r";
            REQUIRE_NOTHROW(beautifySuffix(s));
            REQUIRE(s == EMPTY_STRING);
        }
        SUBCASE("No need in beautifiing") {
            std::string s = "text";
            REQUIRE_NOTHROW(beautifySuffix(s));
            REQUIRE(s == "text");
        }
        SUBCASE("Nasty string") {
            std::string s = "text\r  \n\r \r \n\n   ";
            REQUIRE_NOTHROW(beautifySuffix(s));
            REQUIRE(s == "text");
        }
    }

    SUBCASE("trimBrackets") {
        SUBCASE("Empty string") {
            std::string s = EMPTY_STRING;
            REQUIRE_NOTHROW(trimBrackets(s));
        }
        SUBCASE("Missing brackets") {
            std::string s = "text";
            REQUIRE_NOTHROW(trimBrackets(s));
            REQUIRE(s.empty());
        }
        SUBCASE("Missing opening bracket") {
            std::string s = "text]";
            REQUIRE_THROWS(trimBrackets(s));
        }
        SUBCASE("Missing closing bracket") {
            std::string s = "[text";
            REQUIRE_THROWS(trimBrackets(s));
        }
        SUBCASE("Wrong placed brackets") {
            std::string s = "]text[";
            REQUIRE_THROWS(trimBrackets(s));
        }
        SUBCASE("Section with shit before [") {
            std::string s = "awd[text]";
            REQUIRE_THROWS(trimBrackets(s));
        }
        SUBCASE("Section with shit after ]") {
            std::string s = "[text]adsw";
            REQUIRE_THROWS(trimBrackets(s));
        }
        SUBCASE("Good section") {
            std::string s = "[text]";
            REQUIRE_NOTHROW(trimBrackets(s));
            REQUIRE(s == "text");
        }
    }
}

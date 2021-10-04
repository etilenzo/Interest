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
    SUBCASE("removeComment") {
        SUBCASE("Empty string") {
            std::string s;
            REQUIRE_NOTHROW(removeComment(s));
            REQUIRE(s.empty());
        }
        SUBCASE("No need in uncommenting") {
            std::string s = "Hi! I am pretty string!";
            REQUIRE_NOTHROW(removeComment(s));
            REQUIRE(s == "Hi! I am pretty string!");
        }
        SUBCASE("Empty string after uncommenting") {
            std::string s = "#very useful comment";
            REQUIRE_NOTHROW(removeComment(s));
            REQUIRE(s.empty());
        }
        SUBCASE("Uncomment #") {
            std::string s = "text#comment";
            REQUIRE_NOTHROW(removeComment(s));
            REQUIRE(s == "text");
        }
        SUBCASE("Uncomment ;") {
            std::string s = "text;comment";
            REQUIRE_NOTHROW(removeComment(s));
            REQUIRE(s == "text");
        }
        SUBCASE("Nasty string") {
            std::string s = "text;comment1#comment2#comment3";
            REQUIRE_NOTHROW(removeComment(s));
            REQUIRE(s == "text");
        }
    }

    SUBCASE("beautifyPrefix") {
        SUBCASE("Empty string") {
            std::string s;
            REQUIRE_NOTHROW(beautifyPrefix(s));
            REQUIRE(s.empty());
        }
        SUBCASE("Empty string after beautifiing") {
            std::string s = "    ";
            REQUIRE_NOTHROW(beautifyPrefix(s));
            REQUIRE(s.empty());
        }
        SUBCASE("No need in beautifiing") {
            std::string s = "text";
            REQUIRE_NOTHROW(beautifyPrefix(s));
            REQUIRE(s == "text");
        }
        SUBCASE("Needs to be beautified") {
            std::string s = "   text";
            REQUIRE_NOTHROW(beautifyPrefix(s));
            REQUIRE(s == "text");
        }
    }

    SUBCASE("beautifySuffix") {
        SUBCASE("Empty string") {
            std::string s;
            REQUIRE_NOTHROW(beautifySuffix(s));
            REQUIRE(s.empty());
        }
        SUBCASE("Empty string after beautifiing") {
            std::string s = "   ";
            REQUIRE_NOTHROW(beautifySuffix(s));
            REQUIRE(s.empty());
        }
        SUBCASE("No need in beautifiing") {
            std::string s = "text";
            REQUIRE_NOTHROW(beautifySuffix(s));
            REQUIRE(s == "text");
        }
        SUBCASE("Needs to be beautified") {
            std::string s = "text   ";
            REQUIRE_NOTHROW(beautifySuffix(s));
            REQUIRE(s == "text");
        }
    }

    SUBCASE("removeBreakers") {
        SUBCASE("Empty string") {
            std::string s;
            REQUIRE_NOTHROW(removeBreakers(s));
            REQUIRE(s.empty());
        }
        SUBCASE("Empty string after beautifiing") {
            std::string s = "   ";
            REQUIRE_NOTHROW(removeBreakers(s));
            REQUIRE(s.empty());
        }
        SUBCASE("No need in beautifiing") {
            std::string s = "text";
            REQUIRE_NOTHROW(removeBreakers(s));
            REQUIRE(s == "text");
        }
        SUBCASE("Needs to be beautified") {
            std::string s = "text  \r \n \n\r \r ";
            REQUIRE_NOTHROW(removeBreakers(s));
            REQUIRE(s == "text");
        }
    }

    SUBCASE("trimBrackets") {
        SUBCASE("Empty string") {
            std::string s;
            REQUIRE_NOTHROW(trimBrackets(s));
            REQUIRE(s.empty());
        }
        SUBCASE("Missing brackets") {
            std::string s = "text";
            REQUIRE_NOTHROW(trimBrackets(s));
            REQUIRE(s.empty());
        }
        SUBCASE("Missing opening bracket") {
            std::string s = "text]";
            REQUIRE_NOTHROW(trimBrackets(s));
            REQUIRE(s.empty());
        }
        SUBCASE("Missing closing bracket") {
            std::string s = "[text";
            REQUIRE_NOTHROW(trimBrackets(s));
            REQUIRE(s.empty());
        }
        SUBCASE("Wrong placed brackets") {
            std::string s = "]text[";
            REQUIRE_NOTHROW(trimBrackets(s));
            REQUIRE(s.empty());
        }
        SUBCASE("Section with shit before [") {
            std::string s = "awd[text]";
            REQUIRE_NOTHROW(trimBrackets(s));
            REQUIRE(s.empty());
        }
        SUBCASE("Section with shit after ]") {
            std::string s = "[text]adsw";
            REQUIRE_NOTHROW(trimBrackets(s));
            REQUIRE(s.empty());
        }
        SUBCASE("Good section") {
            std::string s = "[text]";
            REQUIRE_NOTHROW(trimBrackets(s));
            REQUIRE(s == "text");
        }
    }
}

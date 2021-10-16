/**
 * @file
 * @brief This file contains tests of string beautify functions
 * @author Evilenzo
 * @version 0.3
 */

#include "doctest.h"

#include "Utils.hpp"

using namespace ES;

TEST_CASE("Utils") {
    SUBCASE("delComment") {
        SUBCASE("Empty string") {
            std::string s;
            REQUIRE_NOTHROW(delComment(s));
            REQUIRE(s.empty());
        }
        SUBCASE("No need in uncommenting") {
            std::string s = "Hi! I am pretty string!";
            REQUIRE_NOTHROW(delComment(s));
            REQUIRE(s == "Hi! I am pretty string!");
        }
        SUBCASE("Empty string after uncommenting") {
            std::string s = "#very useful comment";
            REQUIRE_NOTHROW(delComment(s));
            REQUIRE(s.empty());
        }
        SUBCASE("Uncomment # in first half") {
            std::string s = "text#comment";
            REQUIRE_NOTHROW(delComment(s));
            REQUIRE(s == "text");
        }
        SUBCASE("Uncomment ; in last part") {
            std::string s = "text;com";
            REQUIRE_NOTHROW(delComment(s));
            REQUIRE(s == "text");
        }
        SUBCASE("Nasty string") {
            std::string s = "text;comment1#comment2#comment3";
            REQUIRE_NOTHROW(delComment(s));
            REQUIRE(s == "text");
        }
        SUBCASE("Comment in the middle") {
            std::string s = "text;txet";
            REQUIRE_NOTHROW(delComment(s));
            REQUIRE(s == "text");
        }
    }

    SUBCASE("delQuotationMarks") {
        SUBCASE("Empty string") {
            std::string s;
            REQUIRE_NOTHROW(delQuotationMarks(s));
            REQUIRE(s.empty());
        }
        SUBCASE("No need in deleting") {
            std::string s = "Hi! I am pretty string!";
            REQUIRE_NOTHROW(delQuotationMarks(s));
            REQUIRE(s == "Hi! I am pretty string!");
        }
        SUBCASE("Delete 's") {
            std::string s = "'text'text";
            REQUIRE_NOTHROW(delQuotationMarks(s));
            REQUIRE(s == "texttext");
        }
        SUBCASE("Delete \"s") {
            std::string s = "\"text\"text";
            REQUIRE_NOTHROW(delQuotationMarks(s));
            REQUIRE(s == "texttext");
        }
    }

    SUBCASE("prefixDelSpaces") {
        SUBCASE("Empty string") {
            std::string s;
            REQUIRE_NOTHROW(prefixDelSpaces(s));
            REQUIRE(s.empty());
        }
        SUBCASE("Empty string after beautifying") {
            std::string s = "    ";
            REQUIRE_NOTHROW(prefixDelSpaces(s));
            REQUIRE(s.empty());
        }
        SUBCASE("No need in beautifying") {
            std::string s = "text";
            REQUIRE_NOTHROW(prefixDelSpaces(s));
            REQUIRE(s == "text");
        }
        SUBCASE("Needs to be beautified") {
            std::string s = "   text";
            REQUIRE_NOTHROW(prefixDelSpaces(s));
            REQUIRE(s == "text");
        }
    }

    SUBCASE("suffixDelSpaces") {
        SUBCASE("Empty string") {
            std::string s;
            REQUIRE_NOTHROW(suffixDelSpaces(s));
            REQUIRE(s.empty());
        }
        SUBCASE("Empty string after beautifying") {
            std::string s = "   ";
            REQUIRE_NOTHROW(suffixDelSpaces(s));
            REQUIRE(s.empty());
        }
        SUBCASE("No need in beautifying") {
            std::string s = "text";
            REQUIRE_NOTHROW(suffixDelSpaces(s));
            REQUIRE(s == "text");
        }
        SUBCASE("Needs to be beautified") {
            std::string s = "text   ";
            REQUIRE_NOTHROW(suffixDelSpaces(s));
            REQUIRE(s == "text");
        }
    }

    SUBCASE("suffixDelBreakers") {
        SUBCASE("Empty string") {
            std::string s;
            REQUIRE_NOTHROW(suffixDelBreakers(s));
            REQUIRE(s.empty());
        }
        SUBCASE("Empty string after beautifying") {
            std::string s = "   ";
            REQUIRE_NOTHROW(suffixDelBreakers(s));
            REQUIRE(s.empty());
        }
        SUBCASE("No need in beautifying") {
            std::string s = "text";
            REQUIRE_NOTHROW(suffixDelBreakers(s));
            REQUIRE(s == "text");
        }
        SUBCASE("Needs to be beautified") {
            std::string s = "text  \r \n \n\r \r ";
            REQUIRE_NOTHROW(suffixDelBreakers(s));
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

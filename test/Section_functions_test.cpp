#include "doctest/doctest.h"

#include "Section.hpp"

using namespace ES;

TEST_CASE("File Section.cpp") {
    SUBCASE("Formatting functions") {
        SUBCASE("uncommentLine") {
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

        SUBCASE("parseBrackets") {
            SUBCASE("Empty string") {
                std::string s = EMPTY_STRING;
                REQUIRE_THROWS(parseBrackets(s));
            }
            SUBCASE("Missing brackets") {
                std::string s = "text";
                REQUIRE_THROWS(parseBrackets(s));
            }
            SUBCASE("Missing opening bracket") {
                std::string s = "text]";
                REQUIRE_THROWS(parseBrackets(s));
            }
            SUBCASE("Missing closing bracket") {
                std::string s = "[text";
                REQUIRE_THROWS(parseBrackets(s));
            }
            SUBCASE("Wrong placed brackets") {
                std::string s = "]text[";
                REQUIRE_THROWS(parseBrackets(s));
            }
            SUBCASE("Section with shit before [") {
                std::string s = "awd[text]";
                REQUIRE_THROWS(parseBrackets(s));
            }
            SUBCASE("Section with shit after ]") {
                std::string s = "[text]adsw";
                REQUIRE_THROWS(parseBrackets(s));
            }
            SUBCASE("Good section") {
                std::string s = "[text]";
                REQUIRE_NOTHROW(parseBrackets(s));
                REQUIRE(s == "text");
            }
        }
    }
}

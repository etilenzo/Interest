/**
 * @file
 * @brief This file contains tests of Ini class
 * @author Evilenzo
 * @version 1.0
 */

#include <sstream>

#include "doctest/doctest.h"

#include "Ini.hpp"

using namespace ES;

TEST_CASE("Ini") {
    SUBCASE("Const operator[] for empty") {
        const Ini ini;
        REQUIRE(ini["Name"].m_name == "");
        REQUIRE(ini["Name"].empty());
    }

    SUBCASE("Const operator[]") {
        const Ini ini({}, {}, {Section("Name", {KV()})});
        REQUIRE(ini["Name"].m_name == "Name");
        REQUIRE(!ini["Name"].empty());
    }

    SUBCASE("Broken input stream") {
        std::ifstream is("/hello_world");
        Ini ini;
        boost::optional<Error> error = ini.parseFromStream(is);
        REQUIRE(error->code == Code::BROKEN_INPUT_STREAM);
    }

    SUBCASE("Dump to stream") {
        Ini ini({}, {},
                {Section("Name", {KV("Key=Value")}), Section("Name2", {KV("Key2=Value2")})});
        std::stringstream os;
        os << ini;
        std::string line;
        getline(os, line);
        REQUIRE(line == "[Name]");
        getline(os, line);
        REQUIRE(line == "Key=Value");
        getline(os, line);
        REQUIRE(line == "");
        getline(os, line);
        REQUIRE(line == "[Name2]");
        getline(os, line);
        REQUIRE(line == "Key2=Value2");
    }

    SUBCASE("Construct Section") {
        Ini ini;
        ini["Name"]["Key"] = "Value";
        REQUIRE(ini.m_elements->size() == 1);
        REQUIRE(ini["Name"]["Key"] == "Value");
    }

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

    SUBCASE("Test Last Section") {
        std::ifstream is("./ini/test_last_section.ini");
        Settings settings;
        settings.m_section_duplicate = SectionDuplicate::LAST;
        Ini ini(settings);
        boost::optional<Error> error = ini.parseFromStream(is);
        REQUIRE(!error);
        REQUIRE(ini["Test"]["a"] == "c");
        REQUIRE(ini["Test"]["b"] == "a");
        REQUIRE(ini["Test"]["c"] == "b");
    }

    SUBCASE("Test Unite Sections") {
        std::ifstream is("./ini/test_unite_sections.ini");
        Settings settings;
        settings.m_section_duplicate = SectionDuplicate::UNITE;
        Ini ini(settings);
        boost::optional<Error> error = ini.parseFromStream(is);
        REQUIRE(!error);
        REQUIRE(ini["Test"]["a"] == "1");
        REQUIRE(ini["Test"]["b"] == "2");
        REQUIRE(ini["Test"]["c"] == "3");
    }

    SUBCASE("Test Last Option") {
        std::ifstream is("./ini/test_last_option.ini");
        Settings settings;
        settings.m_option_duplicate = OptionDuplicate::LAST;
        Ini ini(settings);
        boost::optional<Error> error = ini.parseFromStream(is);
        REQUIRE(!error);
        REQUIRE(ini["Test"]["a"] == "3");
        REQUIRE(ini["Test"]["b"] == "2");
    }

    SUBCASE("Common test") {
        std::ifstream is("./ini/test_stream.ini");
        Ini ini;
        boost::optional<Error> error = ini.parseFromStream(is);
        REQUIRE(!error);
        REQUIRE(ini["SessionKey.UsePotionMP"]["Key1.Offset"] == "72");
    }
}

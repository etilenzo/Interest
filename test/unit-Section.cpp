/**
 * @file
 * @brief This file contains tests of Section class
 * @author Evilenzo
 * @version 1.0
 */

#include <sstream>

#include <boost/optional/optional_io.hpp>
#include "doctest/doctest.h"

#include "Section.hpp"

using namespace ES;

void checkValues(Section& section) {
    REQUIRE(section.m_name == "Name");
    REQUIRE(!section.m_elements->empty());
}

void checkMoved(Section& section) {
    REQUIRE(section.m_name.empty());
    REQUIRE(section.m_elements == nullptr);
}

void checkEmpty(Section& section) {
    REQUIRE(section.m_name.empty());
    REQUIRE(section.m_elements->empty());
}

TEST_CASE("Section") {
    SUBCASE("Empty constructor") {
        REQUIRE_NOTHROW(Section section);
        Section section;
        checkEmpty(section);
    }

    SUBCASE("Param initialization constructor") {
        REQUIRE_NOTHROW(Section section("Name", {KV()}));
        Section section("Name", {KV()});
        checkValues(section);
    }

    SUBCASE("Copy constructor") {
        Section section1("Name", {KV("k=v")});
        REQUIRE_NOTHROW(Section section2(section1));
        Section section2(section1);
        checkValues(section1);
        checkValues(section2);
    }

    SUBCASE("Move constructor") {
        Section section1("Name", {KV("k=v")});
        REQUIRE_NOTHROW(Section section2(std::move(section1)));
        Section section2("Name", {KV("k=v")});
        Section section3(std::move(section2));
        checkMoved(section2);
        checkValues(section3);
    }

    SUBCASE("Copy assignment operator") {
        Section section1("Name", {KV("k=v")});
        REQUIRE_NOTHROW(Section section2 = section1);
        Section section2 = section1;
        checkValues(section1);
        checkValues(section2);
    }

    SUBCASE("Move assignment operator") {
        Section section1("Name", {KV("k=v")});
        Section section2;
        REQUIRE_NOTHROW(section2 = std::move(section1));
        Section section3("Name", {KV("k=v")});
        Section section4;
        section4 = std::move(section3);
        checkMoved(section3);
        checkValues(section4);
    }

    SUBCASE("Empty check") {
        Section section1;
        REQUIRE(section1.empty());
        Section section2("", {KV()});
        REQUIRE(!section2.empty());
    }

    SUBCASE("Add in wrong check") {
        Section section;
        section["Key"] = "Value";
        REQUIRE(section.m_elements->size() == 1);
        REQUIRE(section["Key"] == "Value");
    }

    SUBCASE("Add in non wrong check") {
        Section section("Name", {KV("Key1=Value1")});
        section["Key2"] = "Value2";
        REQUIRE(section.m_elements->size() == 2);
        REQUIRE(section["Key1"] == "Value1");
        REQUIRE(section["Key2"] == "Value2");
    }

    SUBCASE("Const find check") {
        const Section section("Name", {KV("Key1=Value1"), KV("Key2=Value2")});
        REQUIRE(*section["Key2"] == "Value2");
        REQUIRE(!section["Blah"]);
    }

    SUBCASE("Const find wrong check") {
        const Section section;
        REQUIRE(section.empty());
        REQUIRE(!section["Key"]);
    }

    SUBCASE("Ostream operator overload") {
        Section section("Name", {KV("Key=Value")});
        std::stringstream os;
        os << section;
        std::string line;
        getline(os, line);
        REQUIRE(line == "[Name]");
        getline(os, line);
        REQUIRE(line == "Key=Value");
    }

    SUBCASE("RemoveEmpty for Container class") {
        Section section("Name", {KV(), KV("2=1"), KV("1=2"), KV()});
        REQUIRE(section.m_elements->size() == 4);
        section.removeEmpty();
        REQUIRE(section.m_elements->size() == 2);
    }

    SUBCASE("Equality Container") {
        Section section("Name");
        REQUIRE_NOTHROW(section == "Name");
        REQUIRE(section == "Name");
    }
}

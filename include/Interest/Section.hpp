/**
 * @file
 * @brief This file contains declaration of Section class
 * @author Evilenzo
 * @version 1.0
 */

#pragma once

#include <algorithm>
#include <numeric>

#include "Container.hpp"
#include "KV.hpp"

namespace ES {


class Ini;

/// @brief Section container class
class Section : public Container<KV> {
public:
    friend Ini;

    /**
     * @brief Container with param initialization
     * @param name name of container
     * @param options vector of KV
     */
    Section(std::string name = {}, std::vector<KV> options = {})
        : Container(std::move(name), std::move(options)) {}

    /// @brief Copy constructor
    Section(const Section& section) = default;

    /// @brief Move constructor
    Section(Section&& section) noexcept = default;

    /// @brief Copy assignment operator
    Section& operator=(const Section& section) = default;

    /// @brief Move assignment operator
    Section& operator=(Section&& section) = default;

    /**
     * @brief Finds and returns l-value reference on KV's m_value or inserts KV and returns same
     * @details Tries to find element in the m_elements vector. If found, returns l-value reference
     * to it's m_value. If not, calls insert() and returns new KV's m_value
     * @param key key of searched KV
     * @return reference on value of KV
     * @see find()
     * @see insert()
     */
    std::string& operator[](std::string key) { return findOrInsert(std::move(key)).m_value; }

    /**
     * @brief Finds and returns const l-value reference or boost::none
     * @param key key of searched KV
     * @return l-value reference to found KV's value or boost::none if not found
     * @see find()
     */
    boost::optional<const std::string&> operator[](std::string key) const {
        boost::optional<const KV&> temp = find(std::move(key));

        if (temp) {
            return temp->m_value;
        }

        return boost::none;
    }

    /**
     * @brief Overloaded operator << to output section content in std::ostream
     * @param os std::ostream l-value reference
     * @param section section const l-value reference
     * @return std::ostream l-value reference
     */
    friend std::ostream& operator<<(std::ostream& os, const Section& section) {
        os << OPENING_BRACKET << section.m_name << CLOSING_BRACKET << std::endl;

        for (const auto& i : *section.m_elements) {
            os << i;
        }

        return os;
    }

    /// Empty destructor
    ~Section() override = default;

private:
    /// @brief Construct new KV
    KV construct(std::string key) override { return {std::move(key), EMPTY_STRING}; }
};


}  // namespace ES

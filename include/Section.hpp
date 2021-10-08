/**
 * @file
 * @brief This file contains declaration of Section class
 * @author Evilenzo
 * @version 0.1
 */

#pragma once

#include <algorithm>
#include <numeric>

#include "Container.hpp"
#include "KV.hpp"

namespace ES {


/// @brief Section container class
class Section : public Container<KV> {
public:
    /**
     * @brief Container with param initialization
     * @param name m_name
     * @param options m_options
     */
    Section(std::string name = "", std::vector<KV> options = std::vector<KV>())
        : Container(name, options) {}

    /**
     * @brief Copy constructor
     * @param section const l-value reference to another instance
     */
    Section(const Section& section) : Container(section) {}

    /**
     * @brief Move constructor
     * @param section r-value reference to another instance
     */
    Section(Section&& section) noexcept : Container(section) {}

    /// Empty destructor
    ~Section() = default;

private:
    /**
     * @brief Overrided construct function
     * @param key key of new KV
     * @return created KV class
     */
    KV construct(std::string key) override;
};


/**
 * @brief Overloaded operator << to output section content in std::ostream
 * @param os std::ostream l-value reference
 * @param section section const l-value reference
 * @return std::ostream l-value reference
 */
// std::ostream& operator<<(std::ostream& os, const Section& section);


}  // namespace ES

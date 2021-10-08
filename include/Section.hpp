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
class Section : public Container<KV, std::string> {
public:
    /**
     * @brief Container with param initialization
     * @param name m_name
     * @param options m_options
     */
    Section(std::string name = "", std::vector<KV> options = std::vector<KV>())
        : Container(std::move(name), std::move(options)) {}

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

    /**
     * @brief Copy assignment operator
     * @param container const l-value reference to another instance
     * @return *this
     */
    Section& operator=(const Section& section) = default;

    /**
     * @brief Move assignment operator
     * @param container r-value reference to another instance
     * @return *this
     */
    Section& operator=(Section&& section) = default;

    /// Empty destructor
    ~Section() = default;

private:
    /**
     * @brief Overrided construct function
     * @param key key of new KV
     * @return created KV class
     */
    KV construct(std::string key) override;
    std::string& bracketsReturn(KV& kv) override;
};


/**
 * @brief Overloaded operator << to output section content in std::ostream
 * @param os std::ostream l-value reference
 * @param section section const l-value reference
 * @return std::ostream l-value reference
 */
// std::ostream& operator<<(std::ostream& os, const Section& section);


}  // namespace ES

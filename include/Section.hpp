/**
 * @file
 * @brief This file contains declaration Section class
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
    /// @brief Empty constructor
    Section() = default;

    /**
     * @brief Container with param initialization
     * @param name m_name
     * @param options m_options
     */
    Section(std::string name, std::vector<KV> options) noexcept;

    /**
     * @brief Copy constructor
     * @param section const l-value reference to another instance
     */
    Section(const Section& section) noexcept;

    /**
     * @brief Move constructor
     * @param section r-value reference to another instance
     */
    Section(Section&& section) noexcept;

    /// Empty destructor
    ~Section() = default;

private:
    bool comparator(const KV& i, std::string line) const noexcept override;

    KV construct(std::string line) override;
};


/**
 * @brief Overloaded operator << to output section content in std::ostream
 * @param os std::ostream l-value reference
 * @param section section const l-value reference
 * @return std::ostream l-value reference
 */
// std::ostream& operator<<(std::ostream& os, const Section& section);


}  // namespace ES

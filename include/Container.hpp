/**
 * @file
 * @brief This file contains declaration of abstract template Container class
 * @author Evilenzo
 * @version 0.1
 */

#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace ES {
// TODO: Const methods

template <typename T>
using Elements = std::shared_ptr<std::vector<T>>;

template <typename T>
class Container {
public:
    /// @brief Name of container (optional for final containers)
    std::string m_name;

    /// @brief Vector of contained elements
    Elements<T> m_elements;

    /// @brief Empty constructor
    Container() = default;

    /**
     * @brief Copy constructor
     * @param container const l-value reference to another instance
     */
    Container(const Container& container) noexcept
        : m_name(container.m_name), m_elements(container.m_elements) {}

    /**
     * @brief Move constructor
     * @param container r-value reference to another instance
     */
    Container(Container&& container) noexcept
        : m_name(std::move(container.m_name)), m_elements(std::move(container.m_elements)) {
        container.m_name.clear();
        container.m_elements.reset();
    }

    /**
     * @brief Copy assignment operator
     * @param container const l-value reference to another instance
     * @return *this
     */
    virtual Container& operator=(const Container& container) noexcept {
        if (this == &container) {
            return *this;
        }

        m_name = std::move(container.m_name);
        m_elements = std::move(container.m_elements);

        return *this;
    }

    /**
     * @brief Move assignment operator
     * @param container r-value reference to another instance
     * @return *this
     */
    virtual Container& operator=(Container&& container) noexcept {
        if (this == &container) {
            return *this;
        }

        m_name = std::move(container.m_name);
        m_elements = std::move(container.m_elements);

        container.m_name.clear();
        container.m_elements.reset();

        return *this;
    }

    /**
     * @brief Find and return or insert
     * @details Tries to find element with the comparator in the m_elements vector. If found,
     * returns l-value reference to it. If not, calls insert() with construct() to construct and
     * insert object in m_elements
     * @param name key, name etc. of the searched value
     * @return l-value reference to found or created object
     * @see comparator()
     * @see find()
     * @see insert()
     * @see construct()
     */
    virtual Container& operator[](std::string line) {
        std::optional<T&> element = find([this, line](const T& i) { comparator(i, line); });

        if (element) {
            return *element;
        }

        return insert(construct(std::move(line)));
    }

    /**
     * @brief Unary predicate for find_if() function in find() method
     * @details Just a simple function that must return true if element name or key equals to line
     * @param i const l-value reference to current "iterator"
     * @param line the line being checked for compliance
     * @return
     */
    bool comparator(const T& i, std::string line);

    // TODO: Fill in
    /**
     * @brief construct
     * @param line
     * @return
     */
    T& construct(std::string line);

    /**
     * @brief Remove empty entries
     * @details Works only for types having empty() function. Must be overrided for others!
     */
    virtual void removeEmpty() noexcept {
        for (auto it = m_elements->begin(); it != m_elements->end();) {
            if (it->empty()) {
                it = m_elements->erase(it);
            } else {
                ++it;
            }
        }
    }

    /**
     * @brief Clear container
     */
    virtual void clear() noexcept { m_elements->clear(); }

    /**
     * @brief Check on emptyness
     */
    virtual bool empty() const noexcept { return m_elements->empty(); }

    /**
     * @brief Operator << for std::ostream
     * @details Same as dumpToStream() but nice
     * @param os std::ostream l-value reference
     * @param container container container const reference
     * @return Nice formatted stream for output
     */
    // friend std::ostream& operator<<(std::ostream& os, const Container& container);

    /// Empty destructor
    virtual ~Container() = default;

protected:
    virtual std::optional<T&> find(bool (*comp)(const T&)) const {
        if (!m_elements.empty()) {
            auto temp = std::find_if(m_elements->begin(), m_elements->end(), comp);

            if (temp != m_elements->end()) {
                return *temp;
            }

            return std::nullopt;
        }

        return std::nullopt;
    }

    virtual T& insert(T& temp) { m_elements->push_back(temp); }
};


}  // namespace ES

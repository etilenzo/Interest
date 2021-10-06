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

#include <boost/function.hpp>

namespace ES {
// TODO: Check all noexcept methods

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
     * @brief Constructor with param initialization
     * @param name m_name
     * @param elements m_elements
     */
    Container(std::string name, std::vector<T> elements) noexcept
        : m_name(name), m_elements(std::make_shared<std::vector<T>>(elements)) {}

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
     * @brief Finds and returns or inserts
     * @details Tries to find element with the comparator in the m_elements vector. If found,
     * returns l-value reference to it. If not, calls insert() with construct() to construct and
     * insert object in m_elements
     * @param line key, name etc. of the searched value
     * @return l-value reference to found or created object
     * @see comparator()
     * @see find()
     * @see insert()
     * @see construct()
     */
    virtual T& operator[](std::string line) {
        boost::function<bool(const T& i)> cmp = [&, line](const T& i) {
            return comparator(i, line);
        };

        std::optional<T&> element = find(cmp);

        if (element) {
            return *element;
        }

        return insert(construct(std::move(line)));
    }

    /**
     * @brief Finds and returns const l-value reference or std::nullopt
     * @param line key, name etc. of the searched value
     * @return l-value reference to found object or std::nullopt if not found
     * @see comparator()
     * @see find()
     */
    virtual std::optional<const T&> operator[](std::string line) const noexcept {
        boost::function<bool(const T& i)> cmp = [&, line](const T& i) {
            return comparator(i, line);
        };

        return std::optional<const T&>(find(cmp));
    }

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

    /// @brief Clear container
    virtual void clear() noexcept { m_elements->clear(); }

    /// @brief Check if container is empty
    virtual bool empty() const noexcept { return m_elements->empty(); }

    /// @brief Empty destructor
    virtual ~Container() = default;

protected:
    /**
     * @brief Unary predicate for find_if() function in find() method
     * @details Just a simple function that must return true if element name or key equals to line
     * @param i const l-value reference to current "iterator"
     * @param line the line being checked for compliance
     * @return
     */
    virtual bool comparator(const T& i, std::string line) const noexcept;

    /**
     * @brief Construct a new object and return reference on it
     * @param line key, name etc.
     * @return l-value reference on created object
     */
    virtual T construct(std::string line);

    /**
     * @brief Finds element by comparator
     * @details Uses find_if() to find object by comparator
     * @return std::nullopt if not found or l-value reference on object
     */
    virtual std::optional<T&> find(boost::function<bool(const T&)> cmp) const {
        if (!m_elements->empty()) {
            auto temp = std::find_if(m_elements->begin(), m_elements->end(), cmp);

            if (temp != m_elements->end()) {
                return *temp;
            }

            return std::nullopt;
        }

        return std::nullopt;
    }

    /**
     * @brief Inserts temporary object in m_elements
     * @param temp temporary object made by construct
     * @return l-value reference on this object
     */
    virtual T& insert(T& temp) {
        m_elements->push_back(temp);
        return temp;
    }
};


}  // namespace ES

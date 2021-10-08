/**
 * @file
 * @brief This file contains declaration of abstract template Container class
 * @author Evilenzo
 * @version 0.1
 */

#pragma once

#include <memory>
#include <string>
#include <vector>

#include <boost/optional.hpp>

namespace ES {


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
    Container(std::string name, std::vector<T> elements)
        : m_name(name), m_elements(std::make_shared<std::vector<T>>(elements)) {}

    /**
     * @brief Copy constructor
     * @param container const l-value reference to another instance
     */
    Container(const Container& container)
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
    virtual Container& operator=(const Container& container) {
        if (this == &container) {
            return *this;
        }

        m_name = container.m_name;
        m_elements = container.m_elements;

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
     * @brief Equality operator for find algorithm
     * @param name name of container
     * @return m_name == name
     * @see find()
     */
    virtual bool operator==(std::string name) const noexcept { return m_name == name; }

    /**
     * @brief Finds and returns or inserts
     * @details Tries to find element with the comparator in the m_elements vector. If found,
     * returns l-value reference to it. If not, calls insert() with construct() to construct and
     * insert object in m_elements
     * @param line key, name etc. of the searched value
     * @return l-value reference to found or created object
     * @see find()
     * @see insert()
     * @see construct()
     */
    virtual T& operator[](std::string line) {
        boost::optional<T&> element = find(line);

        if (element) {
            return *element;
        }

        return insert(construct(line));
    }

    /**
     * @brief Finds and returns const l-value reference or std::nullopt
     * @param line key, name etc. of the searched value
     * @return l-value reference to found object or std::nullopt if not found
     * @see find()
     */
    virtual boost::optional<const T&> operator[](std::string line) const {
        return boost::optional<const T&>(find(line));
    }

    /**
     * @brief Remove empty entries
     * @details Works only for types having empty() function. Must be overrided for others!
     */
    virtual void removeEmpty() noexcept {
        m_elements.erase(std::remove_if(m_elements->begin(), m_elements->end(),
                                        [](const T& i) { return i.empty(); }),
                         m_elements->end());
    }

    /// @brief Clear container
    virtual void clear() noexcept { m_elements->clear(); }

    /// @brief Check if container is empty
    virtual bool empty() const noexcept { return m_elements->empty(); }

    /// @brief Empty destructor
    virtual ~Container() = default;

protected:
    /**
     * @brief Construct a new object and return it
     * @param line key, name etc.
     * @return created object
     */
    virtual T construct(std::string line) = 0;

    /**
     * @brief Finds element (T must have operator== implementation)
     * @details Uses find() to find object
     * @return boost::none if not found or l-value reference on object
     */
    virtual boost::optional<T&> find(std::string line) const {
        if (!m_elements->empty()) {
            auto temp = std::find(m_elements->begin(), m_elements->end(), line);

            if (temp != m_elements->end()) {
                return *temp;
            }

            return boost::none;
        }

        return boost::none;
    }

    /**
     * @brief Inserts temporary object in m_elements
     * @param temp temporary object made by construct
     * @return l-value reference on this object
     */
    virtual T& insert(T temp) {
        m_elements->push_back(temp);
        return m_elements->back();
    }
};


}  // namespace ES

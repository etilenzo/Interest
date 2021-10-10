/**
 * @file
 * @brief This file contains declaration of template Container class
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

    /**
     * @brief Constructor with param initialization (or empty)
     * @param name name of container
     * @param elements vector of contained elements
     */
    Container(std::string name = std::string(), std::vector<T> elements = std::vector<T>())
        : m_name(std::move(name)),
          m_elements(std::make_shared<std::vector<T>>(std::move(elements))) {}

    /// @brief Copy constructor
    Container(const Container& container) = default;

    /// @brief Move constructor
    Container(Container&& container) noexcept = default;

    /// @brief Copy assignment operator
    Container& operator=(const Container& container) = default;

    /// @brief Move assignment operator
    Container& operator=(Container&& container) noexcept = default;

    /**
     * @brief Equality operator for find algorithm
     * @param name name of container
     * @return m_name == name
     * @see find()
     */
    virtual bool operator==(std::string name) const noexcept { return m_name == name; }

    /**
     * @brief Remove empty entries
     * @details Works only for types having empty() function. Must be overrided for others!
     */
    virtual void removeEmpty() noexcept {
        m_elements->erase(std::remove_if(m_elements->begin(), m_elements->end(),
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
     * @param temp temporary object
     * @return l-value reference on this object
     */
    virtual T& insert(T temp) {
        m_elements->push_back(temp);
        return m_elements->back();
    }
};


}  // namespace ES

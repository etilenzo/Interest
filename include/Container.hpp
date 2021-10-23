/**
 * @file
 * @brief This file contains declaration of abstract template Container class
 * @author Evilenzo
 * @version 1.0
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
    std::string m_name = {};

    /// @brief Vector of contained elements
    Elements<T> m_elements = {};

    /**
     * @brief Constructor with param initialization (or empty)
     * @param name name of container
     * @param elements vector of contained elements
     */
    Container(std::string name = {}, std::vector<T> elements = {})
        : m_name(std::move(name)),
          m_elements(std::make_shared<std::vector<T>>(std::move(elements))) {}

    /// @brief Copy constructor
    Container(const Container& container) = default;

    /// @brief Move constructor
    Container(Container&& container) noexcept = default;

    /// @brief Copy assignment operator
    auto operator=(const Container& container) -> Container& = default;

    /// @brief Move assignment operator
    auto operator=(Container&& container) noexcept -> Container& = default;

    /**
     * @brief Equality operator for find() algorithm
     * @param name name of container
     * @return m_name == name
     * @see find()
     */
    auto operator==(const std::string& name) const noexcept -> bool { return m_name == name; }

    /**
     * @brief Finds element (T must have operator== implementation)
     * @details Uses find() to find object
     * @return boost::none if not found or l-value reference to object
     */
    auto find(std::string line) -> boost::optional<T&> {
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
     * @brief Finds element (T must have operator== implementation)
     * @details Uses find() to find object
     * @return boost::none if not found or const l-value reference on object
     */
    auto find(std::string line) const -> boost::optional<const T&> {
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
     * @brief Remove empty entries
     * @details Works only for types having empty() function. Must be overrided for others!
     */
    virtual auto removeEmpty() noexcept -> void {
        m_elements->erase(std::remove_if(m_elements->begin(), m_elements->end(),
                                         [](const T& i) { return i.empty(); }),
                          m_elements->end());
    }

    /// @brief Clear container
    auto clear() noexcept -> void { m_elements->clear(); }

    /// @brief Check if container is empty
    auto empty() const noexcept -> bool { return m_elements->empty(); }

    /// @brief Empty destructor
    virtual ~Container() = default;

protected:
    /**
     * @brief Construct new element
     * @param line line that used to construct
     * @return new constructed element
     */
    virtual auto construct(std::string line) -> T = 0;

    /**
     * @brief Inserts temporary object in m_elements
     * @param temp temporary object
     * @return l-value reference on this object
     */
    auto insert(T temp) -> T& {
        m_elements->push_back(temp);
        return m_elements->back();
    }

    /**
     * @brief Find element or insert new one
     * @param line line to search
     * @return reference on found of created element
     * @see find()
     * @see construct()
     * @see insert()
     */
    auto findOrInsert(std::string line) -> T& {
        boost::optional<T&> temp = find(line);

        if (temp) {
            return *temp;
        }

        return insert(std::move(construct(line)));
    }
};


}  // namespace ES

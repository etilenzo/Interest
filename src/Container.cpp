/**
 * @file
 * @brief This file contains definitions of abstract template Container class
 * @author Evilenzo
 * @version 0.1
 */

#include "Container.hpp"

namespace ES {


template <typename T>
Container<T>::Container(const Container& container) : m_elements(container.m_elements) {}

template <typename T>
Container<T>::Container(Container&& container) noexcept : m_elements(std::move(container)) {
    container.m_elements.reset();
}


}  // namespace ES

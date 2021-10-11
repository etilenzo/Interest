/**
 * @file
 * @brief This file contains declaration of Error struct
 * @author Evilenzo
 * @version 0.1
 */

#pragma once

#include <memory>

namespace ES {


/// @brief Error codes enum
enum class Code { BROKEN_INPUT_STREAM, MISSING_FIRST_SECTION, WRONG_LINE };

/// @brief Error struct containing code and line number
struct Error {
    /// @brief Error code
    Code code;

    /// @brief Line number
    std::size_t line;

    /**
     * @brief Constructor with param initialization
     * @param _code error code
     * @param _line line number
     */
    Error(Code _code = Code(), std::size_t _line = std::size_t())
        : code(std::move(_code)), line(std::move(_line)) {}

    /// @brief Copy constructor
    Error(const Error& error) = default;

    /// @brief Move constructor
    Error(Error&& error) noexcept = default;

    /// @brief Copy assignment operator
    Error& operator=(const Error& error) = default;

    /// @brief Move assignment operator
    Error& operator=(Error&& error) noexcept = default;

    /// @brief Empty destructor
    ~Error() = default;
};


}  // namespace ES

/**
 * @file
 * @brief This file contains declaration of Settings struct
 * @author Evilenzo
 * @version 0.3
 */

#pragma once

#include <memory>

namespace ES {


/**
 * @brief The Section Duplicate enum
 * @details FIRST - process only first entry
 * LAST - process only last entry
 * UNITE - Unite settings of both sections
 * @see OptionDuplicate
 */
enum class SectionDuplicate { FIRST, LAST, UNITE };

/**
 * @brief The Option Duplicate enum
 * @details FIRST - process only first entry
 * LAST - process only last entry
 */
enum class OptionDuplicate { FIRST, LAST };

/**
 * @brief The Parse Type enum
 * @details NEW - do clear() before parse
 * APPEND - process as continuation of contained ini (you must set right SectionDuplicate and
 * OptionDuplicate values for that. For ex. if you have both settings set to FIRST, nothing is gonna
 * happen)
 */
enum class ParseType { NEW, APPEND };

/// @brief The Quotation Marks enum
enum class QuotationMarks { REMOVE, KEEP };

/// @brief Settings struct for Ini parser
struct Settings {
    /// @brief Decide what to do when there is a section duplicate
    SectionDuplicate m_section_duplicate;

    /// @brief Decide what to do when there is a option duplicate
    OptionDuplicate m_option_duplicate;

    /// @brief Decide how to do parseFromStream()
    ParseType m_parse_type;

    /// @brief Decide what to do when there are quotation marks
    QuotationMarks m_quotation_marks;

    /// @brief Constructor with param initialization (or empty)
    Settings(SectionDuplicate section_duplicate = {}, OptionDuplicate option_duplicate = {},
             ParseType parse_type = {}, QuotationMarks quotation_marks = {})
        : m_section_duplicate(section_duplicate),
          m_option_duplicate(option_duplicate),
          m_parse_type(parse_type),
          m_quotation_marks(quotation_marks) {}

    /// @brief Copy constructor
    Settings(const Settings& settings) = default;

    /// @brief Move constructor
    Settings(Settings&& settings) noexcept = default;

    /// @brief Copy assignment operator
    Settings& operator=(const Settings& settings) = default;

    /// @brief Move assignment operator
    Settings& operator=(Settings&& settings) noexcept = default;

    /// @brief Empty destructor
    ~Settings() = default;
};


}  // namespace ES

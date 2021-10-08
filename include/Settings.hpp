/**
 * @file
 * @brief This file contains declaration of Options struct
 * @author Evilenzo
 * @version 0.1
 */

#pragma once

#include <memory>

namespace ES {


/**
 * @brief The Section Duplicate enum
 * @details FIRST - process only first entry
 * LAST - process only last entry
 * UNITE - Unite options of both sections
 * @see OptionsDuplicate
 */
enum class SectionDuplicate { FIRST, LAST, UNITE };

/**
 * @brief The Option Duplicate enum
 * @details FIRST - process only first entry
 * LAST - process only last entry
 */
enum class OptionDuplicate { FIRST, LAST };

/// @brief The Quotation Marks enum
enum class QuotationMarks { REMOVE, KEEP };

/// @brief The Spaces enum
enum class Spaces { REMOVE, KEEP };

/**
 * @brief The Parse Type enum
 * @details NEW - do clear() before parse
 * APPEND - process as continuation of contained ini (you must set right SecitonDuplicate and
 * OptionDuplicate values for that. For ex. if you have both options set to FIRST, nothing is gonna
 * happen)
 */
enum class ParseType { NEW, APPEND };

/// @brief Options struct for Ini parser
struct Options {
    /// @brief Decide what to do when there is a section duplicate
    SectionDuplicate m_sections_duplicates;

    /// @brief Decide what to do when there is a option duplicate
    OptionDuplicate m_options_duplicates;

    /// @brief Decide what to do when there are a quotation marks
    QuotationMarks m_quotation_marks;

    /// @brief Decide what to do with spaces before and after = symbol (not in a value)
    Spaces m_spaces;

    /// @brief Decide how to do parseFromStream()
    ParseType m_parse_type;

    /// @brief Constructor with param initialization (or empty)
    Options(SectionDuplicate sections_duplicate = SectionDuplicate::FIRST,
            OptionDuplicate options_duplicate = OptionDuplicate::FIRST,
            QuotationMarks quotation_marks = QuotationMarks::REMOVE, Spaces spaces = Spaces::REMOVE,
            ParseType parse_type = ParseType::NEW)
        : m_sections_duplicates(std::move(sections_duplicate)),
          m_options_duplicates(std::move(options_duplicate)),
          m_quotation_marks(std::move(quotation_marks)),
          m_spaces(std::move(spaces)),
          m_parse_type(std::move(parse_type)) {}

    /**
     * @brief Copy constructor
     * @param options const l-value reference to another instance
     */
    Options(const Options& options) = default;

    /**
     * @brief Move constructor
     * @param options r-value reference to another instance
     */
    Options(Options&& options) noexcept = default;

    /**
     * @brief Copy assignment operator
     * @param options const l-value reference to another instance
     * @return *this
     */
    Options& operator=(const Options& options) = default;

    /**
     * @brief Move assignment operator
     * @param options r-value reference to another instance
     * @return *this
     */
    Options& operator=(Options&& options) noexcept = default;

    /// @brief Empty destructor
    ~Options() = default;
};


}  // namespace ES

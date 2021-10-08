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

    /// @brief Constructor with param initialization (or empty)
    Options(SectionDuplicate sections_duplicate = SectionDuplicate::FIRST,
            OptionDuplicate options_duplicate = OptionDuplicate::FIRST,
            QuotationMarks quotation_marks = QuotationMarks::REMOVE, Spaces spaces = Spaces::REMOVE)
        : m_sections_duplicates(std::move(sections_duplicate)),
          m_options_duplicates(std::move(options_duplicate)),
          m_quotation_marks(std::move(quotation_marks)),
          m_spaces(std::move(spaces)) {}

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

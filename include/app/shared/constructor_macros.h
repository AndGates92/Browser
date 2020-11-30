#ifndef CONSTRUCTOR_MACROS_H
#define CONSTRUCTOR_MACROS_H
/**
 * @copyright
 * @file constructor_macros.h
 * @author Andrea Gianarda
 * @date 27th of March 2020
 * @brief Constructor Macros file
*/

/** @defgroup SharedGroup Shared Macros and Functions Doxygen Group
 *  Shared Macros and Functions
 *  @{
 */

/**
 * @brief DISABLE_COPY(CLASS)
 *
 * \param CLASS : class name that cannot be copied
 *
 * Disable copy constructor and operator= overloading
 */
#define DISABLE_COPY(CLASS) \
	explicit CLASS(const CLASS & rhs) = delete; \
	CLASS & operator=(const CLASS & rhs) = delete;

/**
 * @brief DISABLE_MOVE(CLASS)
 *
 * \param CLASS : class name that cannot be moved
 *
 * Disable move constructor and operator= overloading
 */
#define DISABLE_MOVE(CLASS) \
	explicit CLASS(CLASS && rhs) = delete; \
	CLASS & operator=(CLASS && rhs) = delete;

/**
 * @brief DISABLE_COPY_MOVE(CLASS)
 *
 * \param CLASS : class name that cannot be moved and copied
 *
 * Disable move and copy constructors and operator= overloading
 */
#define DISABLE_COPY_MOVE(CLASS) \
	DISABLE_COPY(CLASS) \
	DISABLE_MOVE(CLASS)

/** @} */ // End of SharedGroup group

#endif // CONSTRUCTOR_MACROS_H

#ifndef GLOBAL_MACROS_H
#define GLOBAL_MACROS_H
/**
 * @copyright
 * @file global_macros.h
 * @author Andrea Gianarda
 * @date 30th October 2020
 * @brief Global Macros file
*/

/** @defgroup CommonGroup Common Macros and Functions Doxygen Group
 *  Common Macros and Functions
 *  @{
 */

/**
 * @brief TOKENPASTE2(VALUE1, VALUE2)
 *
 * \param VALUE1: first token
 * \param VALUE2: second token
 *
 * Internal version of token pasting
 */
#define TOKENPASTE2(VALUE1, VALUE2)\
	VALUE1 ## VALUE2

/**
 * @brief TOKENPASTE(VALUE1, VALUE2)
 *
 * \param VALUE1: first token
 * \param VALUE2: second token
 *
 * This macro pastes two tokens
 */
#define TOKENPASTE(VALUE1, VALUE2)\
	TOKENPASTE2(VALUE1, VALUE2)


/**
 * @brief STRINGIFY(VALUE)
 *
 * \param VALUE: first token
 *
 * This macro expands a macro before stringifying it
 */
#define STRINGIFY(VALUE)\
	STRINGIFY2(VALUE)

/**
 * @brief STRINGIFY2(VALUE)
 *
 * \param VALUE: first token
 *
 * This macro stringifies a macro
 */
#define STRINGIFY2(VALUE)\
	#VALUE

/** @} */ // End of CommonGroup group

#endif // GLOBAL_MACROS_H

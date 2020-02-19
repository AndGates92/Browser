#ifndef GLOBAL_TYPES_H
#define GLOBAL_TYPES_H
/**
 * @copyright
 * @file global_types.h
 * @author Andrea Gianarda
 * @date 17th of September 2019
 * @brief Global Types file
*/

/** @defgroup GlobalTypesGroup Global Types Doxygen Group
 *  Global Types
 *  @{
 */
namespace global_types {

	/**
	 * @brief Verbosity levels
	 *
	 */
	typedef enum class qinfo_level_list {
		ZERO,   /**< Always printed */
		LOW,    /**< Low level pf printing */
		MEDIUM, /**< Medium level of printing */
		HIGH    /**< High level of printing */
	} qinfo_level_e;

	/**
	 * @brief Verbosity levels
	 *
	 */
	typedef enum class sign_list {
		MINUS =  -1,   /**< Minus sign */
		NOSIGN =  0,   /**< No sign */
		PLUS =    1,   /**< Plus sign */
	} sign_e;

}

/** @} */ // End of GlobalTypesGroup group

#endif // GLOBAL_TYPES_H

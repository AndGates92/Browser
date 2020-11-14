#ifndef SMART_PTR_MACROS_H
#define SMART_PTR_MACROS_H
/**
 * @copyright
 * @file smart_ptr_macros.h
 * @author Andrea Gianarda
 * @date 27th of March 2020
 * @brief Smart Pointer Macros file
*/

/** @defgroup CommonGroup Common Macros and Functions Doxygen Group
 *  Common Macros and Functions
 *  @{
 */

/**
 * @brief INHERITED_SHARED_FROM_THIS(DERIVED, BASE)
 *
 * \param DERIVED : derived class
 * \param BASE : base class
 *
 * Define shared from this for a derived class
 */
#define INHERITED_SHARED_FROM_THIS(DERIVED, BASE) \
	std::shared_ptr<DERIVED> shared_from_this() { \
		return std::static_pointer_cast<DERIVED>(BASE::shared_from_this()); \
	}

/**
 * @brief INHERITED_WEAK_FROM_THIS(DERIVED)
 *
 * \param DERIVED : derived class
 *
 * Define weak from this for a derived class
 */
#define INHERITED_WEAK_FROM_THIS(DERIVED) \
	std::weak_ptr<DERIVED> weak_from_this() { \
		return this->shared_from_this(); \
	}

/**
 * @brief SMART_POINTER_FROM_THIS_FUNCTIONS(DERIVED, BASE)
 *
 * \param DERIVED : derived class
 * \param BASE : base class
 *
 * Get smart pointer from this
 */
#define SMART_PTR_FROM_THIS_FUNCTIONS(DERIVED, BASE) \
	INHERITED_SHARED_FROM_THIS(DERIVED, BASE) \
	INHERITED_WEAK_FROM_THIS(DERIVED)

/** @} */ // End of CommonGroup group

#endif // SMART_PTR_MACROS_H

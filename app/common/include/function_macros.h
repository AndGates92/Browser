#ifndef FUNCTION_MACROS_H
#define FUNCTION_MACROS_H
/**
 * @copyright
 * @file function_macros.h
 * @author Andrea Gianarda
 * @date 10th of April 2020
 * @brief Function Macros file
*/

/** @defgroup FunctionMacrosGroup Function Macros Doxygen Group
 *  Function Macros
 *  @{
 */

/**
 * @brief PTR_SETTER(FNAME, ARGTYPE, VAR)
 *
 * \param FNAME : function name
 * \param ARGTYPE : type of input argument
 * \param VAR : class member to set
 *
 * Setter for a pointer in a class or struct
 */
#define PTR_SETTER(FNAME, ARGTYPE, VAR) \
	void FNAME(ARGTYPE * ptr) { \
		if (VAR != ptr) { \
			if (VAR != nullptr) { \
				delete VAR; \
			} \
			VAR = ptr; \
		}  \
	}

/**
 * @brief BASE_CLASS_PTR_GETTER(FNAME, ARGTYPE, VAR)
 *
 * \param FNAME : function name
 * \param ARGTYPE : type of returned value
 * \param VAR : class member to return
 *
 * Getter for a pointer in a class or struct
 */
#define BASE_CLASS_PTR_GETTER(FNAME, ARGTYPE, VAR) \
	ARGTYPE * FNAME() const { \
		return VAR; \
	}

/**
 * @brief BASE_CLASS_PTR_SETTER_GETTER(SFNAME, GFNAME, ARGTYPE, VAR)
 *
 * \param SFNAME : setter function name
 * \param GFNAME : getter function name
 * \param ARGTYPE : type of pointer to set and get
 * \param VAR : class member to set and return
 *
 * Create setters and getter for a pointer in a class or struct
 */
#define BASE_CLASS_PTR_SETTER_GETTER(SFNAME, GFNAME, ARGTYPE, VAR) \
	PTR_SETTER(SFNAME, ARGTYPE, VAR) \
	BASE_CLASS_PTR_GETTER(GFNAME, ARGTYPE, VAR)

/**
 * @brief DERIVED_CLASS_PTR_GETTER(FNAME, ARGTYPE, VAR)
 *
 * \param FNAME : function name
 * \param ARGTYPE : type of returned value
 * \param VAR : class member to return
 *
 * Getter for a pointer in a derived class or struct that requires downcasting
 */
#define DERIVED_CLASS_PTR_GETTER(FNAME, ARGTYPE, VAR) \
ARGTYPE * FNAME() const { \
	try { \
		ARGTYPE * ptr = dynamic_cast<ARGTYPE *>(VAR); \
		return ptr; \
	} catch (const std::bad_cast & badCastE) { \
		QEXCEPTION_ACTION(throw, badCastE.what()); \
	} \
	return nullptr; \
}

/** @} */ // End of FunctionMacrosGroup group

#endif // FUNCTION_MACROS_H

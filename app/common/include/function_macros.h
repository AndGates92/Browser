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
 * @brief BASE_SETTER(FNAME, ARGTYPE, VAR)
 *
 * \param FNAME : function name
 * \param ARGTYPE : type of argument to set
 * \param VAR : class member to set
 *
 * General setter for a member in a class or struct
 */
#define BASE_SETTER(FNAME, ARGTYPE, VAR) \
	void FNAME(ARGTYPE value) { \
		if (VAR != value) { \
			VAR = value; \
		}  \
	}

/**
 * @brief BASE_GETTER(FNAME, ARGTYPE, VAR)
 *
 * \param FNAME : function name
 * \param ARGTYPE : type of returned value
 * \param VAR : class member to return
 *
 * General getter for a member in a class or struct
 */
#define BASE_GETTER(FNAME, ARGTYPE, VAR) \
	ARGTYPE FNAME() const { \
		return VAR; \
	}

/**
 * @brief BASE_SETTER_GETTER(SFNAME, GFNAME, ARGTYPE, VAR)
 *
 * \param SFNAME : setter function name
 * \param GFNAME : getter function name
 * \param ARGTYPE : type of variable to set and get
 * \param VAR : class member to set and return
 *
 * Create setters and getter for a member in a class or struct
 */
#define BASE_SETTER_GETTER(SFNAME, GFNAME, ARGTYPE, VAR) \
	BASE_SETTER(SFNAME, ARGTYPE, VAR) \
	BASE_GETTER(GFNAME, ARGTYPE, VAR)

/**
 * @brief CONST_SETTER(FNAME, ARGTYPE, VAR)
 *
 * \param FNAME : function name
 * \param ARGTYPE : type of argument to set
 * \param VAR : class member to set
 *
 * Const setter for a member in a class or struct
 */
#define CONST_SETTER(FNAME, ARGTYPE, VAR) \
	BASE_SETTER(FNAME, const ARGTYPE, VAR)

/**
 * @brief CONST_GETTER(FNAME, ARGTYPE, VAR)
 *
 * \param FNAME : function name
 * \param ARGTYPE : type of returned value
 * \param VAR : class member to return
 *
 * Const getter for a member in a class or struct
 */
#define CONST_GETTER(FNAME, ARGTYPE, VAR) \
	BASE_GETTER(FNAME, const ARGTYPE, VAR)

/**
 * @brief CONST_SETTER_GETTER(SFNAME, GFNAME, ARGTYPE, VAR)
 *
 * \param SFNAME : setter function name
 * \param GFNAME : getter function name
 * \param ARGTYPE : type of variable to set and get
 * \param VAR : class member to set and return
 *
 * Create setters and getter for a member in a class or struct
 * Getter returns a const value
 */
#define CONST_SETTER_GETTER(SFNAME, GFNAME, ARGTYPE, VAR) \
	CONST_SETTER(SFNAME, ARGTYPE, VAR) \
	CONST_GETTER(GFNAME, ARGTYPE, VAR)

/**
 * @brief CONST_REF_SETTER(FNAME, ARGTYPE, VAR)
 *
 * \param FNAME : function name
 * \param ARGTYPE : type of argument to set
 * \param VAR : class member to set
 *
 * Const ref setter for a member in a class or struct
 */
#define CONST_REF_SETTER(FNAME, ARGTYPE, VAR) \
	void FNAME(const ARGTYPE & value) { \
		if (VAR != value) { \
			VAR = value; \
		}  \
	}

/**
 * @brief CONST_REF_SETTER_GETTER(SFNAME, GFNAME, ARGTYPE, VAR)
 *
 * \param SFNAME : setter function name
 * \param GFNAME : getter function name
 * \param ARGTYPE : type of variable to set and get
 * \param VAR : class member to set and return
 *
 * Create setters and getter for a member in a class or struct
 * Setter argument is a const ref
 * Getter returns a const value
 */
#define CONST_REF_SETTER_GETTER(SFNAME, GFNAME, ARGTYPE, VAR) \
	CONST_REF_SETTER(SFNAME, ARGTYPE, VAR) \
	CONST_GETTER(GFNAME, ARGTYPE, VAR)

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
	void FNAME(ARGTYPE * value) { \
		if (VAR != value) { \
			if (VAR != nullptr) { \
				delete VAR; \
			} \
			VAR = value; \
		}  \
	}

/**
 * @brief PTR_GETTER(FNAME, ARGTYPE, VAR)
 *
 * \param FNAME : function name
 * \param ARGTYPE : type of returned value
 * \param VAR : class member to return
 *
 * Getter for a pointer in a class or struct
 */
#define PTR_GETTER(FNAME, ARGTYPE, VAR) \
	BASE_GETTER(FNAME, ARGTYPE *, VAR)

/**
 * @brief PTR_SETTER_GETTER(SFNAME, GFNAME, ARGTYPE, VAR)
 *
 * \param SFNAME : setter function name
 * \param GFNAME : getter function name
 * \param ARGTYPE : type of pointer to set and get
 * \param VAR : class member to set and return
 *
 * Create setters and getter for a pointer in a class or struct
 */
#define PTR_SETTER_GETTER(SFNAME, GFNAME, ARGTYPE, VAR) \
	BASE_SETTER_GETTER(SFNAME, GFNAME, ARGTYPE *, VAR)

/**
 * @brief CASTED_PTR_GETTER(FNAME, ARGTYPE, VAR)
 *
 * \param FNAME : function name
 * \param ARGTYPE : type of returned value
 * \param VAR : class member to return or function returning it
 *
 * Getter for a pointer in a derived class or struct that requires downcasting
 */
#define CASTED_PTR_GETTER(FNAME, ARGTYPE, VAR) \
ARGTYPE * FNAME() const { \
	try { \
		ARGTYPE * ptr = dynamic_cast<ARGTYPE *>(VAR); \
		return ptr; \
	} catch (const std::bad_cast & badCastE) { \
		QEXCEPTION_ACTION(throw, badCastE.what()); \
	} \
	return nullptr; \
}

/**
 * @brief CASTED_PTR_SETTER_GETTER(SFNAME, GFNAME, ARGTYPE, SVAR, GVAR)
 *
 * \param SFNAME : setter function name
 * \param GFNAME : getter function name
 * \param ARGTYPE : type of pointer to set and get
 * \param SVAR : class member to set
 * \param GVAR : class member to return or function returning it
 *
 * Create setters and getter with downcasting for a pointer in a class or struct
 */
#define CASTED_PTR_SETTER_GETTER(SFNAME, GFNAME, ARGTYPE, SVAR, GVAR) \
	PTR_SETTER(SFNAME, ARGTYPE, SVAR) \
	CASTED_PTR_GETTER(GFNAME, ARGTYPE, GVAR)

/**
 * @brief CONST_PTR_SETTER(FNAME, ARGTYPE, VAR)
 *
 * \param FNAME : function name
 * \param ARGTYPE : type of input argument
 * \param VAR : class member to set
 *
 * Setter for a pointer in a class or struct
 */
#define CONST_PTR_SETTER(FNAME, ARGTYPE, VAR) \
	PTR_SETTER(FNAME, const ARGTYPE, VAR)

/**
 * @brief CONST_PTR_GETTER(FNAME, ARGTYPE, VAR)
 *
 * \param FNAME : function name
 * \param ARGTYPE : type of returned value
 * \param VAR : class member to return
 *
 * Getter for a const pointer in a class or struct
 */
#define CONST_PTR_GETTER(FNAME, ARGTYPE, VAR) \
	PTR_GETTER(FNAME, const ARGTYPE, VAR)

/**
 * @brief CONST_PTR_SETTER_GETTER(SFNAME, GFNAME, ARGTYPE, VAR)
 *
 * \param SFNAME : setter function name
 * \param GFNAME : getter function name
 * \param ARGTYPE : type of pointer to set and get
 * \param VAR : class member to set and return
 *
 * Create setters and getter for a const pointer in a class or struct
 */
#define CONST_PTR_SETTER_GETTER(SFNAME, GFNAME, ARGTYPE, VAR) \
	CONST_PTR_SETTER(SFNAME, ARGTYPE, VAR) \
	CONST_PTR_GETTER(GFNAME, ARGTYPE, VAR)

/** @} */ // End of FunctionMacrosGroup group

#endif // FUNCTION_MACROS_H

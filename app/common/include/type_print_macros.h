#ifndef TYPE_PRINT_MACROS_H
#define TYPE_PRINT_MACROS_H
/**
 * @copyright
 * @file logging_macros.h
 * @author Andrea Gianarda
 * @date 17th of September 2019
 * @brief Type Print Macros file
*/

#include "global_functions.h"

/** @defgroup TypePrintMacrosGroup Type Print Macros Doxygen Group
 *  Type Print Macros
 *  @{
 */

/**
 * @brief QDEBUG_OVERLOAD_PRINT_OP(TYPE)
 *
 * \param TYPE : type to have operator << overloaded for
 *
 * Creates function overloading operator << for a type Type.
 * It needs the type to be coverted to a QString
 */
#define QDEBUG_OVERLOAD_PRINT_OP(TYPE) \
	QDebug & operator<< (QDebug & os, const TYPE & value) { \
		QString str(QString::null); \
		str << value; \
		os << str; \
		return os; \
	}

/**
 * @brief QSTRING_OVERLOAD_PRINT_OP(TYPE)
 *
 * \param TYPE : type to have operator << overloaded for
 *
 * Creates function overloading operator << for a type Type.
 * It needs the type to be coverted to a QString
 */
#define QSTRING_OVERLOAD_PRINT_OP(TYPE) \
	QString & operator<< (QString & str, const TYPE & value) { \
		QString valStr(global_functions::qEnumToQString<TYPE>(value, false)); \
		str.append(valStr); \
		return str; \
	}

/**
 * @brief QSTRING_OVERLOAD_PLUS_OP(TYPE)
 *
 * \param TYPE : type to have operator + overloaded for
 *
 * Creates function overloading operator + for a type Type.
 */
#define QSTRING_OVERLOAD_PLUS_OP(TYPE) \
	const QString operator+ (const QString & str, const TYPE & value) { \
		QString mergedStr(QString::null); \
		QTextStream(&mergedStr) << str << value; \
		return str; \
	}

/**
 * @brief STRING_OVERLOAD_PLUS_OP(TYPE)
 *
 * \param TYPE : type to have operator + overloaded for
 *
 * Creates function overloading operator + for a type Type.
 */
#define STRING_OVERLOAD_PLUS_OP(TYPE) \
	const std::string operator+ (const std::string & str, const TYPE & value) { \
		QString valStr(global_functions::qEnumToQString<TYPE>(value, false)); \
		std::string mergedStr; \
		mergedStr = str + valStr.toStdString(); \
		return mergedStr; \
	}

/**
 * @brief CHAR_OVERLOAD_PLUS_OP(TYPE)
 *
 * \param TYPE : type to have operator + overloaded for
 *
 * Creates function overloading operator + for a type Type.
 */
#define CHAR_OVERLOAD_PLUS_OP(TYPE) \
	const std::string operator+ (const char * str, const TYPE & value) { \
		QString valStr(global_functions::qEnumToQString<TYPE>(value, false)); \
		std::string mergedStr; \
		mergedStr = str + valStr.toStdString(); \
		return mergedStr; \
	}

/**
 * @brief QTEXTSTREAM_OVERLOAD_PRINT_OP(TYPE)
 *
 * \param TYPE : type to have operator << overloaded for
 *
 * Creates function overloading operator << for a type Type.
 */
#define QTEXTSTREAM_OVERLOAD_PRINT_OP(TYPE) \
	QTextStream & operator<< (QTextStream & str, const TYPE & value) { \
		QString valStr(global_functions::qEnumToQString<TYPE>(value, false)); \
		str << valStr; \
		return str; \
	}

/**
 * @brief OVERLOAD_OPERATORS_CUSTOM_TYPE(TYPE)
 *
 * \param TYPE : type to have operator overloaded for
 *
 * Define function body to overload operator + and operator << for a type Type.
 */
#define OVERLOAD_OPERATORS_CUSTOM_TYPE(TYPE) \
	STRING_OVERLOAD_PLUS_OP(TYPE) \
	CHAR_OVERLOAD_PLUS_OP(TYPE) \
	QDEBUG_OVERLOAD_PRINT_OP(TYPE) \
	QSTRING_OVERLOAD_PRINT_OP(TYPE) \
	QTEXTSTREAM_OVERLOAD_PRINT_OP(TYPE) \
	QSTRING_OVERLOAD_PLUS_OP(TYPE)

/**
 * @brief OVERLOAD_OPERATORS_CUSTOM_TYPE_FUNCTION_PROTOTYPE(TYPE, ALIAS)
 *
 * \param TYPE : type to have operator overloaded for
 * \param ALIAS : alias for type TYPE
 *
 * Declares function prototypes to overload operator + and operator << for a type Type.
 */
#define OVERLOAD_OPERATORS_CUSTOM_TYPE_FUNCTION_PROTOTYPE(TYPE, ALIAS) \
	Q_ENUM_NS(TYPE) \
	QDebug & operator<< (QDebug & os, const ALIAS & value); \
	QTextStream & operator<< (QTextStream & str, const ALIAS & value); \
	QString & operator<< (QString & str, const ALIAS & value); \
	const QString operator+ (const QString & str, const ALIAS & value); \
	const std::string operator+ (const std::string & str, const ALIAS & value); \
	const std::string operator+ (const char * cStr, const ALIAS & value);

/**
 * @brief PRINT_LIST(VERBOSITY, CATEGORY, TYPE, NAME, LIST)
 *
 * \param TYPE : type to have operator overloaded for
 * \param VERBOSITY: verbosity level
 * \param CATEGORY: print category
 * \param NAME: name of the list
 * \param LIST: list to print
 *
 * Print all elements of a list
 */
#define PRINT_LIST(VERBOSITY, CATEGORY, TYPE, NAME, LIST) \
	std::for_each( \
		LIST.cbegin(), \
		LIST.cend(), \
		[&](const TYPE & el) { \
			QINFO_PRINT(VERBOSITY, CATEGORY,  "[ List " << NAME << " ] Element " << el.qprint()); \
		} \
	);

/** @} */ // End of TypePrintMacrosGroup group

#endif // TYPE_PRINT_MACROS_H

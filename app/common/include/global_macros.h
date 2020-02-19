#ifndef GLOBAL_MACROS_H
#define GLOBAL_MACROS_H
/**
 * @copyright
 * @file global_macros.h
 * @author Andrea Gianarda
 * @date 17th of September 2019
 * @brief Global Macros file
*/

#include "global_types.h"

/** @defgroup GlobalMacrosGroup Global Macros Doxygen Group
 *  Global Macros
 *  @{
 */

/**
 * @brief Default message type level
 *
 */
#if !defined(MSG_TYPE_LEVEL)
	#define MSG_TYPE_LEVEL QtInfoMsg
#endif

/**
 * @brief Default qinfo verbosity level
 *
 */
#if !defined(QINFO_VERBOSITY)
	#define QINFO_VERBOSITY global_types::qinfo_level_e::MEDIUM
#endif

/**
 * @brief QDEBUG_PRINT(CATEGORY, ...)
 *
 * \param CATEGORY  : category of the print
 * \param ...       : variable number of arguments to provide to debugMsg
 *
 * Print a debug message to the log file
 */
#define QDEBUG_PRINT(CATEGORY, ...)\
	QDebug debugMsg(qDebug(CATEGORY)); \
	debugMsg.noquote(); \
	debugMsg.nospace(); \
	debugMsg << __VA_ARGS__; \

/**
 * @brief QINFO_PRINT(VERBOSITY, CATEGORY, ...)
 *
 * \param VERBOSITY : verbosity level
 * \param CATEGORY  : category of the print
 * \param ...       : variable number of arguments to provide to infoMsg
 *
 * Print a message to the log file if the chosen verbosity is less or equal to the default verbosity
 */
#define QINFO_PRINT(VERBOSITY, CATEGORY, ...)\
	if (VERBOSITY <= static_cast<global_types::qinfo_level_e>(QINFO_VERBOSITY)) { \
		QDebug infoMsg(qInfo(CATEGORY)); \
		infoMsg.noquote(); \
		infoMsg.nospace(); \
		infoMsg << __VA_ARGS__; \
	}

/**
 * @brief QWARNING_PRINT(CATEGORY, ...)
 *
 * \param CATEGORY  : category of the print
 * \param ...       : variable number of arguments to provide to warningMsg
 *
 * Print a warning message to the log file
 */
#define QWARNING_PRINT(CATEGORY, ...)\
	QDebug warningMsg(qWarning(CATEGORY)); \
	warningMsg.noquote(); \
	warningMsg.nospace(); \
	warningMsg << __VA_ARGS__; \

/**
 * @brief QCRITICAL_PRINT(CONDITION, CATEGORY, ...)
 *
 * \param CONDITION : condition to print the message
 * \param CATEGORY  : category of the print
 * \param ...       : variable number of arguments to provide to infoMsg
 *
 * Print a critical message to the log file is the condition is true
 */
#define QCRITICAL_PRINT(CONDITION, CATEGORY, ...)\
	if (CONDITION) { \
		QDebug criticalMsg(qCritical(CATEGORY)); \
		criticalMsg.noquote(); \
		criticalMsg.nospace(); \
		criticalMsg << __VA_ARGS__; \
	}

/**
 * @brief QFATAL_PRINT(MSG)
 *
 * \param MSG  : text to print
 *
 * Print a fatal message to the log file
 */
#define QFATAL_PRINT(MSG) \
	qFatal(MSG);

/**
 * @brief QDEBUG_OVERLOAD_PRINT_OP(TYPE)
 *
 * \param TYPE : type to have operator << overloaded for
 *
 * Creates function overloading operator << for a type Type.
 * It needs the type to be coverted to a QString
 */
#define QDEBUG_OVERLOAD_PRINT_OP(TYPE) \
	QDebug & operator<< (QDebug & os, const TYPE & var) { \
		QString str(QString::null); \
		str << var; \
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
	QString operator<< (const QString & str, const TYPE & var) { \
		QString mergedStr(QString::null); \
		QTextStream(&mergedStr) << str <<  var; \
		return mergedStr; \
	}

/**
 * @brief QSTRING_OVERLOAD_PLUS_OP(TYPE)
 *
 * \param TYPE : type to have operator + overloaded for
 *
 * Creates function overloading operator + for a type Type.
 */
#define QSTRING_OVERLOAD_PLUS_OP(TYPE) \
	const QString operator+ (const QString & str, const TYPE & var) { \
		QString mergedStr(QString::null); \
		QTextStream(&mergedStr) << str << var; \
		return str; \
	}

/**
 * @brief OVERLOAD_OPERATORS_CUSTOM_TYPE(TYPE)
 *
 * \param TYPE : type to have operator overloaded for
 *
 * Creates function overloading operator + and operator << for a type Type.
 */
#define OVERLOAD_OPERATORS_CUSTOM_TYPE(TYPE) \
	QDEBUG_OVERLOAD_PRINT_OP(TYPE) \
	QSTRING_OVERLOAD_PRINT_OP(TYPE) \
	QSTRING_OVERLOAD_PLUS_OP(TYPE)

/** @} */ // End of GlobalMacrosGroup group

#endif // GLOBAL_MACROS_H

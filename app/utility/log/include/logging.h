#ifndef LOGGING_H
#define LOGGING_H
/**
 * @copyright
 * @file logging.h
 * @author Andrea Gianarda
 * @date 17th of September 2019
 * @brief Logging header file
*/

// Qt libraries
#include <QtCore/QMessageLogContext>
#include <QtCore/QString>
#include <QtCore/QFile>

/** @defgroup LoggingGroup Logging Doxygen Group
 *  Logging functions and classes
 *  @{
 */
namespace logging {

	/**
	 * @brief Function: void handler(QtMsgType type, const QMessageLogContext & context, const QString & message)
	 *
	 * \param type: message type
	 * \param context: context fo the message (function, file and category)
	 * \param message: message to be printed
	 *
	 * This function initialize graphics
	 */
	void handler(QtMsgType type, const QMessageLogContext & context, const QString & message);

	/**
	 * @brief Function: void set_default_category()
	 *
	 * This function enables message types depending on the MSG_TYPE_LEVEL macro
	 */
	void set_default_category();

	/**
	 * @brief Function: void makeMsg(std::string & str, firstType headArg, otherTypes ... otherArgs)
	 *
	 * \param str: std::string to be expanded by adding arguments
	 * \param headArg: argument to concatenate to the string provided as argument
	 * \param otherArgs: following arguments to concatenate to the string provided as argument
	 *
	 * This function creates a message from a template parameter pack
	 * It is required that the operator+ of std::string is overloaded with all types passed to the template parameter pack
	 */
	template <typename firstType, typename... otherTypes>
	void makeMsg(std::string & str, firstType headArg, otherTypes ... otherArgs);

	/**
	 * @brief Function: void makeMsg(std::string & str, lastType arg)
	 *
	 * \param str: std::string to be expanded by adding arguments
	 * \param arg: argument to concatenate to the string provided as argument
	 *
	 * This function creates a message from a template parameter pack
	 * It is required that the operator+ of std::string is overloaded with all types passed to the template parameter pack
	 */
	template <typename lastType>
	void makeMsg(std::string & str, lastType arg);

}

template <typename lastType>
void logging::makeMsg(std::string & str, lastType arg) {
	str = str + arg;
}

template <typename firstType, typename... otherTypes>
void logging::makeMsg(std::string & str, firstType headArg, otherTypes ... otherArgs) {
	str = str + headArg;
	logging::makeMsg(str, otherArgs...);
}

/** @} */ // End of LoggingGroup group

#endif // LOGGING_H

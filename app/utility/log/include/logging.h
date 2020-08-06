#ifndef LOGGING_H
#define LOGGING_H
/**
 * @copyright
 * @file logging.h
 * @author Andrea Gianarda
 * @date 17th of September 2019
 * @brief Logging header file
*/

#include <QtCore/QMessageLogContext>
#include <QtCore/QString>
#include <QtCore/QtGlobal>
#include <QtCore/QFile>

/**
 * @brief log filename
 *
 */
#if !defined(LOGFILE)
	#define LOGFILE browser.log
#endif

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

}
/** @} */ // End of LoggingGroup group

#endif // LOGGING_H

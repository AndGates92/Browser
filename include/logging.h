#ifndef LOGGING_H
#define LOGGING_H
/**
 * @copyright
 * @file logging.h
 * @author Andrea Gianarda
 * @date 17th of September 2019
 * @brief Logging header file
*/

#include <qt5/QtCore/QMessageLogContext>
#include <qt5/QtCore/QString>
#include <qt5/QtCore/QtGlobal>
#include <qt5/QtCore/QFile>

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

	namespace {
		/**
		 * @brief Global variable logfile
		 *
		 */
		QFile logfile(QT_STRINGIFY(LOGFILE));
	}

	/**
	 * @brief Function: void init_graphics(int argc, char** argv)
	 *
	 * \param argc: number of arguments
	 * \param argv: value of arguments
	 *
	 * This function initialize graphics
	 */
	void handler(QtMsgType type, const QMessageLogContext & context, const QString & message);

}
/** @} */ // End of LoggingGroup group

#endif // LOGGING_H

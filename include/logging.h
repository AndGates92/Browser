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

/**
 * @brief Default qinfo verbosity level
 *
 */
#if !defined(QINFO_VERBOSITY)
	#define QINFO_VERBOSITY MEDIUM
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
	 * @brief Verbosity levels
	 *
	 */
	typedef enum class qinfo_level_list {
		ZERO,   /**< Always printed */
		LOW,    /**< Low level */
		MEDIUM, /**< Medium level */
		HIGH,   /**< High level */
		DEBUG   /**< Debug level */
	} qinfo_level_e;

	/**
	 * @brief Function: void init_graphics(int argc, char** argv)
	 *
	 * \param argc: number of arguments
	 * \param argv: value of arguments
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

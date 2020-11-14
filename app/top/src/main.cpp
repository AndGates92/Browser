/**
 * @copyright
 * @file main.cpp
 * @author Andrea Gianarda
 * @date 15th September 2019
 * @brief Main function of the program
 */

#include <QtCore/QtMessageHandler>
#include <QtCore/QUnhandledException>

#include "top/include/init.h"
#include "utility/logger/include/macros.h"
#include "utility/exception/include/browser_exception.h"
#include "utility/log/include/logging.h"

/** @addtogroup MainGroup
 *  @{
 */

/** 
 * @brief Function: int main (int argc, char * argv[])
 *
 * \param argc: argument count. Number of arguments including the executable itself.
 * \param argv: argument vector. The first argument is the executable name. Last element of the array is NULL.
 * \return an integer corresponging to the exit status
 *
 * Decodes the arguments and call functions for further processing
 *
 */
int main (int argc, char* argv[]) {

	try {
		app::logging::set_default_category();
		qInstallMessageHandler(app::logging::handler);

		app::settings::Global::setLogPath(argc, argv);

		LOG_INFO(app::logger::info_level_e::ZERO, , "Starting browser");
		LOG_INFO(app::logger::info_level_e::ZERO, , "Built on " << __DATE__ << " at " << __TIME__);
		LOG_INFO(app::logger::info_level_e::ZERO, , "QT version " << QT_VERSION_STR);

		app::init::initializeBrowser(argc, argv);
	} catch (const app::browser_exception::BrowserException & bexc) {
		std::string bexcMsg(bexc.print());
		app::browser_exception::printException(bexcMsg);
		return EXIT_FAILURE;
	} catch (const QUnhandledException & unhandledexc) {
		app::browser_exception::printException("Got unhandled exception");
		return EXIT_FAILURE;
	} catch (const std::exception & exc) {
		app::browser_exception::printException(exc.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
/** @} */ // End of MainGroup group

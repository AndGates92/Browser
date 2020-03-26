/**
 * @copyright
 * @file main.cpp
 * @author Andrea Gianarda
 * @date 15th September 2019
 * @brief Main function of the program
 */

#include <qt5/QtCore/QtDebug>
#include <qt5/QtCore/QtGlobal>
#include <qt5/QtCore/QtMessageHandler>
#include <qt5/QtCore/QUnhandledException>

#include "logging_macros.h"
#include "browser_exception.h"
#include "logging.h"
#include "graphics.h"

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
		logging::set_default_category();
		qInstallMessageHandler(logging::handler);
		graphics::init_graphics(argc, argv);
	} catch (browser_exception::BrowserException bexc) {
		QString bexcMsg(bexc.print());
		browser_exception::printException(bexcMsg);
		return EXIT_FAILURE;
	} catch (QUnhandledException unhandledexc) {
		browser_exception::printException("Got unhandled exception");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
/** @} */ // End of MainGroup group

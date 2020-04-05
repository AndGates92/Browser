#ifndef MAIN_WINDOW_WEB_ENGINE_VIEW_H
#define MAIN_WINDOW_WEB_ENGINE_VIEW_H
/**
 * @copyright
 * @file main_window_web_engine_view.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Main Window Web Engine View header file
*/

// Qt libraries
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QLoggingCategory>

#include "main_window_web_engine_page.h"
#include "web_engine_view.h"
#include "global_types.h"
#include "constructor_macros.h"

/** @defgroup MainWindowWebEngineViewGroup Web Engine View Doxygen Group
 *  Main Window Web Engine View functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowWebEngineViewOverall)

namespace main_window_web_engine_view {

	/**
	 * @brief MainWindowWebEngineView class
	 *
	 */
	class MainWindowWebEngineView : public web_engine_view::WebEngineView {

		public:
			/**
			 * @brief Function: explicit MainWindowWebEngineView(QWidget * parent = Q_NULLPTR)
			 *
			 * \param parent: parent widget
			 *
			 * Main window web engine view constructor
			 */
			explicit MainWindowWebEngineView(QWidget * parent = Q_NULLPTR);

			/**
			 * @brief Function: virtual ~MainWindowWebEngineView()
			 *
			 * Main window web engine view destructor
			 */
			virtual ~MainWindowWebEngineView();

		protected:

		private:
			/**
			 * @brief web engine view
			 *
			 */
			main_window_web_engine_page::MainWindowWebEnginePage * page;

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class MainWindowWebEngineView
			 *
			 */
			DISABLE_COPY_MOVE(MainWindowWebEngineView)

	};
}
/** @} */ // End of MainWindowWebEngineViewGroup group

#endif // MAIN_WINDOW_WEB_ENGINE_VIEW_H

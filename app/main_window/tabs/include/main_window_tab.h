#ifndef MAIN_WINDOW_TAB_H
#define MAIN_WINDOW_TAB_H
/**
 * @copyright
 * @file main_window_tab.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Tab header file
*/

// Qt libraries
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QLoggingCategory>

#include <qt5/QtWidgets/QWidget>

#include "tab.h"
#include "global_types.h"
#include "constructor_macros.h"
#include "main_window_shared_types.h"
#include "main_window_web_engine_view.h"
#include "main_window_web_engine_search.h"

/** @defgroup TabGroup Tab Doxygen Group
 *  Tab functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowTabOverall)

namespace main_window_tab {

	/**
	 * @brief MainWindowTab class
	 *
	 */
	class MainWindowTab : public tab::Tab {

		public:
			/**
			 * @brief Function: explicit MainWindowTab(const main_window_shared_types::tab_type_e type, const void * tabContent, QWidget * parent = Q_NULLPTR)
			 *
			 * \param type: parent widget
			 * \param tabContent: tab content 
			 * \param parent: parent widget
			 *
			 * MainWindowTab constructor
			 */
			explicit MainWindowTab(const main_window_shared_types::tab_type_e type, const void * tabContent, QWidget * parent = Q_NULLPTR);

			/**
			 * @brief Function: virtual ~MainWindowTab()
			 *
			 * MainWindowTab destructor
			 */
			virtual ~MainWindowTab();

			/**
			 * @brief web engine view
			 *
			 */
			main_window_web_engine_view::MainWindowWebEngineView * widgetView;

			/**
			 * @brief seach class
			 *
			 */
			main_window_web_engine_search::MainWindowWebEngineSearch * search;

		protected:

		private:
			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class MainWindowTab
			 *
			 */
			DISABLE_COPY_MOVE(MainWindowTab)

	};
}
/** @} */ // End of TabGroup group

#endif // MAIN_WINDOW_TAB_H

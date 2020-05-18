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

#include "web_engine_view.h"
#include "main_window_web_engine_page.h"
#include "main_window_shared_types.h"
#include "global_types.h"
#include "constructor_macros.h"

/** @defgroup MainWindowWebEngineViewGroup Web Engine View Doxygen Group
 *  Main Window Web Engine View functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowWebEngineViewOverall)

namespace main_window_tab {
	class MainWindowTab;
}

namespace main_window_web_engine_view {

	/**
	 * @brief MainWindowWebEngineView class
	 *
	 */
	class MainWindowWebEngineView final : public web_engine_view::WebEngineView {
		friend class main_window_tab::MainWindowTab;

		Q_OBJECT

		public:
			/**
			 * @brief Function: explicit MainWindowWebEngineView(QWidget * parent, const main_window_shared_types::page_type_e type, const QString & src, const void * data)
			 *
			 * \param type: tab type
			 * \param src: source of the tab
			 * \param data: tab extra data
			 * \param parent: parent widget
			 *
			 * Main window web engine view constructor
			 */
			explicit MainWindowWebEngineView(QWidget * parent, const main_window_shared_types::page_type_e type, const QString & src, const void * data);

			/**
			 * @brief Function: virtual ~MainWindowWebEngineView()
			 *
			 * Main window web engine view destructor
			 */
			virtual ~MainWindowWebEngineView();

			/**
			 * @brief Function: main_window_web_engine_page::MainWindowWebEnginePage * page() const
			 *
			 * \return page of the view
			 *
			 * This function returns the page of this web engine view
			 */
			main_window_web_engine_page::MainWindowWebEnginePage * page() const;

		protected:

		private slots:
			/**
			 * @brief Function: void updatePageSource(const QUrl & url)
			 *
			 * \param url: url of the tab
			 *
			 * This function is a slot that receives a notification that the url has changed and it updates the page source
			 */
			void updatePageSource(const QUrl & url);

		private:
			/**
			 * @brief Function: void connectSignals()
			 *
			 * This function connects signals and slots within the web engine view
			 */
			void connectSignals();

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

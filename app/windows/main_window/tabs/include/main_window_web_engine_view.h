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

#include <qt5/QtWidgets/QAction>

#include "web_engine_view.h"
#include "main_window_web_engine_page.h"
#include "main_window_shared_types.h"
#include "global_enums.h"
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
			 * @brief Function: std::shared_ptr<main_window_web_engine_page::MainWindowWebEnginePage> page() const
			 *
			 * \return page of the view
			 *
			 * This function returns the page of this web engine view
			 */
			std::shared_ptr<main_window_web_engine_page::MainWindowWebEnginePage> page() const;

		protected:
			/**
			 * @brief Function: virtual void contextMenuEvent(QContextMenuEvent * event) override
			 *
			 * \param event: context menu event
			 *
			 * This function is a function that handles the context menu event. It editsslot that receives a notification that the url has changed and it updates the page source
			 * It edits the content of the menu
			 */
			virtual void contextMenuEvent(QContextMenuEvent * event) override;

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

			/**
			 * @brief Function: bool isSameAction(const QAction * lhs, const QAction * rhs) const
			 *
			 * \param lhs: left hand side of the comparison
			 * \param rhs: right hand side of the comparison
			 *
			 * \return a boolean is the 2 QAction are identical or not
			 *
			 * This function implements the comparison between two QActions
			 * In order to be identical, QAction must have the following members identical:
			 *  - shortcut list size
			 *  - shortcuts
			 *  - text without mnemonics
			 */
			bool isSameAction(const QAction * lhs, const QAction * rhs) const;

			/**
			 * @brief Function: QAction * addActionListToMenu(QMenu * menu, QAction * pos, const QList<QAction *> & actionList)
			 *
			 * \param menu: menu to add actions to
			 * \param pos: positon of the new added action
			 * \param actionList: list of actions to add
			 *
			 * \return pointer to the action after the last one in the list
			 *
			 * This function adds a list of action to a menu and returns a pointer to the action after the last one in the list
			 */
			QAction * addActionListToMenu(QMenu * menu, QAction * pos, const QList<QAction *> & actionList);

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

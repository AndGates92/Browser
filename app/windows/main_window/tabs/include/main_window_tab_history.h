#ifndef MAIN_WINDOW_TAB_HISTORY_H
#define MAIN_WINDOW_TAB_HISTORY_H
/**
 * @copyright
 * @file main_window_tab_history.h
 * @author Andrea Gianarda
 * @date 25th May 2020
 * @brief Tab History header file
*/

#include "base/tabs/include/tab_history.h"
#include "common/include/global_enums.h"

/** @defgroup MainWindowTabHistoryGroup Tab History Doxygen Group
 *  Tab History functions and classes
 *  @{
 */

namespace main_window_tab {
	class MainWindowTab;
}

namespace main_window_tab_history {

	/**
	 * @brief MainWindowTabHistory class
	 *
	 */
	class MainWindowTabHistory final : public tab_history::TabHistory {
		friend class main_window_tab::MainWindowTab;

		public:
			/**
			 * @brief Function: explicit MainWindowTabHistory(QWidget * parent, std::weak_ptr<tab::Tab> browserTab, QWebEngineHistory * history)
			 *
			 * \param parent: parent widget
			 * \param tab: tab
			 * \param history: history of the history
			 *
			 * Main window tab history constructor
			 */
			explicit MainWindowTabHistory(QWidget * parent, std::weak_ptr<tab::Tab> browserTab, QWebEngineHistory * history);

			/**
			 * @brief Function: virtual ~MainWindowTabHistory()
			 *
			 * Main window tab history destructor
			 */
			virtual ~MainWindowTabHistory();

		protected:

		private:

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class MainWindowTabHistory
			 *
			 */
			DISABLE_COPY_MOVE(MainWindowTabHistory)

	};
}
/** @} */ // End of MainWindowTabHistoryGroup group

#endif // MAIN_WINDOW_TAB_HISTORY_H

#ifndef MAIN_WINDOW_TAB_HISTORY_H
#define MAIN_WINDOW_TAB_HISTORY_H
/**
 * @copyright
 * @file tab_history.h
 * @author Andrea Gianarda
 * @date 25th May 2020
 * @brief Tab History header file
*/

#include "base/tabs/include/tab_history.h"
#include "common/include/global_enums.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */

namespace main_window {

	class Tab;

	/**
	 * @brief TabHistory class
	 *
	 */
	class TabHistory final : public tab_history::TabHistory {
		friend class main_window::Tab;

		public:
			/**
			 * @brief Function: explicit TabHistory(QWidget * parent, std::weak_ptr<tab::Tab> browserTab, QWebEngineHistory * history)
			 *
			 * \param parent: parent widget
			 * \param tab: tab
			 * \param history: history of the history
			 *
			 * Main window tab history constructor
			 */
			explicit TabHistory(QWidget * parent, std::weak_ptr<tab::Tab> browserTab, QWebEngineHistory * history);

			/**
			 * @brief Function: virtual ~TabHistory()
			 *
			 * Main window tab history destructor
			 */
			virtual ~TabHistory();

		protected:

		private:

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class TabHistory
			 *
			 */
			DISABLE_COPY_MOVE(TabHistory)

	};
}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_TAB_HISTORY_H

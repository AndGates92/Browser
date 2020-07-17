#ifndef MAIN_WINDOW_WEB_ENGINE_HISTORY_H
#define MAIN_WINDOW_WEB_ENGINE_HISTORY_H
/**
 * @copyright
 * @file main_window_web_engine_history.h
 * @author Andrea Gianarda
 * @date 25th May 2020
 * @brief Web Engine History header file
*/

// Qt libraries
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QLoggingCategory>

#include "web_engine_history.h"
#include "global_enums.h"

/** @defgroup MainWindowWebEngineHistoryGroup Web Engine History Doxygen Group
 *  Web Engine History functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowWebEngineHistoryOverall)

namespace main_window_tab {
	class MainWindowTab;
}

namespace main_window_web_engine_history {

	/**
	 * @brief MainWindowWebEngineHistory class
	 *
	 */
	class MainWindowWebEngineHistory final : public web_engine_history::WebEngineHistory {
		friend class main_window_tab::MainWindowTab;

		public:
			/**
			 * @brief Function: explicit MainWindowWebEngineHistory(QWebEngineHistory * history)
			 *
			 * \param history: history of the history
			 *
			 * Main window web engine history constructor
			 */
			explicit MainWindowWebEngineHistory(QWebEngineHistory * history);

			// Move and copy constructor
			/**
			 * @brief Function: MainWindowWebEngineHistory(const main_window_web_engine_history::MainWindowWebEngineHistory & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Main window web engine history copy constructor
			 */
			explicit MainWindowWebEngineHistory(const main_window_web_engine_history::MainWindowWebEngineHistory & rhs);

			/**
			 * @brief Function: MainWindowWebEngineHistory::MainWindowWebEngineHistory(main_window_web_engine_history::MainWindowWebEngineHistory && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Main window web engine history move constructor
			 */
			explicit MainWindowWebEngineHistory(main_window_web_engine_history::MainWindowWebEngineHistory && rhs);

			// Move and copy assignment operators
			/**
			 * @brief Function: main_window_web_engine_history::MainWindowWebEngineHistory & operator=(const main_window_web_engine_history::MainWindowWebEngineHistory & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Main window web engine history copy assignment operator
			 */
			main_window_web_engine_history::MainWindowWebEngineHistory & operator=(const main_window_web_engine_history::MainWindowWebEngineHistory & rhs);

			/**
			 * @brief Function: main_window_web_engine_history::MainWindowWebEngineHistory & operator=(main_window_web_engine_history::MainWindowWebEngineHistory && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Main window web engine history move assignment operator
			 */
			main_window_web_engine_history::MainWindowWebEngineHistory & operator=(main_window_web_engine_history::MainWindowWebEngineHistory && rhs);

			/**
			 * @brief Function: virtual ~MainWindowWebEngineHistory()
			 *
			 * Main window web engine history destructor
			 */
			virtual ~MainWindowWebEngineHistory();

		protected:

		private:

	};
}
/** @} */ // End of MainWindowWebEngineHistoryGroup group

#endif // MAIN_WINDOW_WEB_ENGINE_HISTORY_H

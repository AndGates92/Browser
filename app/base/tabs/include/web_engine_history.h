#ifndef WEB_ENGINE_HISTORY_H
#define WEB_ENGINE_HISTORY_H
/**
 * @copyright
 * @file web_engine_history.h
 * @author Andrea Gianarda
 * @date 25th May 2020
 * @brief Web Engine History header file
*/

// Qt libraries
// Required by qInfo
#include <QtCore/QtDebug>

#include <QtCore/QLoggingCategory>

#include <QtWebEngineWidgets/QWebEngineHistory>

#include "global_enums.h"
#include "tab_shared_types.h"

/** @defgroup WebEngineHistoryGroup Web Engine History Doxygen Group
 *  Web Engine History functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(webEngineHistoryOverall)

namespace tab {
	class Tab;
}

namespace web_engine_history {

	/**
	 * @brief WebEngineHistory class
	 *
	 */
	class WebEngineHistory {
		friend class tab::Tab;

		public:
			/**
			 * @brief Function: explicit WebEngineHistory(QWebEngineHistory * history)
			 *
			 * \param history: history to initialize the class width
			 *
			 * Web engine history constructor
			 */
			explicit WebEngineHistory(QWebEngineHistory * newHistory);

			// Move and copy constructor
			/**
			 * @brief Function: WebEngineHistory(const web_engine_history::WebEngineHistory & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Web engine history copy constructor
			 */
			explicit WebEngineHistory(const web_engine_history::WebEngineHistory & rhs);

			/**
			 * @brief Function: WebEngineHistory::WebEngineHistory(web_engine_history::WebEngineHistory && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Web engine history move constructor
			 */
			explicit WebEngineHistory(web_engine_history::WebEngineHistory && rhs);

			// Move and copy assignment operators
			/**
			 * @brief Function: WebEngineHistory & operator=(const web_engine_history::WebEngineHistory & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Web engine history copy assignment operator
			 */
			WebEngineHistory & operator=(const web_engine_history::WebEngineHistory & rhs);

			/**
			 * @brief Function: WebEngineHistory & operator=(web_engine_history::WebEngineHistory && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Web engine history move assignment operator
			 */
			WebEngineHistory & operator=(web_engine_history::WebEngineHistory && rhs);

			/**
			 * @brief Function: virtual ~WebEngineHistory()
			 *
			 * Web engine history destructor
			 */
			virtual ~WebEngineHistory();

		protected:

		private:
			/**
			 * @brief history of the tab
			 *
			 */
			QWebEngineHistory * history;

			/**
			 * @brief Function: virtual void back() const
			 *
			 * THis function tries to go back in the history of the tab
			 */
			virtual void back() const;

			/**
			 * @brief Function: virtual void forward() const
			 *
			 * THis function tries to go forward in the history of the tab
			 */
			virtual void forward() const;

			/**
			 * @brief Function: void goToItem(const tab_shared_types::stepping_e step) const
			 *
			 * \param step: movement across items of the list
			 *
			 * THis function requests to move to items across the list
			 */
			void goToItem(const tab_shared_types::stepping_e step) const;


	};
}
/** @} */ // End of WebEngineHistoryGroup group

#endif // WEB_ENGINE_HISTORY_H

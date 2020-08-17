#ifndef TAB_HISTORY_H
#define TAB_HISTORY_H
/**
 * @copyright
 * @file tab_history.h
 * @author Andrea Gianarda
 * @date 25th May 2020
 * @brief Tab History header file
*/

// Qt libraries
// Required by qInfo
#include <QtCore/QtDebug>

#include <QtCore/QLoggingCategory>

#include <QtWebEngineWidgets/QWebEngineHistory>

#include "global_enums.h"
#include "tab_shared_types.h"
#include "tab_component_widget.h"

/** @defgroup TabHistoryGroup Tab History Doxygen Group
 *  Tab History functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(tabHistoryOverall)

namespace tab {
	class Tab;
}

namespace tab_history {

	/**
	 * @brief TabHistory class
	 *
	 */
	class TabHistory : public tab_component_widget::TabComponentWidget<tab_shared_types::stepping_e> {
		friend class tab::Tab;

		Q_OBJECT

		public:
			/**
			 * @brief Function: explicit TabHistory(QWidget * parent, std::weak_ptr<tab::Tab> browserTab, QWebEngineHistory * newHistory)
			 *
			 * \param parent: parent widget
			 * \param tab: tab
			 * \param history: history to initialize the class width
			 *
			 * Tab history constructor
			 */
			explicit TabHistory(QWidget * parent, std::weak_ptr<tab::Tab> browserTab, QWebEngineHistory * newHistory);

			/**
			 * @brief Function: virtual ~TabHistory()
			 *
			 * Tab history destructor
			 */
			virtual ~TabHistory();

		signals:

			/**
			 * @brief Function: void historyItemChanged(const global_enums::element_position_e & position)
			 *
			 * \param position: position in the history.
			 *
			 * This function is a signal to notify the current position in the history of the tab
			 */
			void historyItemChanged(const global_enums::element_position_e & position);

		protected:

		private:
			/**
			 * @brief history of the tab
			 *
			 */
			QWebEngineHistory * history;

			/**
			 * @brief Function: virtual void back()
			 *
			 * THis function tries to go back in the history of the tab
			 */
			virtual void back();

			/**
			 * @brief Function: virtual void forward()
			 *
			 * THis function tries to go forward in the history of the tab
			 */
			virtual void forward();

			/**
			 * @brief Function: vortual void execute(const tab_shared_types::stepping_e & step) override final
			 *
			 * \param step: movement across items of the list
			 *
			 * This function moves in the history according to the provided step
			 */
			virtual void execute(const tab_shared_types::stepping_e & step) override final;

			/**
			 * @brief Function: virtual void canProcessRequests() const override
			 *
			 * \return whether find requests can be processed
			 *
			 * This function check if find requests can be processed
			 */
			virtual bool canProcessRequests() const override;

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class TabHistory
			 *
			 */
			DISABLE_COPY_MOVE(TabHistory)

	};
}
/** @} */ // End of TabHistoryGroup group

#endif // TAB_HISTORY_H

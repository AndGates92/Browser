#ifndef TAB_HISTORY_H
#define TAB_HISTORY_H
/**
 * @copyright
 * @file history.h
 * @author Andrea Gianarda
 * @date 25th May 2020
 * @brief Tab History header file
*/

// Qt libraries
#include <QtWebEngineWidgets/QWebEngineHistory>

#include "common/include/global_enums.h"
#include "base/tabs/include/tab_shared_types.h"
#include "base/tabs/include/tab_component_widget.h"

/** @defgroup TabGroup Tab Doxygen Group
 *  Tab functions and classes
 *  @{
 */

namespace app {

	namespace base {

		namespace tab {

			class Tab;

			/**
			 * @brief History class
			 *
			 */
			class History : public app::base::tab::TabComponentWidget<app::base::tab::stepping_e> {
				friend class app::base::tab::Tab;

				Q_OBJECT

				public:
					/**
					 * @brief Function: explicit History(QWidget * parent, std::weak_ptr<app::base::tab::Tab> browserTab, QWebEngineHistory * newHistory)
					 *
					 * \param parent: parent widget
					 * \param tab: tab
					 * \param history: history to initialize the class width
					 *
					 * Tab history constructor
					 */
					explicit History(QWidget * parent, std::weak_ptr<app::base::tab::Tab> browserTab, QWebEngineHistory * newHistory);

					/**
					 * @brief Function: virtual ~History()
					 *
					 * Tab history destructor
					 */
					virtual ~History();

				signals:

					/**
					 * @brief Function: void historyItemChanged(const app::shared::element_position_e & position)
					 *
					 * \param position: position in the history.
					 *
					 * This function is a signal to notify the current position in the history of the tab
					 */
					void historyItemChanged(const app::shared::element_position_e & position);

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
					 * @brief Function: vortual void execute(const app::base::tab::stepping_e & step) override final
					 *
					 * \param step: movement across items of the list
					 *
					 * This function moves in the history according to the provided step
					 */
					virtual void execute(const app::base::tab::stepping_e & step) override final;

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
					 * @brief Disable move and copy constructors and operator= overloading for class History
					 *
					 */
					DISABLE_COPY_MOVE(History)

			};

		}

	}

}
/** @} */ // End of TabGroup group

#endif // TAB_HISTORY_H

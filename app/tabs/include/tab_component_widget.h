#ifndef TAB_COMPONENT_WIDGET_H
#define TAB_COMPONENT_WIDGET_H
/**
 * @copyright
 * @file tab_component_widget.h
 * @author Andrea Gianarda
 * @date 13th of May 2020
 * @brief Tab Component Widget header file
*/

#include <queue>

// Qt libraries
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QLoggingCategory>

#include <qt5/QtWidgets/QWidget>

#include "global_types.h"
#include "tab_shared_types.h"
#include "constructor_macros.h"

/** @defgroup TabComponentWidgetGroup Tab Component Widget Doxygen Group
 *  Tab Component Widget functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(tabComponentWidgetOverall)

namespace tab_component_widget {

	/**
	 * @brief TabComponentWidget class
	 *
	 */
	template<typename type>
	class TabComponentWidget : public QWidget {
		public:
			/**
			 * @brief Function: explicit TabComponentWidget(QWidget * parent)
			 *
			 * \param parent: parent widget
			 *
			 * Tab Component Widget constructor
			 */
			explicit TabComponentWidget(QWidget * parent);

			/**
			 * @brief Function: virtual ~TabComponentWidget()
			 *
			 * Tab Component Widget destructor
			 */
			virtual ~TabComponentWidget();

		protected:
			/**
			 * @brief Function: virtual void popRequestQueue()
			 *
			 * This function empties the queue of scroll requests
			 */
			virtual void popRequestQueue() = 0;

			/**
			 * @brief Function: virtual void pushRequestQueue(const tab_shared_types::direction_e & entry) = 0
			 *
			 * \param entry: direction of scrolling
			 *
			 * This function pushes a new entry to the queue
			 */
			virtual void pushRequestQueue(const type & entry) = 0;

			/**
			 * @brief queue of outstanding scroll requests
			 *
			 */
			std::queue<type> requestQueue;

		private:
			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overscrolling for class TabComponentWidget
			 *
			 */
			DISABLE_COPY_MOVE(TabComponentWidget)

	};
}
/** @} */ // End of TabComponentWidgetGroup group

template<typename type>
tab_component_widget::TabComponentWidget<type>::TabComponentWidget(QWidget * parent): QWidget(parent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabComponentWidgetOverall,  "TabComponentWidget constructor");

}

template<typename type>
tab_component_widget::TabComponentWidget<type>::~TabComponentWidget() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabComponentWidgetOverall,  "TabComponentWidget destructor");
}

#endif // TAB_COMPONENT_WIDGET_H

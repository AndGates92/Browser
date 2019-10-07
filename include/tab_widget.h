#ifndef TAB_WIDGET_H
#define TAB_WIDGET_H
/**
 * @copyright
 * @file tab_widget.h
 * @author Andrea Gianarda
 * @date 02rd October 2019
 * @brief Tab Widget header file
*/

// Qt libraries
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtWidgets/QTabWidget>

#include "global_macros.h"
#include "global_types.h"
#include "tab_bar.h"

/** @defgroup TabWidgetGroup Tab Widget Doxygen Group
 *  Tab Widget functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(tabWidgetOverall)

namespace tab_widget {

	class TabWidget : public QTabWidget {

		public:
			/**
			 * @brief Function: explicit TabWidget(QWidget * parent = Q_NULLPTR)
			 *
			 * \param parent: parent widget
			 *
			 * Tab widget constructor
			 */
			explicit TabWidget(QWidget * parent = Q_NULLPTR);

		protected:
			/**
			 * @brief Function: void resizeEvent(QResizeEvent * event) override
			 *
			 * \param event: resize event
			 *
			 * Reimplement resize event
			 */
			void resizeEvent(QResizeEvent * event) override;

		private:
			/**
			 * @brief tab bar
			 *
			 */
			tab_bar::TabBar * tabBar;
	};
}
/** @} */ // End of TabWidgetGroup group

#endif // TAB_WIDGET_H

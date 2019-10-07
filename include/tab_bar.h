#ifndef TAB_BAR_H
#define TAB_BAR_H
/**
 * @copyright
 * @file tab_bar.h
 * @author Andrea Gianarda
 * @date 02rd October 2019
 * @brief Tab Bar header file
*/

// Qt libraries
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtWidgets/QTabBar>

#include "global_macros.h"
#include "global_types.h"

/** @defgroup TabBarGroup Tab Bar Doxygen Group
 *  Tab Bar functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(tabBarOverall)
Q_DECLARE_LOGGING_CATEGORY(tabBarSizeHint)
Q_DECLARE_LOGGING_CATEGORY(tabBarSetWidth)

namespace tab_bar {

	class TabBar : public QTabBar {

		public:
			/**
			 * @brief Function: explicit TabBar(QWidget * parent = Q_NULLPTR)
			 *
			 * \param parent: parent widget
			 *
			 * Tab bar constructor
			 */
			explicit TabBar(QWidget * parent = Q_NULLPTR);

			/**
			 * @brief Function: void setWdith(int newWidth)
			 *
			 * \param newWidth: new tab bar width
			 *
			 * Set the tab bar width
			 */
			void setWidth(int newWidth);

		protected:
			/**
			 * @brief Function: QSize tabSizeHint(int index) const override
			 *
			 * \param index: index of tab
			 *
			 * Calculates the recommended size of the tab
			 */
			QSize tabSizeHint(int index) const override;


		private:

	};
}
/** @} */ // End of TabBarGroup group

#endif // TAB_BAR_H

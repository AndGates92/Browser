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
Q_DECLARE_LOGGING_CATEGORY(tabBarHint)

namespace tab_bar {

	class TabBar : public QTabBar {

		public:
			explicit TabBar(QWidget * parent);

			QSize tabSizeHint(int index) const override;

			void resize(QSize new_size);

		private:
			QSize tabBarSize;

	};
}
/** @} */ // End of TabBarGroup group

#endif // TAB_BAR_H

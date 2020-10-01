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
#include <QtCore/QtDebug>

#include <QtCore/QLoggingCategory>

#include <QtWidgets/QTabBar>

#include "logging_macros.h"
#include "global_enums.h"
#include "constructor_macros.h"

/** @defgroup TabBarGroup Tab Bar Doxygen Group
 *  Tab Bar functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(tabBarOverall)
Q_DECLARE_LOGGING_CATEGORY(tabBarSize)
Q_DECLARE_LOGGING_CATEGORY(tabBarSearch)

namespace tab_bar {

	namespace {
		/**
		 * @brief minimum width
		 *
		 */
		static constexpr int minWidth = 50;// px
	}

	/**
	 * @brief TabBar class
	 *
	 */
	class TabBar : public QTabBar {

		Q_OBJECT

		public:
			/**
			 * @brief Function: explicit TabBar(QWidget * parent, const int & width = tab_bar::minWidth)
			 *
			 * \param parent: parent widget
			 * \param width: width of the tab bar
			 *
			 * Tab bar constructor
			 */
			explicit TabBar(QWidget * parent, const int & width = tab_bar::minWidth);

			/**
			 * @brief Function: void setWdith(int newWidth)
			 *
			 * \param newWidth: new tab bar width
			 *
			 * Set the tab bar width
			 */
			void setWidth(const int & newWidth);

		protected:
			/**
			 * @brief Function: QSize tabSizeHint(int index) const override
			 *
			 * \param index: index of tab
			 *
			 * Calculates the recommended size of the tab
			 */
			QSize tabSizeHint(int index) const override;

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
			 * @brief Function: void keyPressEvent(QKeyEvent * event)
			 *
			 * \param event: key event
			 *
			 * Re-implement key pressed event
			 */
			void keyPressEvent(QKeyEvent * event);

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class TabBar
			 *
			 */
			DISABLE_COPY_MOVE(TabBar)

	};
}
/** @} */ // End of TabBarGroup group

#endif // TAB_BAR_H

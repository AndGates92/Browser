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

#include <qt5/QtCore/QLoggingCategory>

#include <qt5/QtWidgets/QTabBar>

#include "global_macros.h"
#include "global_types.h"

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
		 * @brief height
		 *
		 */
		constexpr int height = 15;// px

		/**
		 * @brief minimum width
		 *
		 */
		constexpr int minWidth = 50;// px
	}

	/**
	 * @brief TabBar class
	 *
	 */
	class TabBar : public QTabBar {

		Q_OBJECT

		public:
			/**
			 * @brief Function: explicit TabBar(QWidget * parent = Q_NULLPTR)
			 *
			 * \param parent: parent widget
			 * \param width: width of the tab bar
			 *
			 * Tab bar constructor
			 */
			explicit TabBar(QWidget * parent = Q_NULLPTR, int width = tab_bar::minWidth);

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
			 * @brief Function: TabBar(const tab_bar::TabBar & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Command Menu copy constructor
			 */
			explicit TabBar(const tab_bar::TabBar & rhs) = delete;

			/**
			 * @brief Function: TabBar(tab_bar::TabBar && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Command Menu move constructor
			 */
			explicit TabBar(tab_bar::TabBar && rhs) = delete;

			// Move and copy assignment operators
			/**
			 * @brief Function: TabBar & operator=(const tab_bar::TabBar & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Command Menu copy assignment operator
			 */
			TabBar & operator=(const tab_bar::TabBar & rhs) = delete;

			/**
			 * @brief Function: TabBar & operator=(tab_bar::TabBar && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Command Menu move assignment operator
			 */
			TabBar & operator=(tab_bar::TabBar && rhs) = delete;

	};
}
/** @} */ // End of TabBarGroup group

#endif // TAB_BAR_H

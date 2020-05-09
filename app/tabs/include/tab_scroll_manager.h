#ifndef TAB_SCROLL_MANAGER_H
#define TAB_SCROLL_MANAGER_H
/**
 * @copyright
 * @file tab_scroll_manager.h
 * @author Andrea Gianarda
 * @date 07th of May 2020
 * @brief Tab Scroll Manager header file
*/

// Qt libraries
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtWidgets/QTabBar>

#include <qt5/QtWidgets/QWidget>

#include "global_types.h"
#include "constructor_macros.h"

/** @defgroup TabScrollManagerGroup Tab Scroll Manager Doxygen Group
 *  Tab Scroll Manager functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(tabScrollManagerOverall)

namespace tab_scroll_manager {

	/**
	 * @brief TabScrollManager class
	 *
	 */
	class TabScrollManager : public QWidget {

		Q_OBJECT

		public:
			/**
			 * @brief Function: explicit TabScrollManager(QWidget * parent, QWidget * tabBar)
			 *
			 * \param parent: parent widget
			 * \param tabBar: tab bar
			 *
			 * Tab Scroll Manager constructor
			 */
			explicit TabScrollManager(QWidget * parent, QWidget * tabBar);

			/**
			 * @brief Function: virtual ~TabScrollManager()
			 *
			 * Tab Scroll Manager destructor
			 */
			virtual ~TabScrollManager();

			/**
			 * @brief Function: const QSizeF & getContentsSize() const
			 *
			 * \return size of the content
			 *
			 * This function returns the size of the content
			 */
			const QSizeF & getContentsSize() const;

			/**
			 * @brief Function: const QPointF & getScrollPosition() const
			 *
			 * \return position of the scrolling
			 *
			 * This function returns the position of the scrolling
			 */
			const QPointF & getScrollPosition() const;

			/**
			 * @brief Function: const int & getHorizontalScrollPercentage() const
			 *
			 * \return percentage of the position of the horizontal scrolling
			 *
			 * This function returns the percentage of the position of the horizontal scrolling
			 */
			const int & getHorizontalScrollPercentage() const;

			/**
			 * @brief Function: const int & getVerticalScrollPercentage() const
			 *
			 * \return percentage of the position of the vertical scrolling
			 *
			 * This function returns the percentage of the position of the vertical scrolling
			 */
			const int & getVerticalScrollPercentage() const;

		public slots:
			/**
			 * @brief Function: void updateContentsSize(const QSizeF & value)
			 *
			 * \param size of the content
			 *
			 * This function sets the size of the content
			 */
			void updateContentsSize(const QSizeF & value);

			/**
			 * @brief Function: void updateScrollPosition(const QPointF & value)
			 *
			 * \param position of the scrolling
			 *
			 * This function sets the position of the scrolling
			 */
			void updateScrollPosition(const QPointF & value);

		signals:
			/**
			 * @brief Function: void verticalScrollChanged(const int & vScroll)
			 *
			 * \param vertical scroll
			 *
			 * This function is a signal to notify that vertical scroll changed
			 */
			void verticalScrollChanged(const int & vScroll);

			/**
			 * @brief Function: void horizontalScrollChanged(const int & hScroll)
			 *
			 * \param horizontal scroll
			 *
			 * This function is a signal to notify that horizontal scroll changed
			 */
			void horizontalScrollChanged(const int & hScroll);

		protected:

			/**
			 * @brief Function: void updateHorizontalScrollPercentage()
			 *
			 * This function computes the percentage of the position of the horizontal scrolling
			 */
			void updateHorizontalScrollPercentage();

			/**
			 * @brief Function: void updateVerticalScrollPercentage()
			 *
			 * This function computes the percentage of the position of the vertical scrolling
			 */
			void updateVerticalScrollPercentage();

			/**
			 * @brief percentage of horizontal scroll
			 *
			 */
			int horizontalScroll;

			/**
			 * @brief percentage of vertical scroll
			 *
			 */
			int verticalScroll;

		private:
			/**
			 * @brief position of the scrolling
			 *
			 */
			QPointF scrollPosition;

			/**
			 * @brief size of the content in the webpage
			 *
			 */
			QSizeF contentsSize;

			/**
			 * @brief tab bar the tab belong to
			 *
			 */
			QTabBar * bar;

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overscrolling for class TabScrollManager
			 *
			 */
			DISABLE_COPY_MOVE(TabScrollManager)

	};
}
/** @} */ // End of TabScrollManagerGroup group

#endif // TAB_SCROLL_MANAGER_H

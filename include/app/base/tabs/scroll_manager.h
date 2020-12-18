#ifndef TAB_SCROLL_MANAGER_H
#define TAB_SCROLL_MANAGER_H
/**
 * @copyright
 * @file scroll_manager.h
 * @author Andrea Gianarda
 * @date 07th of May 2020
 * @brief Tab Scroll Manager header file
*/

#include <memory>

#include "app/base/tabs/tab_component_widget.h"
#include "app/base/tabs/tab_shared_types.h"
#include "app/shared/constructor_macros.h"

/** @defgroup TabGroup Tab Doxygen Group
 *  Tab functions and classes
 *  @{
 */

namespace app {

	namespace base {

		namespace tab {

			class TabBar;

			/**
			 * @brief ScrollManager class
			 *
			 */
			class ScrollManager : public app::base::tab::TabComponentWidget<app::base::tab::direction_e> {
				friend class app::base::tab::Tab;

				Q_OBJECT

				public:
					/**
					 * @brief Function: explicit ScrollManager(QWidget * parent, std::weak_ptr<app::base::tab::Tab> browserTab, const std::shared_ptr<app::base::tab::TabBar> & tabBar)
					 *
					 * \param parent: parent widget
					 * \param tabBar: tab bar
					 * \param tab: tab
					 *
					 * Tab Scroll Manager constructor
					 */
					explicit ScrollManager(QWidget * parent, std::weak_ptr<app::base::tab::Tab> browserTab, const std::shared_ptr<app::base::tab::TabBar> & tabBar);

					/**
					 * @brief Function: virtual ~ScrollManager()
					 *
					 * Tab Scroll Manager destructor
					 */
					virtual ~ScrollManager();

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

				signals:
					/**
					 * @brief Function: void verticalScrollChanged(const int & vScroll)
					 *
					 * \param vScroll: vertical scroll
					 *
					 * This function is a signal to notify that vertical scroll changed
					 */
					void verticalScrollChanged(const int & vScroll);

					/**
					 * @brief Function: void horizontalScrollChanged(const int & hScroll)
					 *
					 * \param hScroll: horizontal scroll
					 *
					 * This function is a signal to notify that horizontal scroll changed
					 */
					void horizontalScrollChanged(const int & hScroll);

					/**
					 * @brief Function: void scrollRequest(const int x, const int y)
					 *
					 * \param x: scroll on the x axis
					 * \param y: scroll on the y axis
					 *
					 * This function is a signal to request scrolling
					 */
					void scrollRequest(const int x, const int y);

				protected:

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

				protected slots:
					/**
					 * @brief Function: void updateContentsSize(const QSizeF & value)
					 *
					 * \param value: size of the content
					 *
					 * This function sets the size of the content
					 */
					void updateContentsSize(const QSizeF & value);

					/**
					 * @brief Function: void updateScrollPosition(const QPointF & value)
					 *
					 * \param value: position of the scrolling
					 *
					 * This function sets the position of the scrolling
					 */
					void updateScrollPosition(const QPointF & value);

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
					std::shared_ptr<app::base::tab::TabBar> bar;

					/**
					 * @brief Function: vortual void execute(const app::base::tab::direction_e & direction) override final
					 *
					 * \param direction: direction of scrolling
					 *
					 * This function scroll the tab in the direction provided as argument
					 */
					virtual void execute(const app::base::tab::direction_e & direction) override final;

					/**
					 * @brief Function: void checkScrollValue(const int & scroll, const QString & direction) const
					 *
					 * \param scroll: value of scrolling
					 * \param direction: direction of scrolling
					 *
					 * This function checks that the value of scrolling is within the allowed range defined by app::base::tab::minScrollPercentage and app::base::tab::maxScrollPercentage
					 */
					void checkScrollValue(const int & scroll, const QString & direction) const;

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
					 * @brief Disable move and copy constructors and operator= overloading for class ScrollManager
					 *
					 */
					DISABLE_COPY_MOVE(ScrollManager)

			};

		}

	}

}
/** @} */ // End of TabGroup group

#endif // TAB_SCROLL_MANAGER_H

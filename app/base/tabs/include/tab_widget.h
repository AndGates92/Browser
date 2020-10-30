#ifndef TAB_WIDGET_H
#define TAB_WIDGET_H
/**
 * @copyright
 * @file tab_widget.h
 * @author Andrea Gianarda
 * @date 02nd October 2019
 * @brief Tab Widget header file
*/

#include <memory>

// Qt libraries
#include <QtWidgets/QTabWidget>
#include <QtGui/QIcon>

#include "macros.h"
#include "global_enums.h"
#include "tab_bar.h"
#include "tab.h"
#include "constructor_macros.h"

/** @defgroup TabWidgetGroup Tab Widget Doxygen Group
 *  Tab Widget functions and classes
 *  @{
 */

namespace tab_widget {

	/**
	 * @brief TabWidget class
	 *
	 */
	class TabWidget : public QTabWidget {

		Q_OBJECT

		public:
			/**
			 * @brief Function: explicit TabWidget(QWidget * parent)
			 *
			 * \param parent: parent widget
			 *
			 * Tab widget constructor
			 */
			explicit TabWidget(QWidget * parent);

			/**
			 * @brief Function: virtual ~TabWidget()
			 *
			 * Tab widget destructor
			 */
			virtual ~TabWidget();

			/**
			 * @brief Function: int addTab(const std::shared_ptr<tab::Tab> & newTab, const QString & label, const QIcon & icon = QIcon())
			 *
			 * \param newTab: widget to fill in
			 * \param label: label of the tab
			 * \param icon: icon of the tab
			 *
			 * \return tab index
			 *
			 * add tab to tab widget
			 */
			int addTab(const std::shared_ptr<tab::Tab> & newTab, const QString & label, const QIcon & icon = QIcon());

			/**
			 * @brief Function: int insertTab(const int & index, const std::shared_ptr<tab::Tab> & newTab, const QString & label, const QIcon & icon = QIcon())
			 *
			 * \param index: index to insert tab to
			 * \param newTab: widget to fill in
			 * \param label: label of the tab
			 * \param icon: icon of the tab
			 *
			 * \return tab index
			 *
			 * add tab to tab widget at index index
			 */
			int insertTab(const int & index, const std::shared_ptr<tab::Tab> & newTab, const QString & label, const QIcon & icon = QIcon());

			/**
			 * @brief Function: void removeTab(const int & index)
			 *
			 * \param index: index of the tab to remove
			 *
			 * remove a tab from tab widget
			 */
			void removeTab(const int & index);

			/**
			 * @brief Function: std::shared_ptr<tab::Tab> widget(const int & index, const bool & checkError = true) const
			 *
			 * \param index: index of the tab to return the widget of
			 * \param checkError: error out if widget is null
			 *
			 * \return tab at position index
			 *
			 * returns a tab from tab widget
			 */
			std::shared_ptr<tab::Tab> widget(const int & index, const bool & checkError = true) const;

		protected:
			/**
			 * @brief Function: void resizeEvent(QResizeEvent * event) override
			 *
			 * \param event: resize event
			 *
			 * Reimplement resize event
			 */
			void resizeEvent(QResizeEvent * event) override;

			/**
			 * @brief Function: void setTabBar(std::shared_ptr<tab_bar::TabBar> newTabBar)
			 *
			 * \param newTabBar: tab bar linked to the tab widget
			 *
			 * add tab bar to tab widget
			 */
			void setTabBar(std::shared_ptr<tab_bar::TabBar> newTabBar);

			/**
			 * @brief Function: const std::shared_ptr<tab_bar::TabBar> & tabBar() const
			 *
			 * \return tab bar linked to the tab widget
			 *
			 * This function returns the tab bar of the tab widget
			 */
			const std::shared_ptr<tab_bar::TabBar> & tabBar() const;

			/**
			 * @brief tab bar
			 *
			 */
			std::shared_ptr<tab_bar::TabBar> bar;

		private:
			/**
			 * @brief Function: void setVisibleAttribute()
			 *
			 * Set tab visible attribute
			 */
			void setVisibleAttribute();

			/**
			 * @brief tab list
			 *
			 */
			std::vector<std::shared_ptr<tab::Tab>> tabs;

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
			 * @brief Disable move and copy constructors and operator= overloading for class TabWidget
			 *
			 */
			DISABLE_COPY_MOVE(TabWidget)

		signals:

	};
}
/** @} */ // End of TabWidgetGroup group

#endif // TAB_WIDGET_H

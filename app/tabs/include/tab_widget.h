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

#include <qt5/QtCore/QLoggingCategory>

#include <qt5/QtWidgets/QTabWidget>
#include <qt5/QtGui/QIcon>

#include "global_macros.h"
#include "global_types.h"
#include "tab_bar.h"

/** @defgroup TabWidgetGroup Tab Widget Doxygen Group
 *  Tab Widget functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(tabWidgetOverall)
Q_DECLARE_LOGGING_CATEGORY(tabWidgetSize)
Q_DECLARE_LOGGING_CATEGORY(tabWidgetSearch)
Q_DECLARE_LOGGING_CATEGORY(tabWidgetVisibility)
Q_DECLARE_LOGGING_CATEGORY(tabWidgetTabs)

namespace tab_widget {

	namespace {
		/**
		 * @brief minimum height
		 *
		 */
		const int minHeight = 200; // px

		/**
		 * @brief minimum width
		 *
		 */
		const int minWidth = 100; // px
	}

	/**
	 * @brief TabWidget class
	 *
	 */
	class TabWidget : public QTabWidget {

		Q_OBJECT

		public:
			/**
			 * @brief Function: explicit TabWidget(QWidget * parent = Q_NULLPTR)
			 *
			 * \param parent: parent widget
			 *
			 * Tab widget constructor
			 */
			explicit TabWidget(QWidget * parent = Q_NULLPTR);

			/**
			 * @brief Function: ~TabWidget()
			 *
			 * Tab widget destructor
			 */
			~TabWidget();

			/**
			 * @brief Function: int addTab(QWidget * page, const QString & label)
			 *
			 * \param page: widget to fill in
			 * \param label: label of the tab
			 *
			 * \return tab index
			 *
			 * add tab to tab widget
			 */
			int addTab(QWidget * page, const QString & label);

			/**
			 * @brief Function: int addTab(QWidget * page, const QIcon & icon, const QString & label)
			 *
			 * \param page: widget to fill in
			 * \param icon: icon of the tab
			 * \param label: label of the tab
			 *
			 * \return tab index
			 *
			 * add tab to tab widget
			 */
			int addTab(QWidget * page, const QIcon & icon, const QString & label);

			/**
			 * @brief Function: void removeTab(int index)
			 *
			 * \param index: index of the tab to remove
			 *
			 * remove a tab from tab widget
			 */
			void removeTab(int index);

			/**
			 * @brief Function: QWidget * widget(int index, bool checkError = true)
			 *
			 * \param index: index of the tab to return the widget of
			 * \param checkError: error out if widget is null
			 *
			 * \return widget of tab page
			 *
			 * remove a tab from tab widget
			 */
			QWidget * widget(int index, bool checkError = true);

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
			 * @brief Function: void setTabBar(tab_bar::TabBar * tabBar)
			 *
			 * \param tabBar: tab bar linked to the tab widget
			 *
			 * add tab bar to tab widget
			 */
			void setTabBar(tab_bar::TabBar * tabBar);

		private slots:
			/**
			 * @brief Function: void visibility()
			 *
			 * Set tab visibility
			 */
			void visibility();

		private:
			/**
			 * @brief tab bar
			 *
			 */
			tab_bar::TabBar * bar;

			/**
			 * @brief Function: void keyPressEvent(QKeyEvent * event)
			 *
			 * \param event: key event
			 *
			 * Re-implement key pressed event
			 */
			void keyPressEvent(QKeyEvent * event);

		signals:
			/**
			 * @brief Function: void tabNumberChange()
			 *
			 * This function is the signal triggered when the tab number changes
			 */
			void tabNumberChange();

	};
}
/** @} */ // End of TabWidgetGroup group

#endif // TAB_WIDGET_H

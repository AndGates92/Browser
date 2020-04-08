#ifndef MAIN_WINDOW_TAB_WIDGET_H
#define MAIN_WINDOW_TAB_WIDGET_H
/**
 * @copyright
 * @file main_window_tab_widget.h
 * @author Andrea Gianarda
 * @date 07th of December 2019
 * @brief Main Window Tab Widget header file
*/

#include <list>

#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtWidgets/QWidget>

#include "main_window_shared_types.h"
#include "main_window_tab_data.h"
#include "tab_widget.h"
#include "constructor_macros.h"

/** @defgroup MainWindowTabWidgetGroup Main Window Tab Widget Doxygen Group
 *  Main Window tab widget functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowTabWidgetOverall)
Q_DECLARE_LOGGING_CATEGORY(mainWindowTabWidgetTabs)

namespace main_window_tab_widget {

	/**
	 * @brief MainWindowTabWidget class
	 *
	 */
	class MainWindowTabWidget final : public tab_widget::TabWidget {

		Q_OBJECT

		public:

			/**
			 * @brief Function: explicit MainWindowTabWidget(QWidget * parent = Q_NULLPTR)
			 *
			 * \param parent: parent window
			 *
			 * Main window tab widget constructor
			 */
			explicit MainWindowTabWidget(QWidget * parent = Q_NULLPTR);

			/**
			 * @brief Function: ~TabWidget()
			 *
			 * Tab widget destructor
			 */
			~MainWindowTabWidget();

			/**
			 * @brief Function: int addEmptyTab(const QString & label, const main_window_shared_types::tab_type_e & type, const void * data = nullptr, const QIcon & icon = QIcon())
			 *
			 * \param label: label of the tab
			 * \param content: content of the tab
			 * \param type: type of the tab
			 * \param data: extra data to be passed through
			 * \param icon: icon of the tab
			 *
			 * \return tab index
			 *
			 * add tab to tab widget
			 */
			int addEmptyTab(const QString & label, const void * content, const main_window_shared_types::tab_type_e & type, const void * data = nullptr, const QIcon & icon = QIcon());

			/**
			 * @brief Function: int insertTab(const int & index, const QString & label, const main_window_shared_types::tab_type_e & type, const void * data = nullptr, const QIcon & icon = QIcon())
			 *
			 * \param index: index to insert tab to
			 * \param label: label of the tab
			 * \param content: content of the tab
			 * \param type: type of the tab
			 * \param data: extra data to be passed through
			 * \param icon: icon of the tab
			 *
			 * \return tab index
			 *
			 * add tab to tab widget at index index
			 */
			int insertTab(const int & index, const QString & label, const void * content, const main_window_shared_types::tab_type_e & type, const void * data = nullptr, const QIcon & icon = QIcon());

			/**
			 * @brief Function: void removeTab(const int & index)
			 *
			 * \param index: index of the tab to remove
			 *
			 * remove a tab from tab widget
			 */
			void removeTab(const int & index);

			/**
			 * @brief Function: void moveTab(const int & indexFrom, const int & indexTo)
			 *
			 * \param indexFrom: index of the tab to move
			 * \param indexTo: destination of the tab
			 *
			 * move a tab from index indexFrom to index indexTo
			 */
			void moveTab(const int & indexFrom, const int & indexTo);

			/**
			 * @brief Function: QWidget * widget(const int & index, bool checkError = true)
			 *
			 * \param index: index of the tab to return the widget of
			 * \param checkError: error out if widget is null
			 *
			 * \return widget of tab page
			 *
			 * remove a tab from tab widget
			 */
			QWidget * widget(const int & index, bool checkError = true) const;

			/**
			 * @brief Function: const main_window_tab_data::MainWindowTabData * getTabData(const int & index) const
			 *
			 * \param index: index of the tab to return the type of
			 *
			 * \return tab data
			 *
			 * return a tab data from tab widget
			 */
			const main_window_tab_data::MainWindowTabData * getTabData(const int & index) const;

			/**
			 * @brief Function: main_window_shared_types::tab_type_e getTabType(const int & index) const
			 *
			 * \param index: index of the tab to return the type of
			 *
			 * \return type of tab page at index index
			 *
			 * return a tab type from tab widget
			 */
			main_window_shared_types::tab_type_e getTabType(const int & index) const;

			/**
			 * @brief Function: const void * getTabExtraData(const int & index) const
			 *
			 * \param index: index of the tab to return the data of
			 *
			 * \return data field of tab page at index index
			 *
			 * return a tab data from tab widget
			 */
			const void * getTabExtraData(const int & index) const;

			/**
			 * @brief Function: void changeTabData(const int & index, const main_window_shared_types::tab_type_e newType, const void * data = nullptr)
			 *
			 * \param index: index of the tab to change the type of
			 * \param newType: new type of tab at index index
			 * \param data: extra data to be passed through
			 *
			 * this function chnages the type and the extra data of a tab
			 */
			void changeTabData(const int & index, const main_window_shared_types::tab_type_e newType, const void * data = nullptr);

			/**
			 * @brief Function: void changeTabContent(const int & index, const QString & label, const void * content, const main_window_shared_types::tab_type_e & type, const void * data)
			 *
			 * \param index: index to insert tab to
			 * \param label: label of the tab
			 * \param content: content of the tab
			 * \param type: type of the tab
			 * \param data: extra data to be passed through
			 *
			 * This function changes the content of a tab
			 */
			void changeTabContent(const int & index, const QString & label, const void * content, const main_window_shared_types::tab_type_e & type, const void * data);

		signals:
			/**
			 * @brief Function: void numberTabsChanged(int index)
			 *
			 * \param index: index of the current tab
			 *
			 * This function is a signal to notify that the number of tabs has changed
			 */
			void numberTabsChanged(int index);

			/**
			 * @brief Function: void tabTitleChanged(const QString & title)
			 *
			 * \param title: title of the tab
			 *
			 * This function is a signal to notify that the title of a tab changed
			 */
			void tabTitleChanged(const QString & title);

			/**
			 * @brief Function: void tabUrlChanged(const QString & url)
			 *
			 * \param url: url of the tab
			 *
			 * This function is a signal to notify that the url of a tab has changed
			 */
			void tabUrlChanged(const QString & url);

		protected:

		private:

			/**
			 * @brief Function: void disconnectTab(const int & index)
			 *
			 * \param index: index of the tab to disconnect signals from
			 *
			 * This function disconnects signals from a tab
			 */
			void disconnectTab();

			/**
			 * @brief Function: void connectTab(const int & index)
			 *
			 * \param index: index of the tab to connect signals from
			 *
			 * This function connects signals from a tab
			 */
			void connectTab();


			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class MainWindowTabWidget
			 *
			 */
			DISABLE_COPY_MOVE(MainWindowTabWidget)

		private slots:
			/**
			 * @brief Function: void processTabTitleChanged(const QString & title)
			 *
			 * \param title: title of the tab
			 *
			 * This function is a slot that receives a notification that the title of a tab has changed
			 */
			void processTabTitleChanged(const QString & title);

			/**
			 * @brief Function: void processTabUrlChanged(const QUrl & url)
			 *
			 * \param url: url of the tab
			 *
			 * This function is a slot that receives a notification that the url of a tab has changed
			 */
			void processTabUrlChanged(const QUrl & url);

	};

}
/** @} */ // End of MainWindowTabWidgetGroup group

#endif // MAIN_WINDOW_TAB_WIDGET_H

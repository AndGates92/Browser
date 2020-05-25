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
#include "main_window_page_data.h"
#include "tab_widget.h"
#include "constructor_macros.h"

/** @defgroup MainWindowTabWidgetGroup Main Window Tab Widget Doxygen Group
 *  Main Window tab widget functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowTabWidgetOverall)
Q_DECLARE_LOGGING_CATEGORY(mainWindowTabWidgetTabs)

namespace main_window_tab_widget {

	namespace {

		/**
		 * @brief https string
		 *
		 */
		const QString https("https://");

		/**
		 * @brief www string
		 *
		 */
		const QString www("www.");

		/**
		 * @brief default serch engine is duckduckgo
		 *
		 */
		const QString defaultSearchEngine(https + www + "duckduckgo.com/?q=%1");

	}

	/**
	 * @brief MainWindowTabWidget class
	 *
	 */
	class MainWindowTabWidget final : public tab_widget::TabWidget {

		Q_OBJECT

		public:

			/**
			 * @brief Function: explicit MainWindowTabWidget(QWidget * parent)
			 *
			 * \param parent: parent window
			 *
			 * Main window tab widget constructor
			 */
			explicit MainWindowTabWidget(QWidget * parent);

			/**
			 * @brief Function: ~TabWidget()
			 *
			 * Tab widget destructor
			 */
			~MainWindowTabWidget();

			/**
			 * @brief Function: int addTab(const main_window_shared_types::page_type_e & type, const QString & userInput, const void * data = nullptr, const QIcon & icon = QIcon())
			 *
			 * \param userInput: input typed by the user
			 * \param type: type of the tab page
			 * \param data: extra data to be passed through
			 * \param icon: icon of the page
			 *
			 * \return tab index
			 *
			 * This function adds tab to tab widget at the end of the tab bar
			 * It calls insertTab, therefore for more details on the argument meaning, please refer to insertTab function
			 */
			int addTab(const main_window_shared_types::page_type_e & type, const QString & userInput, const void * data = nullptr, const QIcon & icon = QIcon());

			/**
			 * @brief Function: int insertTab(const int & index, const main_window_shared_types::page_type_e & type, const QString & userInput, const void * data = nullptr, const QIcon & icon = QIcon())
			 *
			 * \param index: index to insert tab to
			 * \param userInput: input typed by the user
			 * \param type: type of the tab page
			 * \param data: extra data to be passed through
			 * \param icon: icon of the page
			 *
			 * \return tab index
			 *
			 * add tab to tab widget at index index
			 * The userInput argument constains the following informations:
			 * if the type is WEB_CONTENT, it is the search keywords
			 * if the type is TEXT, it is the filepath of the file to print
			 */
			int insertTab(const int & index, const main_window_shared_types::page_type_e & type, const QString & userInput, const void * data = nullptr, const QIcon & icon = QIcon());

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
			 * @brief Function: void setPageData(const int & index, const main_window_page_data::MainWindowPageData * pageData)
			 *
			 * \param index: index of the tab to return the type of
			 * \param pageData: new page data
			 *
			 * This function changes the page data of the tab at index index
			 */
			void setPageData(const int & index, const main_window_page_data::MainWindowPageData * pageData);

			/**
			 * @brief Function: const main_window_page_data::MainWindowPageData * getPageData(const int & index) const
			 *
			 * \param index: index of the tab to return the type of
			 *
			 * \return page data
			 *
			 * return a page data from tab widget
			 */
			const main_window_page_data::MainWindowPageData * getPageData(const int & index) const;

			/**
			 * @brief Function: main_window_shared_types::page_type_e getPageType(const int & index) const
			 *
			 * \param index: index of the tab to return the type of
			 *
			 * \return type of page page at index index
			 *
			 * return a page type from tab widget
			 */
			main_window_shared_types::page_type_e getPageType(const int & index) const;

			/**
			 * @brief Function: const QString getPageSource(const int & index) const
			 *
			 * \param index: index of the tab to return the type of
			 *
			 * \return source of the content of the tab page at index index
			 *
			 * return the source of the content of a tab from tab widget
			 */
			const QString getPageSource(const int & index) const;

			/**
			 * @brief Function: const void * getPageExtraData(const int & index) const
			 *
			 * \param index: index of the tab to return the data of
			 *
			 * \return data field of tab page at index index
			 *
			 * return a page data from tab widget
			 */
			const void * getPageExtraData(const int & index) const;

			/**
			 * @brief Function: void changePageData(const int & index, const main_window_shared_types::page_type_e & type, const QString & source, const void * data = nullptr)
			 *
			 * \param index: index of the tab to change the type of
			 * \param type: new type of page at index index
			 * \param source: new source of tab at index index
			 * \param data: extra data to be passed through
			 *
			 * this function chnages the type and the extra data of a tab
			 */
			void changePageData(const int & index, const main_window_shared_types::page_type_e & type, const QString & source, const void * data = nullptr);

			/**
			 * @brief Function: void changeTabContent(const int & index, const main_window_shared_types::page_type_e & type, const QString & userInput, const void * data)
			 *
			 * \param index: index to insert tab to
			 * \param userInput: input typed by the user
			 * \param type: type of the tab page
			 * \param data: extra data to be passed through
			 *
			 * This function changes the content of a tab
			 */
			void changeTabContent(const int & index, const main_window_shared_types::page_type_e & type, const QString & userInput, const void * data);

			/**
			 * @brief Function: void reloadTabContent(const int & index)
			 *
			 * \param index: index of the tab to reload
			 *
			 * This function reloads the content of the page of tab at index index
			 */
			void reloadTabContent(const int & index);

			/**
			 * @brief Function: void findInTab(const int & index, const QString & text, const main_window_shared_types::navigation_type_e & direction)
			 *
			 * \param index: index of the tab
			 * \param text: text to find in the tab
			 * \param direction: direction of the search
			 *
			 * This function request a tab to find text provided by argument text
			 */
			void findInTab(const int & index, const QString & text, const main_window_shared_types::navigation_type_e & direction);

			/**
			 * @brief Function: void scrollTab(const int & index, const main_window_shared_types::offset_type_e direction)
			 *
			 * \param index: index of the tab
			 * \param direction: direction of scrolling
			 *
			 * This function scroll the tab in the direction provided as argument
			 */
			void scrollTab(const int & index, const main_window_shared_types::offset_type_e direction);

			/**
			 * @brief Function: void goToHistoryItem(const int & index, const main_window_shared_types::navigation_type_e & direction)
			 *
			 * \param index: index of the tab
			 * \param direction: direction of the search in the history
			 *
			 * This function request a tab to move in its history
			 */
			void goToHistoryItem(const int & index, const main_window_shared_types::navigation_type_e & direction);

		public slots:
			/**
			 * @brief Function: void openFileInCurrentTab(const QString & filepath, const void * data)
			 *
			 * \param filepath: path of the file
			 * \param data: extra data to be passed through
			 *
			 * This function writes the widget with the content of the file read (stored in argument str)
			 */
			void openFileInCurrentTab(const QString & filepath, const void * data);

		signals:

			/**
			 * @brief Function: void tabNearlyDisconnected(const int & index)
			 *
			 * \param index: index of the current tab
			 *
			 * This function is a signal to notify that tab signals are no longer tied to window
			 */
			void tabNearlyDisconnected(const int & index);

			/**
			 * @brief Function: void tabNearlyConnected(const int &  index)
			 *
			 * \param index: index of the current tab
			 *
			 * This function is a signal to notify that tab signals are about to be associated to window
			 */
			void tabNearlyConnected(const int & index);

			/**
			 * @brief Function: void numberTabsChanged(int index)
			 *
			 * \param index: index of the current tab
			 *
			 * This function is a signal to notify that the number of tabs has changed
			 */
			void numberTabsChanged(int index);

			/**
			 * @brief Function: void tabSourceChanged(const main_window_shared_types::page_type_e & type, const QString & source)
			 *
			 * \param type: type of the tab page
			 * \param source: source of the tab
			 *
			 * This function is a signal to notify that the source of a tab changed
			 */
			void tabSourceChanged(const main_window_shared_types::page_type_e & type, const QString & source);

			/**
			 * @brief Function: void tabTitleChanged(const QString & title)
			 *
			 * \param title: title of the tab
			 *
			 * This function is a signal to notify that the title of a tab changed
			 */
			void tabTitleChanged(const QString & title);

			/**
			 * @brief Function: void tabUrlChanged(const main_window_shared_types::page_type_e & type, const QString & url)
			 *
			 * \param type: type of the tab page
			 * \param url: url of the tab
			 *
			 * This function is a signal to notify that the url of a tab has changed
			 */
			void tabUrlChanged(const main_window_shared_types::page_type_e & type, const QString & url);

		protected:

		private:

			/**
			 * @brief source change connection
			 *
			 */
			QMetaObject::Connection tabSourceConnection;

			/**
			 * @brief url change connection
			 *
			 */
			QMetaObject::Connection tabUrlConnection;

			/**
			 * @brief title change connection
			 *
			 */
			QMetaObject::Connection tabTitleConnection;

			/**
			 * @brief Function: void disconnectTab(const int & index)
			 *
			 * \param index: index of the tab to disconnect signals from
			 *
			 * This function disconnects signals from a tab
			 */
			void disconnectTab(const int & index);

			/**
			 * @brief Function: void connectTab(const int & index)
			 *
			 * \param index: index of the tab to connect signals from
			 *
			 * This function connects signals from a tab
			 */
			void connectTab(const int & index);

			/**
			 * @brief Function: QString searchToUrl(const QString & search) const
			 *
			 * \param search: string to search
			 *
			 * \return URL as QString
			 *
			 * This function is creates the URL based on the input from the user
			 * If the user writes down a URL himself/herself, it will return it adding, if required, https
			 * If the user is writing a string to search, it will be searched in the chosen search engine
			 */
			QString searchToUrl(const QString & search) const;

			/**
			 * @brief Function: void setTabTitle(const int & index, const QString & source)
			 *
			 * \param index: index of the tab
			 * \param source: source of the page content
			 *
			 * This function sets the title of a tab as well as the source of the page from the source of the content
			 */
			void setTabTitle(const int & index, const QString & source);

			/**
			 * @brief Function: QString createSource(const main_window_shared_types::page_type_e & type, const QString & userInput)
			 *
			 * \param type: type of the tab page
			 * \param userInput: input typed by the user
			 *
			 * \return source of the tab as derived from the user input string
			 *
			 * This function creates a string with the source of the content on a tab based on the user input
			 * if the type is WEB_CONTENT, it returns a string containign the URL (see searchToUrl method)
			 * if the type is TEXT, it returns the filepath of the file to print (i.e. the userInput)
			 */
			QString createSource(const main_window_shared_types::page_type_e & type, const QString & userInput);

			/**
			 * @brief Function: QString createLabel(const main_window_shared_types::page_type_e & type, const QString & userInput)
			 *
			 * \param type: type of the tab page
			 * \param userInput: userInput of the content of the page
			 *
			 * \return tab label
			 *
			 * This function creates a label for a tab
			 */
			QString createLabel(const main_window_shared_types::page_type_e & type, const QString & userInput);

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class MainWindowTabWidget
			 *
			 */
			DISABLE_COPY_MOVE(MainWindowTabWidget)

		private slots:
			/**
			 * @brief Function: void processTabSourceChanged(const QString & source)
			 *
			 * \param source: source of the tab
			 *
			 * This function is a slot that receives a notification that the source of a tab has changed
			 */
			void processTabSourceChanged(const QString & source);

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

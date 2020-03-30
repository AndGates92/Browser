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
			 * @brief Function: int addEmptyTab(const QString & label, const main_window_shared_types::tab_type_e & type, const void * data = nullptr)
			 *
			 * \param label: label of the tab
			 * \param type: type of the tab
			 * \param data: extra data to be passed through
			 *
			 * \return tab index
			 *
			 * add tab to tab widget
			 */
			int addEmptyTab(const QString & label, const main_window_shared_types::tab_type_e & type, const void * data = nullptr);

			/**
			 * @brief Function: int addEmptyTab(const QIcon & icon, const QString & label, const main_window_shared_types::tab_type_e & type, const void * data = nullptr)
			 *
			 * \param icon: icon of the tab
			 * \param label: label of the tab
			 * \param type: type of the tab
			 * \param data: extra data to be passed through
			 *
			 * \return tab index
			 *
			 * add tab to tab widget
			 */
			int addEmptyTab(const QIcon & icon, const QString & label, const main_window_shared_types::tab_type_e & type, const void * data = nullptr);

			/**
			 * @brief Function: int insertEmptyTab(const int & index, const QString & label, const main_window_shared_types::tab_type_e & type, const void * data = nullptr)
			 *
			 * \param index: index to insert tab to
			 * \param label: label of the tab
			 * \param type: type of the tab
			 * \param data: extra data to be passed through
			 *
			 * \return tab index
			 *
			 * add tab to tab widget at index index
			 */
			int insertEmptyTab(const int & index, const QString & label, const main_window_shared_types::tab_type_e & type, const void * data = nullptr);

			/**
			 * @brief Function: int insertEmptyTab(const int & index, const QIcon & icon, const QString & label, const main_window_shared_types::tab_type_e & type, const void * data = nullptr)
			 *
			 * \param index: index to insert tab to
			 * \param icon: icon of the tab
			 * \param label: label of the tab
			 * \param type: type of the tab
			 * \param data: extra data to be passed through
			 *
			 * \return tab index
			 *
			 * add tab to tab widget at index index
			 */
			int insertEmptyTab(const int & index, const QIcon & icon, const QString & label, const main_window_shared_types::tab_type_e & type, const void * data = nullptr);

			/**
			 * @brief Function: int addTab(QWidget * page, const QString & label, const main_window_shared_types::tab_type_e & type, const void * data = nullptr)
			 *
			 * \param page: widget to fill in
			 * \param label: label of the tab
			 * \param type: type of the tab
			 * \param data: extra data to be passed through
			 *
			 * \return tab index
			 *
			 * add tab to tab widget
			 */
			int addTab(QWidget * page, const QString & label, const main_window_shared_types::tab_type_e & type, const void * data = nullptr);

			/**
			 * @brief Function: int addTab(QWidget * page, const QIcon & icon, const QString & label, const main_window_shared_types::tab_type_e & type, const void * data = nullptr)
			 *
			 * \param page: widget to fill in
			 * \param icon: icon of the tab
			 * \param label: label of the tab
			 * \param type: type of the tab
			 * \param data: extra data to be passed through
			 *
			 * \return tab index
			 *
			 * add tab to tab widget
			 */
			int addTab(QWidget * page, const QIcon & icon, const QString & label, const main_window_shared_types::tab_type_e & type, const void * data = nullptr);

			/**
			 * @brief Function: int insertTab(const int & index, QWidget * page, const QString & label, const main_window_shared_types::tab_type_e & type, const void * data = nullptr)
			 *
			 * \param index: index to insert tab to
			 * \param page: widget to fill in
			 * \param label: label of the tab
			 * \param type: type of the tab
			 * \param data: extra data to be passed through
			 *
			 * \return tab index
			 *
			 * add tab to tab widget at index index
			 */
			int insertTab(const int & index, QWidget * page, const QString & label, const main_window_shared_types::tab_type_e & type, const void * data = nullptr);

			/**
			 * @brief Function: int insertTab(const int & index, QWidget * page, const QIcon & icon, const QString & label, const main_window_shared_types::tab_type_e & type, const void * data = nullptr)
			 *
			 * \param index: index to insert tab to
			 * \param page: widget to fill in
			 * \param icon: icon of the tab
			 * \param label: label of the tab
			 * \param type: type of the tab
			 * \param data: extra data to be passed through
			 *
			 * \return tab index
			 *
			 * add tab to tab widget at index index
			 */
			int insertTab(const int & index, QWidget * page, const QIcon & icon, const QString & label, const main_window_shared_types::tab_type_e & type, const void * data = nullptr);

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
			QWidget * widget(const int & index, bool checkError = true);

			/**
			 * @brief Function: main_window_shared_types::tab_type_e getTabType(const int & index)
			 *
			 * \param index: index of the tab to return the type of
			 *
			 * \return type of tab page at index index
			 *
			 * return a tab type from tab widget
			 */
			main_window_shared_types::tab_type_e getTabType(const int & index);

			/**
			 * @brief Function: const void * getTabData(const int & index)
			 *
			 * \param index: index of the tab to return the data of
			 *
			 * \return data field of tab page at index index
			 *
			 * return a tab data from tab widget
			 */
			const void * getTabData(const int & index);

			/**
			 * @brief Function: void changeTabType(const int & index, const main_window_shared_types::tab_type_e newType, const void * data = nullptr)
			 *
			 * \param index: index of the tab to change the type of
			 * \param newType: new type of tab at index index
			 * \param data: extra data to be passed through
			 *
			 * change the type of a tab
			 */
			void changeTabType(const int & index, const main_window_shared_types::tab_type_e newType, const void * data = nullptr);

		protected:

		private:
			/**
			 * @brief tab data
			 *
			 */
			std::list<main_window_tab_data::MainWindowTabData> tabData;

			/**
			 * @brief Function: void deleteListElement(const int & index)
			 *
			 * \param index: index of the list to remove
			 *
			 * remove an element of the list
			 */
			void deleteListElement(const int & index);

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class MainWindowTabWidget
			 *
			 */
			DISABLE_COPY_MOVE(MainWindowTabWidget)

	};

}
/** @} */ // End of MainWindowTabWidgetGroup group

#endif // MAIN_WINDOW_TAB_WIDGET_H

#ifndef MAIN_WINDOW_TAB_WIDGET_H
#define MAIN_WINDOW_TAB_WIDGET_H
/**
 * @copyright
 * @file main_window_tab_widget.h
 * @author Andrea Gianarda
 * @date 07th of December 2020
 * @brief Main Window Tab Widget header file
*/

#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtWidgets/QWidget>

#include "main_window_shared_types.h"
#include "tab_widget.h"

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
	class MainWindowTabWidget : public tab_widget::TabWidget {

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
			 * @brief Function: int addEmptyTab(const QString & label, main_window_shared_types::tab_type_e & type)
			 *
			 * \param label: label of the tab
			 * \param type: type of the tab
			 *
			 * \return tab index
			 *
			 * add tab to tab widget
			 */
			int addEmptyTab(const QString & label, main_window_shared_types::tab_type_e & type);

			/**
			 * @brief Function: int addEmptyTab(const QIcon & icon, const QString & label, main_window_shared_types::tab_type_e & type)
			 *
			 * \param icon: icon of the tab
			 * \param label: label of the tab
			 * \param type: type of the tab
			 *
			 * \return tab index
			 *
			 * add tab to tab widget
			 */
			int addEmptyTab(const QIcon & icon, const QString & label, main_window_shared_types::tab_type_e & type);

			/**
			 * @brief Function: int insertEmptyTab(int index, const QString & label, main_window_shared_types::tab_type_e & type)
			 *
			 * \param index: index to insert tab to
			 * \param label: label of the tab
			 * \param type: type of the tab
			 *
			 * \return tab index
			 *
			 * add tab to tab widget at index index
			 */
			int insertEmptyTab(int index, const QString & label, main_window_shared_types::tab_type_e & type);

			/**
			 * @brief Function: int insertEmptyTab(int index, const QIcon & icon, const QString & label, main_window_shared_types::tab_type_e & type)
			 *
			 * \param index: index to insert tab to
			 * \param icon: icon of the tab
			 * \param label: label of the tab
			 * \param type: type of the tab
			 *
			 * \return tab index
			 *
			 * add tab to tab widget at index index
			 */
			int insertEmptyTab(int index, const QIcon & icon, const QString & label, main_window_shared_types::tab_type_e & type);

			/**
			 * @brief Function: int addTab(QWidget * page, const QString & label, main_window_shared_types::tab_type_e & type)
			 *
			 * \param page: widget to fill in
			 * \param label: label of the tab
			 * \param type: type of the tab
			 *
			 * \return tab index
			 *
			 * add tab to tab widget
			 */
			int addTab(QWidget * page, const QString & label, main_window_shared_types::tab_type_e & type);

			/**
			 * @brief Function: int addTab(QWidget * page, const QIcon & icon, const QString & label, main_window_shared_types::tab_type_e & type)
			 *
			 * \param page: widget to fill in
			 * \param icon: icon of the tab
			 * \param label: label of the tab
			 * \param type: type of the tab
			 *
			 * \return tab index
			 *
			 * add tab to tab widget
			 */
			int addTab(QWidget * page, const QIcon & icon, const QString & label, main_window_shared_types::tab_type_e & type);

			/**
			 * @brief Function: int insertTab(int index, QWidget * page, const QString & label, main_window_shared_types::tab_type_e & type)
			 *
			 * \param index: index to insert tab to
			 * \param page: widget to fill in
			 * \param label: label of the tab
			 * \param type: type of the tab
			 *
			 * \return tab index
			 *
			 * add tab to tab widget at index index
			 */
			int insertTab(int index, QWidget * page, const QString & label, main_window_shared_types::tab_type_e & type);

			/**
			 * @brief Function: int insertTab(int index, QWidget * page, const QIcon & icon, const QString & label, main_window_shared_types::tab_type_e & type)
			 *
			 * \param index: index to insert tab to
			 * \param page: widget to fill in
			 * \param icon: icon of the tab
			 * \param label: label of the tab
			 * \param type: type of the tab
			 *
			 * \return tab index
			 *
			 * add tab to tab widget at index index
			 */
			int insertTab(int index, QWidget * page, const QIcon & icon, const QString & label, main_window_shared_types::tab_type_e & type);

			/**
			 * @brief Function: void removeTab(int index)
			 *
			 * \param index: index of the tab to remove
			 *
			 * remove a tab from tab widget
			 */
			void removeTab(int index);

			/**
			 * @brief Function: void moveTab(int indexFrom, int indexTo)
			 *
			 * \param indexFrom: index of the tab to move
			 * \param indexTo: destination of the tab
			 *
			 * move a tab from index indexFrom to index indexTo
			 */
			void moveTab(int indexFrom, int indexTo);

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

			/**
			 * @brief Function: main_window_shared_types::tab_type_e getTabType(int index)
			 *
			 * \param index: index of the tab to return the type of
			 *
			 * \return type of tab page at index index
			 *
			 * return a tab type from tab widget
			 */
			main_window_shared_types::tab_type_e getTabType(int index);

			/**
			 * @brief Function: void changeTabType(int index, main_window_shared_types::tab_type_e newType)
			 *
			 * \param index: index of the tab to change the type of
			 * \param newType: new type of tab at index index
			 *
			 * change the type of a tab
			 */
			void changeTabType(int index, main_window_shared_types::tab_type_e newType);

		protected:

		private:
			/**
			 * @brief list of tab types
			 *
			 */
			QList<main_window_shared_types::tab_type_e> tabTypes;

			/**
			 * @brief Function: void deleteListElement(int index)
			 *
			 * \param index: index of the list to remove
			 *
			 * remove an element of the list
			 */
			void deleteListElement(int index);

			// Move and copy constructor
			/**
			 * @brief Function: MainWindowTabWidget(const main_window_tab_widget::MainWindowTabWidget & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Command MainWindowTabWidget copy constructor
			 */
			explicit MainWindowTabWidget(const main_window_tab_widget::MainWindowTabWidget & rhs) = delete;

			/**
			 * @brief Function: MainWindowTabWidget(main_window_tab_widget::MainWindowTabWidget && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Command MainWindowTabWidget move constructor
			 */
			explicit MainWindowTabWidget(main_window_tab_widget::MainWindowTabWidget && rhs) = delete;

			// Move and copy assignment operators
			/**
			 * @brief Function: MainWindowTabWidget & operator=(const main_window_tab_widget::MainWindowTabWidget & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Command MainWindowTabWidget copy assignment operator
			 */
			MainWindowTabWidget & operator=(const main_window_tab_widget::MainWindowTabWidget & rhs) = delete;

			/**
			 * @brief Function: MainWindowTabWidget & operator=(main_window_tab_widget::MainWindowTabWidget && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Command MainWindowTabWidget move assignment operator
			 */
			MainWindowTabWidget & operator=(main_window_tab_widget::MainWindowTabWidget && rhs) = delete;

	};

}
/** @} */ // End of MainWindowTabWidgetGroup group

#endif // MAIN_WINDOW_TAB_WIDGET_H

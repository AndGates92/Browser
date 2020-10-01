#ifndef MAIN_WINDOW_CTRL_TAB_H
#define MAIN_WINDOW_CTRL_TAB_H
/**
 * @copyright
 * @file main_window_ctrl_tab.h
 * @author Andrea Gianarda
 * @date 21st of December 2019
 * @brief Main Window Tab Control header file
*/

#include <QtCore/QLoggingCategory>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QAction>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

#include "main_window_shared_types.h"
#include "main_window_ctrl_base.h"
#include "main_window_tab.h"
#include "constructor_macros.h"

/** @defgroup MainWindowCtrlTabGroup Main Window Control Tab Doxygen Group
 *  Main Window control functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowCtrlTabOverall)
Q_DECLARE_LOGGING_CATEGORY(mainWindowCtrlTabUserInput)
Q_DECLARE_LOGGING_CATEGORY(mainWindowCtrlTabSearch)
Q_DECLARE_LOGGING_CATEGORY(mainWindowCtrlTabTabs)
Q_DECLARE_LOGGING_CATEGORY(mainWindowCtrlTabUrl)

namespace main_window_ctrl_tab {

	namespace {

		/**
		 * @brief invalid tab index - default value of optional argument index of executeActionOnTab function
		 *
		 */
		static constexpr int emptyUserInput = -1;

	}

	/**
	 * @brief MainWindowCtrlTab class
	 *
	 */
	class MainWindowCtrlTab final : public main_window_ctrl_base::MainWindowCtrlBase {

		Q_OBJECT

		public:

			/**
			 * @brief Function: explicit MainWindowCtrlTab(QWidget * parent, const std::shared_ptr<main_window_core::MainWindowCore> & core)
			 *
			 * \param core: main window core
			 * \param parent: parent windget
			 *
			 * Main window tab control constructor
			 */
			explicit MainWindowCtrlTab(QWidget * parent, const std::shared_ptr<main_window_core::MainWindowCore> & core);

			/**
			 * @brief Function: virtual ~MainWindowCtrlTab()
			 *
			 * Main window tab control destructor
			 */
			virtual ~MainWindowCtrlTab();

			/**
			 * @brief Function: void processTabIndex(const QString & userInputStr)
			 *
			 * This function converts the string indexStr to an integer and executes desired action on it
			 */
			void processTabIndex(const QString & userInputStr);

		public slots:

			/**
			 * @brief Function: void setUpOpenNewTab()
			 *
			 * This function prepares to add a new tab and automatically search the user input
			 */
			void setUpOpenNewTab();

		signals:
			/**
			 * @brief Function: void  currentTabSrcChanged(const QString & path)
			 *
			 * \param path: path of where the tab content originates from.
			 *
			 * This function is a signal to communicate changes in the tab source
			 */
			void currentTabSrcChanged(const QString & path);

		protected:
			/**
			 * @brief Function: virtual void actionOnReleasedKey(const main_window_shared_types::state_e & windowState, QKeyEvent * event) override
			 *
			 * \param windowState: state the window is into.
			 * \param event: key event.
			 *
			 * This function executes an action when a key is released
			 */
			virtual void actionOnReleasedKey(const main_window_shared_types::state_e & windowState, QKeyEvent * event) override;

		private slots:

			/**
			 * @brief Function: void historyBoundaryHit(const global_enums::element_position_e & position)
			 *
			 * \param position: position in the history.
			 *
			 * This function is a slot that receives a notification that the tab moved in the history of the tab
			 */
			void historyBoundaryHit(const global_enums::element_position_e & position);

			/**
			 * @brief Function: void processSearchReturnValue(const bool & found)
			 *
			 * \param found: search result data.
			 *
			 * This function is a slot that receives a notification that the search data changed
			 */
			void processSearchReturnValue(const bool & found);

			/**
			 * @brief Function: void printSearchResult(const main_window_tab_search::search_data_s & data) const
			 *
			 * \param data: search result data.
			 *
			 * This function is a slot that receives a notification that the search data changed
			 */
			void printSearchResult(const main_window_tab_search::search_data_s & data) const;

			/**
			 * @brief Function: void updateStatusBar(const int & tabIndex)
			 *
			 * \param tabIndex: index of the tab to connect signals from
			 *
			 * This function sends signals to update the status bar
			 */
			void updateStatusBar(const int & tabIndex);

			/**
			 * @brief Function: void disconnectTab(const int & tabIndex)
			 *
			 * \param tabIndex: index of the tab to disconnect signals from
			 *
			 * This function disconnects progress bar signal from a tab
			 */
			void disconnectTab(const int & tabIndex);

			/**
			 * @brief Function: void connectTab(const int & tabIndex)
			 *
			 * \param tabIndex: index of the tab to connect signals from
			 *
			 * This function connects progress bar signal from a tab
			 */
			void connectTab(const int & tabIndex);

			/**
			 * @brief Function: void createContentPathTextFromSource(const main_window_shared_types::page_type_e & type, const QString & source)
			 *
			 * \param type: type of the tab
			 * \param source: source of the tab
			 *
			 * This function creates the text to put in the context path from a string containing the source of the content in a tab
			 */
			void createContentPathTextFromSource(const main_window_shared_types::page_type_e & type, const QString & source);

			/**
			 * @brief Function: void setUpSearchFromMenu(const find_settings::FindSettings & settings)
			 *
			 * \param settings: search settings
			 *
			 * This function is the slot to trigger a find in the current tab
			 */
			void setUpSearchFromMenu(const find_settings::FindSettings & settings);

		private:
			/**
			 * @brief find direction
			 *
			 */
			find_settings::FindSettings findSettings;

			/**
			 * @brief Function: virtual void createExtraShortcuts() override
			 *
			 * This function creates shortcuts for the items on the window
			 */
			virtual void createExtraShortcuts() override;

			/**
			 * @brief Function: virtual void connectExtraSignals() override
			 *
			 * This function connects signals and slots within main window controller
			 */
			virtual void connectExtraSignals() override;

			/**
			 * @brief Function: virtual bool isValidWindowState(const main_window_shared_types::state_e & requestedWindowState) override
			 *
			 * \param requestedWindowState: state the window is requested to go into.
			 *
			 * \return boolean whether the state is valid or not. true if the state is valid and false otherwise.
			 *
			 * This function checks that the state is valid
			 */
			virtual bool isValidWindowState(const main_window_shared_types::state_e & requestedWindowState) override;

			/**
			 * @brief Function: virtual void postprocessWindowStateChange(const main_window_shared_types::state_e & previousState) override
			 *
			 * \param previousState: state the window was into before the transition.
			 *
			 * This function defines actions to be taken immediately after the window has changed state
			 */
			virtual void postprocessWindowStateChange(const main_window_shared_types::state_e & previousState) override;

			/**
			 * @brief Function: void executeActionOnTab(const int & index = main_window_ctrl_tab::emptyUserInput)
			 *
			 * \param index: index of tab to execute action on
			 *
			 * This function executes action on a based on user input
			 */
			void executeActionOnTab(const int & index = main_window_ctrl_tab::emptyUserInput);

			/**
			 * @brief Function: void executeActionOnOffset(const int & offset)
			 *
			 * \param offset: offset of tab to execute action on
			 *
			 * This function executes action on a based on user input
			 */
			void executeActionOnOffset(const int & offset);

			/**
			 * @brief Function: void executeTabAction(const int & userInput = main_window_ctrl_tab::emptyUserInput)
			 *
			 * \param userInput: user input to execute action. If not specified it is default to main_window_ctrl_tab::emptyUserInput
			 *
			 * This function executes action on a based on user input
			 */
			void executeTabAction(const int & userInput = main_window_ctrl_tab::emptyUserInput);

			/**
			 * @brief Function: void convertToAbsTabIndex(const int & offset, const global_enums::sign_e & sign)
			 *
			 * \param offset: relatinve tab index
			 * \param sign: direction of tab to apply action on: global_enums::sign_e::MINUS for left move and global_enums::sign_e::PLUS for right move
			 *
			 * This function moves to a different tab as specified by the user
			 */
			void convertToAbsTabIndex(const int & offset, const global_enums::sign_e & sign);

			/**
			 * @brief Function: void extractContentPath(const int & index)
			 *
			 * \param index: index of tab where the content has to be updated
			 *
			 * This function updates the content label
			 */
			void extractContentPath(const int & index);

			/**
			 * @brief Function: void addNewTabAndSearch(const QString & search)
			 *
			 * \param search: string to search
			 *
			 * This function adds a new tab to the tab widget and searches the user string
			 */
			void addNewTabAndSearch(const QString & search);

			/**
			 * @brief Function: virtual void prepareAction(const main_window_shared_types::state_e & windowState, QKeyEvent * event) override
			 *
			 * \param windowState: state the window is into.
			 * \param event: key event.
			 *
			 * This function executes a command on a based on user input and the state the window is in
			 */
			virtual void prepareAction(const main_window_shared_types::state_e & windowState, QKeyEvent * event) override;

			/**
			 * @brief Function: virtual void executeAction(const main_window_shared_types::state_e & windowState) override
			 *
			 * \param windowState: state the window is into.
			 *
			 * This function executes the actions required when the window is a given state
			 */
			virtual void executeAction(const main_window_shared_types::state_e & windowState) override;

			// ================================ START ACTIONS ========================================//
			/**
			 * @brief Function: int addNewTab(const main_window_shared_types::page_type_e & type, , const void * data = nullptr)
			 *
			 * \param type: type of tab to be added
			 * \param data: extra data to be passed through
			 *
			 * \return the tab index
			 *
			 * This function adds a new tab to the tab widget
			 */
			int addNewTab(const main_window_shared_types::page_type_e & type, const void * data = nullptr);

			/**
			 * @brief Function: void searchTab(const int & index, const QString & search)
			 *
			 * \param index: tab index to be searched
			 * \param search: string to search
			 *
			 * This function search on the tab at index index
			 */
			void searchTab(const int & index, const QString & search);

			/**
			 * @brief Function: void searchCurrentTab(const QString & search)
			 *
			 * \param search: string to search
			 *
			 * This function search on the current tab
			 */
			void searchCurrentTab(const QString & search);

			/**
			 * @brief Function: void scrollTab(const global_enums::offset_type_e direction)
			 *
			 * \param direction: direction of scrolling
			 *
			 * This function scroll the tab in the direction provided as argument
			 */
			void scrollTab(const global_enums::offset_type_e direction);

			/**
			 * @brief Function: void goToPageInHistory(const main_window_shared_types::navigation_type_e direction)
			 *
			 * \param direction: direction in the history
			 *
			 * This function goes to a page in the history of the tab
			 */
			void goToPageInHistory(const main_window_shared_types::navigation_type_e direction);

			/**
			 * @brief Function: void reloadTab(const int & tabIndex)
			 *
			 * \param tabIndex: tab index to reload
			 *
			 * This function reloads a tab as specified by the user
			 */
			void reloadTab(const int & tabIndex);

			/**
			 * @brief Function: void closeTab(const int & index)
			 *
			 * \param index: index of tab to close
			 *
			 * This function is a signal to close a tab
			 */
			void closeTab(const int & index);

			/**
			 * @brief Function: void moveTab(const int & tabIndex)
			 *
			 * \param tabIndex: index to move the tab to
			 *
			 * This function moves the current tab to a different tab as specified by the user
			 */
			void moveTab(const int & tabIndex);

			/**
			 * @brief Function: void moveCursor(const int & tabIndex)
			 *
			 * \param tabIndex: index to move the cursor to
			 *
			 * This function moves the cursor to a different tab as specified by the user
			 */
			void moveCursor(const int & tabIndex);

			/**
			 * @brief Function: void createOpenPrompt()
			 *
			 * This function creates and sets the open prompt
			 */
			void createOpenPrompt();

			// ================================ END ACTIONS ========================================//

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class MainWindowCtrlTab
			 *
			 */
			DISABLE_COPY_MOVE(MainWindowCtrlTab)

	};

}
/** @} */ // End of MainWindowCtrlTabGroup group

#endif // MAIN_WINDOW_CTRL_TAB_H

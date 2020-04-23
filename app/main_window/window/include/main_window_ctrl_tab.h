#ifndef MAIN_WINDOW_CTRL_TAB_H
#define MAIN_WINDOW_CTRL_TAB_H
/**
 * @copyright
 * @file main_window_ctrl_tab.h
 * @author Andrea Gianarda
 * @date 21st of December 2019
 * @brief Main Window Tab Control header file
*/

#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtWidgets/QMainWindow>
#include <qt5/QtWidgets/QMenu>
#include <qt5/QtWidgets/QAction>
#include <qt5/QtWidgets/QMenuBar>
#include <qt5/QtWidgets/QWidget>

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
		constexpr int emptyUserInput = -1;

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

		/**
		 * @brief Path towards JSON file storing informations about commands and shortcuts
		 *
		 */
		const QString commandFilePath("json/");

		/**
		 * @brief Filename storing informations about commands and shortcuts
		 *
		 */
		const QString commandFileName("tab_commands.json");

		/**
		 * @brief Full path towards JSON file storing informations about commands and shortcuts
		 *
		 */
		const QString commandFileFullPath(commandFilePath + commandFileName);

	}

	/**
	 * @brief MainWindowCtrlTab class
	 *
	 */
	class MainWindowCtrlTab final : public main_window_ctrl_base::MainWindowCtrlBase {

		Q_OBJECT

		public:

			/**
			 * @brief Function: explicit MainWindowCtrlTab(main_window_core::MainWindowCore * core, QWidget * window, QWidget * parent = Q_NULLPTR)
			 *
			 * \param core: main window core
			 * \param parent: parent windget
			 * \param window: window controlled
			 *
			 * Main window tab control constructor
			 */
			explicit MainWindowCtrlTab(QSharedPointer<main_window_core::MainWindowCore> core,  QWidget * window, QWidget * parent = Q_NULLPTR);

			/**
			 * @brief Function: ~MainWindowCtrlTab()
			 *
			 * Main window tab control destructor
			 */
			~MainWindowCtrlTab();

			/**
			 * @brief Function: void processTabIndex(const QString & userInputStr)
			 *
			 * This function converts the string indexStr to an integer and executes desired action on it
			 */
			void processTabIndex(const QString & userInputStr);

			/**
			 * @brief Function: void keyPressEvent(QKeyEvent * event) override
			 *
			 * \param event: event coming from keyboard
			 *
			 * This function handles event coming from the keyboard
			 * Escape is not triggered in keyPressedEvent
			 * Re-implement key pressed event
			 */
			void keyPressEvent(QKeyEvent * event) override;

			/**
			 * @brief Function: void keyReleaseEvent(QKeyEvent * event) override
			 *
			 * \param event: event coming from keyboard
			 *
			 * This function handles event coming from the keyboard
			 * Re-implement key released event
			 */
			void keyReleaseEvent(QKeyEvent * event) override;

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

		private slots:

			/**
			 * @brief Function: void updateStatusBar(const int & tabIndex)
			 *
			 * \param tabIndex: index of the tab to connect signals from
			 *
			 * This function sends signals to update the status bar
			 */
			void updateStatusBar(const int & tabIndex);

			/**
			 * @brief Function: void disconnectProgressBar(const int & tabIndex)
			 *
			 * \param tabIndex: index of the tab to disconnect signals from
			 *
			 * This function disconnects progress bar signal from a tab
			 */
			void disconnectProgressBar(const int & tabIndex);

			/**
			 * @brief Function: void connectProgressBar(const int & tabIndex)
			 *
			 * \param tabIndex: index of the tab to connect signals from
			 *
			 * This function connects progress bar signal from a tab
			 */
			void connectProgressBar(const int & tabIndex);

			/**
			 * @brief Function: void createContentPathTextFromSource(const main_window_shared_types::page_type_e & type, const QString & source)
			 *
			 * \param type: type of the tab
			 * \param source: source of the tab
			 *
			 * This function creates the text to put in the context path from a string containing the source of the content in a tab
			 */
			void createContentPathTextFromSource(const main_window_shared_types::page_type_e & type, const QString & source);

		private:
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
			 * @brief Function: void convertToAbsTabIndex(const int & offset, const global_types::sign_e & sign)
			 *
			 * \param offset: relatinve tab index
			 * \param sign: direction of tab to apply action on: global_types::sign_e::MINUS for left move and global_types::sign_e::PLUS for right move
			 *
			 * This function moves to a different tab as specified by the user
			 */
			void convertToAbsTabIndex(const int & offset, const global_types::sign_e & sign);

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
			 * @brief Function: virtual void setStateAction(const main_window_shared_types::state_e & windowState, QKeyEvent * event) override
			 *
			 * \param windowState: state the window is into.
			 * \param event: key event.
			 *
			 * This function executes a command on a based on user input and the state the window is in
			 */
			virtual void setStateAction(const main_window_shared_types::state_e & windowState, QKeyEvent * event) override;

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
			 * @brief Function: int addNewTab(const QString & search, const main_window_shared_types::page_type_e & type, , const void * data = nullptr)
			 *
			 * \param search: string to search
			 * \param type: type of tab to be added
			 * \param data: extra data to be passed through
			 *
			 * \return the tab index
			 *
			 * This function adds a new tab to the tab widget
			 */
			int addNewTab(const QString & search, const main_window_shared_types::page_type_e & type, const void * data = nullptr);

			/**
			 * @brief Function: void newSearchTab(const int & index, const QString & search)
			 *
			 * \param index: tab index to be searched
			 * \param search: string to search
			 *
			 * This function search on the tab at index index
			 */
			void newSearchTab(const int & index, const QString & search);

			/**
			 * @brief Function: void searchCurrentTab(const QString & search)
			 *
			 * \param search: string to search
			 *
			 * This function search on the current tab
			 */
			void searchCurrentTab(const QString & search);

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

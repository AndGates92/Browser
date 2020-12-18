#ifndef MAIN_WINDOW_CTRL_TAB_H
#define MAIN_WINDOW_CTRL_TAB_H
/**
 * @copyright
 * @file ctrl_tab.h
 * @author Andrea Gianarda
 * @date 21st of December 2019
 * @brief Main Window Tab Control header file
*/

#include <QtWidgets/QWidget>

#include "app/windows/main_window/shared/shared_types.h"
#include "app/windows/main_window/window/ctrl_base.h"
#include "app/windows/main_window/tabs/types.h"
#include "app/shared/constructor_macros.h"

// Included here because it is an argument to a Qt slot hence MOC must be able to find it
#include "app/windows/shared/find_settings.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */
namespace app {

	namespace main_window {

		namespace window {

			class Tab;

		}

		namespace window {

			namespace tab_ctrl {

				namespace {

					/**
					 * @brief invalid tab index - default value of optional argument index of executeActionOnTab function
					 *
					 */
					static constexpr int emptyUserInput = -1;

				}

			}

			class CtrlWrapper;

			/**
			 * @brief CtrlTab class
			 *
			 */
			class CtrlTab final : public app::main_window::window::CtrlBase {
				friend class app::main_window::window::CtrlWrapper;

				Q_OBJECT

				public:

					/**
					 * @brief Function: explicit CtrlTab(QWidget * parent, const std::shared_ptr<app::main_window::window::Core> & core)
					 *
					 * \param core: main window core
					 * \param parent: parent windget
					 *
					 * Main window tab control constructor
					 */
					explicit CtrlTab(QWidget * parent, const std::shared_ptr<app::main_window::window::Core> & core);

					/**
					 * @brief Function: virtual ~CtrlTab()
					 *
					 * Main window tab control destructor
					 */
					virtual ~CtrlTab();

					/**
					 * @brief Function: void processTabIndex(const QString & userInputStr)
					 *
					 * This function converts the string indexStr to an integer and executes desired action on it
					 */
					void processTabIndex(const QString & userInputStr);

					/**
					 * @brief Function: void setFindDirection(const app::shared::offset_type_e direction)
					 *
					 * \param direction: direction of find
					 *
					 * This function sets the direction of the search of text in a tab
					 */
					void setFindDirection(const app::shared::offset_type_e direction);

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
					 * @brief Function: virtual void actionOnReleasedKey(const app::main_window::state_e & windowState, QKeyEvent * event) override
					 *
					 * \param windowState: state the window is into.
					 * \param event: key event.
					 *
					 * This function executes an action when a key is released
					 */
					virtual void actionOnReleasedKey(const app::main_window::state_e & windowState, QKeyEvent * event) override;

				private slots:

					/**
					 * @brief Function: void historyBoundaryHit(const app::shared::element_position_e & position)
					 *
					 * \param position: position in the history.
					 *
					 * This function is a slot that receives a notification that the tab moved in the history of the tab
					 */
					void historyBoundaryHit(const app::shared::element_position_e & position);

					/**
					 * @brief Function: void processSearchReturnValue(const bool & found)
					 *
					 * \param found: search result data.
					 *
					 * This function is a slot that receives a notification that the search data changed
					 */
					void processSearchReturnValue(const bool & found);

					/**
					 * @brief Function: void printSearchResult(const app::main_window::tab::search_data_s & data) const
					 *
					 * \param data: search result data.
					 *
					 * This function is a slot that receives a notification that the search data changed
					 */
					void printSearchResult(const app::main_window::tab::search_data_s & data) const;

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
					 * @brief Function: void createContentPathTextFromSource(const app::main_window::page_type_e & type, const QString & source)
					 *
					 * \param type: type of the tab
					 * \param source: source of the tab
					 *
					 * This function creates the text to put in the context path from a string containing the source of the content in a tab
					 */
					void createContentPathTextFromSource(const app::main_window::page_type_e & type, const QString & source);

					/**
					 * @brief Function: void setUpSearchFromMenu(const app::windows::shared::FindSettings & settings)
					 *
					 * \param settings: search settings
					 *
					 * This function is the slot to trigger a find in the current tab
					 */
					void setUpSearchFromMenu(const app::windows::shared::FindSettings & settings);

				private:
					/**
					 * @brief find direction
					 *
					 */
					app::windows::shared::FindSettings findSettings;

					/**
					 * @brief Function: virtual void createShortcuts() override
					 *
					 * This function creates shortcuts for the items on the window
					 */
					virtual void createShortcuts() override;

					/**
					 * @brief Function: virtual void connectSignals() override
					 *
					 * This function connects signals and slots within main window controller
					 */
					virtual void connectSignals() override;

					/**
					 * @brief Function: void executeActionOnTab(const int & index = app::main_window::window::tab_ctrl::emptyUserInput)
					 *
					 * \param index: index of tab to execute action on
					 *
					 * This function executes action on a based on user input
					 */
					void executeActionOnTab(const int & index = app::main_window::window::tab_ctrl::emptyUserInput);

					/**
					 * @brief Function: void executeActionOnOffset(const int & offset)
					 *
					 * \param offset: offset of tab to execute action on
					 *
					 * This function executes action on a based on user input
					 */
					void executeActionOnOffset(const int & offset);

					/**
					 * @brief Function: void executeTabAction(const int & userInput = app::main_window::window::tab_ctrl::emptyUserInput)
					 *
					 * \param userInput: user input to execute action. If not specified it is default to app::main_window::window::tab_ctrl::emptyUserInput
					 *
					 * This function executes action on a based on user input
					 */
					void executeTabAction(const int & userInput = app::main_window::window::tab_ctrl::emptyUserInput);

					/**
					 * @brief Function: void convertToAbsTabIndex(const int & offset, const app::shared::sign_e & sign)
					 *
					 * \param offset: relatinve tab index
					 * \param sign: direction of tab to apply action on: app::shared::sign_e::MINUS for left move and app::shared::sign_e::PLUS for right move
					 *
					 * This function moves to a different tab as specified by the user
					 */
					void convertToAbsTabIndex(const int & offset, const app::shared::sign_e & sign);

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
					 * @brief Function: virtual void prepareAction(const app::main_window::state_e & windowState, QKeyEvent * event) override
					 *
					 * \param windowState: state the window is into.
					 * \param event: key event.
					 *
					 * This function executes a command on a based on user input and the state the window is in
					 */
					virtual void prepareAction(const app::main_window::state_e & windowState, QKeyEvent * event) override;

					/**
					 * @brief Function: virtual void executeAction(const app::main_window::state_e & windowState) override
					 *
					 * \param windowState: state the window is into.
					 *
					 * This function executes the actions required when the window is a given state
					 */
					virtual void executeAction(const app::main_window::state_e & windowState) override;

					// ================================ START ACTIONS ========================================//
					/**
					 * @brief Function: int addNewTab(const app::main_window::page_type_e & type, , const void * data = nullptr)
					 *
					 * \param type: type of tab to be added
					 * \param data: extra data to be passed through
					 *
					 * \return the tab index
					 *
					 * This function adds a new tab to the tab widget
					 */
					int addNewTab(const app::main_window::page_type_e & type, const void * data = nullptr);

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
					 * @brief Function: void scrollTab(const app::shared::offset_type_e direction)
					 *
					 * \param direction: direction of scrolling
					 *
					 * This function scroll the tab in the direction provided as argument
					 */
					void scrollTab(const app::shared::offset_type_e direction);

					/**
					 * @brief Function: void goToPageInHistory(const app::main_window::navigation_type_e direction)
					 *
					 * \param direction: direction in the history
					 *
					 * This function goes to a page in the history of the tab
					 */
					void goToPageInHistory(const app::main_window::navigation_type_e direction);

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
					 * @brief Disable move and copy constructors and operator= overloading for class CtrlTab
					 *
					 */
					DISABLE_COPY_MOVE(CtrlTab)

			};

		}

	}

}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_CTRL_TAB_H

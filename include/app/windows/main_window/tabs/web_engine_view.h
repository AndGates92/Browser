#ifndef MAIN_WINDOW_WEB_ENGINE_VIEW_H
#define MAIN_WINDOW_WEB_ENGINE_VIEW_H
/**
 * @copyright
 * @file web_engine_view.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Main Window Web Engine View header file
*/

// Qt libraries
#include <QtWidgets/QAction>

#include "app/base/tabs/web_engine_view.h"
#include "app/windows/main_window/shared/shared_types.h"
#include "app/shared/enums.h"
#include "app/shared/classes.h"
#include "app/shared/constructor_macros.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */
namespace app {

	namespace main_window {

		namespace tab {

			class Tab;
			class WebEnginePage;

			/**
			 * @brief action enable function
			 *
			 */
			using enable_function_t = std::function<bool()>;

			/**
			 * @brief search data changed
			 *
			 */
			typedef struct context_menu_list_item_t {
				QAction * action;                                 /**< action */
				app::main_window::tab::enable_function_t enabled; /**< Enable function */
			} context_menu_list_item_s;

			/**
			 * @brief context menu of the engine view
			 *
			 */
			using action_list_t = std::list<app::main_window::tab::context_menu_list_item_s>;

			/**
			 * @brief WebEngineView class
			 *
			 */
			class WebEngineView final : public app::base::tab::WebEngineView {
				friend class app::main_window::tab::Tab;

				Q_OBJECT

				public:
					/**
					 * @brief Function: explicit WebEngineView(QWidget * parent, std::weak_ptr<app::main_window::tab::Tab> attachedTab, const app::main_window::page_type_e & type, const QString & src, const void * data)
					 *
					 * \param type: tab type
					 * \param attachedTab: tab attached to this view
					 * \param src: source of the tab
					 * \param data: tab extra data
					 * \param parent: parent widget
					 *
					 * Main window web engine view constructor
					 */
					explicit WebEngineView(QWidget * parent, std::weak_ptr<app::main_window::tab::Tab> attachedTab, const app::main_window::page_type_e & type, const QString & src, const void * data);

					/**
					 * @brief Function: virtual ~WebEngineView()
					 *
					 * Main window web engine view destructor
					 */
					virtual ~WebEngineView();

					/**
					 * @brief Function: std::shared_ptr<app::main_window::tab::WebEnginePage> page() const
					 *
					 * \return page of the view
					 *
					 * This function returns the page of this web engine view
					 */
					std::shared_ptr<app::main_window::tab::WebEnginePage> page() const;

					/**
					 * @brief Function: const std::shared_ptr<app::main_window::tab::Tab> getTab() const
					 *
					 * \return tab the view belongs to
					 *
					 * This function returns the tab the web widget view belongs to
					 */
					const std::shared_ptr<app::main_window::tab::Tab> getTab() const;

				protected:

					/**
					 * @brief Function: virtual void contextMenuEvent(QContextMenuEvent * event) override
					 *
					 * \param event: Context menu event
					 *
					 * This function is triggered when the context menu has to be shown
					 */
					virtual void contextMenuEvent(QContextMenuEvent * event) override;

				private slots:

				private:
					/**
					 * @brief actions of the context menu
					 * key is the action
					 * value is a function that returns a boolean stating whether the action should be enabled or not
					 *
					 */
					action_list_t contextMenuExtraActions;

					/**
					 * @brief Function: void connectSignals()
					 *
					 * This function connects signals and slots within the web engine view
					 */
					void connectSignals();

					/**
					 * @brief Function: const std::string printActionMap() const
					 *
					 * \return string listing the actions in the context menu
					 *
					 * This function returns a string of listing the actions in the context menu
					 */
					const std::string printActionMap() const;

					/**
					 * @brief Function: void enableMenuCustomAction(QMenu * menu)
					 *
					 * \param menu: menu to enabled actions to
					 * \param position: position in the web engine view where the menu was requested
					 *
					 * This function is a function that shows the context menu.
					 */
					void enableMenuCustomAction(QMenu * menu);

					// Move and copy constructor
					/**
					 * @brief Disable move and copy constructors and operator= overloading for class WebEngineView
					 *
					 */
					DISABLE_COPY_MOVE(WebEngineView)

			};

		}

	}

}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_WEB_ENGINE_VIEW_H

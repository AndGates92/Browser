#ifndef MAIN_WINDOW_TAB_HISTORY_H
#define MAIN_WINDOW_TAB_HISTORY_H
/**
 * @copyright
 * @file history.h
 * @author Andrea Gianarda
 * @date 25th May 2020
 * @brief Tab History header file
*/

#include "base/tabs/include/history.h"
#include "common/include/global_enums.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */
namespace app {

	namespace main_window {

		namespace tab {

			class Tab;

			/**
			 * @brief History class
			 *
			 */
			class History final : public app::base::tab::History {
				friend class app::main_window::tab::Tab;

				public:
					/**
					 * @brief Function: explicit History(QWidget * parent, std::weak_ptr<app::base::tab::Tab> browserTab, QWebEngineHistory * history)
					 *
					 * \param parent: parent widget
					 * \param tab: tab
					 * \param history: history of the history
					 *
					 * Main window tab history constructor
					 */
					explicit History(QWidget * parent, std::weak_ptr<app::base::tab::Tab> browserTab, QWebEngineHistory * history);

					/**
					 * @brief Function: virtual ~History()
					 *
					 * Main window tab history destructor
					 */
					virtual ~History();

				protected:

				private:

					// Move and copy constructor
					/**
					 * @brief Disable move and copy constructors and operator= overloading for class History
					 *
					 */
					DISABLE_COPY_MOVE(History)

			};

		}

	}

}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_TAB_HISTORY_H

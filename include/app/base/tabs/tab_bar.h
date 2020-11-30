#ifndef TAB_BAR_H
#define TAB_BAR_H
/**
 * @copyright
 * @file tab_bar.h
 * @author Andrea Gianarda
 * @date 02rd October 2019
 * @brief Tab Bar header file
*/

// Qt libraries
#include <QtWidgets/QTabBar>

#include "app/utility/logger/macros.h"
#include "app/shared/enums.h"
#include "app/shared/constructor_macros.h"

/** @defgroup TabGroup Tab Doxygen Group
 *  Tab functions and classes
 *  @{
 */

namespace app {

	namespace base {

		namespace tab {

			namespace tab_bar {

				namespace {
					/**
					 * @brief minimum width of the tab bar
					 *
					 */
					static constexpr int minWidth = 50;// px
				}

			}

			/**
			 * @brief TabBar class
			 *
			 */
			class TabBar : public QTabBar {

				Q_OBJECT

				public:
					/**
					 * @brief Function: explicit TabBar(QWidget * parent, const int & width = app::base::tab::tab_bar::minWidth)
					 *
					 * \param parent: parent widget
					 * \param width: width of the tab bar
					 *
					 * Tab bar constructor
					 */
					explicit TabBar(QWidget * parent, const int & width = app::base::tab::tab_bar::minWidth);

					/**
					 * @brief Function: void setWdith(int newWidth)
					 *
					 * \param newWidth: new tab bar width
					 *
					 * Set the tab bar width
					 */
					void setWidth(const int & newWidth);

				protected:
					/**
					 * @brief Function: QSize tabSizeHint(int index) const override
					 *
					 * \param index: index of tab
					 *
					 * Calculates the recommended size of the tab
					 */
					QSize tabSizeHint(int index) const override;

					/**
					 * @brief Function: void resizeEvent(QResizeEvent * event) override
					 *
					 * \param event: resize event
					 *
					 * Reimplement resize event
					 */
					void resizeEvent(QResizeEvent * event) override;

				private:
					/**
					 * @brief Function: void keyPressEvent(QKeyEvent * event)
					 *
					 * \param event: key event
					 *
					 * Re-implement key pressed event
					 */
					void keyPressEvent(QKeyEvent * event);

					// Move and copy constructor
					/**
					 * @brief Disable move and copy constructors and operator= overloading for class TabBar
					 *
					 */
					DISABLE_COPY_MOVE(TabBar)

			};

		}

	}

}
/** @} */ // End of TabGroup group

#endif // TAB_BAR_H

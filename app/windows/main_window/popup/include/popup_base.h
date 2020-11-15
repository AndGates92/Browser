#ifndef MAIN_WINDOW_POPUP_BASE_H
#define MAIN_WINDOW_POPUP_BASE_H
/**
 * @copyright
 * @file popup_base.h
 * @author Andrea Gianarda
 * @date 03rd of June 2020
 * @brief Main Window popup base class header file
*/

#include <QtCore/QLoggingCategory>
#include <QtWidgets/QWidget>

#include "base/popup/include/popup_base.h"

#include "common/include/constructor_macros.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */

namespace main_window {

	/**
	 * @brief PopupBase class
	 *
	 */
	class PopupBase : public popup_base::PopupBase {

		public:
			/**
			 * @brief Function: explicit PopupBase(QWidget * parent, const bool & centerWidget, const int & widgetPadding, Qt::WindowFlags flags = Qt::WindowFlags())
			 *
			 * \param parent: parent window
			 * \param centerWidget: boolean to state whether the widget has to be centered
			 * \param widgetPadding: padding of the widget with respect to the sides of the window
			 * \param flags: window flags
			 *
			 * Main window popup base constructor
			 */
			explicit PopupBase(QWidget * parent, const bool & centerWidget, const int & widgetPadding, Qt::WindowFlags flags = Qt::WindowFlags());

			/**
			 * @brief Function: virtual ~PopupBase()
			 *
			 * Main window popup base destructor
			 */
			virtual ~PopupBase();

		protected:

			/**
			 * @brief Function: virtual void activatePopup()
			 *
			 * This function activates the popup.
			 * It sets the focus and proxy focus and prepare it for user input
			 */
			virtual void activatePopup() = 0;

			/**
			 * @brief Function: virtual void popupLayout()
			 *
			 * This function creates the layout of the popup base
			 */
			virtual void popupLayout() = 0;

			/**
			 * @brief Function: virtual void fillWindow()
			 *
			 * This function creates menus that are part of the popup base
			 */
			virtual void fillPopup() = 0;

			/**
			 * @brief Function: virtual void connectSignals()
			 *
			 * This function connects signals and slots between main popup base elements
			 */
			virtual void connectSignals() = 0;

		private:

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class PopupBase
			 *
			 */
			DISABLE_COPY_MOVE(PopupBase)

	};

}

/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_POPUP_BASE_H

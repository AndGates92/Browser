#ifndef MAIN_WINDOW_POPUP_BASE_H
#define MAIN_WINDOW_POPUP_BASE_H
/**
 * @copyright
 * @file main_window_popup_base.h
 * @author Andrea Gianarda
 * @date 03rd of June 2020
 * @brief Main Window popup base class header file
*/

#include <QtCore/QLoggingCategory>
#include <QtWidgets/QWidget>

#include "popup_base.h"

#include "constructor_macros.h"

/** @defgroup MainWindowPopupBaseGroup Main Window Popup Base Doxygen Group
 *  Main Window popup base functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowPopupBaseOverall)

namespace main_window_popup_base {

	/**
	 * @brief MainWindowPopupBase class
	 *
	 */
	class MainWindowPopupBase : public popup_base::PopupBase {

		public:
			/**
			 * @brief Function: explicit MainWindowPopupBase(QWidget * parent, const bool & centerWidget, const int & widgetPadding, Qt::WindowFlags flags = Qt::WindowFlags())
			 *
			 * \param parent: parent window
			 * \param centerWidget: boolean to state whether the widget has to be centered
			 * \param widgetPadding: padding of the widget with respect to the sides of the window
			 * \param flags: window flags
			 *
			 * Main window popup base constructor
			 */
			explicit MainWindowPopupBase(QWidget * parent, const bool & centerWidget, const int & widgetPadding, Qt::WindowFlags flags = Qt::WindowFlags());

			/**
			 * @brief Function: virtual ~MainWindowPopupBase()
			 *
			 * Main window popup base destructor
			 */
			virtual ~MainWindowPopupBase();

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
			 * @brief Disable move and copy constructors and operator= overloading for class MainWindowPopupBase
			 *
			 */
			DISABLE_COPY_MOVE(MainWindowPopupBase)

	};

}

/** @} */ // End of MainWindowPopupBaseGroup group

#endif // MAIN_WINDOW_POPUP_BASE_H

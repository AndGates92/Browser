#ifndef POPUP_BASE_H
#define POPUP_BASE_H
/**
 * @copyright
 * @file popup_base.h
 * @author Andrea Gianarda
 * @date 21st of June 2020
 * @brief Popup base class header file
*/

#include <memory>

// Qt libraries
#include <QtWidgets/QWidget>
#include <QtWidgets/QAction>
#include <QtWidgets/QLabel>

#include "popup_properties.h"

#include "action.h"
#include "constructor_macros.h"

/** @defgroup PopupBaseGroup Main Window Popup Base Doxygen Group
 *  Popup base functions and classes
 *  @{
 */

namespace popup_base {

	/**
	 * @brief PopupBase class
	 *
	 */
	class PopupBase : public QWidget, public popup_properties::PopupProperties {

		Q_OBJECT

		public:
			/**
			 * @brief Function: explicit PopupBase(QWidget * parent, const bool & centerWidget, const int & widgetPadding, Qt::WindowFlags flags = Qt::WindowFlags())
			 *
			 * \param parent: parent widget
			 * \param centerWidget: boolean to state whether the widget has to be centered
			 * \param widgetPadding: padding of the widget with respect to the sides of the window
			 * \param flags: window flags
			 *
			 * Popup base constructor
			 */
			explicit PopupBase(QWidget * parent, const bool & centerWidget, const int & widgetPadding, Qt::WindowFlags flags = Qt::WindowFlags());

			/**
			 * @brief Function: virtual ~PopupBase()
			 *
			 * Popup base destructor
			 */
			virtual ~PopupBase();

		signals:
			/**
			 * @brief Function: void closePopup()
			 *
			 * This function is a signal emitted when the popup is closed
			 */
			void closePopup();

		protected:
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

			/**
			 * @brief Function: std::unique_ptr<QLabel> actionToLabel(QWidget * parent, const std::unique_ptr<QAction> & action) const
			 *
			 * \param parent: parent widget of QLabel
			 * \param action: action to convert to QLabel
			 *
			 * This function allows to print text and shortcut in a QLabel
			 */
			std::unique_ptr<QLabel> actionToLabel(QWidget * parent, const std::unique_ptr<action::Action> & action) const;

		private:

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class PopupBase
			 *
			 */
			DISABLE_COPY_MOVE(PopupBase)

	};

}

/** @} */ // End of PopupBaseGroup group

#endif // POPUP_BASE_H

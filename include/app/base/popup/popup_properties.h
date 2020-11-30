#ifndef POPUP_PROPERTIES_H
#define POPUP_PROPERTIES_H
/**
 * @copyright
 * @file popup_properties.h
 * @author Andrea Gianarda
 * @date 21st of June 2020
 * @brief Popup properties class header file
*/

// Qt libraries
#include <QtWidgets/QWidget>

#include "app/shared/constructor_macros.h"

/** @defgroup PopupGroup Popup Doxygen Group
 *  Popup functions and classes
 *  @{
 */

namespace app {

	namespace base {

		namespace popup {

			/**
			 * @brief PopupProperties class
			 *
			 */
			class PopupProperties {

				public:
					/**
					 * @brief Function: bool isCentered() const
					 *
					 * \return boolean whether the widget has to be centered or not
					 *
					 * This function returns whether the widget has to be centered or not
					 */
					bool isCentered() const;

					/**
					 * @brief Function: int getPadding() const
					 *
					 * \return padding of this widget
					 *
					 * This function returns the padding to be applied for this widget
					 */
					int getPadding() const;

				protected:

					/**
					 * @brief boolean stating whether the widget is centered or not
					 *
					 */
					bool centered;

					/**
					 * @brief widget padding with respect to the right side is the widget is not centered or both sides if it is
					 *
					 */
					int padding;

					/**
					 * @brief Function: explicit PopupProperties(const bool & center, const int & sidePadding)
					 *
					 * \param center: boolean to state whether the widget has to be centered
					 * \param sidePadding: padding of the widget with respect to the sides of the window
					 *
					 * Popup properties constructor
					 */
					explicit PopupProperties(const bool & center, const int & sidePadding);

					/**
					 * @brief Function: virtual ~PopupProperties()
					 *
					 * Popup properties destructor
					 */
					virtual ~PopupProperties();

					// Move and copy constructor
					/**
					 * @brief Function: PopupProperties(const app::base::popup::PopupProperties & rhs)
					 *
					 * \param rhs: class to copy
					 *
					 * popup properties copy constructor
					 * Do not set it as explicit as copy-initialization is allowed
					 */
					PopupProperties(const app::base::popup::PopupProperties & rhs);

					/**
					 * @brief Function: PopupProperties::PopupProperties(app::base::popup::PopupProperties && rhs)
					 *
					 * \param rhs: class to move
					 *
					 * popup properties move constructor
					 */
					explicit PopupProperties(app::base::popup::PopupProperties && rhs);

					// Move and copy assignment operators
					/**
					 * @brief Function: PopupProperties & operator=(const app::base::popup::PopupProperties & rhs)
					 *
					 * \param rhs: class to copy
					 *
					 * popup properties copy assignment operator
					 */
					PopupProperties & operator=(const app::base::popup::PopupProperties & rhs);

					/**
					 * @brief Function: PopupProperties & operator=(app::base::popup::PopupProperties && rhs)
					 *
					 * \param rhs: class to move
					 *
					 * popup properties move assignment operator
					 */
					PopupProperties & operator=(app::base::popup::PopupProperties && rhs);

					/**
					 * @brief Function: void setCentered(const bool & center)
					 *
					 * \param center: boolean value to set centered property
					 *
					 * This function sets centered property
					 */
					void setCentered(const bool & center);

					/**
					 * @brief Function: void setPadding(const int & sidePadding)
					 *
					 * \param sidePadding: side padding of the widget
					 *
					 * This function sets the padding for the popup
					 */
					void setPadding(const int & sidePadding);

				private:

			};

		}

	}

}

/** @} */ // End of PopupGroup group

#endif // POPUP_PROPERTIES_H

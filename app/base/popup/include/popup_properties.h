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

#include "constructor_macros.h"

/** @defgroup PopupPropertiesGroup Popup properties Doxygen Group
 *  Popup properties functions and classes
 *  @{
 */

namespace popup_properties {

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
			 * @brief Function: PopupProperties(const popup_properties::PopupProperties & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * popup properties copy constructor
			 * Do not set it as explicit as copy-initialization is allowed
			 */
			PopupProperties(const popup_properties::PopupProperties & rhs);

			/**
			 * @brief Function: PopupProperties::PopupProperties(popup_properties::PopupProperties && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * popup properties move constructor
			 */
			explicit PopupProperties(popup_properties::PopupProperties && rhs);

			// Move and copy assignment operators
			/**
			 * @brief Function: PopupProperties & operator=(const popup_properties::PopupProperties & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * popup properties copy assignment operator
			 */
			PopupProperties & operator=(const popup_properties::PopupProperties & rhs);

			/**
			 * @brief Function: PopupProperties & operator=(popup_properties::PopupProperties && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * popup properties move assignment operator
			 */
			PopupProperties & operator=(popup_properties::PopupProperties && rhs);

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

/** @} */ // End of PopupPropertiesGroup group

#endif // POPUP_PROPERTIES_H

#ifndef POPUP_CONTAINER_LAYOUT_H
#define POPUP_CONTAINER_LAYOUT_H
/**
 * @copyright
 * @file popup_container_layout.h
 * @author Andrea Gianarda
 * @date 14th of August 2020
 * @brief Popup container layout class header file
 */

// Qt libraries
#include <QtWidgets/QStackedLayout>

#include "app/shared/constructor_macros.h"

/** @defgroup PopupGroup Popup Doxygen Group
 *  Popup functions and classes
 *  @{
 */

namespace app {

	namespace base {

		namespace popup {

			/**
			 * @brief PopupContainerLayout class
			 *
			 */
			class PopupContainerLayout : public QStackedLayout {

				public:
					/**
					 * @brief Function: explicit PopupContainerLayout(QWidget * parent)
					 *
					 * \param parent: parent window
					 *
					 * Pop up container layout constructor
					 */
					explicit PopupContainerLayout(QWidget * parent);

					/**
					 * @brief Function: virtual ~PopupContainerLayout()
					 *
					 * Pop up container layout destructor
					 */
					virtual ~PopupContainerLayout();

				protected:

				private:
					/**
					 * @brief Function: virtual QSize sizeHint() const override
					 *
					 * \return return recommended size of the widget
					 *
					 * Compute recommendend size of the widget
					 */
					virtual QSize sizeHint() const override;

					// Move and copy constructor
					/**
					 * @brief Disable move and copy constructors and operator= overloading for class PopupContainerLayout
					 *
					 */
					DISABLE_COPY_MOVE(PopupContainerLayout)

			};

		}

	}

}

/** @} */ // End of PopupGroup group

#endif // POPUP_CONTAINER_LAYOUT_H

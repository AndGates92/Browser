#ifndef POPUP_CONTAINER_LAYOUT_H
#define POPUP_CONTAINER_LAYOUT_H
/**
 * @copyright
 * @file popup_container_layout.h
 * @author Andrea Gianarda
 * @date 14th of August 2020
 * @brief Popup container layout class header file
 */

#include <QtCore/QLoggingCategory>
#include <QtWidgets/QStackedLayout>

#include "constructor_macros.h"


/** @defgroup PopupContainerLayoutGroup Popup Container Layout Doxygen Group
 *  Pop up container layout functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(popupContainerLayoutOverall)

namespace popup_container_layout {

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

/** @} */ // End of PopupContainerLayoutGroup group

#endif // POPUP_CONTAINER_LAYOUT_H

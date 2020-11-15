#ifndef LABEL_POPUP_H
#define LABEL_POPUP_H
/**
 * @copyright
 * @file label_popup.h
 * @author Andrea Gianarda
 * @date 13th of August 2020
 * @brief Label popup class header file
*/

#include <QtCore/QLoggingCategory>
#include <QtWidgets/QWidget>
#include <QtCore/QTimer>

#include "widgets/elided_label/include/elided_label.h"
#include "windows/main_window/popup/include/popup_base.h"
#include "common/include/constructor_macros.h"

/** @defgroup LabelPopupGroup Label Popup Widget Doxygen Group
 *  Label popup menu functions and classes
 *  @{
 */

namespace label_popup {

	/**
	 * @brief LabelPopup class
	 *
	 */
	class LabelPopup final : public main_window::PopupBase {

		Q_OBJECT

		public:
			/**
			 * @brief Function: explicit LabelPopup(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags())
			 *
			 * \param parent: parent window
			 * \param flags: window flags
			 *
			 * Main window label popup constructor
			 */
			explicit LabelPopup(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags());

			/**
			 * @brief Function: virtual ~LabelPopup()
			 *
			 * Main window label popup destructor
			 */
			virtual ~LabelPopup();

			/**
			 * @brief Function: virtual void activatePopup() override
			 *
			 * This function activates the popup.
			 * It sets the focus and proxy focus and prepare it for user input
			 */
			virtual void activatePopup() override;

		public slots:

			/**
			 * @brief Function: void setLabelText(const QString & text)
			 *
			 * \param text: text of the label
			 *
			 * This function sets the text of the label.
			 */
			void setLabelText(const QString & text);

		signals:

		protected:
			/**
			 * @brief Function: virtual void popupLayout() override
			 *
			 * This function creates the layout of the popup menu
			 */
			virtual void popupLayout() override;

			/**
			 * @brief Function: virtual void fillWindow() override
			 *
			 * This function creates menus that are part of the popup menu
			 */
			virtual void fillPopup() override;

			/**
			 * @brief Function: virtual void connectSignals() override
			 *
			 * This function connects signals and slots between main popup menu elements
			 */
			virtual void connectSignals() override;

		private:

			/**
			 * @brief insert label
			 *
			 */
			std::unique_ptr<elided_label::ElidedLabel> label;

			/**
			 * @brief insert label
			 *
			 */
			std::unique_ptr<QTimer> timer;

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
			 * @brief Disable move and copy constructors and operator= overloading for class LabelPopup
			 *
			 */
			DISABLE_COPY_MOVE(LabelPopup)

			/**
			 * @brief Function: void close()
			 *
			 * This function closes the popup
			 */
			void close();

		private slots:

	};

}

/** @} */ // End of LabelPopupGroup group

#endif // LABEL_POPUP_H

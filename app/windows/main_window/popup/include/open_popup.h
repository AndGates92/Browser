#ifndef OPEN_POPUP_H
#define OPEN_POPUP_H
/**
 * @copyright
 * @file open_popup.h
 * @author Andrea Gianarda
 * @date 03rd of June 2020
 * @brief Open popup class header file
*/

#include <QtCore/QLoggingCategory>
#include <QtWidgets/QWidget>

#include "open_content.h"
#include "main_window_popup_base.h"
#include "constructor_macros.h"

/** @defgroup OpenPopupGroup Open Popup Widget Doxygen Group
 *  Open popup menu functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(openPopupOverall)
Q_DECLARE_LOGGING_CATEGORY(openPopupOpen)
Q_DECLARE_LOGGING_CATEGORY(openPopupBrowse)
Q_DECLARE_LOGGING_CATEGORY(openPopupCancel)

namespace open_popup {

	/**
	 * @brief OpenPopup class
	 *
	 */
	class OpenPopup final : public main_window_popup_base::MainWindowPopupBase, public open_content::OpenContent {

		Q_OBJECT

		public:
			/**
			 * @brief Function: explicit OpenPopup(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags())
			 *
			 * \param parent: parent window
			 * \param flags: window flags
			 *
			 * Main window open popup constructor
			 */
			explicit OpenPopup(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags());

			/**
			 * @brief Function: virtual ~OpenPopup()
			 *
			 * Main window open popup destructor
			 */
			virtual ~OpenPopup();

			/**
			 * @brief Function: virtual void activatePopup() override
			 *
			 * This function activates the popup.
			 * It sets the focus and proxy focus and prepare it for user input
			 */
			virtual void activatePopup() override;

			/**
			 * @brief Function: virtual void keyPressEvent(QKeyEvent * event) final
			 *
			 * \param event: event coming from keyboard
			 *
			 * This function handles event coming from the keyboard
			 * Escape is not triggered in keyPressedEvent
			 * Re-implement key pressed event
			 */
			virtual void keyPressEvent(QKeyEvent * event) final;

		signals:
			/**
			 * @brief Function: void fileRead(const QString & filepath, const void * data)
			 *
			 * \param filepath: path of the file
			 * \param data: extra data to be passed through
			 *
			 * This function is a signal to inform the menu that the center window must be updated
			 */
			void fileRead(const QString & filepath, const void * data);

			/**
			 * @brief Function: void sizeChanged()
			 *
			 * This function is a signal to inform that the size of the widget has changed.
			 * It should not be emitted when the change in size is due to a resize event
			 */
			void sizeChanged();

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

		private slots:

			/**
			 * @brief Function: virtual void apply() override
			 *
			 * This function is the slot of the open action
			 */
			virtual void apply() override;

			/**
			 * @brief Function: virtual void browse() override
			 *
			 * This function is the slot of the browse action 
			 */
			virtual void browse() override;

			/**
			 * @brief Function: virtual void cancel() override
			 *
			 * This function is the slot of the cancel action
			 */
			virtual void cancel() override;

			/**
			 * @brief Function: void postProcessTypeAction()
			 *
			 * This function is the slot of the insert action
			 */
			void postProcessTypeAction();

			/**
			 * @brief Function: virtual void pathChanged(const QString & path) override
			 *
			 * \param path: path of the file
			 *
			 * This function is the slot triggered whenever the path of the file changes on the QLineEdit
			 */
			virtual void pathChanged(const QString & path) override;

		private:
			/**
			 * @brief open label
			 *
			 */
			std::unique_ptr<QLabel> openLabel;

			/**
			 * @brief browse label
			 *
			 */
			std::unique_ptr<QLabel> browseLabel;

			/**
			 * @brief cancel label
			 *
			 */
			std::unique_ptr<QLabel> cancelLabel;

			/**
			 * @brief insert label
			 *
			 */
			std::unique_ptr<QLabel> insertLabel;

			/**
			 * @brief Function: virtual void close() override
			 *
			 * This function closes the popup
			 */
			virtual void close() override;

			/**
			 * @brief Function: virtual void openItem(const QString & path) override
			 *
			 * \param path: path of the file
			 *
			 * This function triggers the opening of the item
			 */
			virtual void openItem(const QString & path) override;

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
			 * @brief Disable move and copy constructors and operator= overloading for class OpenPopup
			 *
			 */
			DISABLE_COPY_MOVE(OpenPopup)

	};

}

/** @} */ // End of OpenPopupGroup group

#endif // OPEN_POPUP_H

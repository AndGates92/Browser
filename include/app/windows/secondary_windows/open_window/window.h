#ifndef OPEN_BUTTON_WINDOW_H
#define OPEN_BUTTON_WINDOW_H
/**
 * @copyright
 * @file window.h
 * @author Andrea Gianarda
 * @date 25th of September 2019
 * @brief Open Window header file
*/

#include <QtCore/QLoggingCategory>
#include <QtWidgets/QWidget>

#include <QtWidgets/QPushButton>

#include "app/shared/constructor_macros.h"
#include "app/base/window/open_content.h"

/** @defgroup OpenWindowGroup Open Window Doxygen Group
 *  Open Window functions and classes
 *  @{
 */
namespace app {

	namespace open_window {

		/**
		 * @brief Window class
		 *
		 */
		class Window final : public QWidget, public app::base::window::OpenContent {

			Q_OBJECT

			public:
				/**
				 * @brief Function: explicit Window(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags())
				 *
				 * \param parent: parent window
				 * \param flags: window flags
				 *
				 * Open button window constructor
				 */
				explicit Window(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags());

				/**
				 * @brief Function: virtual ~Window()
				 *
				 * Open button window destructor
				 */
				virtual ~Window();

			protected:

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
				 * This function is the slot of the browse button
				 */
				virtual void browse() override;

				/**
				 * @brief Function: virtual void cancel() override
				 *
				 * This function is the slot of the cancel button
				 */
				virtual void cancel() override;

				/**
				 * @brief Function: virtual void pathChanged(const QString & path) override
				 *
				 * \param path: path of the file
				 *
				 * This function is the slot triggered whenever the path of the file changes on the QLineEdit
				 */
				virtual void pathChanged(const QString & path) override;

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

			private:
				/**
				 * @brief Function: void windowLayout()
				 *
				 * This function creates the layout of the window
				 */
				void windowLayout();

				/**
				 * @brief Function: void fillWindow()
				 *
				 * This function creates widgets that are part of the window
				 */
				void fillWindow();

				/**
				 * @brief Function: virtual void connectSignals() override
				 *
				 * This function connects signals and slots between main window elements
				 */
				virtual void connectSignals() override;

				/**
				 * @brief Function: virtual void close() override
				 *
				 * This function closes the window
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

				/**
				 * @brief open button
				 *
				 */
				std::unique_ptr<QPushButton> openButton;

				/**
				 * @brief browse button
				 *
				 */
				std::unique_ptr<QPushButton> browseButton;

				/**
				 * @brief cancel button
				 *
				 */
				std::unique_ptr<QPushButton> cancelButton;

				// Move and copy constructor
				/**
				 * @brief Disable move and copy constructors and operator= overloading for class Window
				 *
				 */
				DISABLE_COPY_MOVE(Window)

		};

	}

}
/** @} */ // End of OpenWindowGroup group

#endif // OPEN_BUTTON_WINDOW_H

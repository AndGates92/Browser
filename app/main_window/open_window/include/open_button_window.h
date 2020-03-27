#ifndef OPEN_BUTTON_WINDOW_H
#define OPEN_BUTTON_WINDOW_H
/**
 * @copyright
 * @file open_button_window.h
 * @author Andrea Gianarda
 * @date 25th of September 2019
 * @brief Open Button Window header file
*/

#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtWidgets/QDialog>
#include <qt5/QtWidgets/QLineEdit>
#include <qt5/QtWidgets/QPushButton>

#include "constructor_macros.h"

/** @defgroup OpenButtonWindowGroup Open Button Window Doxygen Group
 *  Open Button Window functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(openButtonWindowOverall)
Q_DECLARE_LOGGING_CATEGORY(openButtonWindowLayout)
Q_DECLARE_LOGGING_CATEGORY(openButtonWindowOpen)
Q_DECLARE_LOGGING_CATEGORY(openButtonWindowCancel)


namespace open_button_window {

	namespace {
		/**
		 * @brief maximum number of location in the array storing a line of the user selected file
		 *
		 */
		const int userFileSize = 1024;
	}

	/**
	 * @brief OpenButtonWindow class
	 *
	 */
	class OpenButtonWindow final : public QDialog {

		Q_OBJECT

		public:
			/**
			 * @brief Function: explicit OpenButtonWindow(QWidget * parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags())
			 *
			 * \param parent: parent window
			 * \param flags: window flags
			 *
			 * Open button window constructor
			 */
			explicit OpenButtonWindow(QWidget * parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());

			/**
			 * @brief Function: ~OpenButtonWindow()
			 *
			 * Open button window destructor
			 */
			~OpenButtonWindow();

		protected:

		private slots:

			/**
			 * @brief Function: void open()
			 *
			 * This function is the slot of the open button
			 */
			void open();

			/**
			 * @brief Function: void browse()
			 *
			 * This function is the slot of the browse button
			 */
			void browse();

			/**
			 * @brief Function: void cancel()
			 *
			 * This function is the slot of the cancel button
			 */
			void cancel();

		signals:
			/**
			 * @brief Function: void fileRead(const QString & title, const QString & content, const void * data)
			 *
			 * \param title: title of the widget
			 * \param content: content of the file read
			 * \param data: extra data to be passed through
			 *
			 * This function is a signal to inform the menu that the center window must be updated
			 */
			void fileRead(const QString & title, const QString & content, const void * data);


		private:
			/**
			 * @brief user typed text
			 *
			 */
			QLineEdit * text;

			/**
			 * @brief open button
			 *
			 */
			QPushButton * openButton;

			/**
			 * @brief browse button
			 *
			 */
			QPushButton * browseButton;

			/**
			 * @brief cancel button
			 *
			 */
			QPushButton * cancelButton;

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
			 * @brief Function: void connectSignals()
			 *
			 * This function connects signals and slots between main window elements
			 */
			void connectSignals();

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class OpenButtonWindow
			 *
			 */
			DISABLE_COPY_MOVE(OpenButtonWindow)

	};
}
/** @} */ // End of OpenButtonWindowGroup group

#endif // OPEN_BUTTON_WINDOW_H

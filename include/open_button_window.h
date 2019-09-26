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
#include <qt5/QtWidgets/QLabel>
#include <qt5/QtWidgets/QLineEdit>
#include <qt5/QtWidgets/QPushButton>

/** @defgroup OpenButtonWindowGroup Open Button Window Doxygen Group
 *  Open Button Window functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(openButtonWindowOverall)
Q_DECLARE_LOGGING_CATEGORY(openButtonWindowLayout)
Q_DECLARE_LOGGING_CATEGORY(openButtonWindowOpen)
Q_DECLARE_LOGGING_CATEGORY(openButtonWindowCancel)

namespace open_button_window {

	class OpenButtonWindow : public QDialog {

		Q_OBJECT

		public:

			explicit OpenButtonWindow(QWidget * parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());

		protected:

		private slots:
			void openSlot();
			void cancelSlot();

		private:
			QLabel * label;
			QLineEdit * text;
			QPushButton * openButton;
			QPushButton * cancelButton;

	};
}
/** @} */ // End of OpenButtonWindowGroup group

#endif // OPEN_BUTTON_WINDOW_H

#ifndef MAIN_WINDOW_STATUS_BAR_H
#define MAIN_WINDOW_STATUS_BAR_H
/**
 * @copyright
 * @file main_window_status_bar.h
 * @author Andrea Gianarda
 * @date 03rd of February 2020
 * @brief Main Window statusbar class header file
*/

#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtWidgets/QWidget>

#include "elided_label.h"
#include "progress_bar.h"

/** @defgroup MainWindowStatusBarGroup Main Window StatusBar Doxygen Group
 *  Main Window statusbar functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowStatusBarOverall)

namespace main_window_status_bar {

	namespace {
		/**
		 * @brief default origin of text in status bar widget
		 *
		 */
		const QPoint textOrigin(0,0);

		/**
		 * @brief bottom information text height
		 *
		 */
		const int textHeight = 20;

		/**
		 * @brief horizontal spacing between widgets
		 *
		 */
		const int horizontalWidgetSpacing = 0;

		/**
		 * @brief left margin between widget and window
		 *
		 */
		const int leftMargin = 0;

		/**
		 * @brief right margin between widget and window
		 *
		 */
		const int rightMargin = 0;

		/**
		 * @brief top margin between widget and window
		 *
		 */
		const int topMargin = 0;

		/**
		 * @brief bottom margin between widget and window
		 *
		 */
		const int bottomMargin = 0;
	}

	/**
	 * @brief MainWindowStatusBar class
	 *
	 */
	class MainWindowStatusBar : public QWidget {

		public:
			/**
			 * @brief Function: explicit MainWindowStatusBar(QWidget * parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags())
			 *
			 * \param parent: parent window
			 * \param flags: window flags
			 *
			 * Main window statusbar constructor
			 */
			explicit MainWindowStatusBar(QWidget * parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());

			/**
			 * @brief Function: ~MainWindowStatusBar()
			 *
			 * Main window statusbar destructor
			 */
			~MainWindowStatusBar();

			/**
			 * Function: elided_label::ElidedLabel * getUserInputText()
			 *
			 * \return the label containing the text typed by the user
			 *
			 * This function returns the label storing the text typed by the user
			 */
			elided_label::ElidedLabel * getUserInputText();

			/**
			 * Function: elided_label::ElidedLabel * getContentPathText()
			 *
			 * \return the label containing the path to the content (i.e. website URL or file path)
			 *
			 * This function returns the label storing the path to the content (i.e. website URL or file path)
			 */
			elided_label::ElidedLabel * getContentPathText();

			/**
			 * Function: elided_label::ElidedLabel * getInfoText()
			 *
			 * \return the label containing the text storing information about the webpage/browser
			 *
			 * This function returns the label storing information about the webpage/browser
			 */
			elided_label::ElidedLabel * getInfoText();

			/**
			 * Function: progress_bar::ProgressBar * getLoadBar()
			 *
			 * \return the bar storing the value of the progress in loading a page
			 *
			 * This function returns the bar storing the value of the progress in loading a page
			 */
			progress_bar::ProgressBar * getLoadBar();

		protected:

		private:

			// Labels placed at the bottom of the window
			/**
			 * @brief user input
			 *
			 */
			elided_label::ElidedLabel * userInputText;

			/**
			 * @brief content
			 *
			 */
			elided_label::ElidedLabel * contentPathText;

			/**
			 * @brief info
			 *
			 */
			elided_label::ElidedLabel * infoText;

			/**
			 * @brief load bar
			 *
			 */
			progress_bar::ProgressBar * loadBar;

			/**
			 * @brief Function: elided_label::ElidedLabel * newWindowLabel()
			 *
			 * \return configured label
			 *
			 * Configure window label
			 */
			elided_label::ElidedLabel * newWindowLabel();

			/**
			 * @brief Function: void fillStatusBar()
			 *
			 * This function fills the status bar
			 */
			void fillStatusBar();

			/**
			 * @brief Function: QSize minimumSizeHint()
			 *
			 * \return return minimum size of the widget
			 *
			 * Compute minimum size of the widget
			 */
			QSize minimumSizeHint();

	};

}

/** @} */ // End of MainWindowStatusBarGroup group

#endif // MAIN_WINDOW_STATUS_BAR_H

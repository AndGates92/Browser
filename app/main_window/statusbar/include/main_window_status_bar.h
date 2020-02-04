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
#include <qt5/QtWidgets/QLabel>

/** @defgroup MainWindowStatusBarGroup Main Window StatusBar Doxygen Group
 *  Main Window statusbar functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowStatusBarOverall)

namespace main_window_status_bar {

	namespace {
		/**
		 * @brief bottom information label height
		 *
		 */
		const int labelHeight = 20;

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
	 * @brief MainWindowWrapper class
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
			 * Function: QLabel * getUserInputText()
			 *
			 * \return the label containing the text typed by the user
			 *
			 * This function returns the label storing the text typed by the user
			 */
			QLabel * getUserInputText();

			/**
			 * Function: QLabel * getWebsiteText()
			 *
			 * \return the label containing the website URL
			 *
			 * This function returns the label storing the website URL
			 */
			QLabel * getWebsiteText();

			/**
			 * Function: QLabel * getInfoText()
			 *
			 * \return the label containing the text storing information about the webpage/browser
			 *
			 * This function returns the label storing information about the webpage/browser
			 */
			QLabel * getInfoText();

		protected:

		private:

			// Labels placed at the bottom of the window
			/**
			 * @brief user input
			 *
			 */
			QLabel * userInputText;

			/**
			 * @brief website
			 *
			 */
			QLabel * websiteText;

			/**
			 * @brief info
			 *
			 */
			QLabel * infoText;

			/**
			 * @brief Function: QLabel * newWindowLabel()
			 *
			 * \return configured label
			 *
			 * Configure window label
			 */
			QLabel * newWindowLabel();

			/**
			 * @brief Function: void fillStatusBar()
			 *
			 * This function fills the status bar
			 */
			void fillStatusBar();


	};

}

/** @} */ // End of MainWindowStatusBarGroup group

#endif // MAIN_WINDOW_STATUS_BAR_H

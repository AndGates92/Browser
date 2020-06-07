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
#include "constructor_macros.h"

/** @defgroup MainWindowStatusBarGroup Main Window StatusBar Doxygen Group
 *  Main Window statusbar functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowStatusBarOverall)

namespace main_window_status_bar {

	/**
	 * @brief MainWindowStatusBar class
	 *
	 */
	class MainWindowStatusBar final : public QWidget {

		Q_OBJECT

		public:
			/**
			 * @brief Function: explicit MainWindowStatusBar(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags())
			 *
			 * \param parent: parent window
			 * \param flags: window flags
			 *
			 * Main window statusbar constructor
			 */
			explicit MainWindowStatusBar(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags());

			/**
			 * @brief Function: virtual ~MainWindowStatusBar()
			 *
			 * Main window statusbar destructor
			 */
			virtual ~MainWindowStatusBar();

		public slots:
			/**
			 * Function: void setProgressValue(const int & value)
			 *
			 * \param value: value of the progress
			 *
			 * This function sets the text in the load bar from the integer value provided as argument
			 */
			void setProgressValue(const int & value);

			/**
			 * Function: void setVScroll(const int & vScroll)
			 *
			 * \param vScroll: vertical scroll percentage
			 *
			 * This function sets the text in the scroll label from the integer value provided as argument
			 */
			void setVScroll(const int & vScroll);

			/**
			 * Function: void setInfoText(const QString & text)
			 *
			 * \param text: text to set the label to
			 *
			 * This function sets the text in the info label
			 */
			void setInfoText(const QString & text);

			/**
			 * Function: void setUserInputText(const QString & text)
			 *
			 * \param text: text to set the label to
			 *
			 * This function sets the text in the user input label
			 */
			void setUserInputText(const QString & text);

			/**
			 * Function: void setContentPathText(const QString & text)
			 *
			 * \param text: text to set the label to
			 *
			 * This function sets the text in the content path label
			 */
			void setContentPathText(const QString & text);

		protected:

		private:

			// Labels placed at the bottom of the window
			/**
			 * @brief user input
			 *
			 */
			elided_label::ElidedLabel * const userInput;

			/**
			 * @brief content
			 *
			 */
			elided_label::ElidedLabel * const contentPath;

			/**
			 * @brief scroll position
			 *
			 */
			elided_label::ElidedLabel * const scroll;

			/**
			 * @brief info
			 *
			 */
			elided_label::ElidedLabel * const info;

			/**
			 * @brief load bar
			 *
			 */
			progress_bar::ProgressBar * const loadBar;

			/**
			 * @brief Function: elided_label::ElidedLabel * newWindowLabel()
			 *
			 * \return configured label
			 *
			 * Configure window label
			 */
			elided_label::ElidedLabel * newWindowLabel();

			/**
			 * @brief Function: progress_bar::ProgressBar * newProgressBar()
			 *
			 * \return configured progress bar
			 *
			 * Configure progress bar
			 */
			progress_bar::ProgressBar * newProgressBar();

			/**
			 * @brief Function: void fillStatusBar()
			 *
			 * This function fills the status bar
			 */
			void fillStatusBar();

			/**
			 * @brief Function: QSize minimumSizeHint() const override
			 *
			 * \return return minimum size of the widget
			 *
			 * Compute minimum size of the widget
			 */
			QSize minimumSizeHint() const override;

			/**
			 * Function: elided_label::ElidedLabel * getUserInput() const
			 *
			 * \return the label containing the text typed by the user
			 *
			 * This function returns the label storing the text typed by the user
			 */
			elided_label::ElidedLabel * getUserInput() const;

			/**
			 * Function: elided_label::ElidedLabel * getScroll() const
			 *
			 * \return the label containing the text storing information about the scroll position
			 *
			 * This function returns the label storing information about the scroll position
			 */
			elided_label::ElidedLabel * getScroll() const;

			/**
			 * Function: elided_label::ElidedLabel * getInfo() const
			 *
			 * \return the label containing the text storing information about the webpage/browser
			 *
			 * This function returns the label storing information about the webpage/browser
			 */
			elided_label::ElidedLabel * getInfo() const;

			/**
			 * Function: elided_label::ElidedLabel * getContentPath() const
			 *
			 * \return the label containing the path to the content (i.e. website URL or file path)
			 *
			 * This function returns the label storing the path to the content (i.e. website URL or file path)
			 */
			elided_label::ElidedLabel * getContentPath() const;

			/**
			 * Function: progress_bar::ProgressBar * getLoadBar() const
			 *
			 * \return the bar storing the value of the progress in loading a page
			 *
			 * This function returns the bar storing the value of the progress in loading a page
			 */
			progress_bar::ProgressBar * getLoadBar() const;

			/**
			 * Function: bool isValidScrollValue(const int & value) const
			 *
			 * \param value: value of scrolling
			 *
			 * \return a boolean to indicate whether the input value is valid
			 *
			 * This function returns whether the input value is valid
			 */
			bool isValidScrollValue(const int & value) const;

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class MainWindowStatusBar
			 *
			 */
			DISABLE_COPY_MOVE(MainWindowStatusBar)

	};

}

/** @} */ // End of MainWindowStatusBarGroup group

#endif // MAIN_WINDOW_STATUS_BAR_H

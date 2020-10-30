#ifndef MAIN_WINDOW_STATUS_BAR_H
#define MAIN_WINDOW_STATUS_BAR_H
/**
 * @copyright
 * @file main_window_status_bar.h
 * @author Andrea Gianarda
 * @date 03rd of February 2020
 * @brief Main Window statusbar class header file
*/

#include <memory>

// Qt libraries
#include <QtWidgets/QWidget>

#include "elided_label.h"
#include "progress_bar.h"
#include "constructor_macros.h"

/** @defgroup MainWindowStatusBarGroup Main Window StatusBar Doxygen Group
 *  Main Window statusbar functions and classes
 *  @{
 */

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

			/**
			 * Function: void showSearchResult(const bool & showWidget)
			 *
			 * \param showWidget: boolean indicating whether to show the search result or not
			 *
			 * This function shows or hides the search result label
			 */
			void showSearchResult(const bool & showWidget);

			/**
			 * Function: const QString getContentPathText() const
			 *
			 * \return text of the label
			 *
			 * This function returns the text in the search result label
			 */
			const QString getSearchResultText() const;

			/**
			 * Function: bool getLoadBarVisibility() const
			 *
			 * \returns the boolean value of the visibility attribute of the load bar
			 *
			 * This function returns the visibility attribute of the load bar as a boolean
			 */
			bool getLoadBarVisibility() const;

			/**
			 * Function: int getProgressValue() const
			 *
			 * \returns the value of the progress
			 *
			 * This function returns the value of the progress bar
			 */
			int getProgressValue() const;

			/**
			 * Function: int getVScroll() const
			 *
			 * \returns the vertical scroll percentage
			 *
			 * This function returns the vertical scroll percentage
			 */
			int getVScroll() const;

			/**
			 * Function: const QString getInfoText() const
			 *
			 * \return text of the label
			 *
			 * This function returns the text in the info label
			 */
			const QString getInfoText() const;

			/**
			 * Function: const QString getUserInputText() const
			 *
			 * \return text of the label
			 *
			 * This function returns the text in the user input label
			 */
			const QString getUserInputText() const;

			/**
			 * Function: const QString getContentPathText() const
			 *
			 * \return text of the label
			 *
			 * This function returns the text in the content path label
			 */
			const QString getContentPathText() const;

			/**
			 * Function: void setContentPathText(const QString & text)
			 *
			 * \param text: text to set the label to
			 *
			 * This function sets the text in the search result label
			 */
			void setSearchResultText(const QString & text);

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
			std::unique_ptr<elided_label::ElidedLabel> userInput;

			/**
			 * @brief content
			 *
			 */
			std::unique_ptr<elided_label::ElidedLabel> contentPath;

			/**
			 * @brief scroll position
			 *
			 */
			std::unique_ptr<elided_label::ElidedLabel> scroll;

			/**
			 * @brief info
			 *
			 */
			std::unique_ptr<elided_label::ElidedLabel> info;

			/**
			 * @brief search result
			 *
			 */
			std::unique_ptr<elided_label::ElidedLabel> searchResult;

			/**
			 * @brief load bar
			 *
			 */
			std::unique_ptr<progress_bar::ProgressBar> loadBar;

			/**
			 * @brief Function: std::unique_ptr<elided_label::ElidedLabel> newWindowLabel()
			 *
			 * \return configured label
			 *
			 * Configure window label
			 */
			std::unique_ptr<elided_label::ElidedLabel> newWindowLabel();

			/**
			 * @brief Function: std::unique_ptr<progress_bar::ProgressBar> newProgressBar()
			 *
			 * \return configured progress bar
			 *
			 * Configure progress bar
			 */
			std::unique_ptr<progress_bar::ProgressBar> newProgressBar();

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

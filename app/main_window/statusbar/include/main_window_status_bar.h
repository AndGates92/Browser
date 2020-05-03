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
		constexpr int textHeight = 20;

		/**
		 * @brief horizontal spacing between widgets
		 *
		 */
		constexpr int horizontalWidgetSpacing = 0;

		/**
		 * @brief left margin between widget and window
		 *
		 */
		constexpr int leftMargin = 0;

		/**
		 * @brief right margin between widget and window
		 *
		 */
		constexpr int rightMargin = 0;

		/**
		 * @brief top margin between widget and window
		 *
		 */
		constexpr int topMargin = 0;

		/**
		 * @brief bottom margin between widget and window
		 *
		 */
		constexpr int bottomMargin = 0;
	}

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
			 * @brief Function: ~MainWindowStatusBar()
			 *
			 * Main window statusbar destructor
			 */
			~MainWindowStatusBar();

			/**
			 * Function: elided_label::ElidedLabel * getUserInputText() const
			 *
			 * \return the label containing the text typed by the user
			 *
			 * This function returns the label storing the text typed by the user
			 */
			elided_label::ElidedLabel * getUserInputText() const;

			/**
			 * Function: elided_label::ElidedLabel * getContentPathText() const
			 *
			 * \return the label containing the path to the content (i.e. website URL or file path)
			 *
			 * This function returns the label storing the path to the content (i.e. website URL or file path)
			 */
			elided_label::ElidedLabel * getContentPathText() const;

			/**
			 * Function: elided_label::ElidedLabel * getInfoText() const
			 *
			 * \return the label containing the text storing information about the webpage/browser
			 *
			 * This function returns the label storing information about the webpage/browser
			 */
			elided_label::ElidedLabel * getInfoText() const;

			/**
			 * Function: progress_bar::ProgressBar * getLoadBar() const
			 *
			 * \return the bar storing the value of the progress in loading a page
			 *
			 * This function returns the bar storing the value of the progress in loading a page
			 */
			progress_bar::ProgressBar * getLoadBar() const;

			/**
			 * Function: void setContentPathText(const QString & base)
			 *
			 * \param base: base string to use to fill the content path
			 *
			 * This function sets the text in the content path from a string provided as input
			 */
			void setContentPathText(const QString & source);

		protected:

		private:

			// Labels placed at the bottom of the window
			/**
			 * @brief user input
			 *
			 */
			elided_label::ElidedLabel * const userInputText;

			/**
			 * @brief content
			 *
			 */
			elided_label::ElidedLabel * const contentPathText;

			/**
			 * @brief info
			 *
			 */
			elided_label::ElidedLabel * const infoText;

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

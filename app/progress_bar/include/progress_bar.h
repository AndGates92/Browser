#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H
/**
 * @copyright
 * @file progress_bar.h
 * @author Andrea Gianarda
 * @date 04th of March 2020
 * @brief Progress bar class header file
*/

#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtWidgets/QProgressBar>

/** @defgroup ProgressBarGroup Progress Bar Doxygen Group
 *  Progress bar functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(progressBarOverall)

namespace progress_bar {

	namespace {
		/**
		 * @brief default progres bar alignment
		 *
		 */
		constexpr Qt::Alignment progressAlignment = (Qt::AlignHCenter | Qt::AlignVCenter);

		/**
		 * @brief default direction of the text
		 *
		 */
		constexpr QProgressBar::Direction progressTextDirection = QProgressBar::TopToBottom;

		/**
		 * @brief default visible text flag
		 *
		 */
		constexpr bool progressTextVisible = true;

		/**
		 * @brief default format of the text
		 *
		 */
		const QString barTextFormat("%p%");

		/**
		 * @brief default inverted progress flag
		 *
		 */
		constexpr bool invertedProgress = false;
	}

	/**
	 * @brief ProgressBar class
	 *
	 */
	class ProgressBar : public QProgressBar {

		Q_OBJECT

		public:
			/**
			 * @brief Function: explicit ProgressBar(QWidget * parent = Q_NULLPTR)
			 *
			 * \param parent: parent window
			 *
			 * Progress bar constructor
			 */
			explicit ProgressBar(QWidget * parent = Q_NULLPTR);

			/**
			 * @brief Function: ~ProgressBar()
			 *
			 * Progress bar destructor
			 */
			~ProgressBar();

		public slots:
			/**
			 * @brief Function: void startLoading()
			 *
			 * This function executes actions to perform at the start of a loading operation
			 */
			void startLoading();

			/**
			 * @brief Function: void setValue(int value)
			 *
			 * \param value: value to set the bar to
			 *
			 * This function executes actions to set teh progress bar to the desired value
			 */
			void setValue(int value);

			/**
			 * @brief Function: void endLoading(bool success)
			 *
			 * \param success: loading success flag
			 *
			 * This function executes actions to perform at the end of a loading operation
			 */
			void endLoading(bool success);

		protected:

		private:

			/**
			 * @brief Function: QSize minimumSizeHint()
			 *
			 * \return return minimum size of the widget
			 *
			 * Compute minimum size of the widget
			 */
			QSize minimumSizeHint();

			/**
			 * @brief Function: QSize sizeHint()
			 *
			 * \return return recommended size of the widget
			 *
			 * Compute recommendend size of the widget
			 */
			QSize sizeHint();

			// Move and copy constructor
			/**
			 * @brief Function: ProgressBar(const progress_bar::ProgressBar & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Command Menu copy constructor
			 */
			explicit ProgressBar(const progress_bar::ProgressBar & rhs) = delete;

			/**
			 * @brief Function: ProgressBar(progress_bar::ProgressBar && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Command Menu move constructor
			 */
			explicit ProgressBar(progress_bar::ProgressBar && rhs) = delete;

			// Move and copy assignment operators
			/**
			 * @brief Function: ProgressBar & operator=(const progress_bar::ProgressBar & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Command Menu copy assignment operator
			 */
			ProgressBar & operator=(const progress_bar::ProgressBar & rhs) = delete;

			/**
			 * @brief Function: ProgressBar & operator=(progress_bar::ProgressBar && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Command Menu move assignment operator
			 */
			ProgressBar & operator=(progress_bar::ProgressBar && rhs) = delete;

	};

}

/** @} */ // End of ProgressBarGroup group

#endif // PROGRESS_BAR_H

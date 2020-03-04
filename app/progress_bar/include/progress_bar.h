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
		const Qt::Alignment progressAlignment = (Qt::AlignHCenter | Qt::AlignVCenter);

		/**
		 * @brief default direction of the text
		 *
		 */
		const QProgressBar::Direction progressTextDirection = QProgressBar::TopToBottom;

		/**
		 * @brief default visible text flag
		 *
		 */
		const bool progressTextVisible = true;

		/**
		 * @brief default format of the text
		 *
		 */
		const QString barTextFormat("%p%");

		/**
		 * @brief default inverted progress flag
		 *
		 */
		const bool invertedProgress = false;
	}

	/**
	 * @brief ProgressBar class
	 *
	 */
	class ProgressBar : public QProgressBar {
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

		protected:

		private:

	};

}

/** @} */ // End of ProgressBarGroup group

#endif // PROGRESS_BAR_H

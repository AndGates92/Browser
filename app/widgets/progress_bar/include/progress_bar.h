#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H
/**
 * @copyright
 * @file progress_bar.h
 * @author Andrea Gianarda
 * @date 04th of March 2020
 * @brief Progress bar class header file
*/

// Qt libraries
#include <QtWidgets/QProgressBar>

#include "common/include/constructor_macros.h"

/** @defgroup ProgressBarGroup Progress Bar Doxygen Group
 *  Progress bar functions and classes
 *  @{
 */

namespace progress_bar {

	/**
	 * @brief ProgressBar class
	 *
	 */
	class ProgressBar final : public QProgressBar {

		Q_OBJECT

		public:
			/**
			 * @brief Function: explicit ProgressBar(QWidget * parent)
			 *
			 * \param parent: parent window
			 *
			 * Progress bar constructor
			 */
			explicit ProgressBar(QWidget * parent);

			/**
			 * @brief Function: virtual ~ProgressBar()
			 *
			 * Progress bar destructor
			 */
			virtual ~ProgressBar();

			/**
			 * @brief Function: static int getMinimumValue()
			 *
			 * \return the minimum value of the progress bar
			 *
			 * this function returns the minimum value of the progress bar
			 */
			static int getMinimumValue();

			/**
			 * @brief Function: static int getMaximumValue()
			 *
			 * \return the maximum value of the progress bar
			 *
			 * this function returns the maximum value of the progress bar
			 */
			static int getMaximumValue();

		public slots:
			/**
			 * @brief Function: void startLoading()
			 *
			 * This function executes actions to perform at the start of a loading operation
			 */
			void startLoading();

			/**
			 * @brief Function: void setValue(const int & value)
			 *
			 * \param value: value to set the bar to
			 *
			 * This function executes actions to set teh progress bar to the desired value
			 */
			void setValue(const int & value);

			/**
			 * @brief Function: void endLoading(const bool & success)
			 *
			 * \param success: loading success flag
			 *
			 * This function executes actions to perform at the end of a loading operation
			 */
			void endLoading(const bool & success);

		protected:

		private:

			/**
			 * @brief Function: void setMinimum(const int value)
			 *
			 * \param value: minimum value of the progress bar
			 *
			 * This function sets the minimum value of the progress bar
			 */
			void setMinimum(const int value);

			/**
			 * @brief Function: void setMaximum(const int value)
			 *
			 * \param value: maximum value of the progress bar
			 *
			 * This function sets the maximum value of the progress bar
			 */
			void setMaximum(const int value);

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

			/**
			 * @brief Disable move and copy constructors and operator= overloading for class ProgressBar
			 *
			 */
			DISABLE_COPY_MOVE(ProgressBar)

	};

}

/** @} */ // End of ProgressBarGroup group

#endif // PROGRESS_BAR_H

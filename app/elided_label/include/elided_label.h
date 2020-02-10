#ifndef ELIDED_LABEL_H
#define ELIDED_LABEL_H
/**
 * @copyright
 * @file elided_label.h
 * @author Andrea Gianarda
 * @date 04th of February 2020
 * @brief Elided label class header file
*/

#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtCore/QPoint>
#include <qt5/QtGui/QResizeEvent>
#include <qt5/QtWidgets/QWidget>
#include <qt5/QtWidgets/QLabel>

/** @defgroup ElidedLabelGroup Elided Label Doxygen Group
 *  Elided label functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(elidedLabelOverall)
Q_DECLARE_LOGGING_CATEGORY(elidedLabelElision)
Q_DECLARE_LOGGING_CATEGORY(elidedLabelPaint)

namespace elided_label {

	namespace {
		/**
		 * @brief Default x coordinate of QLabel retangle origincommand menu title
		 *
		 */
		const int labelOriginX = 0;

		/**
		 * @brief Default y coordinate of QLabel retangle origincommand menu title
		 *
		 */
		const int labelOriginY = 0;

	}

	/**
	 * @brief Label class
	 *
	 */
	class ElidedLabel : public QLabel {

		public:
			/**
			 * @brief Function: explicit ElidedLabel(QString textLabel = QString::null, QPoint labelOrigin = QPoint(elided_label::labelOriginX,elided_label::labelOriginY), QWidget * parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags(), Qt::TextElideMode textElisionMode = Qt::ElideNone)
			 *
			 * \param textLabel: text to write into QLabel
			 * \param labelOrigin: origin of the rectangle the label is drawn into
			 * \param parent: parent window
			 * \param flags: window flags
			 * \param textElisionMode: elision mode
			 *
			 * Elided label constructor
			 */
			explicit ElidedLabel(QString textLabel = QString::null, QPoint labelOrigin = QPoint(elided_label::labelOriginX,elided_label::labelOriginY), QWidget * parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags(), Qt::TextElideMode textElisionMode = Qt::ElideNone);

			/**
			 * @brief Function: ~ElidedLabel()
			 *
			 * Elided label destructor
			 */
			~ElidedLabel();

			/**
			 * @brief Function: void setText(const QString & text)
			 *
			 * \param text: text to write into QLabel
			 *
			 * Overload setText of base QLabel to account for elision
			 */
			void setText(const QString & text);

		protected:


		private:

			/**
			 * @brief elision mode
			 *
			 */
			Qt::TextElideMode elisionMode;

			/**
			 * @brief elided text
			 *
			 */
			QString elisionText;

			/**
			 * @brief origin of the rectangle
			 *
			 */
			QPoint origin;

			/**
			 * @brief Function: void updateElidedText(int width)
			 *
			 * \param width: width of the elided text
			 *
			 * This function sets elided text variable
			 * text label will be QString::null if elision is not enabled
			 */
			void updateElidedText(int width);

			/**
			 * @brief Function: void paintEvent(QPaintEvent * event)
			 *
			 * \param event: paint event
			 *
			 * This function paints the text of the QLabel as elided text if elide mode is different from None
			 */
			void paintEvent(QPaintEvent * event);

			/**
			 * @brief Function: void resizeEvent(QResizeEvent * event)
			 *
			 * \param event: resize event
			 *
			 * This function is called when the widget is resized
			 * In such a scenario, the elided text must be updated
			 */
			void resizeEvent(QResizeEvent * event);

	};

}

/** @} */ // End of ElidedLabelGroup group

#endif // ELIDED_LABEL_H

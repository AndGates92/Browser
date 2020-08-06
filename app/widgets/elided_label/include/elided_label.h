#ifndef ELIDED_LABEL_H
#define ELIDED_LABEL_H
/**
 * @copyright
 * @file elided_label.h
 * @author Andrea Gianarda
 * @date 04th of February 2020
 * @brief Elided label class header file
*/

#include <QtCore/QLoggingCategory>
#include <QtCore/QPoint>
#include <QtGui/QResizeEvent>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>

#include "constructor_macros.h"

/** @defgroup ElidedLabelGroup Elided Label Doxygen Group
 *  Elided label functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(elidedLabelOverall)
Q_DECLARE_LOGGING_CATEGORY(elidedLabelElision)
Q_DECLARE_LOGGING_CATEGORY(elidedLabelPaint)

namespace elided_label {

	// TODO: Try to move to the cpp file
	namespace {
		/**
		 * @brief Default x coordinate of QLabel retangle origincommand menu title
		 *
		 */
		static constexpr int labelOriginX = 0;

		/**
		 * @brief Default y coordinate of QLabel retangle origincommand menu title
		 *
		 */
		static constexpr int labelOriginY = 0;

	}

	/**
	 * @brief Label class
	 *
	 */
	class ElidedLabel final : public QLabel {

		Q_OBJECT

		public:
			/**
			 * @brief Function: explicit ElidedLabel(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags(), QString textLabel = QString(), QPoint labelOrigin = QPoint(elided_label::labelOriginX,elided_label::labelOriginY), Qt::TextElideMode textElisionMode = Qt::ElideNone)
			 *
			 * \param textLabel: text to write into QLabel
			 * \param labelOrigin: origin of the rectangle the label is drawn into
			 * \param parent: parent window
			 * \param flags: window flags
			 * \param textElisionMode: elision mode
			 *
			 * Elided label constructor
			 */
			explicit ElidedLabel(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags(), QString textLabel = QString(), QPoint labelOrigin = QPoint(elided_label::labelOriginX,elided_label::labelOriginY), Qt::TextElideMode textElisionMode = Qt::ElideNone);

			/**
			 * @brief Function: virtual ~ElidedLabel()
			 *
			 * Elided label destructor
			 */
			virtual ~ElidedLabel();

			/**
			 * @brief Function: Qt::TextElideMode getElisionMode() const
			 *
			 * \return elision mode
			 *
			 * This functions returns the elision mode of a label
			 */
			Qt::TextElideMode getElisionMode() const;

			/**
			 * @brief Function: const QPoint getOrigin() const
			 *
			 * \param value: new origin
			 *
			 * This functions returns the origin of the label
			 */
			const QPoint getOrigin() const;

			/**
			 * @brief Function: void setElisionMode(const Qt::TextElideMode & value)
			 *
			 * \param value: new elision mode
			 *
			 * This functions sets the elision mode of a label
			 */
			void setElisionMode(const Qt::TextElideMode & value);

			/**
			 * @brief Function: void setOrigin(const QPoint & value)
			 *
			 * \param value: new origin
			 *
			 * This functions sets the origin of the label
			 */
			void setOrigin(const QPoint & value);

		public slots:
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
			 * @brief Function: void updateElidedText(const int & width)
			 *
			 * \param width: width of the elided text
			 *
			 * This function sets elided text variable
			 * text label will be QString() if elision is not enabled
			 */
			void updateElidedText(const int & width);

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

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class ElidedLabel
			 *
			 */
			DISABLE_COPY_MOVE(ElidedLabel)
	};

}

/** @} */ // End of ElidedLabelGroup group

#endif // ELIDED_LABEL_H

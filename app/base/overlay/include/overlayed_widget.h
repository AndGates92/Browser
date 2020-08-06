#ifndef OVERLAYED_WIDGET_H
#define OVERLAYED_WIDGET_H
/**
 * @copyright
 * @file overlayed_widget.h
 * @author Andrea Gianarda
 * @date 19th of June 2020
 * @brief Overlayed widget class header file
*/

#include <memory>

#include <QtCore/QLoggingCategory>
#include <QtWidgets/QWidget>

#include "constructor_macros.h"

/** @defgroup OverlayedWidgetGroup Main Window Popup Base Doxygen Group
 *  Overlayed widget functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(overlayedWidgetOverall)

namespace overlayed_widget {

	/**
	 * @brief OverlayedWidget class
	 *
	 */
	class OverlayedWidget : public QWidget, public std::enable_shared_from_this<overlayed_widget::OverlayedWidget> {

		Q_OBJECT

		public:
			/**
			 * @brief Function: explicit OverlayedWidget(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags())
			 *
			 * \param parent: parent window
			 * \param flags: window flags
			 *
			 * Overlayed widget constructor
			 */
			explicit OverlayedWidget(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags());

			/**
			 * @brief Function: virtual ~OverlayedWidget()
			 *
			 * Overlayed widget destructor
			 */
			virtual ~OverlayedWidget();

			/**
			 * @brief Function: virtual bool isCentered() const
			 *
			 * \return boolean whether the widget has to be centered or not
			 *
			 * This function returns whether the widget has to be centered or not
			 */
			virtual bool isCentered() const = 0;

			/**
			 * @brief Function: virtual int getPadding() const
			 *
			 * \return padding of this widget
			 *
			 * This function returns the padding to be applied for this widget
			 */
			virtual int getPadding() const = 0;

			/**
			 * @brief Function: void paintEvent(QPaintEvent * event)
			 *
			 * \param event: paint event to treat
			 *
			 * This function handles paint events
			 * It is required as this is a custom widget that uses stylesheet in its derived classes
			 */
			void paintEvent(QPaintEvent * event);

			/**
			 * @brief Function: void setGeometry(const QRect & rect)
			 *
			 * \param rect: geometry of the widget
			 *
			 * This function set the geometry for this widget and its children
			 */
			void setGeometry(const QRect & rect);

		signals:

			/**
			 * @brief Function: void updateGeometryRequest(std::shared_ptr<overlayed_widget::OverlayedWidget> widget)
			 *
			 * \param widget: widget that is requesting to update its geometry
			 *
			 * This function is a signal to trigger an update of the widget geometry
			 */
			void updateGeometryRequest(std::shared_ptr<overlayed_widget::OverlayedWidget> widget);

		protected:

		private:

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class OverlayedWidget
			 *
			 */
			DISABLE_COPY_MOVE(OverlayedWidget)

	};

}

/** @} */ // End of OverlayedWidgetGroup group

#endif // OVERLAYED_WIDGET_H

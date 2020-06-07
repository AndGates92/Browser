/**
 * @copyright
 * @file main_window_popup_container.cpp
 * @author Andrea Gianarda
 * @date 07th of June 2020
 * @brief Main Window popoup container functions
*/

// Qt libraries
#include <qt5/QtCore/QtGlobal>
#include <qt5/QtGui/QResizeEvent>

#include "main_window_popup_container.h"
#include "exception_macros.h"
#include "logging_macros.h"
#include "global_types.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowPopupContainerOverall, "mainWindowPopupContainer.overall", MSG_TYPE_LEVEL)

namespace main_window_popup_container {

	/**
	 * @brief postprocessing action after state change
	 *
	 */
	typedef enum class popup_widget_list {
		OPEN_FILE        /**< Open file popup */
	} popup_widget_e;

	/**
	 * @brief Overload operators to ease print of the state of the main window controller
	 *
	 */
	OVERLOAD_OPERATORS_CUSTOM_TYPE_FUNCTION_PROTOTYPE(popup_widget_list, main_window_popup_container::popup_widget_e)

	OVERLOAD_OPERATORS_CUSTOM_TYPE(main_window_popup_container::popup_widget_e)

}

main_window_popup_container::MainWindowPopupContainer::MainWindowPopupContainer(QWidget * parent, Qt::WindowFlags flags) : popup_container::PopupContainer(parent, flags) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowPopupContainerOverall,  "Main window popup container constructor");

	this->addOpenPopup();

	this->connectSignals();

	this->setObjectName("MainWindowPopupContainer");

	this->setStyleSheet(
		"QWidget#MainWindowPopupContainer {"
			"border-top-left-radius: 10px;"
			"border-top-right-radius: 10px;"
		"}"
		// It applies to this widget as well as its children
		"QWidget {"
			"background-color: gray;"
		"}"
	);
}

main_window_popup_container::MainWindowPopupContainer::~MainWindowPopupContainer() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowPopupContainerOverall,  "Main window popup container destructor");
}

bool main_window_popup_container::MainWindowPopupContainer::showOpenFilePopup() {
	const unsigned int idx = (unsigned int)main_window_popup_container::popup_widget_e::OPEN_FILE;
	bool success = this->chooseWidgetToShow(idx);

	this->getOpenFilePopup()->activatePopup();

	return success;
}

open_popup::OpenPopup * main_window_popup_container::MainWindowPopupContainer::getOpenFilePopup() const {
	main_window_popup_container::popup_widget_e index = main_window_popup_container::popup_widget_e::OPEN_FILE;
	popup_properties::PopupProperties * widget = this->getWidget((unsigned int)index);
	QEXCEPTION_ACTION_COND((widget == nullptr), throw, "Unable to find widget " << index);
	open_popup::OpenPopup * popup = nullptr;

	if (widget != Q_NULLPTR) {
		try {
			popup = dynamic_cast<open_popup::OpenPopup *>(widget);
		} catch (const std::bad_cast & badCastE) {
			QEXCEPTION_ACTION(throw, badCastE.what());
		}
	}

	return popup;
}

void main_window_popup_container::MainWindowPopupContainer::connectSignals() {
	connect(this->getOpenFilePopup(), &open_popup::OpenPopup::sizeChanged,  [this] () {
		emit this->updateGeometryRequest(this);
	});
}

void main_window_popup_container::MainWindowPopupContainer::addOpenPopup() {
	open_popup::OpenPopup * popup = new open_popup::OpenPopup(this);
	this->addWidget((unsigned int)main_window_popup_container::popup_widget_e::OPEN_FILE, popup);
}

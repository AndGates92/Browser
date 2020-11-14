/**
 * @copyright
 * @file main_window_popup_container.cpp
 * @author Andrea Gianarda
 * @date 07th of June 2020
 * @brief Main Window popoup container functions
*/

// Qt libraries
#include <QtGui/QResizeEvent>

#include "windows/main_window/popup/include/main_window_popup_container.h"
#include "common/include/exception_macros.h"
#include "utility/logger/include/macros.h"
#include "common/include/global_enums.h"

// Categories
LOGGING_CONTEXT(mainWindowPopupContainerOverall, mainWindowPopupContainer.overall, TYPE_LEVEL, INFO_VERBOSITY)

namespace main_window_popup_container {

	/**
	 * @brief postprocessing action after state change
	 *
	 */
	typedef enum class popup_widget_list {
		OPEN_FILE,       /**< Open file popup */
		WARNING          /**< Warning popup */
	} popup_widget_e;

	/**
	 * @brief Overload operators to ease print of the state of the main window controller
	 *
	 */
	OVERLOAD_OPERATORS_CUSTOM_TYPE_FUNCTION_PROTOTYPE(popup_widget_list, main_window_popup_container::popup_widget_e)

	OVERLOAD_OPERATORS_CUSTOM_TYPE(main_window_popup_container::popup_widget_e)

}

main_window_popup_container::MainWindowPopupContainer::MainWindowPopupContainer(QWidget * parent, Qt::WindowFlags flags) : popup_container::PopupContainer(parent, flags) {

	LOG_INFO(logger::info_level_e::ZERO, mainWindowPopupContainerOverall,  "Main window popup container constructor");

	this->addOpenPopup();
	this->addWarningPopup();

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
	LOG_INFO(logger::info_level_e::ZERO, mainWindowPopupContainerOverall,  "Main window popup container destructor");
}

bool main_window_popup_container::MainWindowPopupContainer::showWarningPopup() {
	const main_window_popup_container::popup_widget_e index = main_window_popup_container::popup_widget_e::WARNING;
	return this->showPopup<label_popup::LabelPopup>((unsigned int)index);
}

bool main_window_popup_container::MainWindowPopupContainer::showOpenFilePopup() {
	const main_window_popup_container::popup_widget_e index = main_window_popup_container::popup_widget_e::OPEN_FILE;
	return this->showPopup<open_popup::OpenPopup>((unsigned int)index);
}

std::shared_ptr<label_popup::LabelPopup> main_window_popup_container::MainWindowPopupContainer::getWarningPopup() const {
	const main_window_popup_container::popup_widget_e index = main_window_popup_container::popup_widget_e::WARNING;
	return this->getPopup<label_popup::LabelPopup>((unsigned int)index);
}

std::shared_ptr<open_popup::OpenPopup> main_window_popup_container::MainWindowPopupContainer::getOpenFilePopup() const {
	const main_window_popup_container::popup_widget_e index = main_window_popup_container::popup_widget_e::OPEN_FILE;
	return this->getPopup<open_popup::OpenPopup>((unsigned int)index);
}

void main_window_popup_container::MainWindowPopupContainer::connectSignals() {
	connect(this->getOpenFilePopup().get(), &open_popup::OpenPopup::sizeChanged,  [this] () {
		emit this->updateGeometryRequest(this->shared_from_this());
	});
}

void main_window_popup_container::MainWindowPopupContainer::addOpenPopup() {
	std::shared_ptr<open_popup::OpenPopup> popup = std::make_shared<open_popup::OpenPopup>(this);
	this->addWidget((unsigned int)main_window_popup_container::popup_widget_e::OPEN_FILE, popup);
}

void main_window_popup_container::MainWindowPopupContainer::addWarningPopup() {
	std::shared_ptr<label_popup::LabelPopup> popup = std::make_shared<label_popup::LabelPopup>(this);
	popup->setStyleSheet(
		"QLabel {"
			"color: orange;"
		"}"
	);
	this->addWidget((unsigned int)main_window_popup_container::popup_widget_e::WARNING, popup);
}

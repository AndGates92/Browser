/**
 * @copyright
 * @file popup_container.cpp
 * @author Andrea Gianarda
 * @date 07th of June 2020
 * @brief Main Window popoup container functions
*/

// Qt libraries
#include <QtGui/QResizeEvent>

#include "app/shared/exception.h"
#include "app/utility/logger/macros.h"
#include "app/shared/enums.h"
#include "app/windows/main_window/popup/open_popup.h"
#include "app/windows/main_window/popup/label_popup.h"
#include "app/windows/main_window/popup/popup_container.h"

// Categories
LOGGING_CONTEXT(mainWindowPopupContainerOverall, mainWindowPopupContainer.overall, TYPE_LEVEL, INFO_VERBOSITY)

namespace app {

	namespace main_window {

		namespace popup {

//			Q_NAMESPACE

			/**
			 * @brief postprocessing action after state change
			 *
			 */
//			typedef enum class widget_list {
//				OPEN_FILE,       /**< Open file popup */
//				WARNING          /**< Warning popup */
//			} widget_e;

			/**
			 * @brief Overload operators to ease print of the state of the main window controller
			 *
			 */
//			OVERLOAD_OPERATORS_CUSTOM_TYPE_FUNCTION_PROTOTYPE(widget_list, app::main_window::popup::widget_e)

			OVERLOAD_OPERATORS_CUSTOM_TYPE(app::main_window::popup::widget_e)

		}

	}

}

app::main_window::popup::PopupContainer::PopupContainer(QWidget * parent, Qt::WindowFlags flags) : app::base::popup::PopupContainer(parent, flags) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowPopupContainerOverall,  "Main window popup container constructor");

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

app::main_window::popup::PopupContainer::~PopupContainer() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowPopupContainerOverall,  "Main window popup container destructor");
}

bool app::main_window::popup::PopupContainer::showWarningPopup() {
	const app::main_window::popup::widget_e index = app::main_window::popup::widget_e::WARNING;
	return this->showPopup<app::main_window::popup::LabelPopup>((unsigned int)index);
}

bool app::main_window::popup::PopupContainer::showOpenFilePopup() {
	const app::main_window::popup::widget_e index = app::main_window::popup::widget_e::OPEN_FILE;
	return this->showPopup<app::main_window::popup::OpenPopup>((unsigned int)index);
}

std::shared_ptr<app::main_window::popup::LabelPopup> app::main_window::popup::PopupContainer::getWarningPopup() const {
	const app::main_window::popup::widget_e index = app::main_window::popup::widget_e::WARNING;
	return this->getPopup<app::main_window::popup::LabelPopup>((unsigned int)index);
}

std::shared_ptr<app::main_window::popup::OpenPopup> app::main_window::popup::PopupContainer::getOpenFilePopup() const {
	const app::main_window::popup::widget_e index = app::main_window::popup::widget_e::OPEN_FILE;
	return this->getPopup<app::main_window::popup::OpenPopup>((unsigned int)index);
}

void app::main_window::popup::PopupContainer::connectSignals() {
	connect(this->getOpenFilePopup().get(), &app::main_window::popup::OpenPopup::sizeChanged,  [this] () {
		emit this->updateGeometryRequest(this->shared_from_this());
	});
}

void app::main_window::popup::PopupContainer::addOpenPopup() {
	std::shared_ptr<app::main_window::popup::OpenPopup> popup = std::make_shared<app::main_window::popup::OpenPopup>(this);
	this->addWidget((unsigned int)app::main_window::popup::widget_e::OPEN_FILE, popup);
}

void app::main_window::popup::PopupContainer::addWarningPopup() {
	std::shared_ptr<app::main_window::popup::LabelPopup> popup = std::make_shared<app::main_window::popup::LabelPopup>(this);
	popup->setStyleSheet(
		"QLabel {"
			"color: orange;"
		"}"
	);
	this->addWidget((unsigned int)app::main_window::popup::widget_e::WARNING, popup);
}

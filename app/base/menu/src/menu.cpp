/**
 * @copyright
 * @file menu.cpp
 * @author Andrea Gianarda
 * @date 23th September 2019
 * @brief Top Menu functions
 */

#include "macros.h"
#include "global_enums.h"
#include "cpp_operator.h"

#include "menu.h"

// Categories
LOGGING_CONTEXT(menuOverall, menu.overall, TYPE_LEVEL, INFO_VERBOSITY)

menu::Menu::Menu(QWidget * parent, std::weak_ptr<QMenuBar> menuBar, const char* menuName, const key_sequence::KeySequence & key) : QWidget(parent), printable_object::PrintableObject(), menuBar(menuBar), menuName(menuName), key(key) {

	LOG_INFO(logger::info_level_e::ZERO, menuOverall, "Create menu:  " << *this);
	this->createMenu();
	this->createShortcuts();
}

menu::Menu::~Menu() {
	LOG_INFO(logger::info_level_e::ZERO, menuOverall,  "menu destructor");
}

void menu::Menu::createMenu() {
	EXCEPTION_ACTION_COND((this->menuBar.expired() == true), throw,  "Unable to get menu bar for menu " << menuName << " as it has already expired");
	std::shared_ptr<QMenuBar> bar = this->menuBar.lock();
	if (bar != Q_NULLPTR) {
		this->winMenu.reset(bar->addMenu(QWidget::tr(menuName)));
	}
}

void menu::Menu::createShortcuts() {
	this->expandMenu.reset(new QShortcut(this));

	// Do not bind key if it is not set
	if (this->key != key_sequence::KeySequence(QKeySequence::UnknownKey)) {
		this->expandMenu->setKey(this->key.toQKeySequence());
		connect(this->expandMenu.get(), &QShortcut::activated, this, &menu::Menu::expand);
	}
}

void menu::Menu::expand() {
	EXCEPTION_ACTION_COND((this->menuBar.expired() == true), throw,  "Unable to get menu bar for menu " << this->menuName << " as it has already expired");
	std::shared_ptr<QMenuBar> bar = this->menuBar.lock();
	if (bar != Q_NULLPTR) {
		// menu is expanded only if menu bar is visible
		if (bar->isVisible()) {
			LOG_INFO(logger::info_level_e::ZERO, menuOverall, "Expand menu " << this->menuName << " because shortcut key " << this->key.toString() << " has been pressed");
			this->winMenu->exec();
			this->setFocus();
		}
	}
}

void menu::Menu::setEnabledProperty(const bool & enabled) {
	this->expandMenu->setEnabled(enabled);
}

const std::string menu::Menu::print() const {
	std::string menuInfo;

	menuInfo = menuInfo + " name: " + this->menuName;
	menuInfo = menuInfo + " shortcut key: " + this->key.toString().toStdString();

	return menuInfo;
}

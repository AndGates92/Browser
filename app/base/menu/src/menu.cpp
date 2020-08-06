/**
 * @copyright
 * @file menu.cpp
 * @author Andrea Gianarda
 * @date 23th September 2019
 * @brief Top Menu functions
 */

// Qt libraries
// Required by qInfo
#include <QtCore/QtDebug>

#include "logging_macros.h"
#include "global_enums.h"

#include "menu.h"

// Categories
Q_LOGGING_CATEGORY(menuOverall, "menu.overall", MSG_TYPE_LEVEL)

menu::Menu::Menu(QWidget * parent, std::weak_ptr<QMenuBar> menuBar, const char* menuName, const key_sequence::KeySequence & key) : QWidget(parent), menuBar(menuBar), menuName(menuName), key(key) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, menuOverall, "Create menu " << this->menuName << " shortcut key " << this->key.toString());
	this->createMenu();
	this->createShortcuts();
}

menu::Menu::~Menu() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, menuOverall,  "menu destructor");
}

void menu::Menu::createMenu() {
	QEXCEPTION_ACTION_COND((this->menuBar.expired() == true), throw,  "Unable to get menu bar for menu " << menuName << " as it has already expired");
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
	QEXCEPTION_ACTION_COND((this->menuBar.expired() == true), throw,  "Unable to get menu bar for menu " << menuName << " as it has already expired");
	std::shared_ptr<QMenuBar> bar = this->menuBar.lock();
	if (bar != Q_NULLPTR) {
		// menu is expanded only if menu bar is visible
		if (bar->isVisible()) {
			QINFO_PRINT(global_enums::qinfo_level_e::ZERO, menuOverall, "Expand menu " << this->menuName << " because shortcut key " << this->key.toString() << " has been pressed");
			this->winMenu->exec();
			this->setFocus();
		}
	}
}

void menu::Menu::setEnabledProperty(const bool & enabled) {
	this->expandMenu->setEnabled(enabled);
}

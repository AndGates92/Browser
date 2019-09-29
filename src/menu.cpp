/**
 * @copyright
 * @file menu.cpp
 * @author Andrea Gianarda
 * @date 23th September 2019
 * @brief Top Menu functions
 */

// Qt libraries
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtWidgets/QShortcut>

#include "global_macros.h"
#include "global_types.h"

#include "menu.h"

// Categories
Q_LOGGING_CATEGORY(menuOverall, "menu.overall", MSG_TYPE_LEVEL)

menu::Menu::Menu(QWidget * window, QMenuBar * menuBar, const char* menuName, const QKeySequence & key) : window(window), menuBar(menuBar), menuName(menuName), key(key) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, menuOverall, "Create menu " << this->menuName << " shortcut key " << this->key.toString());
	this->createMenu();
	this->createShortcuts();
}

void menu::Menu::createMenu() {
	//Use QObject::tr as Menu is not a derived class of QObject
	this->winMenu = this->menuBar->addMenu(QObject::tr(menuName));
}

void menu::Menu::createShortcuts() {
	// Do not bind key if it is not set
	if (this->key != QKeySequence::UnknownKey) {
		QShortcut * expandMenu = new QShortcut(this->window);
		expandMenu->setKey(this->key);
		connect(expandMenu, SIGNAL(activated()), this, SLOT(expandSlot()));
	}
}

void menu::Menu::expandSlot() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, menuOverall, "Expand menu " << this->menuName << " because shortcut key " << this->key.toString() << " has been pressed");

	this->winMenu->show();
}

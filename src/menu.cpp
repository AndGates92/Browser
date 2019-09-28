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
	this->createMenu();
	this->createShortcuts();
}

void menu::Menu::createMenu() {
	//Use QObject::tr as Menu is not a derived class of QObject
	this->winMenu = this->menuBar->addMenu(QObject::tr(menuName));
}

void menu::Menu::createShortcuts() {
//	QShortcut * expandMenu = new QShortcut(this);
//	expandMenu->setKey(key);
//	connect(hideMenuBar, SIGNAL(activated()), this, SLOT(disableMenubar()));
}

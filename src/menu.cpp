/**
 * @copyright
 * @file menu.cpp
 * @author Andrea Gianarda
 * @date 23th September 2019
 * @brief Top Menu functions
 */

// Qt libraries
#include <qt5/QtWidgets/QMenu>
#include <qt5/QtWidgets/QGridLayout>
#include <qt5/QtCore/QLoggingCategory>

#include "global_macros.h"
#include "global_types.h"
#include "menu.h"

// Categories
Q_LOGGING_CATEGORY(menuOverall, "menu.overall", MSG_TYPE_LEVEL)

//void menu::addTopMenu(QGridLayout & layout) {
void menu::addTopMenu() {

	QMenu * top_menu = new QMenu();
	QAction * File = new QAction("File");
	File->setCheckable(true);
	top_menu->addAction(File);
//	layout.addWidget(&top_menu, 0, 0, Qt::AlignLeft);

}

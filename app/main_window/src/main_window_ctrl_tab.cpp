/**
 * @copyright
 * @file main_window_ctrl_tab.cpp
 * @author Andrea Gianarda
 * @date 22nd December 2019
 * @brief Main Window Tab Control functions
 */

// Qt libraries
// QtGlobal defines qWarning
#include <qt5/QtCore/QtGlobal>
#include <qt5/QtGui/QKeyEvent>

// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include "key_sequence.h"
#include "main_window_ctrl_tab.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowCtrlTabOverall, "mainWindowCtrlTab.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCtrlTabUserInput, "mainWindowCtrlTab.userInput", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCtrlTabSearch, "mainWindowCtrlTab.search", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCtrlTabTabs, "mainWindowCtrlTab.tabs", MSG_TYPE_LEVEL)


main_window_ctrl_tab::MainWindowCtrlTab::MainWindowCtrlTab(main_window_core::MainWindowCore * windowCore, QWidget * parent) : main_window_ctrl_base::MainWindowCtrlBase(windowCore, parent, main_window_ctrl_tab::commandFileFullPath) {

	// Shortcuts
	this->createShortcuts();

	// Connect signals and slots
	this->connectSignals();

}

main_window_ctrl_tab::MainWindowCtrlTab::~MainWindowCtrlTab() {

	// deleting shortcuts
	delete this->openNewTabKey;
	delete this->newSearchTabKey;
	delete this->closeTabKey;
	delete this->moveTabToKey;
	delete this->moveLeftKey;
	delete this->moveRightKey;
	delete this->refreshUrlKey;

}

void main_window_ctrl_tab::MainWindowCtrlTab::createShortcuts() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabOverall,  "Create shortcuts");

	// o will open a new tab
	this->openNewTabKey = new QShortcut(parent);
	this->openNewTabKey->setKey(Qt::Key_O);

	// s will search on the current tab
	this->newSearchTabKey = new QShortcut(parent);
	this->newSearchTabKey->setKey(Qt::Key_S);

	// c will close a tab
	this->closeTabKey = new QShortcut(parent);
	this->closeTabKey->setKey(Qt::Key_C);

	// t will move tab in the tab bar
	this->moveTabToKey = new QShortcut(parent);
	this->moveTabToKey->setKey(Qt::Key_T);

	// h will move left in the tab bar
	this->moveLeftKey = new QShortcut(parent);
	this->moveLeftKey->setKey(Qt::Key_H);

	// l will move right in the tab bar
	this->moveRightKey = new QShortcut(parent);
	this->moveRightKey->setKey(Qt::Key_L);

	// r will refresh a webpage
	this->refreshUrlKey = new QShortcut(parent);
	this->refreshUrlKey->setKey(Qt::Key_R);
}

void main_window_ctrl_tab::MainWindowCtrlTab::connectSignals() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabOverall,  "Connect signals");
	connect(this->openNewTabKey, &QShortcut::activated, this, &main_window_ctrl_tab::MainWindowCtrlTab::openNewTab);
	connect(this->newSearchTabKey, &QShortcut::activated, this, &main_window_ctrl_tab::MainWindowCtrlTab::newSearchTab);
	connect(this->closeTabKey, &QShortcut::activated, this, &main_window_ctrl_tab::MainWindowCtrlTab::closeTab);
	connect(this->moveTabToKey, &QShortcut::activated, this, &main_window_ctrl_tab::MainWindowCtrlTab::moveTabTo);
	connect(this->moveLeftKey, &QShortcut::activated, this, &main_window_ctrl_tab::MainWindowCtrlTab::moveLeft);
	connect(this->moveRightKey, &QShortcut::activated, this, &main_window_ctrl_tab::MainWindowCtrlTab::moveRight);
	connect(this->refreshUrlKey, &QShortcut::activated, this, &main_window_ctrl_tab::MainWindowCtrlTab::refreshTabUrl);
}


void main_window_ctrl_tab::MainWindowCtrlTab::moveTabTo() {
	this->mainWindowCore->setMainWindowState(main_window_shared_types::state_e::TAB_MOVE);
	this->printUserInput(main_window_shared_types::text_action_e::CLEAR);
	emit this->setShortcutEnabledPropertySignal(false);
}

void main_window_ctrl_tab::MainWindowCtrlTab::moveLeft() {
	this->mainWindowCore->setMainWindowState(main_window_shared_types::state_e::MOVE_LEFT);
	this->printUserInput(main_window_shared_types::text_action_e::CLEAR);
	emit this->setShortcutEnabledPropertySignal(false);
}

void main_window_ctrl_tab::MainWindowCtrlTab::moveRight() {
	this->mainWindowCore->setMainWindowState(main_window_shared_types::state_e::MOVE_RIGHT);
	this->printUserInput(main_window_shared_types::text_action_e::CLEAR);
	emit this->setShortcutEnabledPropertySignal(false);
}

void main_window_ctrl_tab::MainWindowCtrlTab::closeTab() {
	this->mainWindowCore->setMainWindowState(main_window_shared_types::state_e::CLOSE_TAB);
	this->printUserInput(main_window_shared_types::text_action_e::CLEAR);
	emit this->setShortcutEnabledPropertySignal(false);
}

void main_window_ctrl_tab::MainWindowCtrlTab::executeActionOnOffset(int offset) {
	int sign = 0;

	main_window_shared_types::state_e windowState = this->mainWindowCore->getMainWindowState();
	main_window_shared_types::move_value_e moveType = this->mainWindowCore->getMoveValueType();

	if (windowState == main_window_shared_types::state_e::MOVE_RIGHT) {
		sign = 1;
	} else if (windowState == main_window_shared_types::state_e::MOVE_LEFT) {
		sign = -1;
	} else if (windowState == main_window_shared_types::state_e::TAB_MOVE) {
		if (moveType == main_window_shared_types::move_value_e::RIGHT) {
			sign = 1;
		} else if (moveType == main_window_shared_types::move_value_e::LEFT) {
			sign = -1;
		}
	}

	Q_ASSERT_X(((sign == -1) || (sign == 1)), "execute movement on offset", "sign input must be either -1 or 1");
	this->convertToAbsTabIndex(offset, sign);
}

void main_window_ctrl_tab::MainWindowCtrlTab::executeActionOnTab(int index) {
	int tabIndex = main_window_ctrl_tab::emptyUserInput;
	// index is main_window_ctrl_tab::emptyUserInput if the argument is not passed
	if (index == main_window_ctrl_tab::emptyUserInput) {
		tabIndex = this->mainWindowCore->getCurrentTabIndex();
	} else {
		// start indexing tab to close with 0
		tabIndex = index;
	}

	int tabCount = this->mainWindowCore->getTabCount();

	main_window_shared_types::state_e windowState = this->mainWindowCore->getMainWindowState();

	if ((tabCount > tabIndex) && (tabIndex >= 0)) {
		if (windowState == main_window_shared_types::state_e::CLOSE_TAB) {
			emit this->closeTabSignal(tabIndex);
		} else if (windowState == main_window_shared_types::state_e::TAB_MOVE) {
			this->convertToAbsTabIndex(tabIndex, 0);
		} else if (windowState == main_window_shared_types::state_e::REFRESH_TAB) {
			this->convertToAbsTabIndex(tabIndex, 0);
		}
	} else {
		int maxTabRange = tabCount;
		qWarning(mainWindowCtrlTabTabs) << "Tab " << tabIndex << " doesn't exists. Valid range of tab is the integer number between 1 and " << maxTabRange << "\n";
	}
}

void main_window_ctrl_tab::MainWindowCtrlTab::openNewTab() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabSearch,  "Open new tab");
	this->mainWindowCore->setMainWindowState(main_window_shared_types::state_e::OPEN_TAB);
	this->printUserInput(main_window_shared_types::text_action_e::CLEAR);
	emit this->setShortcutEnabledPropertySignal(false);
}

void main_window_ctrl_tab::MainWindowCtrlTab::newSearchTab() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabSearch,  "Search in current tab");
	this->mainWindowCore->setMainWindowState(main_window_shared_types::state_e::SEARCH);
	this->printUserInput(main_window_shared_types::text_action_e::CLEAR);
	emit this->setShortcutEnabledPropertySignal(false);
}

void main_window_ctrl_tab::MainWindowCtrlTab::executeTabAction(int userInput) {
	main_window_shared_types::state_e windowState = this->mainWindowCore->getMainWindowState();
	main_window_shared_types::move_value_e moveType = this->mainWindowCore->getMoveValueType();

	if (windowState == main_window_shared_types::state_e::CLOSE_TAB) {
		this->executeActionOnTab(userInput);
	} else if ((windowState == main_window_shared_types::state_e::MOVE_RIGHT) || (windowState == main_window_shared_types::state_e::MOVE_LEFT)) {
		this->executeActionOnOffset(userInput);
	} else if (windowState == main_window_shared_types::state_e::TAB_MOVE) {
	       if ((moveType == main_window_shared_types::move_value_e::LEFT) || (moveType == main_window_shared_types::move_value_e::RIGHT)) {
			this->executeActionOnOffset(userInput);
		} else if (moveType == main_window_shared_types::move_value_e::ABSOLUTE) {
			this->executeActionOnTab(userInput);
		}
	}

	int tabIndex = this->mainWindowCore->getCurrentTabIndex();
	emit this->updateInfo();
	emit this->updateWebsiteSignal(tabIndex);
}

void main_window_ctrl_tab::MainWindowCtrlTab::processTabIndex(QString userInputStr) {
	// If indexStr is an empty string, do not pass any argument to executeTabAction (i.e. execute action on current tab)
	if (userInputStr.isEmpty()) {
		this->executeTabAction();
	} else {
		bool conversionSuccessful = false;
		int userInputInt = userInputStr.toInt(&conversionSuccessful, 10);
		if (conversionSuccessful == true) {
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabUserInput,  "user input succesfully converted to integer: string " << userInputStr << " integer " << userInputInt);
			this->executeTabAction(userInputInt);
		} else {
			qWarning(mainWindowCtrlTabTabs) << "tab index " << userInputStr << " is not made up by numbers only\n";
		}
	}
}



void main_window_ctrl_tab::MainWindowCtrlTab::executeCommand(QString command) {

	if (command.compare("open-tab") == 0) {
		this->openNewTab();
	} else if (command.compare("search-tab") == 0) {
		this->newSearchTab();
	} else if (command.compare("close-tab") == 0) {
		this->closeTab();
	} else if (command.compare("move-tab") == 0) {
		this->moveTabTo();
	} else if (command.compare("move-cursor-left") == 0) {
		this->moveLeft();
	} else if (command.compare("move-cursor-right") == 0) {
		this->moveRight();
	}

}

void main_window_ctrl_tab::MainWindowCtrlTab::keyReleaseEvent(QKeyEvent * event) {

	int releasedKey = event->key();
	Qt::KeyboardModifiers keyModifiers = event->modifiers();

	key_sequence::KeySequence keySeq(releasedKey | keyModifiers);

	if (event->type() == QEvent::KeyRelease) {

		main_window_shared_types::state_e windowState = this->mainWindowCore->getMainWindowState();

		// Retrieve main window controller state
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabUserInput,  "State " << windowState << " key " << keySeq.toString());

		switch (releasedKey) {
			case Qt::Key_Escape:
				this->mainWindowCore->setMoveValueType(main_window_shared_types::move_value_e::IDLE);
				break;
			case Qt::Key_Backspace:
				break;
			default:
				break;
		}
	}
}

void main_window_ctrl_tab::MainWindowCtrlTab::refreshTabUrl() {
	this->mainWindowCore->setMainWindowState(main_window_shared_types::state_e::REFRESH_TAB);
	this->printUserInput(main_window_shared_types::text_action_e::CLEAR);
	emit this->setShortcutEnabledPropertySignal(false);
}

void main_window_ctrl_tab::MainWindowCtrlTab::keyPressEvent(QKeyEvent * event) {

	int pressedKey = event->key();
	Qt::KeyboardModifiers keyModifiers = event->modifiers();

	key_sequence::KeySequence keySeq(pressedKey | keyModifiers);

	if (event->type() == QEvent::KeyPress) {

		main_window_shared_types::state_e windowState = this->mainWindowCore->getMainWindowState();
		main_window_shared_types::move_value_e moveType = this->mainWindowCore->getMoveValueType();

		// Retrieve main window controller state
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlTabUserInput,  "State " << windowState << " key " << keySeq.toString());

		switch (pressedKey) {
			case Qt::Key_Enter:
			case Qt::Key_Return:
				this->mainWindowCore->setMoveValueType(main_window_shared_types::move_value_e::IDLE);
				break;
			default:
				if (windowState == main_window_shared_types::state_e::TAB_MOVE) {
					if ((pressedKey >= Qt::Key_0) && (pressedKey <= Qt::Key_9)) {
						if (moveType == main_window_shared_types::move_value_e::IDLE) {
							this->mainWindowCore->setMoveValueType(main_window_shared_types::move_value_e::ABSOLUTE);
						}
					} else if ((moveType == main_window_shared_types::move_value_e::IDLE) && ((pressedKey == Qt::Key_H) || (pressedKey == Qt::Key_L) || (pressedKey == Qt::Key_Plus) || (pressedKey == Qt::Key_Minus))) {
						if ((pressedKey == Qt::Key_Plus) || (pressedKey == Qt::Key_L)) {
							this->mainWindowCore->setMoveValueType(main_window_shared_types::move_value_e::RIGHT);
						} else {
							this->mainWindowCore->setMoveValueType(main_window_shared_types::move_value_e::LEFT);
						}
					}
				}
				break;
		}

	}

}

main_window_shared_types::object_type_e main_window_ctrl_tab::MainWindowCtrlTab::setAffectedObject() {

	main_window_shared_types::object_type_e object = main_window_shared_types::object_type_e::UNKNOWN;

	main_window_shared_types::state_e windowState = this->mainWindowCore->getMainWindowState();

	// Retrieve main window controller state
	if ((windowState == main_window_shared_types::state_e::MOVE_RIGHT) || (windowState == main_window_shared_types::state_e::MOVE_LEFT)) {
		object = main_window_shared_types::object_type_e::CURSOR;
	} else if (windowState == main_window_shared_types::state_e::TAB_MOVE) {
		object = main_window_shared_types::object_type_e::TAB;
	}

	return object;
}

void main_window_ctrl_tab::MainWindowCtrlTab::convertToAbsTabIndex(int offset, int sign) {

	Q_ASSERT_X(((sign == 0) || (sign == -1) || (sign == 1)), "main window move", "sign input must be either 0 or -1 or 1");

	main_window_shared_types::state_e windowState = this->mainWindowCore->getMainWindowState();

	int distance = 0;
	// offset is main_window_ctrl_tab::emptyUserInput if the argument is not passed
	if (offset == main_window_ctrl_tab::emptyUserInput) {
		if ((windowState == main_window_shared_types::state_e::MOVE_RIGHT) || (windowState == main_window_shared_types::state_e::MOVE_LEFT) || (windowState == main_window_shared_types::state_e::TAB_MOVE)) {
			distance = 1;
		} else if (windowState == main_window_shared_types::state_e::REFRESH_TAB) {
			distance = 0;
		}
	} else {
		distance = offset;
	}

	int tabCount = this->mainWindowCore->getTabCount();

	int tabIndexDst = 0;
	if (sign == 0) {
		tabIndexDst = distance;
	} else {
		tabIndexDst = this->mainWindowCore->getCurrentTabIndex() + (sign * distance);
	}
	if (offset > tabCount) {
		int maxTabRange = tabCount - 1;
		qWarning(mainWindowCtrlTabTabs) << "Offset " << offset << " is bigger than the number of tabs " << tabCount << " Bringing tab index withing the valid range of tab (between 0 and " << maxTabRange << ")\n";
	}
	while (tabIndexDst < 0) {
		tabIndexDst +=  tabCount;
	}

	// Keep tabIndex values within valid range (0 and (tabCount -1))
	int tabIndex = tabIndexDst % tabCount;

	if ((windowState == main_window_shared_types::state_e::MOVE_RIGHT) || (windowState == main_window_shared_types::state_e::MOVE_LEFT)) {
		emit this->moveCursorSignal(tabIndex);
	} else if (windowState == main_window_shared_types::state_e::TAB_MOVE) {
		emit this->moveTabSignal(tabIndex);
	} else if (windowState == main_window_shared_types::state_e::REFRESH_TAB) {
		emit this->refreshUrlSignal(tabIndex);
	}
}

QString main_window_ctrl_tab::MainWindowCtrlTab::createUrl(QString search) {
	bool containsSpace = search.contains(" ");
	bool containsWww = search.contains(main_window_ctrl_tab::www);
	int numberDots = search.count(".");

	QString url(QString::null);

	// if contains at least 1 dot and no space, it could be a URL
	if ((numberDots > 0) && (containsSpace == false)) {
		url = main_window_ctrl_tab::https;
		if (containsWww == true) {
			url += search;
		} else {
			url += main_window_ctrl_tab::www + search;
		}
	} else {
		url = main_window_ctrl_tab::defaultSearchEngine.arg(search);
	}

	return url;
}


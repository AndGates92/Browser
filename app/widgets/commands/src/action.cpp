/**
 * @copyright
 * @file action.cpp
 * @author Andrea Gianarda
 * @date 12th of June 2020
 * @brief Action functions
 */

// Qt libraries
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtGui/QKeySequence>

#include "logging_macros.h"
#include "global_enums.h"
#include "action.h"


// Categories
Q_LOGGING_CATEGORY(actionOverall, "action.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(actionShortcut, "action.shortcut", MSG_TYPE_LEVEL)

action::Action::Action(QObject * parent, const QString & text, const QIcon & icon) : QAction(icon, text, parent) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, actionOverall,  "Creating action");

}

action::Action::~Action() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, actionOverall,  "Destructor of action class");

}

void action::Action::setShortcut(const key_sequence::KeySequence & key) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, actionShortcut,  "Setting primary shortcut: " << key.toString());
	QAction::setShortcut(key.toQKeySequence());

}

void action::Action::setShortcuts(const std::list<key_sequence::KeySequence> & keys) {

	QList<QKeySequence> keyList = QList<QKeySequence>();

	for (std::list<key_sequence::KeySequence>::const_iterator key = keys.cbegin(); key != keys.cend(); key++) {
		QINFO_PRINT(global_enums::qinfo_level_e::ZERO, actionShortcut,  "Appending shortcut " << key->toString());
		keyList.append(key->toQKeySequence());
	}

	QAction::setShortcuts(keyList);

}

key_sequence::KeySequence action::Action::shortcut() const {

	QKeySequence primaryQKey(QAction::shortcut());
	key_sequence::KeySequence primaryKey(primaryQKey);
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, actionShortcut,  "Setting primary shortcut: " << primaryKey.toString());

	return primaryKey;

}


std::list<key_sequence::KeySequence> action::Action::shortcuts() const {

	QList<QKeySequence> keyQList = QAction::shortcuts();

	std::list<key_sequence::KeySequence> keyList = std::list<key_sequence::KeySequence>();

	for (QList<QKeySequence>::const_iterator qKey = keyQList.cbegin(); qKey != keyQList.cend(); qKey++) {
		key_sequence::KeySequence key(*qKey);
		QINFO_PRINT(global_enums::qinfo_level_e::ZERO, actionShortcut,  "Appending shortcut " << key.toString());
		keyList.push_back(key);
	}

	return keyList;

}

std::string action::Action::textWithShortcut() const {

	QEXCEPTION_ACTION_COND((this->text().isEmpty() == true), throw,  "Action text cannot be empty when getting text using method " << __func__);

	std::string actionText(this->text().toStdString());
	if (this->shortcut().isEmpty() == false) {
		actionText.append(" (");
		actionText.append(this->shortcut().toString().toStdString());
		actionText.append(")");
	}

	return actionText;
}

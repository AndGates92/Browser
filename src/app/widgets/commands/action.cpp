/**
 * @copyright
 * @file action.cpp
 * @author Andrea Gianarda
 * @date 12th of June 2020
 * @brief Action functions
 */

// Qt libraries
#include <QtGui/QKeySequence>

#include "app/utility/cpp/cpp_operator.h"
#include "app/utility/logger/macros.h"
#include "app/shared/enums.h"
#include "app/widgets/commands/action.h"
#include "app/widgets/commands/key_sequence.h"

// Categories
LOGGING_CONTEXT(actionOverall, action.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(actionShortcut, action.shortcut, TYPE_LEVEL, INFO_VERBOSITY)

app::action::Action::Action(QObject * parent, const QString & text, const QIcon & icon) : QAction(icon, text, parent), app::printable_object::PrintableObject() {

	LOG_INFO(app::logger::info_level_e::ZERO, actionOverall,  "Creating action");

}

app::action::Action::~Action() {
	LOG_INFO(app::logger::info_level_e::ZERO, actionOverall,  "Destructor of action class");

}

void app::action::Action::setShortcut(const app::key_sequence::KeySequence & key) {

	LOG_INFO(app::logger::info_level_e::ZERO, actionShortcut,  "Setting primary shortcut: " << key.toString());
	QAction::setShortcut(key.toQKeySequence());

}

void app::action::Action::setShortcuts(const std::list<app::key_sequence::KeySequence> & keys) {

	QList<QKeySequence> keyList = QList<QKeySequence>();

	for (std::list<app::key_sequence::KeySequence>::const_iterator key = keys.cbegin(); key != keys.cend(); key++) {
		LOG_INFO(app::logger::info_level_e::ZERO, actionShortcut,  "Appending shortcut " << key->toString());
		keyList.append(key->toQKeySequence());
	}

	QAction::setShortcuts(keyList);

}

app::key_sequence::KeySequence app::action::Action::shortcut() const {

	QKeySequence primaryQKey(QAction::shortcut());
	app::key_sequence::KeySequence primaryKey(primaryQKey);
	LOG_INFO(app::logger::info_level_e::ZERO, actionShortcut,  "Setting primary shortcut: " << primaryKey.toString());

	return primaryKey;

}

std::list<app::key_sequence::KeySequence> app::action::Action::shortcuts() const {

	QList<QKeySequence> keyQList = QAction::shortcuts();

	std::list<app::key_sequence::KeySequence> keyList = std::list<app::key_sequence::KeySequence>();

	for (QList<QKeySequence>::const_iterator qKey = keyQList.cbegin(); qKey != keyQList.cend(); qKey++) {
		app::key_sequence::KeySequence key(*qKey);
		LOG_INFO(app::logger::info_level_e::ZERO, actionShortcut,  "Appending shortcut " << key.toString());
		keyList.push_back(key);
	}

	return keyList;

}

const std::string app::action::Action::print() const {

	EXCEPTION_ACTION_COND((this->text().isEmpty() == true), throw,  "Action text cannot be empty when getting text using method " << __func__);

	std::string actionText(this->text().toStdString());
	if (this->shortcut().isEmpty() == false) {
		actionText.append(" (");
		actionText.append(this->shortcut().toString().toStdString());
		actionText.append(")");
	}

	return actionText;
}

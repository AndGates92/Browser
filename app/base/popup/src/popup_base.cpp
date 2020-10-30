/**
 * @copyright
 * @file popup_base.cpp
 * @author Andrea Gianarda
 * @date 21st of June 2020
 * @brief Popup base functions
*/

// Qt libraries
#include <QtGui/QFont>

#include "popup_base.h"
#include "key_sequence.h"
#include "macros.h"
#include "global_enums.h"

// Categories
LOGGING_CONTEXT(popupBaseOverall, PopupBase.overall, TYPE_LEVEL, INFO_VERBOSITY)

popup_base::PopupBase::PopupBase(QWidget * parent, const bool & centerWidget, const int & widgetPadding, Qt::WindowFlags flags) : QWidget(parent, flags), popup_properties::PopupProperties(centerWidget, widgetPadding) {

	LOG_INFO(logger::info_level_e::ZERO, popupBaseOverall,  "Popup base constructor");

}

popup_base::PopupBase::~PopupBase() {
	LOG_INFO(logger::info_level_e::ZERO, popupBaseOverall,  "Popup base destructor");

}

std::unique_ptr<QLabel> popup_base::PopupBase::actionToLabel(QWidget * parent, const std::unique_ptr<action::Action> & action) const {
	std::unique_ptr<QLabel> label = std::make_unique<QLabel>(parent);

	key_sequence::KeySequence actionKey(action->shortcut());
	QString actionText(action->text());

	QString labelText = QString();
	if (actionText.isEmpty() == false) {
		labelText.append(actionText);
	}

	if (actionKey.count() > 0) {
		if (labelText.isEmpty() == false) {
			labelText.append(" <");
		}
		labelText.append(actionKey.toString());
		labelText.append(">");
	}

	label->setText(labelText);
	label->setTextFormat(Qt::PlainText);

	// font
	QFont labelFont(label->font());
	labelFont.setBold(true);
	label->setFont(labelFont);

	return label;
}

/**
 * @copyright
 * @file popup_base.cpp
 * @author Andrea Gianarda
 * @date 21st of June 2020
 * @brief Popup base functions
*/

// Qt libraries
#include <QtGui/QFont>

#include "app/base/popup/popup_base.h"
#include "app/widgets/commands/action.h"
#include "app/widgets/commands/key_sequence.h"
#include "app/utility/logger/macros.h"
#include "app/shared/enums.h"

// Categories
LOGGING_CONTEXT(popupBaseOverall, PopupBase.overall, TYPE_LEVEL, INFO_VERBOSITY)

app::base::popup::PopupBase::PopupBase(QWidget * parent, const bool & centerWidget, const int & widgetPadding, Qt::WindowFlags flags) : QWidget(parent, flags), app::base::popup::PopupProperties(centerWidget, widgetPadding) {

	LOG_INFO(app::logger::info_level_e::ZERO, popupBaseOverall,  "Popup base constructor");

}

app::base::popup::PopupBase::~PopupBase() {
	LOG_INFO(app::logger::info_level_e::ZERO, popupBaseOverall,  "Popup base destructor");

}

std::unique_ptr<QLabel> app::base::popup::PopupBase::actionToLabel(QWidget * parent, const std::unique_ptr<app::commands::Action> & action) const {
	std::unique_ptr<QLabel> label = std::make_unique<QLabel>(parent);

	app::commands::KeySequence actionKey(action->shortcut());
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

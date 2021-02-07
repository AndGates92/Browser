/**
 * @copyright
 * @file line_edit.cpp
 * @author Andrea Gianarda
 * @date 02nd of February 2021
 * @brief Line edit functions
*/

// Qt libraries
#include "app/utility/cpp/cpp_operator.h"
#include "app/utility/logger/macros.h"
#include "app/widgets/text/line_edit.h"

// Categories
LOGGING_CONTEXT(lineEditOverall, lineEdit.overall, TYPE_LEVEL, INFO_VERBOSITY)

app::text_widgets::LineEdit::LineEdit(QWidget * parent, const QString & text) : QLineEdit(text, parent) {

	LOG_INFO(app::logger::info_level_e::ZERO, lineEditOverall, "Line edit constructor for text " << this->text());

	this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
	this->connectSignals();
}

app::text_widgets::LineEdit::~LineEdit() {
	LOG_INFO(app::logger::info_level_e::ZERO, lineEditOverall, "Text edit destructor");
}

void app::text_widgets::LineEdit::connectSignals() {
	LOG_INFO(app::logger::info_level_e::ZERO, lineEditOverall, "Connect signals");

}

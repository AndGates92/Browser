/**
 * @copyright
 * @file text_edit.cpp
 * @author Andrea Gianarda
 * @date 02nd of February 2021
 * @brief Main Window statusbar functions
*/

// Qt libraries
#include "app/utility/cpp/cpp_operator.h"
#include "app/utility/logger/macros.h"
#include "app/widgets/text/text_edit.h"

// Categories
LOGGING_CONTEXT(textEditOverall, textEdit.overall, TYPE_LEVEL, INFO_VERBOSITY)

app::text_widgets::TextEdit::TextEdit(QWidget * parent, const QString & text) : QTextEdit(text, parent) {

	LOG_INFO(app::logger::info_level_e::ZERO, textEditOverall, "Text edit constructor for text " << this->toPlainText());

	this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
	this->setUndoRedoEnabled(true);
	this->setWordWrapMode(QTextOption::NoWrap);
	this->setTextInteractionFlags(Qt::TextSelectableByKeyboard);
}

app::text_widgets::TextEdit::~TextEdit() {
	LOG_INFO(app::logger::info_level_e::ZERO, textEditOverall, "Text edit destructor");
}



/**
 * @copyright
 * @file secondary_window_utility.cpp
 * @author Andrea Gianarda
 * @date 10th June 2020
 * @brief Secondary Window Utility functions
 */

#include <string>

// Qt libraries
#include <QtCore/QObject>

#include "utility/stl/include/cpp_operator.h"
#include "utility/qt/include/qt_operator.h"
#include "utility/logger/include/macros.h"
#include "common/include/global_enums.h"
#include "windows/secondary_windows/common/include/secondary_window_utility.h"

namespace secondary_window_utility {

	namespace {

		/**
		 * @brief margin above the text inside the line edit
		 *
		 */
		static constexpr int topLineEditMargin = 2;

		/**
		 * @brief margin underneat the text inside the line edit
		 *
		 */
		static constexpr int bottomLineEditMargin = 2;

		/**
		 * @brief margin above the text inside the push button
		 *
		 */
		static constexpr int topButtonMargin = 5;

		/**
		 * @brief margin underneat the text inside the push button
		 *
		 */
		static constexpr int bottomButtonMargin = 5;

	}

}

// Categories
LOGGING_CONTEXT(secondaryWindowUtilityOverall, secondaryWindowUtility.overall, TYPE_LEVEL, INFO_VERBOSITY)

std::unique_ptr<QFileSystemModel> secondary_window_utility::createFileModel(QWidget *parent, const QStringList & filters, const QDir & directory) {

	LOG_INFO(logger::info_level_e::ZERO, secondaryWindowUtilityOverall,  "Creating File Model widget object starting with directory " << directory.path());
	LOG_INFO(logger::info_level_e::ZERO, secondaryWindowUtilityOverall,  "File Model filters: ");

	for (QStringList::const_iterator filterIt = filters.cbegin(); filterIt != filters.cend(); filterIt++) {
		LOG_INFO(logger::info_level_e::ZERO, secondaryWindowUtilityOverall,  "- " << (*filterIt));
	}

	std::unique_ptr<QFileSystemModel> model = std::make_unique<QFileSystemModel>(parent);
	#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
	model->setOption(QFileSystemModel::DontResolveSymlinks, true);
	#endif
	model->setFilter(QDir::AllDirs | QDir::Hidden | QDir::AllEntries);

	model->setNameFilterDisables(true);
	model->setNameFilters(filters);

	model->setRootPath(directory.path());

	return model;
}

std::unique_ptr<QTreeView> secondary_window_utility::createFileView(std::unique_ptr<QFileSystemModel> & model, QWidget *parent, const QStringList & filters, const QDir & directory) {

	if (model == Q_NULLPTR) {
		model = std::move(secondary_window_utility::createFileModel(parent, filters, directory));
	}

	LOG_INFO(logger::info_level_e::ZERO, secondaryWindowUtilityOverall,  "Creating File View widget object starting with directory " << directory.path());

	std::unique_ptr<QTreeView> tree = std::make_unique<QTreeView>(parent);
	tree->setModel(model.get());
	tree->setRootIndex(model->index(directory.path()));
	tree->setExpandsOnDoubleClick(false);
	tree->setItemsExpandable(false);

	return tree;

}

std::unique_ptr<action::Action> secondary_window_utility::createAction(QObject * parent, const std::string & text, const std::string & tip, const key_sequence::KeySequence & shortcut) {

	LOG_INFO(logger::info_level_e::ZERO, secondaryWindowUtilityOverall,  "Creating Action object with text " << text << " tip " << tip << " key " << shortcut.toString());

	QString actionText = QString();
	if (text.empty() == false) {
		actionText = QAction::tr(text.c_str());
	}

	std::unique_ptr<action::Action> newAction = std::make_unique<action::Action>(parent, actionText);
	if (tip.empty() == false) {
		newAction->setStatusTip(QAction::tr(tip.c_str()));
	}
	newAction->setShortcut(shortcut);

	return newAction;
}

std::shared_ptr<QLineEdit> secondary_window_utility::createLineEdit(QWidget * parent, const std::string & text, const std::unique_ptr<action::Action> & focusAction) {

	LOG_INFO(logger::info_level_e::ZERO, secondaryWindowUtilityOverall,  "Creating Line Edit object with text " << text << " action " << *focusAction);

	std::shared_ptr<QLineEdit> lineEdit = std::make_unique<QLineEdit>(parent);
	if (text.empty() == false) {
		lineEdit->setPlaceholderText(QLineEdit::tr(text.c_str()));
	}
	lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	lineEdit->setFixedHeight(lineEdit->fontMetrics().height() + secondary_window_utility::topLineEditMargin + secondary_window_utility::bottomLineEditMargin);
	if (focusAction != nullptr) {
		lineEdit->addAction(const_cast<action::Action *>(focusAction.get()));
		QObject::connect(focusAction.get(), &action::Action::triggered, lineEdit.get(), [lineEdit] () {
			lineEdit->setFocus();
		});
	}

	return lineEdit;
}

std::unique_ptr<QPushButton> secondary_window_utility::createPushButton(QWidget *parent, const std::unique_ptr<action::Action> & actionPtr) {

	std::string buttonText(actionPtr->print());

	LOG_INFO(logger::info_level_e::ZERO, secondaryWindowUtilityOverall,  "Creating Push Button object with text " << buttonText << " action " << *actionPtr);

	std::unique_ptr<QPushButton> button = std::make_unique<QPushButton>(QPushButton::tr(buttonText.c_str()), parent);
	button->addAction(const_cast<action::Action *>(actionPtr.get()));
	button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	button->setFixedHeight(button->fontMetrics().height() + secondary_window_utility::topButtonMargin + secondary_window_utility::bottomButtonMargin);

	return button;
}

std::unique_ptr<QGroupBox> secondary_window_utility::createGroupBox(QWidget *parent, const std::string title) {

	LOG_INFO(logger::info_level_e::ZERO, secondaryWindowUtilityOverall,  "Creating Group Box object with title " << title);

	std::unique_ptr<QGroupBox> groupBox = std::make_unique<QGroupBox>(QString::fromStdString(title), parent);
	groupBox->setCheckable(false);
	groupBox->setChecked(false);
	groupBox->setFlat(true);

	return groupBox;
}

std::unique_ptr<QCheckBox> secondary_window_utility::createCheckBox(QWidget *parent, const std::unique_ptr<action::Action> & toggleAction) {

	LOG_INFO(logger::info_level_e::ZERO, secondaryWindowUtilityOverall,  "Creating Check Box object" << " action " << *toggleAction);

	std::unique_ptr<QCheckBox> checkBox = std::make_unique<QCheckBox>(QString(), parent);
	checkBox->setCheckState(Qt::Unchecked);
	checkBox->setTristate(false);
	if (toggleAction != nullptr) {
		std::string checkBoxText(toggleAction->print());
		LOG_INFO(logger::info_level_e::ZERO, secondaryWindowUtilityOverall,  "Setting Check Box text to " << checkBoxText);
		checkBox->setText(QCheckBox::tr(checkBoxText.c_str()));
		checkBox->addAction(const_cast<action::Action *>(toggleAction.get()));
		QObject::connect(toggleAction.get(), &action::Action::triggered, checkBox.get(), &QCheckBox::toggle);
	}

	return checkBox;
}

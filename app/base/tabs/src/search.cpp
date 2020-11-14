/**
 * @copyright
 * @file search.cpp
 * @author Andrea Gianarda
 * @date 02nd April 2020
 * @brief Tab search functions
 */

#include <QtWidgets/QMessageBox>

// Qt libraries
#include <QtGui/QKeyEvent>

#include "utility/logger/include/macros.h"
#include "base/tabs/include/search.h"
#include "common/include/exception_macros.h"

// Categories
LOGGING_CONTEXT(tabSearchOverall, tabSearch.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(tabSearchFind, tabSearch.find, TYPE_LEVEL, INFO_VERBOSITY)

app::base::tab::Search::Search(QWidget * parent, std::weak_ptr<app::base::tab::Tab> attachedTab): app::base::tab::TabComponentWidget<app::windows::shared::FindSettings>(parent, attachedTab), settings(QString(), app::shared::offset_type_e::IDLE, false, false), callback(nullptr) {
	LOG_INFO(app::logger::info_level_e::ZERO, tabSearchOverall,  "Tab search constructor");
}

app::base::tab::Search::~Search() {
	LOG_INFO(app::logger::info_level_e::ZERO, tabSearchOverall,  "Tab search destructor");

}

void app::base::tab::Search::execute(const app::windows::shared::FindSettings & newSettings) {

	this->settings = newSettings;
	this->setCallback();

	this->search();
}

void app::base::tab::Search::search() {

	if (this->canProcessRequests() == true) {
		try {
			std::shared_ptr<app::base::tab::Tab> currentTab = this->getTab();
			std::shared_ptr<app::base::tab::WebEnginePage> currentTabPage = currentTab->getPage();

			const QString text = this->settings.getText();
			const bool caseSensitive = this->settings.getCaseSensitive();
			const app::shared::offset_type_e direction = this->settings.getDirection();

			EXCEPTION_ACTION_COND(((direction != app::shared::offset_type_e::DOWN) && (direction != app::shared::offset_type_e::UP)), throw, "Unable to perform search with direction set to " << direction);

			// No flag set by default
			// Available search flags are:
			// - QWebEnginePage::FindBackward
			// - QWebEnginePage::FindCaseSensitively
			QWebEnginePage::FindFlags flags = QWebEnginePage::FindFlag(0);
			if (direction == app::shared::offset_type_e::UP) {
				flags |= QWebEnginePage::FindBackward;
			} else {
				flags &= ~QWebEnginePage::FindBackward;
			}
			if (caseSensitive == true) {
				flags |= QWebEnginePage::FindCaseSensitively;
			} else {
				flags &= ~QWebEnginePage::FindCaseSensitively;
			}

			currentTabPage->findText(text, flags,
				[=](bool found) {
					if (this->callback) {
						this->callback(found);
					}
				}
			);
		} catch (const std::bad_cast & badCastE) {
			EXCEPTION_ACTION(throw, badCastE.what());
		}

	} else {
		this->pushRequestQueue(this->settings);
	}
}

bool app::base::tab::Search::canProcessRequests() const {
	const std::shared_ptr<app::base::tab::Tab> currentTab = this->getTab();
	const app::base::tab::load_status_e & loadManagerStatus = currentTab->getLoadStatus();

	return ((loadManagerStatus == app::base::tab::load_status_e::FINISHED) || (loadManagerStatus == app::base::tab::load_status_e::ERROR));
}

void app::base::tab::Search::setCallback() {

	this->callback = nullptr;

}

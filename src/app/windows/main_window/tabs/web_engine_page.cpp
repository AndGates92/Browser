/**
 * @copyright
 * @file web_engine_page.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Web engine page functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "app/utility/cpp/cpp_operator.h"
#include "app/utility/logger/macros.h"
#include "app/shared/setters_getters.h"
#include "app/shared/cpp_functions.h"
#include "app/windows/main_window/tabs/web_engine_page.h"
#include "app/windows/main_window/tabs/page_data.h"

// Categories
LOGGING_CONTEXT(mainWindowWebEnginePageOverall, mainWindowWebEnginePage.overall, TYPE_LEVEL, INFO_VERBOSITY)

app::main_window::tab::WebEnginePage::WebEnginePage(QWidget * parent, const app::main_window::page_type_e & type, const QString & src, app::main_window::tab::WebEngineProfile * profile, const void * data): app::base::tab::WebEnginePage(parent, profile), pageData(app::main_window::tab::PageData::makePageData(type, src.toStdString(), data)) {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowWebEnginePageOverall, "Web engine page constructor");

	this->setBody();
	if (src != QString()) {
		emit this->sourceChanged(src);
	}

}

void app::main_window::tab::WebEnginePage::setSource(const QString & src) {
	bool changed = this->pageData->setSource(src.toStdString());

	if (changed == true) {
		emit this->sourceChanged(src);
	}
}

void app::main_window::tab::WebEnginePage::setBody() {

	app::main_window::page_type_e type = this->getType();

	switch (type) {
		case app::main_window::page_type_e::WEB_CONTENT:
		{
			const QUrl url(this->getSource(), QUrl::TolerantMode);
			EXCEPTION_ACTION_COND((url.isValid() == false), throw, "URL is not valid. The following error has been identified: " << url.errorString());
			this->setUrl(url);
			this->setSource(url.toString());
			break;
		}
		case app::main_window::page_type_e::TEXT:
			this->setContent(this->getTextFileBody());
			break;
		case app::main_window::page_type_e::UNKNOWN:
			break;
		default:
			EXCEPTION_ACTION(throw, "Unable to set body for this page as type " << type << " is not recognised");
			break;
	}
}

app::main_window::tab::WebEnginePage::~WebEnginePage() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowWebEnginePageOverall, "Web engine page destructor");
}

CONST_GETTER(app::main_window::tab::WebEnginePage::getType, app::main_window::page_type_e &, this->pageData->type)
CONST_GETTER(app::main_window::tab::WebEnginePage::getSource, QString, QString::fromStdString(this->pageData->source))
CONST_PTR_GETTER(app::main_window::tab::WebEnginePage::getExtraData, void, this->pageData->data)
CONST_GETTER(app::main_window::tab::WebEnginePage::getData, std::shared_ptr<app::main_window::tab::PageData> &, this->pageData)

void app::main_window::tab::WebEnginePage::reload() {
	const app::main_window::page_type_e type = this->getType();
	switch (type) {
		case app::main_window::page_type_e::WEB_CONTENT:
			this->triggerAction(QWebEnginePage::Reload);
			break;
		case app::main_window::page_type_e::TEXT:
			this->setContent(this->getTextFileBody());
			break;
		default:
			EXCEPTION_ACTION(throw, "Unable to reload page as type " << type << " is not recognised");
			break;
	}
}

QByteArray app::main_window::tab::WebEnginePage::getTextFileBody() const {

	QByteArray pageContent(nullptr, -1);

	const QString source = this->getSource();

	if (source.isEmpty() == false) {
		app::main_window::page_type_e type = this->getType();
		EXCEPTION_ACTION_COND((type != app::main_window::page_type_e::TEXT), throw, "Unable to get body of text file for tab of type " << type);
		// Convert QString to std::string
		std::string filename = source.toStdString();
		const QString fileContent(QString::fromStdString(app::shared::readFile(filename.c_str())));
		pageContent = fileContent.toUtf8();
	}

	return pageContent;
}

void app::main_window::tab::WebEnginePage::setData(const std::shared_ptr<app::main_window::tab::PageData> & newData) {
	this->pageData = newData;
	emit this->sourceChanged(QString::fromStdString(this->pageData->source));
}

void app::main_window::tab::WebEnginePage::applyScrollRequest(const int & x, const int & y) {
	// Quite annoying work-around as QT C++ API doesn't allow the user to set the scroll position of a web page direction
	this->runJavaScript(QString("window.scrollTo(%1, %2)").arg(x).arg(y));
}

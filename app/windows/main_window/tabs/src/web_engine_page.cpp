/**
 * @copyright
 * @file web_engine_page.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Web engine page functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "utility/stl/include/cpp_operator.h"
#include "utility/logger/include/macros.h"
#include "common/include/function_macros.h"
#include "common/include/global_functions.h"
#include "windows/main_window/tabs/include/web_engine_page.h"

// Categories
LOGGING_CONTEXT(mainWindowWebEnginePageOverall, mainWindowWebEnginePage.overall, TYPE_LEVEL, INFO_VERBOSITY)

main_window::WebEnginePage::WebEnginePage(QWidget * parent, const main_window::page_type_e & type, const QString & src, main_window::WebEngineProfile * profile, const void * data): web_engine_page::WebEnginePage(parent, profile), pageData(main_window::PageData::makePageData(type, src.toStdString(), data)) {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowWebEnginePageOverall,  "Web engine page constructor");

	this->setBody();
	if (src != QString()) {
		emit this->sourceChanged(src);
	}

}

void main_window::WebEnginePage::setSource(const QString & src) {
	bool changed = this->pageData->setSource(src.toStdString());

	if (changed == true) {
		emit this->sourceChanged(src);
	}
}

void main_window::WebEnginePage::setBody() {

	main_window::page_type_e type = this->getType();

	switch (type) {
		case main_window::page_type_e::WEB_CONTENT:
		{
			const QUrl url(this->getSource(), QUrl::StrictMode);
			EXCEPTION_ACTION_COND((url.isValid() == false), throw,  "URL is not valid. The following error has been identified: " << url.errorString());
			this->setUrl(url);
			break;
		}
		case main_window::page_type_e::TEXT:
			this->setContent(this->getTextFileBody());
			break;
		case main_window::page_type_e::UNKNOWN:
			break;
		default:
			EXCEPTION_ACTION(throw, "Unable to set body for this page as type " << type << " is not recognised");
			break;
	}
}

main_window::WebEnginePage::~WebEnginePage() {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowWebEnginePageOverall,  "Web engine page destructor");
}

CONST_GETTER(main_window::WebEnginePage::getType, main_window::page_type_e &, this->pageData->type)
CONST_GETTER(main_window::WebEnginePage::getSource, QString, QString::fromStdString(this->pageData->source))
CONST_PTR_GETTER(main_window::WebEnginePage::getExtraData, void, this->pageData->data)
CONST_GETTER(main_window::WebEnginePage::getData, std::shared_ptr<main_window::PageData> &, this->pageData)

void main_window::WebEnginePage::reload() {
	const main_window::page_type_e type = this->getType();
	switch (type) {
		case main_window::page_type_e::WEB_CONTENT:
			this->triggerAction(QWebEnginePage::Reload);
			break;
		case main_window::page_type_e::TEXT:
			this->setContent(this->getTextFileBody());
			break;
		default:
			EXCEPTION_ACTION(throw, "Unable to reload page as type " << type << " is not recognised");
			break;
	}
}

QByteArray main_window::WebEnginePage::getTextFileBody() const {

	QByteArray pageContent(nullptr, -1);

	const QString source = this->getSource();

	if (source.isEmpty() == false) {
		main_window::page_type_e type = this->getType();
		EXCEPTION_ACTION_COND((type != main_window::page_type_e::TEXT), throw,  "Unable to get body of text file for tab of type " << type);
		// Convert QString to std::string
		std::string filename = source.toStdString();
		const QString fileContent(QString::fromStdString(global_functions::readFile(filename.c_str())));
		pageContent = fileContent.toUtf8();
	}

	return pageContent;
}

void main_window::WebEnginePage::setData(const std::shared_ptr<main_window::PageData> & newData) {
	this->pageData = newData;
	emit this->sourceChanged(QString::fromStdString(this->pageData->source));
}

void main_window::WebEnginePage::applyScrollRequest(const int & x, const int & y) {
	// Quite annoying work-around as QT C++ API doesn't allow the user to set the scroll position of a web page direction
	this->runJavaScript(QString("window.scrollTo(%1, %2)").arg(x).arg(y));
}

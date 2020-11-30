/**
 * @copyright
 * @file logging.cpp
 * @author Andrea Gianarda
 * @date 17th of April 2020
 * @brief Logging function definition
 */

#include <QtCore/QDateTime>
#include <QtCore/QTimeZone>

#include "app/shared/logging.h"

QString app::shared::getDateTime() {
	QString datetimeStr = QString();

	QLocale locale(QLocale::AnyLanguage, QLocale::AnyScript, QLocale::AnyCountry);
	QDateTime datetime = QDateTime::currentDateTime();
	datetime.setTimeSpec(Qt::TimeZone);
	datetimeStr.append(locale.toString(datetime, QLocale::ShortFormat));
	datetimeStr.append(" ");
	datetimeStr.append(datetime.timeZoneAbbreviation());

	return datetimeStr;
}

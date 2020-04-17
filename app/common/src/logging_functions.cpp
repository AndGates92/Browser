/**
 * @copyright
 * @file logging_functions.cpp
 * @author Andrea Gianarda
 * @date 17th of April 2020
 * @brief Logging function definition
 */

#include <qt5/QtCore/QDateTime>
#include <qt5/QtCore/QTimeZone>

#include "logging_functions.h"

QString logging_functions::getDateTime() {
	QString datetimeStr(QString::null);

	QDateTime datetime = QDateTime::currentDateTime();
	datetime.setTimeSpec(Qt::TimeZone);
	datetimeStr.append(datetime.toString(Qt::SystemLocaleShortDate));
	datetimeStr.append(" ");
	datetimeStr.append(datetime.timeZoneAbbreviation());

	return datetimeStr;
}

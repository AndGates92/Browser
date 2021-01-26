/**
 * @copyright
 * @file classes.cpp
 * @author Andrea Gianarda
 * @date 31st of March 2020
 * @brief Global class definition
 */

#include "app/shared/classes.h"
#include "app/utility/cpp/cpp_operator.h"
#include "app/utility/logger/macros.h"

LOGGING_CONTEXT(qactionCompare, qaction.compare, TYPE_LEVEL, INFO_VERBOSITY)

bool app::shared::StringCompare::operator() (const std::string & rhs, const std::string & lhs) const {
	return (rhs.compare(lhs) < 0);
}

bool app::shared::QActionCompare::operator() (const QAction & lhs, const QAction & rhs) const {

	const QList<QKeySequence> keyList1(lhs.shortcuts());
	const QList<QKeySequence> keyList2(rhs.shortcuts());

	bool compare = (keyList1.size() < keyList2.size());

	if (keyList1.size() != keyList2.size()) {
		LOG_INFO(app::logger::info_level_e::ZERO, qactionCompare, "Size mismatch: " << &lhs << " (text: " << lhs.text() << "): " << keyList1.size() << " and " << &rhs << " (text: " << rhs.text() << "): " << keyList2.size());
	}

	for(QList<QKeySequence>::const_iterator keyIt1 = keyList1.cbegin(), keyIt2 = keyList2.cbegin(); (keyIt1 != keyList1.cend() && keyIt2 != keyList2.cend()); keyIt1++, keyIt2++) {

		compare |= ((*keyIt1) < (*keyIt2));

		if ((*keyIt1) != (*keyIt2)) {
			LOG_INFO(app::logger::info_level_e::ZERO, qactionCompare, "Key sequence mismatch: " << &lhs << " (text: " << lhs.text() << "): " << keyIt1->toString() << " and " << &rhs << " (text: " << rhs.text() << "): " << keyIt2->toString());
		}
	}

	// Discard mnemonic that could cause comparison to mismatch
	QString lhsText(lhs.text().replace(QString("&"), QString("")));
	QString rhsText(rhs.text().replace(QString("&"), QString("")));

	int textCompare = QString::compare(lhsText, rhsText, Qt::CaseSensitive);

	compare |= (textCompare < 0);

	if (textCompare != 0) {
		LOG_INFO(app::logger::info_level_e::ZERO, qactionCompare, "Text mismatch (compare value " << textCompare << "): " << &lhs << " (text: " << lhs.text() << "): " << lhsText << " and " << &rhs << " (text: " << rhs.text() << "): " << rhsText);
	}

	return compare;

}

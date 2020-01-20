/**
 * @copyright
 * @file key_info.cpp
 * @author Andrea Gianarda
 * @date 13th January 2020
 * @brief Key Info functions
 */

// Qt libraries
#include <qt5/QtCore/QLoggingCategory>

#include "global_types.h"
#include "global_macros.h"
#include "key_info.h"

// Categories
Q_LOGGING_CATEGORY(keyInfoOverall, "keyInfo.overall", MSG_TYPE_LEVEL)

key_info::KeyInfo::KeyInfo(const QKeySequence & keySeq) {

	// Assert that only1 key is stored in the QKeySequence
	Q_ASSERT_X((keySeq.count() == 1), "keyInfo to string", "QKeySequence passed to KeyInfo class instance must contain one key sequence");

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, keyInfoOverall,  "Key Info constructor");
	this->key = QKeySequence(keySeq);

}

QString key_info::KeyInfo::toString(QKeySequence::SequenceFormat format) const {

	int keyInt = this->key[0];
	Qt::Key key = Qt::Key(keyInt);

	// Find key into special key map
	keyInfoMap::const_iterator specialKey = key_info::specialKeyMap.find(key);

	QString keyStr(QString::null);

	if (specialKey == key_info::specialKeyMap.end()) {
		keyStr = this->key.toString(format);
	} else {
		keyStr = QString(specialKey->second);
	}

	return keyStr;

}

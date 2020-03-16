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
Q_LOGGING_CATEGORY(keyInfoString, "keyInfo.string", MSG_TYPE_LEVEL)

key_info::KeyInfo::KeyInfo(const QKeySequence & keySeq) {

	// Assert that only1 key is stored in the QKeySequence
	Q_ASSERT_X((keySeq.count() == 1), "key sequence length", "QKeySequence passed to KeyInfo class instance must contain one key sequence");

	// Cast first element of key sequence to int in order to extract the key and the modifier
	int keyInt = keySeq[0];

	this->key = Qt::Key(keyInt & ~(Qt::KeyboardModifierMask));
	this->modifier = Qt::KeyboardModifier(keyInt & Qt::KeyboardModifierMask);

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, keyInfoOverall,  "Key Info constructor (key " << this->key << " (0x" << QString("%1").arg(int(this->key), 0, 16) << "), modifier " << this->modifierToString(this->modifier) << " (0x" << QString("%1").arg(this->modifier, 0, 16) << "))");

}

key_info::KeyInfo::KeyInfo(const key_info::KeyInfo & rhs) : key(rhs.key), modifier(rhs.modifier) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, keyInfoOverall,  "Copy constructor key info");

}

key_info::KeyInfo & key_info::KeyInfo::operator=(const key_info::KeyInfo & rhs) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, keyInfoOverall,  "Copy assignment operator for key info");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}

	if (this->key != rhs.key) {
		this->key = rhs.key;
	}

	if (this->modifier != rhs.modifier) {
		this->modifier = rhs.modifier;
	}

	return *this;
}

key_info::KeyInfo::KeyInfo(key_info::KeyInfo && rhs) : key(std::move(rhs.key)), modifier(std::move(rhs.modifier)) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, keyInfoOverall,  "Move constructor key info");

	rhs.key = Qt::Key_unknown;
	rhs.modifier = Qt::NoModifier;
}

key_info::KeyInfo & key_info::KeyInfo::operator=(key_info::KeyInfo && rhs) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, keyInfoOverall,  "Move assignment operator for key info");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}

	if (this->key != rhs.key) {
		this->key = std::move(rhs.key);
	}
	rhs.key = Qt::Key_unknown;

	if (this->modifier != rhs.modifier) {
		this->modifier = std::move(rhs.modifier);
	}
	rhs.modifier = Qt::NoModifier;

	return *this;
}

key_info::KeyInfo::~KeyInfo() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, keyInfoOverall,  "Destructor of KeyInfo class");

}

QString key_info::KeyInfo::toString(QKeySequence::SequenceFormat format) const {

	// Convert key to string
	QString keyStr(this->keyToString(this->key, format));
	QString commentStr(QString::null);

	int tmpModifier = int(this->modifier);
	modifierKeyMap::const_iterator modifierKey = key_info::modifierKeys.find(this->key);

	if (modifierKey == key_info::modifierKeys.end()) {
		// If key is not only a special character, then act based on the modifier if the key is printable
		if (isKeyPrintable(this->key)) {
			if (this->modifier == Qt::ShiftModifier) {
				keyStr = keyStr.toUpper();
				tmpModifier &= ~Qt::ShiftModifier;
				commentStr.append("(Shift+" + keyStr.toLower() + ")");
			} else {
				// Make string lowercase
				keyStr = keyStr.toLower();
			}
		}
	} else {
		// If key is only a special character, then cancel out modifier
		tmpModifier &= ~(modifierKey->second);
	}

	QString modifierStr(this->modifierToString(Qt::KeyboardModifier(tmpModifier), format));

	QString keySeqStr(QString::null);
	keySeqStr.append(modifierStr);
	keySeqStr.append(keyStr);
	// If commentStr is not empty, then add a space and print it
	if (!commentStr.isEmpty()) {
		keySeqStr.append(" " + commentStr);
	}

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, keyInfoString,  "Key sequence (key " << this->key << " (0x" << QString("%1").arg(int(this->key), 0, 16) << "), modifier " << this->modifierToString(this->modifier) << " (0x" << QString("%1").arg(this->modifier, 0, 16) << ")) to " << keySeqStr);

	return keySeqStr;

}

QString key_info::KeyInfo::keyToString(Qt::Key keyPrint, QKeySequence::SequenceFormat format) const {
	specialKeyMap::const_iterator specialKey = key_info::specialKeys.find(keyPrint);

	QString keyStr(QString::null);

	// key no found in specialKeys unordered map
	if (specialKey == key_info::specialKeys.end()) {
		QKeySequence keySeq = QKeySequence(int(keyPrint));
		keyStr.append(keySeq.toString(format));
	} else {
		keyStr.append(QString(specialKey->second));
	}

	return keyStr;
}

QString key_info::KeyInfo::modifierToString(Qt::KeyboardModifier modifierPrint, QKeySequence::SequenceFormat format) const {
	QString modifierStr(QString::null);

	// Concert to key sequence
	QKeySequence modifierSeq(modifierPrint);

	modifierStr.append(modifierSeq.toString(format));

	return modifierStr;

}

bool key_info::KeyInfo::isKeyPrintable(Qt::Key keyCheck) const {
	bool isPrintable = false;

	if ((keyCheck >= Qt::Key_A) && (keyCheck <= Qt::Key_ydiaeresis)) {
		isPrintable = true;
	}

	return isPrintable;
}

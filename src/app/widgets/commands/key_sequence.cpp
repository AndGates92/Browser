/**
 * @copyright
 * @file key_sequence.cpp
 * @author Andrea Gianarda
 * @date 11th January 2020
 * @brief Key Sequence functions
 */

#include "app/utility/cpp/cpp_operator.h"
#include "app/shared/exception.h"
#include "app/shared/setters_getters.h"
#include "app/shared/enums.h"
#include "app/utility/logger/macros.h"
#include "app/widgets/commands/key_info.h"
#include "app/widgets/commands/key_sequence.h"

// Categories
LOGGING_CONTEXT(keySequenceOverall, keySequence.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(keySequenceString, keySequence.string, TYPE_LEVEL, INFO_VERBOSITY)

namespace app {

	namespace commands {

		namespace key_sequence {

			namespace {
				/**
				 * @brief Maximum number of element on the QKeySequence vector
				 *
				 */
				static constexpr unsigned int maxCount = 4;

				/**
				 * @brief Maximum number of key codes in every element of the vector
				 *
				 */
				static constexpr unsigned int maxKeyCodesInEl = 1;
			}

		}

	}

}

app::commands::KeySequence::KeySequence(const QString & keyStr, QKeySequence::SequenceFormat format) {
	LOG_INFO(app::logger::info_level_e::ZERO, keySequenceOverall, "Key Sequence constructor: key " << keyStr);

	// Split key sequence string into individual key sequences
	#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
	QStringList keySeqList = keyStr.split(",", Qt::SkipEmptyParts);
	#else
	QStringList keySeqList = keyStr.split(",", QString::SkipEmptyParts);
	#endif

	for (QStringList::const_iterator cIter = keySeqList.cbegin(); cIter != keySeqList.cend(); cIter++) {
		QKeySequence keySeq(*cIter, format);
		LOG_INFO(app::logger::info_level_e::ZERO, keySequenceOverall, "Adding " << (*cIter) << " to key sequence vector");
		this->keySeqVec.append(keySeq);
	}

	this->checkRules();
}

app::commands::KeySequence::KeySequence(int key0, int key1, int key2, int key3) {
	LOG_INFO(app::logger::info_level_e::ZERO, keySequenceOverall, "Key Sequence constructor: key0 0x" << QString("%1").arg(key0, 0, 16) << " key1 0x" << QString("%1").arg(key1, 0, 16) << " key2 0x" << QString("%1").arg(key2, 0, 16) << " key3 0x" << QString("%1").arg(key3, 0, 16));
	this->addKey(key0);
	this->addKey(key1);
	this->addKey(key2);
	this->addKey(key3);

	this->checkRules();
}

app::commands::KeySequence::KeySequence(const QKeySequence & qKeySeq) {
	const unsigned int thisSize = qKeySeq.count();

	for (unsigned int idx = 0; idx < thisSize; idx++) {
		int key = qKeySeq[idx];
		LOG_INFO(app::logger::info_level_e::ZERO, keySequenceOverall, "Key Sequence constructor. Keys are 0x" << QString("%1").arg(key, 0, 16));
		this->keySeqVec.append(key);
	}

	this->checkRules();
}

app::commands::KeySequence::KeySequence(const QKeySequence::StandardKey stdKey) {
	LOG_INFO(app::logger::info_level_e::ZERO, keySequenceOverall, "Key Sequence constructor: key " << stdKey);
	const QKeySequence qKeySeq(stdKey);
	// There is only 1 key in the key sequence, therefore accessing it at index 0
	const int key = qKeySeq[0];
	this->keySeqVec.append(key);

	this->checkRules();
}

app::commands::KeySequence::KeySequence(const app::commands::KeySequence & rhs) : keySeqVec(rhs.keySeqVec) {

	LOG_INFO(app::logger::info_level_e::ZERO, keySequenceOverall, "Copy constructor key sequence");

}

app::commands::KeySequence & app::commands::KeySequence::operator=(const app::commands::KeySequence & rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, keySequenceOverall, "Copy assignment operator for key sequence");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}

	if (this->keySeqVec != rhs.keySeqVec) {
		this->keySeqVec = rhs.keySeqVec;
	}

	return *this;
}

app::commands::KeySequence::KeySequence(app::commands::KeySequence && rhs) : keySeqVec(std::exchange(rhs.keySeqVec, QVector<QKeySequence>())) {

	LOG_INFO(app::logger::info_level_e::ZERO, keySequenceOverall, "Move constructor key sequence");

	EXCEPTION_ACTION_COND((rhs.keySeqVec.capacity() != 0), throw, "Released all memory used by vector but capacity is still non-zero - actual capacity " << rhs.keySeqVec.capacity());
}

app::commands::KeySequence & app::commands::KeySequence::operator=(app::commands::KeySequence && rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, keySequenceOverall, "Move assignment operator for key sequence");

	if (&rhs != this) {
		this->keySeqVec = std::exchange(rhs.keySeqVec, QVector<QKeySequence>());
		EXCEPTION_ACTION_COND((rhs.keySeqVec.capacity() != 0), throw, "Released all memory used by vector but capacity is still non-zero - actual capacity " << rhs.keySeqVec.capacity());
	}

	return *this;
}

app::commands::KeySequence::~KeySequence() {
	LOG_INFO(app::logger::info_level_e::ZERO, keySequenceOverall, "Destructor of KeySequence class");

}

void app::commands::KeySequence::addKey(int key, QKeySequence::SequenceFormat format) {
	if (key != Qt::Key_unknown) {
		LOG_INFO(app::logger::info_level_e::ZERO, keySequenceOverall, "Adding 0x" << QString("%1").arg(int(key), 0, 16) << " to key sequence vector");
		const QKeySequence keySeq(key, format);
		this->keySeqVec.append(keySeq);
	}
}

unsigned int app::commands::KeySequence::count() const {
	return this->keySeqVec.size();
}

int app::commands::KeySequence::getIntKey(const unsigned int & index) const {

	this->checkRules();

	// Default key to 0
	int key = 0;

	if (index < this->count()) {
		const QKeySequence qKeyVec(this->keySeqVec.at(index));

		// Return index 0 as it is expected that the sequence has only 1 element
		key = qKeyVec[0];
	}

	return key;
}

void app::commands::KeySequence::checkRules() const {
	unsigned int numEl = this->count();
	EXCEPTION_ACTION_COND((numEl > app::commands::key_sequence::maxCount), throw, "Vector has " << numEl << " elements which is larger than the allowed maximum number " << app::commands::key_sequence::maxCount);

	for (QVector<QKeySequence>::const_iterator cIter = this->keySeqVec.cbegin(); cIter != this->keySeqVec.cend(); cIter++) {
		unsigned int numKeyCode = cIter->count();
		EXCEPTION_ACTION_COND((numKeyCode > app::commands::key_sequence::maxKeyCodesInEl), throw, "Element has " << numKeyCode << " key codes which is larger than the allowed maximum number " << app::commands::key_sequence::maxKeyCodesInEl);
	}
}

QKeySequence app::commands::KeySequence::toQKeySequence() const {

	int key0 = this->getIntKey(0);
	int key1 = this->getIntKey(1);
	int key2 = this->getIntKey(2);
	int key3 = this->getIntKey(3);

	QKeySequence qKeySeq(key0, key1, key2, key3);

	return qKeySeq;

}

bool app::commands::KeySequence::isEmpty() const {
	const bool emptyVector = keySeqVec.empty();


	bool unknownKeyAtHead = true;

	if (keySeqVec.size() == 1) {
		unknownKeyAtHead = (keySeqVec[0] == Qt::Key_unknown);
	} else {
		const QVector<QKeySequence>::const_iterator unknownKey = std::find_if(keySeqVec.cbegin(), keySeqVec.cend(),
			[] (const QKeySequence & keySeq) {
				return (keySeq[0] == (int)Qt::Key_unknown);
			}
		);

		const int unknownKeyPosition = (unknownKey == keySeqVec.cbegin());
		unknownKeyAtHead = (unknownKeyPosition == 0);
	}

	const bool emptyKeySequence = emptyVector || unknownKeyAtHead;

	return emptyKeySequence;
}

QString app::commands::KeySequence::toString(QKeySequence::SequenceFormat format) const {

	QStringList keySeqList;

	for (QVector<QKeySequence>::const_iterator cIter = this->keySeqVec.cbegin(); cIter != this->keySeqVec.cend(); cIter++) {
		// Retrieve sequence to:
		// - split the key from the modifier (using Qt::KeyboardModifierMask)
		// - if the sequence is only a special character then print string from the lookup table
		// - if the sequence contains also a non-special character then call QKeySequence method toString
		app::commands::KeyInfo seqInfo(*cIter);
		LOG_INFO(app::logger::info_level_e::ZERO, keySequenceString, "Processing key " << seqInfo.toString(format));
		keySeqList.append(seqInfo.toString(format));
	}

	QString separator(",");
	const QString keyStr(keySeqList.join(separator));

	return keyStr;
}

std::string app::commands::KeySequence::toStdString(const QKeySequence::SequenceFormat format) const {
	QString keyQStr(this->toString(format));
	return keyQStr.toStdString();
}

CONST_GETTER(app::commands::KeySequence::getSeqVec, QVector<QKeySequence> &, this->keySeqVec)

QKeySequence::SequenceMatch app::commands::KeySequence::matches(const app::commands::KeySequence & otherSeq) const {
	const unsigned int thisSize = this->count();
	const unsigned int otherSize = otherSeq.count();

	// if this object vector has more than elements than the other one, then there is no match
	if (thisSize > otherSize) {
		return QKeySequence::NoMatch;
	}

	const QVector<QKeySequence> otherKeySeq(otherSeq.getSeqVec());

	for (QVector<QKeySequence>::const_iterator cIter = this->keySeqVec.cbegin(), cOtherIter = otherKeySeq.cbegin(); cIter != this->keySeqVec.cend(); cIter++, cOtherIter++) {
		// if elements are different. then return NoMatch
		if (*cIter != *cOtherIter) {
			return QKeySequence::NoMatch;
		}
	}

	QKeySequence::SequenceMatch match = QKeySequence::ExactMatch;

	// if this object has less elements than the other one, we can have a partial match
	if (thisSize < otherSize) {
		match = QKeySequence::PartialMatch;
	}

	return match;
}

// Operator overloading
bool app::commands::KeySequence::operator< (const app::commands::KeySequence & otherSeq) const {
	QVector<QKeySequence> otherKeySeq(otherSeq.getSeqVec());
	bool cmp = std::lexicographical_compare(this->keySeqVec.cbegin(), this->keySeqVec.cend(), otherKeySeq.cbegin(), otherKeySeq.cend());
	return cmp;
}

bool app::commands::KeySequence::operator> (const app::commands::KeySequence & otherSeq) const {
	return (otherSeq < *this);
}

bool app::commands::KeySequence::operator>= (const app::commands::KeySequence & otherSeq) const {
	return !(*this < otherSeq);
}

bool app::commands::KeySequence::operator<= (const app::commands::KeySequence & otherSeq) const {
	return !(otherSeq < *this);
}

bool app::commands::KeySequence::operator== (const app::commands::KeySequence & otherSeq) const {
	// If the length of the two key sequences are different, they cannot be equal
	if (this->count() != otherSeq.count()) {
		return false;
	}

	QVector<QKeySequence> otherKeySeq(otherSeq.getSeqVec());

	bool equal = true;

	//for (QVector<QKeySequence>::const_iterator cIter = this->keySeqVec.cbegin(), QVector<QKeySequence>::const_iterator cOtherIter = otherKeySeq.cbegin(); cIter != this->keySeqVec.cend(); cIter++, cOtherIter++) {
	for (QVector<QKeySequence>::const_iterator cIter = this->keySeqVec.cbegin(), cOtherIter = otherKeySeq.cbegin(); cIter != this->keySeqVec.cend(); cIter++, cOtherIter++) {
		// if elements are different. then set equal to false
		if (*cIter != *cOtherIter) {
			equal = false;
		}
	}
	return equal;
}

bool app::commands::KeySequence::operator!= (const app::commands::KeySequence & otherSeq) const {
	return !(*this == otherSeq);
}

int app::commands::KeySequence::operator[] (const int & index) const {
	return this->getIntKey(index);
}

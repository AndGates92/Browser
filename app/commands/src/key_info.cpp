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
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, keyInfoOverall,  "Key Sequence constructor");
	this->key = keySeq;

}

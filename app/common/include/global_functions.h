#ifndef GLOBAL_FUNCTIONS_H
#define GLOBAL_FUNCTIONS_H
/**
 * @copyright
 * @file global_functions.h
 * @author Andrea Gianarda
 * @date 19th of February 2020
 * @brief Global Functions header file
*/

#include <string>

#include <qt5/QtCore/QMetaEnum>
#include <qt5/QtCore/QVariant>

#include "exception_macros.h"

/** @defgroup GlobalFunctionsGroup Global Functions Doxygen Group
 *  Global Functions
 *  @{
 */
namespace global_functions {

	/**
	 * @brief Function: QString qEnumToQString(const qenum value)
	 *
	 * \param value: enumerator to be converted to a string
	 *
	 * \return enumerator converted to a std::string
	 *
	 * This function converts an enumerator registered with the Qt Meta-Object system to a string
	 */
	template<typename qenum>
	QString qEnumToQString(const qenum value);
}
/** @} */ // End of GlobalFunctionsGroup group

template<typename qenum>
QString global_functions::qEnumToQString(const qenum value) {

	QMetaEnum metaEnum(QMetaEnum::fromType<qenum>());
	// Convert enumeration value to std::string
	// Cast value to int to comply with function definition
	std::string valueStr = metaEnum.valueToKey(int(value));

	QEXCEPTION_ACTION_COND((valueStr.empty() == true), throw,  "Convertion of enuerator " << metaEnum.scope() << "::" << metaEnum.name() << " to string return a null std::string");

	QString fullValueStr(QString::null);
	fullValueStr.append(metaEnum.scope());
	fullValueStr.append("::");
	fullValueStr.append(metaEnum.name());
	fullValueStr.append("::");
	fullValueStr.append(valueStr.c_str());

	return fullValueStr;
}

#endif // GLOBAL_FUNCTIONS_H

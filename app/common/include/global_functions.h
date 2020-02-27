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
	 * @brief Function: QString qEnumToQString(const qenum value, const bool printEnumKeyOnly = false)
	 *
	 * \param value: enumerator to be converted to a string
	 * \param printEnumKeyOnly: boolean to choose whether the namespace and enumerator type name are printed. True means print only enumator key and false means print key as well as scope and type name
	 *
	 * \return enumerator converted to a QString
	 *
	 * This function converts an enumerator registered with the Qt Meta-Object system to a QString
	 */
	template<typename qenum>
	QString qEnumToQString(const qenum value, const bool printEnumKeyOnly = false);
}
/** @} */ // End of GlobalFunctionsGroup group

template<typename qenum>
QString global_functions::qEnumToQString(const qenum value, const bool printEnumKeyOnly) {

	QMetaEnum metaEnum(QMetaEnum::fromType<qenum>());
	// Convert enumeration value to std::string
	// Cast value to int to comply with function definition
	std::string valueStr = metaEnum.valueToKey(int(value));

	QEXCEPTION_ACTION_COND((valueStr.empty() == true), throw,  "Convertion of enuerator " << metaEnum.scope() << "::" << metaEnum.name() << " to string return a null std::string");

	QString fullValueStr(QString::null);

	if (printEnumKeyOnly == false) {
		fullValueStr.append(metaEnum.scope());
		fullValueStr.append("::");
		fullValueStr.append(metaEnum.name());
		fullValueStr.append("::");
	}

	fullValueStr.append(valueStr.c_str());

	return fullValueStr;
}

#endif // GLOBAL_FUNCTIONS_H

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
#include <list>

#include <qt5/QtCore/QMetaEnum>

#include "logging_macros.h"
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

	/**
	 * @brief Function: void moveListElements(std::list<type> & l, cons int & from, const int & to)
	 *
	 * \param l: list whose elements are to be moved
	 * \param from: position where the element to move is
	 * \param to: position where the element has to be moved
	 *
	 * This function moves an element of the list l from position from to position to
	 */
	template<typename type>
	void moveListElements(std::list<type> & l, const int & from, const int & to);

	/**
	 * @brief Function: std::string readFile(const std::string & filename)
	 *
	 * \param filename: file to read
	 *
	 * \return: content of the file
	 *
	 * This function reads a file and returns its content
	 */
	std::string readFile(const std::string & filename);

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

template<typename type>
void global_functions::moveListElements(std::list<type> & l, const int & from, const int & to) {

	if (from != to) {
		const int lSize = l.size();

		auto fromIter = l.begin();
		QEXCEPTION_ACTION_COND((lSize < from), throw,  "Trying to access element at position " << from << " of a list that has " << lSize << " elements");
		std::advance(fromIter, from);

		auto toAdjustedIter = l.begin();
		// If from < to, we want to move the tab after index to meaning that we want to add it after index to, i.e. before the tab after index to
		// Assume tabs: a b c
		// Scenarion 1 (from < to):
		// Move a at the position of c -> copy a after c (i.e. before index of c + 1) leading to the following situation a b c aCopy and then delete a
		// Result: b c aCopy
		// Scenarion 2 (from > to):
		// Move c at the position of a -> copy c after a (i.e. before index of a + 1) leading to the following scenario cCopy a b c and then delete c
		// Result: cCopy a b
		const int adjustment = (from < to) ? 1 : 0;
		const int toAdjusted = to + adjustment;
		QEXCEPTION_ACTION_COND((lSize < toAdjusted), throw,  "Trying to move element at position " << from << " to position " << to << " of a list that has " << lSize << " elements");
		if (toAdjusted == lSize) {
			toAdjustedIter = l.end();
		} else {
			std::advance(toAdjustedIter, toAdjusted);
		}

		// copy element at index from at index to
		l.emplace(toAdjustedIter, *fromIter);

		// Delete element at position from as it has already copied at position to
		l.erase(fromIter);
	}

}

#endif // GLOBAL_FUNCTIONS_H

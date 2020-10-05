#ifndef QT_TYPES_TO_STL_H
#define QT_TYPES_TO_STL_H
/**
 * @copyright
 * @file qt_types_to_stl.h
 * @author Andrea Gianarda
 * @date 19th of September 2020
 * @brief Qt Types To STL header file
*/

#include <algorithm>
#include <string>
#include <list>

#include <QtCore/QStringList>

/** @defgroup QtTypesToStlGroup Qt Types To STL Doxygen Group
 *  Qt Types To STL
 *  @{
 */

namespace qt_types_to_stl {

	/**
	 * @brief Function: const std::list<std::string> qStringListToStdList(const QStringList & qtList)
	 *
	 * \param qtList: string list to convert to an list of std::string
	 *
	 * \return: list of std::string
	 *
	 * This function converts a QStringList to a list of std::string
	 */
	const std::list<std::string> qStringListToStdList(const QStringList & qtList);

	/**
	 * @brief Function: const std::map<std::string, std::string> qMapOfqStringToStdMapofStdStrings(const QMap<QString, QString> & qtMap)
	 *
	 * \param qtList: string list to convert to an list of std::string
	 *
	 * \return: list of std::string
	 *
	 * This function converts a QStringList to a list of std::string
	 */
	const std::map<std::string, std::string> qMapOfqStringToStdMapofStdStrings(const QMap<QString, QString> & qtMap);

}
/** @} */ // End of QtTypesToStlGroup group

#endif // QT_TYPES_TO_STL_H

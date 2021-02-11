#ifndef APP_CONSTANTS_H
#define APP_CONSTANTS_H
/**
 * @copyright
 * @file constants.h
 * @author Andrea Gianarda
 * @date 2nd of May 2020
 * @brief Global Constants file
*/

#include <QtCore/QString>

/** @defgroup SharedGroup Shared Macros and Functions Doxygen Group
 *  Shared Macros and Functions
 *  @{
 */
namespace app {

	namespace shared {

		/**
		 * @brief QModifier mask
		 *
		 */
		constexpr int qmodifierMask = (int)Qt::NoModifier | (int)Qt::ShiftModifier | (int)Qt::ControlModifier | (int)Qt::AltModifier | (int)Qt::MetaModifier | (int)Qt::KeypadModifier | (int)Qt::GroupSwitchModifier;

		/**
		 * @brief https string
		 *
		 */
		const QString https("https://");

		/**
		 * @brief www string
		 *
		 */
		const QString www("www.");

		/**
		 * @brief String with white-spaces as defined by the current C locale:
		 * - ' ': space
		 * - \r: carriage return
		 * - \n: line feed
		 * - \t: horizontal tab
		 * - \v: vertical tab
		 * - \f: form feed
		 *
		 */
		static const std::string whiteSpaces(" \n\t\v\f\r");

	}

}

/** @} */ // End of SharedGroup group

#endif // APP_CONSTANTS_H

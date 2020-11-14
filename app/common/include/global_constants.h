#ifndef GLOBAL_CONSTANTS_H
#define GLOBAL_CONSTANTS_H
/**
 * @copyright
 * @file global_constants.h
 * @author Andrea Gianarda
 * @date 2nd of May 2020
 * @brief Global Constants file
*/

#include <QtCore/QString>

/** @defgroup CommonGroup Common Macros and Functions Doxygen Group
 *  Common Macros and Functions
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

	}

}

/** @} */ // End of CommonGroup group

#endif // GLOBAL_CONSTANTS_H

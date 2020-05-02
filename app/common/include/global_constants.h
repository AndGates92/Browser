#ifndef GLOBAL_CONSTANTS_H
#define GLOBAL_CONSTANTS_H
/**
 * @copyright
 * @file global_constants.h
 * @author Andrea Gianarda
 * @date 2nd of May 2020
 * @brief Global Constants file
*/

/** @defgroup GlobalConstantsGroup Global Constants Doxygen Group
 *  Global Constants
 *  @{
 */
namespace global_constants {

	/**
	 * @brief QModifier mask
	 *
	 */
	constexpr int qmodifierMask = (int)Qt::NoModifier | (int)Qt::ShiftModifier | (int)Qt::ControlModifier | (int)Qt::AltModifier | (int)Qt::MetaModifier | (int)Qt::KeypadModifier | (int)Qt::GroupSwitchModifier;

}

/** @} */ // End of GlobalConstantsGroup group

#endif // GLOBAL_CONSTANTS_H

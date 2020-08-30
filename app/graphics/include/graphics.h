#ifndef GRAPHICS_H
#define GRAPHICS_H
/**
 * @copyright
 * @file graphics.h
 * @author Andrea Gianarda
 * @date 17th of September 2019
 * @brief Graphics header file
*/

#include <QtCore/QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(graphicsOverall)

/** @defgroup GraphicsGroup Graphics Doxygen Group
 *  Graphics functions and classes
 *  @{
 */
namespace graphics {

	/**
	 * @brief Function: void init_graphics(int argc, char** argv)
	 *
	 * \param argc: number of arguments
	 * \param argv: value of arguments
	 *
	 * This function initialize graphics
	 */
	void init_graphics(int & argc, char** argv);

}
/** @} */ // End of GraphicsGroup group

#endif // GRAPHICS_H

#ifndef INIT_H
#define INIT_H
/**
 * @copyright
 * @file init.h
 * @author Andrea Gianarda
 * @date 11th of November 2020
 * @brief Initialization header file
*/

/** @defgroup InitializeGroup Initialize Doxygen Group
 *  Initialize functions and classes
 *  @{
 */
namespace init {

	/**
	 * @brief Function: void initializeBrowser(int argc, char** argv)
	 *
	 * \param argc: number of arguments
	 * \param argv: value of arguments
	 *
	 * This function is a wrapper that call all initialize functions
	 */
	void initializeBrowser(int & argc, char** argv);

	/**
	 * @brief Function: void initializeSettings(int argc, char** argv)
	 *
	 * \param argc: number of arguments
	 * \param argv: value of arguments
	 *
	 * This function initialize settings
	 */
	void initializeSettings(int & argc, char** argv);

	/**
	 * @brief Function: void initializeGraphics(int argc, char** argv)
	 *
	 * \param argc: number of arguments
	 * \param argv: value of arguments
	 *
	 * This function initialize graphics
	 */
	void initializeGraphics(int & argc, char** argv);

}
/** @} */ // End of InitGroup group

#endif // INIT_H

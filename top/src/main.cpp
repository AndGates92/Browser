/**
 * @copyright
 * @file main.cpp
 * @author Andrea Gianarda
 * @date 15th September 2019
 * @brief Main function of the program
 */

#include <iostream>

#include "graphics.h"

/** @addtogroup MainGroup
 *  @{
 */
/** 
 * @brief Function: int main (int argc, char * argv[])
 *
 * \param argc: argument count. Number of arguments including the executable itself.
 * \param argv: argument vector. The first argument is the executable name. Last element of the array is NULL.
 * \return an integer corresponging to the exit status
 *
 * Decodes the arguments and call functions for further processing
 *
 */

int main (int argc, char* argv[]) {
	graphics::init_graphics(argc, argv);

	return EXIT_SUCCESS;
}

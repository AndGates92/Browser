#ifndef APP_CLASSES_H
#define APP_CLASSES_H
/**
 * @copyright
 * @file classes.h
 * @author Andrea Gianarda
 * @date 19th of February 2020
 * @brief Global Classes header file
*/

#include <string>
#include <QtWidgets/QAction>

/** @defgroup SharedGroup Shared Macros and Functions Doxygen Group
 *  Shared Macros and Functions
 *  @{
 */

namespace app {

	namespace shared {

		/**
		 * @brief StringCompare struct
		 *
		 */
		struct StringCompare {
			// Struct sets the default access to public
			/**
			 * @brief Function: bool operator() (const std::string & rhs, const std::string & lhs) const
			 *
			 * \param rhs: string to compare
			 * \param lhs: string to compare
			 *
			 * \return: true if the two strings are identical, false otherwise
			 *
			 * This function compares two std::string objects
			 */
			bool operator() (const std::string & rhs, const std::string & lhs) const;
		};

		/**
		 * @brief QActionCompare struct
		 *
		 */
		struct QActionCompare {
			// Struct sets the default access to public
			/**
			 * @brief Function: bool operator() (const QAction & lhs, const QAction & rhs) const
			 *
			 * \param rhs: QAction to compare
			 * \param lhs: QAction to compare
			 *
			 * \return: true if the two QActions are identical, false otherwise
			 *
			 * This function compares two QAction objects
			 */
			bool operator() (const QAction & lhs, const QAction & rhs) const;
		};


	}

}
/** @} */ // End of SharedGroup group

#endif // APP_CLASSES_H

#ifndef MAIN_WINDOW_TAB_TYPES_H
#define MAIN_WINDOW_TAB_TYPES_H
/**
 * @copyright
 * @file types.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Main Window Tab Types header file
*/

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */
namespace app {

	namespace main_window {

		namespace tab {

			/**
			 * @brief search data changed
			 *
			 */
			typedef struct search_data_t {
				const int activeMatch;       /**< active match */
				const int numberOfMatches;   /**< total number of matches */
			} search_data_s;

		}

	}

}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_TAB_TYPES_H

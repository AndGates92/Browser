#ifndef MAIN_WINDOW_SHARED_TYPES_H
#define MAIN_WINDOW_SHARED_TYPES_H
/**
 * @copyright
 * @file main_window_shared_types.h
 * @author Andrea Gianarda
 * @date 21st of December 2019
 * @brief Main Window Shared Types file
*/

#include <qt5/QtCore/QtDebug>

/** @defgroup MainWindowSharedTypesGroup Main Window Shared Types Doxygen Group
 *  Main Window Shared Types
 *  @{
 */
namespace main_window_shared_types {

	/**
	 * @brief list of objects to execute actions on 
	 *
	 */
	typedef enum class object_type_list {
		CURSOR,              /**< cursor */
		TAB,                 /**< tab */
		UNKNOWN              /**< unknown object */
	} object_type_e;

	/**
	 * @brief Function: QDebug & operator<< (QDebug & os, const main_window::MainWindow::object_type_e & object)
	 *
	 * \param os: output stream
	 * \param object: object type the action is applied on
	 *
	 * Overload << operator to print they object type the action is execute on
	 */
	QDebug & operator<< (QDebug & os, const main_window_shared_types::object_type_e & object);

}

/** @} */ // End of MainWindowSharedTypesGroup group

#endif // MAIN_WINDOW_SHARED_TYPES_H

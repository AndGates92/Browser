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

	Q_NAMESPACE

	/**
	 * @brief states
	 *
	 */
	typedef enum class state_list {
		IDLE,             /**< Idle state - no user input */
		COMMAND,          /**< Typing command */
		OPEN_TAB,         /**< Open new tab */
		CLOSE_TAB,        /**< Close tab */
		REFRESH_TAB,      /**< Refresh tab */
		MOVE_LEFT,        /**< Move to tab to the left */
		MOVE_RIGHT,       /**< Move to tab to the right */
		TAB_MOVE,         /**< Move tab */
		SEARCH            /**< Search on same tab */
	} state_e;

	/**
	 * @brief register state_e with meta-object system
	 *
	 */
	Q_ENUM_NS(main_window_shared_types::state_e)

	/**
	 * @brief Function: QDebug & operator<< (QDebug & os, const main_window_shared_types::state_e & state)
	 *
	 * \param os: output stream
	 * \param state: state of the main window controller
	 *
	 * Overload << operator to print state
	 */
	QDebug & operator<< (QDebug & os, const main_window_shared_types::state_e & state);

	/**
	 * @brief Function: QTextStream & operator<< (QTextStream & str, const main_window_shared_types::state_e & state)
	 *
	 * \param str: text stream
	 * \param state: state of the main window controller
	 *
	 * Overload << operator to print state
	 */
	QTextStream & operator<< (QTextStream & str, const main_window_shared_types::state_e & state);

	/**
	 * @brief Function: QString & operator<< (QString & str, const main_window_shared_types::state_e & state)
	 *
	 * \param str: text stream
	 * \param state: state of the main window controller
	 *
	 * Overload << operator to print state
	 */
	QString operator<< (const QString & str, const main_window_shared_types::state_e & state);

	/**
	 * @brief Function: const QString operator<< (const QString & str, const main_window_shared_types::state_e & state)
	 *
	 * \param str: text stream
	 * \param state: state of the main window controller
	 *
	 * Overload + operator to print state
	 */
	const QString operator+ (const QString & str, const main_window_shared_types::state_e & state);

	/**
	 * @brief move info
	 *
	 */
	typedef enum class move_value_list {
		IDLE,             /**< Idle state - no user input */
		LEFT,             /**< Left movement */
		RIGHT,            /**< Right movement */
		ABSOLUTE          /**< Absolute value - action on the tab index equal to value */
	} move_value_e;

	/**
	 * @brief register move_value_e with meta-object system
	 *
	 */
	Q_ENUM_NS(main_window_shared_types::move_value_e)

	/**
	 * @brief Function: QDebug & operator<< (QDebug & os, const main_window_shared_types::move_value_e & value_type)
	 *
	 * \param os: output stream
	 * \param value_type: move type
	 *
	 * Overload << operator to print the move type
	 */
	QDebug & operator<< (QDebug & os, const main_window_shared_types::move_value_e & value_type);

	/**
	 * @brief Function: QTextStream & operator<< (QTextStream & str, const main_window_shared_types::move_value_e & value_type)
	 *
	 * \param str: text stream
	 * \param value_type: move type
	 *
	 * Overload << operator to print the move type
	 */
	QTextStream & operator<< (QTextStream & str, const main_window_shared_types::move_value_e & value_type);

	/**
	 * @brief Function: QString & operator<< (QString & str, const main_window_shared_types::move_value_e & value_type)
	 *
	 * \param str: text stream
	 * \param value_type: move type
	 *
	 * Overload << operator to print the move type
	 */
	QString operator<< (const QString & str, const main_window_shared_types::move_value_e & value_type);

	/**
	 * @brief Function: const QString operator+ (const QString & str, const main_window_shared_types::move_value_e & value_type)
	 *
	 * \param str: text stream
	 * \param value_type: move type
	 *
	 * Overload + operator to print the move type
	 */
	const QString operator+ (const QString & str, const main_window_shared_types::move_value_e & value_type);

	/**
	 * @brief text action 
	 *
	 */
	typedef enum class text_action_list {
		SET,              /**< Set text */
		APPEND,           /**< Append text */
		CLEAR             /**< Clear text */
	} text_action_e;

	/**
	 * @brief register text_action_e with meta-object system
	 *
	 */
	Q_ENUM_NS(main_window_shared_types::text_action_e)

	/**
	 * @brief Function: QDebug & operator<< (QDebug & os, const main_window_shared_types::text_action_e & action)
	 *
	 * \param os: output stream
	 * \param action: action applied on the text in the status bar
	 *
	 * Overload << operator to print text action in the status bar
	 */
	QDebug & operator<< (QDebug & os, const main_window_shared_types::text_action_e & action);

	/**
	 * @brief Function: QTextStream & operator<< (QTextStream & str, const main_window_shared_types::text_action_e & action)
	 *
	 * \param str: text stream
	 * \param action: action applied on the text in the status bar
	 *
	 * Overload << operator to print text action in the status bar
	 */
	QTextStream & operator<< (QTextStream & str, const main_window_shared_types::text_action_e & action);

	/**
	 * @brief Function: QString & operator<< (QString & str, const main_window_shared_types::text_action_e & action)
	 *
	 * \param str: text stream
	 * \param action: action applied on the text in the status bar
	 *
	 * Overload << operator to print text action in the status bar
	 */
	QString operator<< (const QString & str, const main_window_shared_types::text_action_e & action);

	/**
	 * @brief Function: const QString operator+ (const QString & str, const main_window_shared_types::text_action_e & action)
	 *
	 * \param str: text stream
	 * \param action: action applied on the text in the status bar
	 *
	 * Overload + operator to print text action in the status bar
	 */
	const QString operator+ (const QString & str, const main_window_shared_types::text_action_e & action);

	/**
	 * @brief text action
	 *
	 */
	typedef enum class tab_type_list {
		WEB_ENGINE,       /**< Tab type is a web engine */
		LABEL,            /**< Tab type is QLabel */
		UNKNOWN           /**< Tab type is unknown */
	} tab_type_e;

	/**
	 * @brief register tab_type_e with meta-object system
	 *
	 */
	Q_ENUM_NS(main_window_shared_types::tab_type_e)

	/**
	 * @brief Function: QDebug & operator<< (QDebug & os, const main_window_shared_types::tab_type_e & type)
	 *
	 * \param os: output stream
	 * \param type: type of the tab
	 *
	 * Overload << operator to print text type
	 */
	QDebug & operator<< (QDebug & os, const main_window_shared_types::tab_type_e & type);

	/**
	 * @brief Function: QTextStream & operator<< (QTextStream & str, const main_window_shared_types::tab_type_e & type)
	 *
	 * \param str: text stream
	 * \param type: type of the tab
	 *
	 * Overload << operator to print text type
	 */
	QTextStream & operator<< (QTextStream & str, const main_window_shared_types::tab_type_e & type);

	/**
	 * @brief Function: QString & operator<< (QString & str, const main_window_shared_types::tab_type_e & type)
	 *
	 * \param str: text stream
	 * \param type: type of the tab
	 *
	 * Overload << operator to print text type
	 */
	QString operator<< (const QString & str, const main_window_shared_types::tab_type_e & type);

	/**
	 * @brief Function: const QString operator+ (const QString & str, const main_window_shared_types::tab_type_e & type)
	 *
	 * \param str: text stream
	 * \param type: type of the tab
	 *
	 * Overload + operator to print text type
	 */
	const QString operator+ (const QString & str, const main_window_shared_types::tab_type_e & type);

}

/** @} */ // End of MainWindowSharedTypesGroup group

#endif // MAIN_WINDOW_SHARED_TYPES_H

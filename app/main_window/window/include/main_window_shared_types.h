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
	Q_ENUM_NS(state_list)

	/**
	 * @brief Function: QDebug & operator<< (QDebug & os, const main_window_shared_types::state_e & value)
	 *
	 * \param os: output stream
	 * \param value: state of the main window controller
	 *
	 * Overload << operator to print state
	 */
	QDebug & operator<< (QDebug & os, const main_window_shared_types::state_e & value);

	/**
	 * @brief Function: QTextStream & operator<< (QTextStream & str, const main_window_shared_types::state_e & value)
	 *
	 * \param str: text stream
	 * \param value: state of the main window controller
	 *
	 * Overload << operator to print state
	 */
	QTextStream & operator<< (QTextStream & str, const main_window_shared_types::state_e & value);

	/**
	 * @brief Function: QString & operator<< (QString & str, const main_window_shared_types::state_e & value)
	 *
	 * \param str: text stream
	 * \param value: state of the main window controller
	 *
	 * Overload << operator to print state
	 */
	QString & operator<< (QString & str, const main_window_shared_types::state_e & value);

	/**
	 * @brief Function: const QString operator<< (const QString & str, const main_window_shared_types::state_e & value)
	 *
	 * \param str: text stream
	 * \param value: state of the main window controller
	 *
	 * Overload + operator to print state
	 */
	const QString operator+ (const QString & str, const main_window_shared_types::state_e & value);

	/**
	 * @brief Function: const std::string operator+ (const char * str, const main_window_shared_types::state_e & value)
	 *
	 * \param str: text stream
	 * \param value: state of the main window controller
	 *
	 * Overload + operator to print state
	 */
	const std::string operator+ (const char * str, const main_window_shared_types::state_e & value);

	/**
	 * @brief Function: const std::string operator+ (const std::string & str, const main_window_shared_types::state_e & value)
	 *
	 * \param str: text stream
	 * \param value: state of the main window controller
	 *
	 * Overload + operator to print state
	 */
	const std::string operator+ (const std::string & str, const main_window_shared_types::state_e & value);

	/**
	 * @brief move info
	 *
	 */
	typedef enum class offset_type_list {
		IDLE,             /**< Idle state - no user input */
		LEFT,             /**< Left movement */
		RIGHT,            /**< Right movement */
		ABSOLUTE          /**< Absolute value - action on the tab index equal to value */
	} offset_type_e;

	/**
	 * @brief register offset_type_e with meta-object system
	 *
	 */
	Q_ENUM_NS(offset_type_list)

	/**
	 * @brief Function: QDebug & operator<< (QDebug & os, const main_window_shared_types::offset_type_e & value)
	 *
	 * \param os: output stream
	 * \param value: move type
	 *
	 * Overload << operator to print the move type
	 */
	QDebug & operator<< (QDebug & os, const main_window_shared_types::offset_type_e & value);

	/**
	 * @brief Function: QTextStream & operator<< (QTextStream & str, const main_window_shared_types::offset_type_e & value)
	 *
	 * \param str: text stream
	 * \param value: move type
	 *
	 * Overload << operator to print the move type
	 */
	QTextStream & operator<< (QTextStream & str, const main_window_shared_types::offset_type_e & value);

	/**
	 * @brief Function: QString & operator<< (QString & str, const main_window_shared_types::offset_type_e & value)
	 *
	 * \param str: text stream
	 * \param value: move type
	 *
	 * Overload << operator to print the move type
	 */
	QString & operator<< (QString & str, const main_window_shared_types::offset_type_e & value);

	/**
	 * @brief Function: const QString operator+ (const QString & str, const main_window_shared_types::offset_type_e & value)
	 *
	 * \param str: text stream
	 * \param value: move type
	 *
	 * Overload + operator to print the move type
	 */
	const QString operator+ (const QString & str, const main_window_shared_types::offset_type_e & value);

	/**
	 * @brief Function: const std::string operator+ (const char * str, const main_window_shared_types::offset_type_e & value)
	 *
	 * \param str: text stream
	 * \param value: move type
	 *
	 * Overload + operator to print text move
	 */
	const std::string operator+ (const char * str, const main_window_shared_types::offset_type_e & value);

	/**
	 * @brief Function: const std::string operator+ (const std::string & str, const main_window_shared_types::offset_type_e & value)
	 *
	 * \param str: text stream
	 * \param value: move type
	 *
	 * Overload + operator to print text move
	 */
	const std::string operator+ (const std::string & str, const main_window_shared_types::offset_type_e & value);

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
	Q_ENUM_NS(text_action_list)

	/**
	 * @brief Function: QDebug & operator<< (QDebug & os, const main_window_shared_types::text_action_e & value)
	 *
	 * \param os: output stream
	 * \param value: action applied on the text in the status bar
	 *
	 * Overload << operator to print text action in the status bar
	 */
	QDebug & operator<< (QDebug & os, const main_window_shared_types::text_action_e & value);

	/**
	 * @brief Function: QTextStream & operator<< (QTextStream & str, const main_window_shared_types::text_action_e & value)
	 *
	 * \param str: text stream
	 * \param value: action applied on the text in the status bar
	 *
	 * Overload << operator to print text action in the status bar
	 */
	QTextStream & operator<< (QTextStream & str, const main_window_shared_types::text_action_e & value);

	/**
	 * @brief Function: QString & operator<< (QString & str, const main_window_shared_types::text_action_e & value)
	 *
	 * \param str: text stream
	 * \param value: action applied on the text in the status bar
	 *
	 * Overload << operator to print text action in the status bar
	 */
	QString & operator<< (QString & str, const main_window_shared_types::text_action_e & value);

	/**
	 * @brief Function: const QString operator+ (const QString & str, const main_window_shared_types::text_action_e & value)
	 *
	 * \param str: text stream
	 * \param value: action applied on the text in the status bar
	 *
	 * Overload + operator to print text action in the status bar
	 */
	const QString operator+ (const QString & str, const main_window_shared_types::text_action_e & value);

	/**
	 * @brief Function: const std::string operator+ (const char * str, const main_window_shared_types::text_action_e & value)
	 *
	 * \param str: text stream
	 * \param value: action applied on the text in the status bar
	 *
	 * Overload + operator to print text action
	 */
	const std::string operator+ (const char * str, const main_window_shared_types::text_action_e & value);

	/**
	 * @brief Function: const std::string operator+ (const std::string & str, const main_window_shared_types::text_action_e & value)
	 *
	 * \param str: text stream
	 * \param value: action applied on the text in the status bar
	 *
	 * Overload + operator to print text action
	 */
	const std::string operator+ (const std::string & str, const main_window_shared_types::text_action_e & value);

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
	Q_ENUM_NS(tab_type_list)

	/**
	 * @brief Function: QDebug & operator<< (QDebug & os, const main_window_shared_types::tab_type_e & value)
	 *
	 * \param os: output stream
	 * \param value: type of the tab
	 *
	 * Overload << operator to print text type
	 */
	QDebug & operator<< (QDebug & os, const main_window_shared_types::tab_type_e & value);

	/**
	 * @brief Function: QTextStream & operator<< (QTextStream & str, const main_window_shared_types::tab_type_e & value)
	 *
	 * \param str: text stream
	 * \param value: type of the tab
	 *
	 * Overload << operator to print text type
	 */
	QTextStream & operator<< (QTextStream & str, const main_window_shared_types::tab_type_e & value);

	/**
	 * @brief Function: QString & operator<< (QString & str, const main_window_shared_types::tab_type_e & value)
	 *
	 * \param str: text stream
	 * \param value: type of the tab
	 *
	 * Overload << operator to print text type
	 */
	QString & operator<< (QString & str, const main_window_shared_types::tab_type_e & value);

	/**
	 * @brief Function: const QString operator+ (const QString & str, const main_window_shared_types::tab_type_e & value)
	 *
	 * \param str: text stream
	 * \param value: type of the tab
	 *
	 * Overload + operator to print text type
	 */
	const QString operator+ (const QString & str, const main_window_shared_types::tab_type_e & value);

	/**
	 * @brief Function: const std::string operator+ (const char * str, const main_window_shared_types::tab_type_e & value)
	 *
	 * \param str: text stream
	 * \param value: type of the tab
	 *
	 * Overload + operator to print text type
	 */
	const std::string operator+ (const char * str, const main_window_shared_types::tab_type_e & value);

	/**
	 * @brief Function: const std::string operator+ (const std::string & str, const main_window_shared_types::tab_type_e & value)
	 *
	 * \param str: text stream
	 * \param value: type of the tab
	 *
	 * Overload + operator to print text type
	 */
	const std::string operator+ (const std::string & str, const main_window_shared_types::tab_type_e & value);

}

/** @} */ // End of MainWindowSharedTypesGroup group

#endif // MAIN_WINDOW_SHARED_TYPES_H

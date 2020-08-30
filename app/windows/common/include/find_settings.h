#ifndef FIND_SETTINGS_H
#define FIND_SETTINGS_H
/**
 * @copyright
 * @file find_settings.h
 * @author Andrea Gianarda
 * @date 3rd of August 2020
 * @brief Find Settings header file
*/

#include <memory>

#include <QtCore/QLoggingCategory>

#include "global_enums.h"
#include "constructor_macros.h"
#include "printable_object.h"

/** @defgroup FindSettingsGroup Find Settings Doxygen Group
 *  Find Settings functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(findSettingsOverall)

namespace main_window_ctrl_tab {
	class MainWindowCtrlTab;
}

namespace find_settings {

	/**
	 * @brief FindSettings class
	 *
	 */
	class FindSettings final : public printable_object::PrintableObject {

		friend main_window_ctrl_tab::MainWindowCtrlTab;

		public:
			/**
			 * @brief Function: explicit FindSettings(const QString & initText, const global_enums::offset_type_e & initDirection, const bool & initCaseSensitive, const bool & initMatchFullWord)
			 *
			 * \param initText: text to find
			 * \param initDirection: direction of find
			 * \param initCaseSensitive: case sensitive search
			 * \param initMatchFullWord: match full word search
			 *
			 * Find settings constructor
			 */
			explicit FindSettings(const QString & initText, const global_enums::offset_type_e & initDirection, const bool & initCaseSensitive, const bool & initMatchFullWord);

			// Move and copy constructor
			/**
			 * @brief Function: FindSettings(const find_settings::FindSettings & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Find settings copy constructor
			 */
			FindSettings(const find_settings::FindSettings & rhs);

			/**
			 * @brief Function: explicit FindSettings(find_settings::FindSettings && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Find settings move constructor
			 */
			explicit FindSettings(find_settings::FindSettings && rhs);

			// Move and copy assignment operators
			/**
			 * @brief Function: FindSettings & operator=(const find_settings::FindSettings & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Find settings copy assignment operator
			 */
			FindSettings & operator=(const find_settings::FindSettings & rhs);

			/**
			 * @brief Function: FindSettings & operator=(find_settings::FindSettings && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Find settings move assignment operator
			 */
			FindSettings & operator=(find_settings::FindSettings && rhs);

			/**
			 * @brief Function: virtual ~FindSettingsSettings()
			 *
			 * Find settings window destructor
			 */
			virtual ~FindSettings();

			/**
			 * @brief Function: bool getCaseSensitive() const
			 *
			 * \return case sensitive search
			 *
			 * This function returns a boolean with the case sensitive flag
			 */
			bool getCaseSensitive() const;

			/**
			 * @brief Function: bool getMatchFullWord() const
			 *
			 * \return match full word flag
			 *
			 * This function returns a boolean with the match full word flag
			 */
			bool getMatchFullWord() const;

			/**
			 * @brief Function: global_enums::offset_type_e getDirection() const
			 *
			 * \return search direction
			 *
			 * This function returns the direction of the search
			 */
			global_enums::offset_type_e getDirection() const;

			/**
			 * @brief Function: const QString getText() const
			 *
			 * \return text to search
			 *
			 * This function returns the text to search
			 */
			const QString getText() const;

			/**
			 * @brief Function: const std::string print() const
			 *
			 * \return find settings converted to std::string
			 *
			 * This functions prints find settings info to std::string
			 */
			const std::string print() const;

		protected:

		private:

			/**
			 * @brief Function: void setCaseSensitive(const bool & value)
			 *
			 * \param value: case sensitive search
			 *
			 * This function returns a boolean with the case sensitive flag
			 */
			void setCaseSensitive(const bool & value);

			/**
			 * @brief Function: void setMatchFullWord(const bool & value)
			 *
			 * \param value: match full word flag
			 *
			 * This function returns a boolean with the match full word flag
			 */
			void setMatchFullWord(const bool & value);

			/**
			 * @brief Function: void setDirection(const global_enums::offset_type_e & value)
			 *
			 * \param value: search direction
			 *
			 * This function returns the direction of the search
			 */
			void setDirection(const global_enums::offset_type_e & value);

			/**
			 * @brief Function: void setText(const QString & value)
			 *
			 * \param value: text to search
			 *
			 * This function returns text to search
			 */
			void setText(const QString & value);

			/**
			 * @brief text to search
			 *
			 */
			 QString text;

			/**
			 * @brief direction of the search
			 *
			 */
			 global_enums::offset_type_e direction;

			/**
			 * @brief case sensitive flag
			 *
			 */
			 bool caseSensitive;

			/**
			 * @brief match full word flag
			 *
			 */
			 bool matchFullWord;

	};
}
/** @} */ // End of FindSettingsGroup group

#endif // FIND_SETTINGS_H

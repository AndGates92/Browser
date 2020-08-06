#ifndef FIND_BUTTON_WINDOW_SETTINGS_H
#define FIND_BUTTON_WINDOW_SETTINGS_H
/**
 * @copyright
 * @file find_button_window_settings.h
 * @author Andrea Gianarda
 * @date 29th of July 2020
 * @brief Find Button Window Settings header file
*/

#include <memory>

#include <QtCore/QLoggingCategory>
#include <QtWidgets/QWidget>

#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>

#include "global_enums.h"
#include "constructor_macros.h"
#include "action.h"
#include "combo_box_find.h"

/** @defgroup FindButtonWindowSettingsGroup Find Button Window Doxygen Group
 *  Find Button Window functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(findButtonWindowSettingsOverall)

namespace find_button_window_settings {

	/**
	 * @brief FindButtonWindowSettings class
	 *
	 */
	class FindButtonWindowSettings final : public QGroupBox {

		Q_OBJECT

		public:
			/**
			 * @brief Function: explicit FindButtonWindowSettings(QWidget * parent)
			 *
			 * \param parent: parent window
			 * \param flags: window flags
			 *
			 * Find button window constructor
			 */
			explicit FindButtonWindowSettings(QWidget * parent);

			/**
			 * @brief Function: virtual ~FindButtonWindowSettings()
			 *
			 * Find button window destructor
			 */
			virtual ~FindButtonWindowSettings();

			/**
			 * @brief Function: global_enums::offset_type_e getSearchDirection() const
			 *
			 * \return search direction
			 *
			 * This function returns the direction of the search
			 */
			global_enums::offset_type_e getSearchDirection() const;

			/**
			 * @brief Function: bool isCaseSensitiveSearch() const
			 *
			 * \return case sensitive check box checked boolean
			 *
			 * This function returns a boolean with the case sensitive check box state
			 */
			bool isCaseSensitiveSearch() const;

			/**
			 * @brief Function: const bool isMatchFullWordSearch() const
			 *
			 * \return match full word check box checked boolean
			 *
			 * This function returns a boolean with the match full word check box state
			 */
			bool isMatchFullWordSearch() const;

		protected:

		private slots:

		signals:

		private:
			/**
			 * @brief Function: void widgetLayout()
			 *
			 * This function creates the layout of the widget
			 */
			void widgetLayout();

			/**
			 * @brief Function: void createActions()
			 *
			 * This function creates actions for the find window settings
			 */
			void createActions();

			/**
			 * @brief Function: void fillWidget()
			 *
			 * This function creates widgets that are part of the settings widget
			 */
			void fillWidget();

			/**
			 * @brief Function: void connectSignals()
			 *
			 * This function connects signals and slots between main widget elements
			 */
			void connectSignals();

			/**
			 * @brief Function: virtual QSize sizeHint() const override
			 *
			 * \return recommended size of the widget
			 *
			 * Compute recommendend size of the widget
			 */
			virtual QSize sizeHint() const override;

			/**
			 * @brief case sensitive action
			 *
			 */
			std::unique_ptr<action::Action> caseSensitiveAction;

			/**
			 * @brief match full word only action
			 *
			 */
			std::unique_ptr<action::Action> matchFullWordOnlyAction;

			/**
			 * @brief search direction items
			 *
			 */
			std::list<combo_box_find::ComboBoxFind> directionItems;

			/**
			 * @brief find direction
			 *
			 */
			std::shared_ptr<QComboBox> findDirectionDropDown;

			/**
			 * @brief case sensitive search check box
			 *
			 */
			std::unique_ptr<QCheckBox> caseSensitiveBox;

			/**
			 * @brief match full word only check box
			 *
			 */
			std::unique_ptr<QCheckBox> matchFullWordOnlyBox;

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class FindButtonWindowSettings
			 *
			 */
			DISABLE_COPY_MOVE(FindButtonWindowSettings)

	};
}
/** @} */ // End of FindButtonWindowSettingsGroup group

#endif // FIND_BUTTON_WINDOW_SETTINGS_H

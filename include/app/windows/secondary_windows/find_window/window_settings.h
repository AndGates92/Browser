#ifndef FIND_BUTTON_WINDOW_SETTINGS_H
#define FIND_BUTTON_WINDOW_SETTINGS_H
/**
 * @copyright
 * @file window_settings.h
 * @author Andrea Gianarda
 * @date 29th of July 2020
 * @brief Find Window Settings header file
*/

#include <memory>

#include <QtCore/QLoggingCategory>
#include <QtWidgets/QWidget>

#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>

#include "app/shared/enums.h"
#include "app/shared/constructor_macros.h"
#include "app/widgets/commands/action.h"
#include "app/windows/secondary_windows/find_window/combo_box_find.h"

/** @defgroup FindWindowGroup Find Window Doxygen Group
 *  Find Window functions and classes
 *  @{
 */
namespace app {

	namespace find_window {

		/**
		 * @brief Settings class
		 *
		 */
		class Settings final : public QGroupBox {

			Q_OBJECT

			public:
				/**
				 * @brief Function: explicit Settings(QWidget * parent)
				 *
				 * \param parent: parent window
				 * \param flags: window flags
				 *
				 * Find button window constructor
				 */
				explicit Settings(QWidget * parent);

				/**
				 * @brief Function: virtual ~Settings()
				 *
				 * Find button window destructor
				 */
				virtual ~Settings();

				/**
				 * @brief Function: app::shared::offset_type_e getSearchDirection() const
				 *
				 * \return search direction
				 *
				 * This function returns the direction of the search
				 */
				app::shared::offset_type_e getSearchDirection() const;

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
				std::unique_ptr<app::action::Action> caseSensitiveAction;

				/**
				 * @brief match full word only action
				 *
				 */
				std::unique_ptr<app::action::Action> matchFullWordOnlyAction;

				/**
				 * @brief search direction items
				 *
				 */
				std::list<app::find_window::ComboBoxFind> directionItems;

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
				 * @brief Disable move and copy constructors and operator= overloading for class Settings
				 *
				 */
				DISABLE_COPY_MOVE(Settings)

		};

	}

}
/** @} */ // End of FindWindowGroup group

#endif // FIND_BUTTON_WINDOW_SETTINGS_H

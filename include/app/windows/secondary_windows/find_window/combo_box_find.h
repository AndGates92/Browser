#ifndef COMBO_BOX_FIND_H
#define COMBO_BOX_FIND_H
/**
 * @copyright
 * @file combo_box_find.h
 * @author Andrea Gianarda
 * @date 27th July 2020
 * @brief Combo Box Find file
*/

#include <memory>

// Qt libraries
#include <QtCore/QVariant>
#include <QtGui/QIcon>

#include "app/shared/enums.h"
#include "app/windows/secondary_windows/shared/combo_box_item.h"

/** @defgroup FindWindowGroup Find Window Doxygen Group
 *  Find Window functions and classes
 *  @{
 */
namespace app {

	namespace action {

		class Action;

	}

	namespace find_window {

		/**
		 * @brief Combo box find class
		 *
		 */
		class ComboBoxFind final : public app::combo_box_item::ComboBoxItem {
			public:

				/**
				 * @brief Function: explicit ComboBoxFind(const QIcon itemIcon, const QVariant itemUserData, const app::shared::offset_type_e itemDirection, std::unique_ptr<app::action::Action> itemAction)
				 *
				 * \param itemIcon: icon of the combo box item
				 * \param itemUserData: user data of the combo box item
				 * \param itemDirection: direction of search of the combo box item
				 * \param itemAction: user data of the combo box item
				 *
				 * Combo box find constructor
				 */
				explicit ComboBoxFind(const QIcon itemIcon, const QVariant itemUserData, const app::shared::offset_type_e itemDirection, std::unique_ptr<app::action::Action> itemAction);

				/**
				 * @brief Function: virtual ~ComboBoxFind()
				 *
				 * Combo box find destructor
				 */
				virtual ~ComboBoxFind();

				// Move and copy constructor
				/**
				 * @brief Function: ComboBoxFind(ComboBoxFind && rhs)
				 *
				 * \param rhs: right hand side operand
				 *
				 * Combo box find move constructor
				 */
				ComboBoxFind(app::find_window::ComboBoxFind && rhs);

				// Move and copy assignment operators
				/**
				 * @brief Function: ComboBoxFind & operator=(app::find_window::ComboBoxFind && rhs)
				 *
				 * \param rhs: class to move
				 *
				 * Command Combo box find move assignment operator
				 */
				ComboBoxFind & operator=(app::find_window::ComboBoxFind && rhs);

				/**
				 * @brief Function: const app::shared::offset_type_e & getDirection() const
				 *
				 * \return the direction of the search of a combo box find
				 *
				 * This function returns the direction of the search of a combo box find
				 */
				const app::shared::offset_type_e & getDirection() const;

			protected:

			private:
				/**
				 * @brief Function: ComboBoxFind()
				 *
				 * Combo box find default constructor
				 */
				ComboBoxFind() = delete;

				/**
				 * @brief Function: ComboBoxFind(const ComboBoxFind && rhs)
				 *
				 * \param rhs: right hand side operand
				 *
				 * Combo box find copy constructor
				 */
				ComboBoxFind(const app::find_window::ComboBoxFind & rhs) = delete;

				/**
				 * @brief Function: ComboBoxFind & operator=(const app::find_window::ComboBoxFind & rhs)
				 *
				 * \param rhs: class to copy
				 *
				 * Command Combo box find copy assignment operator
				 */
				ComboBoxFind & operator=(const app::find_window::ComboBoxFind & rhs) = delete;

				/**
				 * @brief direction of search of the combo box find
				 *
				 */
				app::shared::offset_type_e direction;

		};

	}

}
/** @} */ // End of FindWindowGroup group

#endif // COMBO_BOX_FIND_H

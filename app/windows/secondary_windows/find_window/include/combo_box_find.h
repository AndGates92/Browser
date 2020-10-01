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

#include <QtCore/QLoggingCategory>
#include <QtCore/QtDebug>
#include <QtCore/QVariant>
#include <QtGui/QIcon>

#include "global_enums.h"
#include "action.h"
#include "combo_box_item.h"

/** @defgroup ComboBoxFindGroup Combo Box Find Doxygen Group
 *  Combo Box Find header functions and class
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(comboBoxFindOverall)

namespace combo_box_find {

	class ComboBoxFind final : public combo_box_item::ComboBoxItem {
		public:

			/**
			 * @brief Function: ComboBoxFind(const QIcon itemIcon, const QVariant itemUserData, const global_enums::offset_type_e itemDirection, std::unique_ptr<action::Action> itemAction)
			 *
			 * \param itemIcon: icon of the combo box item
			 * \param itemUserData: user data of the combo box item
			 * \param itemDirection: direction of search of the combo box item
			 * \param itemAction: user data of the combo box item
			 *
			 * Combo box find constructor
			 */
			ComboBoxFind(const QIcon itemIcon, const QVariant itemUserData, const global_enums::offset_type_e itemDirection, std::unique_ptr<action::Action> itemAction);

			// Move and copy constructor
			/**
			 * @brief Function: ComboBoxFind(ComboBoxFind && rhs)
			 *
			 * \param rhs: right hand side operand
			 *
			 * Combo box find move constructor
			 */
			ComboBoxFind(combo_box_find::ComboBoxFind && rhs);

			// Move and copy assignment operators
			/**
			 * @brief Function: ComboBoxFind & operator=(combo_box_find::ComboBoxFind && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Command Combo box find move assignment operator
			 */
			ComboBoxFind & operator=(combo_box_find::ComboBoxFind && rhs);

			/**
			 * @brief Function: const global_enums::offset_type_e & getDirection() const
			 *
			 * \return the direction of the search of a combo box find
			 *
			 * This function returns the direction of the search of a combo box find
			 */
			const global_enums::offset_type_e & getDirection() const;

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
			ComboBoxFind(const combo_box_find::ComboBoxFind & rhs) = delete;

			/**
			 * @brief Function: ComboBoxFind & operator=(const combo_box_find::ComboBoxFind & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Command Combo box find copy assignment operator
			 */
			ComboBoxFind & operator=(const combo_box_find::ComboBoxFind & rhs) = delete;

			/**
			 * @brief direction of search of the combo box find
			 *
			 */
			global_enums::offset_type_e direction;

	};

}

/** @} */ // End of ComboBoxFindGroup group

#endif // COMBO_BOX_FIND_H

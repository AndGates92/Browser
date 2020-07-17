#ifndef COMBO_BOX_ITEM_H
#define COMBO_BOX_ITEM_H
/**
 * @copyright
 * @file combo_box_item.h
 * @author Andrea Gianarda
 * @date 27th July 2020
 * @brief Combo Box Item file
*/

#include <memory>

#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtCore/QtDebug>
#include <qt5/QtCore/QVariant>
#include <qt5/QtGui/QIcon>

#include "global_enums.h"
#include "action.h"

/** @defgroup ComboBoxItemGroup Combo Box Item Doxygen Group
 *  Combo Box Item header functions and class
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(comboBoxItemOverall)

namespace combo_box_item {

	class ComboBoxItem {
		public:

			/**
			 * @brief Function: ComboBoxItem(const QIcon itemIcon, const QVariant itemUserData, std::unique_ptr<action::Action> & itemAction)
			 *
			 * \param itemIcon: icon of the combo box item
			 * \param itemUserData: user data of the combo box item
			 * \param itemAction: user data of the combo box item
			 *
			 * Combo box item constructor
			 */
			ComboBoxItem(const QIcon itemIcon, const QVariant itemUserData, std::unique_ptr<action::Action> & itemAction);

			// Move and copy constructor
			/**
			 * @brief Function: ComboBoxItem(ComboBoxItem && rhs)
			 *
			 * \param rhs: right hand side operand
			 *
			 * Combo box item move constructor
			 */
			ComboBoxItem(combo_box_item::ComboBoxItem && rhs);

			// Move and copy assignment operators
			/**
			 * @brief Function: ComboBoxItem & operator=(combo_box_item::ComboBoxItem && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Command Combo box item move assignment operator
			 */
			ComboBoxItem & operator=(combo_box_item::ComboBoxItem && rhs);

			/**
			 * @brief Function: const QIcon getIcon() const
			 *
			 * \return the icon of a combo box item
			 *
			 * This function returns the icon of a combo box item
			 */
			const QIcon getIcon() const;

			/**
			 * @brief Function: const std::string getText() const
			 *
			 * \return the text of the action of a combo box item
			 *
			 * This function returns the text of the action of a combo box item
			 */
			const std::string getText() const;

			/**
			 * @brief Function: const QIcon getUserData() const
			 *
			 * \return the user data of a combo box item
			 *
			 * This function returns the user data of a combo box item
			 */
			const QVariant getUserData() const;

			/**
			 * @brief Function: const std::unique_ptr<action::Action> & getAction() const
			 *
			 * \return the action of a combo box item
			 *
			 * This function returns the action of a combo box item
			 */
			const std::unique_ptr<action::Action> & getAction() const;

		protected:

		private:
			/**
			 * @brief Function: ComboBoxItem()
			 *
			 * Combo box item default constructor
			 */
			ComboBoxItem() = delete;

			/**
			 * @brief Function: ComboBoxItem(const ComboBoxItem && rhs)
			 *
			 * \param rhs: right hand side operand
			 *
			 * Combo box item copy constructor
			 */
			ComboBoxItem(const combo_box_item::ComboBoxItem & rhs) = delete;

			/**
			 * @brief Function: ComboBoxItem & operator=(const combo_box_item::ComboBoxItem & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Command Combo box item copy assignment operator
			 */
			ComboBoxItem & operator=(const combo_box_item::ComboBoxItem & rhs) = delete;

			/**
			 * @brief icon of the combo box item
			 *
			 */
			QIcon icon;

			/**
			 * @brief user data of the combo box item
			 *
			 */
			QVariant userData;

			/**
			 * @brief action of the combo box item
			 *
			 */
			std::unique_ptr<action::Action> action;

	};

}

/** @} */ // End of ComboBoxItemGroup group

#endif // COMBO_BOX_ITEM_H

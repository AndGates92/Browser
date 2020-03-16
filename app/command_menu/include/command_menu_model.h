#ifndef COMMAND_MENU_MODEL_H
#define COMMAND_MENU_MODEL_H

/**
 * @copyright
 * @file command_menu_model.h
 * @author Andrea Gianarda
 * @date 24th of January 2020
 * @brief Command Menu Model file
*/

#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtCore/QAbstractItemModel>
#include <qt5/QtCore/QModelIndex>
#include <qt5/QtCore/QVariant>

/** @defgroup CommandMenuModelGroup Command Menu Model Doxygen Group
 *  Command Menu Model functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(commandMenuModelOverall)
Q_DECLARE_LOGGING_CATEGORY(commandMenuModelSettings)

namespace command_menu_model {
	/**
	 * @brief CommandMenuModel class
	 *
	 */
	class CommandMenuModel : public QAbstractItemModel {

		Q_OBJECT

		public:

			/**
			 * @brief Function: explicit CommandMenuModel(QObject * parent = Q_NULLPTR)
			 *
			 * \param parent: parent object
			 *
			 * Command menu model constructor
			 */
			explicit CommandMenuModel(QObject * parent = Q_NULLPTR);

			/**
			 * @brief Function: ~CommandMenuModel()
			 *
			 * Command menu model destructor
			 */
			~CommandMenuModel();

		protected:

		private:
			/**
			 * @brief Function: QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const
			 *
			 * \param row: row of the item
			 * \param column: column of the item
			 * \param parent: model item to search
			 *
			 * \return the index of the item in the model specified by the input arguments

			 * This function returns the index of the item specified by the input arguments row, column and parent
			 *
			 */
			QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;

			/**
			 * @brief Function: QModelIndex parent(const QModelIndex & child) const
			 *
			 * \param child: model item to search
			 * 
			 * \return the parent of the model item child
			 *
			 * This function returns the parent of the model item child
			 */
			QModelIndex parent(const QModelIndex & child) const;

			/**
			 * @brief Function: int rowCount(const QModelIndex & parent = QModelIndex()) const
			 *
			 * \param parent: model item to search
			 *
			 * \return the number of children of the parent
			 *
			 * This function returns the number of row of the model item parent
			 */
			int rowCount(const QModelIndex & parent = QModelIndex()) const;

			/**
			 * @brief Function: int columnCount(const QModelIndex & parent = QModelIndex()) const
			 *
			 * \param parent: model item to search
			 *
			 * \return the number of column of the parent
			 *
			 * This function returns the number of column of the model item parent
			 */
			int columnCount(const QModelIndex & parent = QModelIndex()) const;

			/**
			 * @brief Function: QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const
			 *
			 * \param index: model item to search
			 * \param role: model item to search
			 *
			 * \return the data stored under the given role for item referred by index index
			 *
			 * This function returns the data stored under the given role for item referred by index index
			 * An invalid QVariant is returned if there is no value to be returned
			 */
			QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

			// Move and copy constructor
			/**
			 * @brief Function: CommandMenuModel(const command_menu_model::CommandMenuModel & rhs)
			 *
			 * param rhs: class to copy
			 *
			 * Command Menu Model copy constructor
			 */
			explicit CommandMenuModel(const command_menu_model::CommandMenuModel & rhs) = delete;

			/**
			 * @brief Function: CommandMenuModel(command_menu_model::CommandMenuModel && rhs)
			 *
			 * param rhs: class to move
			 *
			 * Command Menu Model move constructor
			 */
			explicit CommandMenuModel(command_menu_model::CommandMenuModel && rhs) = delete;

			// Move and copy assignment operators
			/**
			 * @brief Function: CommandMenuModel & operator=(const command_menu_model::CommandMenuModel & rhs)
			 *
			 * param rhs: class to copy
			 *
			 * Command Menu Model copy assignment operator
			 */
			CommandMenuModel & operator=(const command_menu_model::CommandMenuModel & rhs) = delete;

			/**
			 * @brief Function: CommandMenuModel & operator=(command_menu_model::CommandMenuModel && rhs)
			 *
			 * param rhs: class to move
			 *
			 * Command Menu Model move assignment operator
			 */
			CommandMenuModel & operator=(command_menu_model::CommandMenuModel && rhs) = delete;


	};
}
/** @} */ // End of CommandMenuModelGroup group

#endif // COMMAND_MENU_MODEL_H

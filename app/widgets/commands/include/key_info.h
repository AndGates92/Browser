#ifndef KEY_INFO_H
#define KEY_INFO_H
/**
 * @copyright
 * @file key_info.h
 * @author Andrea Gianarda
 * @date 13th January 2020
 * @brief Key Info header file
*/

#include <unordered_map>
#include <functional>

// Qt libraries
#include <QtGui/QKeySequence>
#include <QtCore/QString>

/** @defgroup KeyInfoGroup Key Info Doxygen Group
 *  Key Info functions and classes
 *  @{
 */
namespace app {

	namespace key_info {

		/**
		 * @brief KeyInfo class
		 *
		 */
		class KeyInfo {

			public:
				/**
				 * @brief Function: explicit KeyInfo(const QKeySequence & keySeq, QKeyInfo::SequenceFormat format = QKeyInfoNativeText)
				 *
				 * \param keySeq: key sequence
				 *
				 * Key Info constructor
				 */
				explicit KeyInfo(const QKeySequence & keySeq);

				// Move and copy constructor
				/**
				 * @brief Function: KeyInfo(const app::key_info::KeyInfo & rhs)
				 *
				 * \param rhs: class to copy
				 *
				 * JSON parser copy constructor
				 */
				explicit KeyInfo(const app::key_info::KeyInfo & rhs);

				/**
				 * @brief Function: KeyInfo::KeyInfo(app::key_info::KeyInfo && rhs)
				 *
				 * \param rhs: class to move
				 *
				 * JSON parser move constructor
				 */
				explicit KeyInfo(app::key_info::KeyInfo && rhs);

				// Move and copy assignment operators
				/**
				 * @brief Function: KeyInfo & operator=(const app::key_info::KeyInfo & rhs)
				 *
				 * \param rhs: class to copy
				 *
				 * JSON parser copy assignment operator
				 */
				KeyInfo & operator=(const app::key_info::KeyInfo & rhs);

				/**
				 * @brief Function: KeyInfo & operator=(app::key_info::KeyInfo && rhs)
				 *
				 * \param rhs: class to move
				 *
				 * JSON parser move assignment operator
				 */
				KeyInfo & operator=(app::key_info::KeyInfo && rhs);

				/**
				 * @brief Function: virtual ~KeyInfo()
				 *
				 * JSON parser destructor
				 */
				virtual ~KeyInfo();

				/**
				 * @brief Function: QString toString(QKeySequence::SequenceFormat format = QKeySequence::NativeText) const
				 *
				 * \param format: format of key string
				 *
				 * \return a string with all key sequences
				 *
				 * This function returns a string with the key sequences
				 */
				QString toString(QKeySequence::SequenceFormat format = QKeySequence::NativeText) const;

			private:
				/**
				 * @brief key
				 *
				 */
				Qt::Key key;

				/**
				 * @brief modifier
				 *
				 */
				Qt::KeyboardModifier modifier;

				/**
				 * @brief Function: QString keyToString(const Qt::Key keyPrint, const QKeySequence::SequenceFormat format = QKeySequence::NativeText) const
				 *
				 * \param keyPrint: key
				 * \param format: format of key string
				 *
				 * \return a string with all key sequences
				 *
				 * This function returns a string with the key converted to a string
				 */
				QString keyToString(const Qt::Key keyPrint, const QKeySequence::SequenceFormat format = QKeySequence::NativeText) const;

				/**
				 * @brief Function: QString modifierToString(const Qt::KeyboardModifier keyPrint, const QKeySequence::SequenceFormat format = QKeySequence::NativeText) const
				 *
				 * \param modifierPrint: modifier
				 * \param format: format of key string
				 *
				 * \return a string with all key sequences
				 *
				 * This function returns a string with the modifier converted to a string 
				 */
				QString modifierToString(const Qt::KeyboardModifier modifierPrint, const QKeySequence::SequenceFormat format = QKeySequence::NativeText) const;

				/**
				 * @brief Function: bool isKeyPrintable(const Qt::Key keyCheck) const
				 *
				 * \param keyCheck: key
				 *
				 * \return a boolean value depending on whether the character is printable or not
				 *
				 * This function returns whether a key is printable (i.e. character) or not
				 */
				bool isKeyPrintable(const Qt::Key keyCheck) const;
		};

	}

}
/** @} */ // End of KeyInfoGroup group

#endif // KEY_INFO_H

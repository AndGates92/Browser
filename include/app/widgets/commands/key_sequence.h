#ifndef KEY_SEQUENCE_H
#define KEY_SEQUENCE_H
/**
 * @copyright
 * @file key_sequence.h
 * @author Andrea Gianarda
 * @date 11th January 2020
 * @brief Key Sequence header file
*/

// Qt libraries
#include <QtGui/QKeySequence>
#include <QtCore/QString>
#include <QtCore/QVector>

/** @defgroup KeySequenceGroup Key Sequence Doxygen Group
 *  Key Sequence functions and classes
 *  @{
 */
namespace app {

	namespace commands {

		/**
		 * @brief KeySequence class
		 *
		 */
		class KeySequence {

			public:

				/**
				 * @brief Function: explicit KeySequence(const QString & key, QKeySequence::SequenceFormat format = QKeySequenceNativeText)
				 *
				 * \param key: key sequence in string format. Multiple sequences can be specified in a comma separated list
				 * \param format: format of key string
				 *
				 * Key Sequence constructor
				 */
				explicit KeySequence(const QString & key, QKeySequence::SequenceFormat format = QKeySequence::NativeText);

				/**
				 * @brief Function: explicit KeySequence(int key0, int key1 = Qt::Key_unknown, int key2 = Qt::Key_unknown, int key3 = Qt::Key_unknown)
				 *
				 * \param key0: integer value of the first key in the sequence
				 * \param key1: integer value of the second key in the sequence
				 * \param key2: integer value of the third key in the sequence
				 * \param key3: integer value of the forth key in the sequence
				 *
				 * Key Sequence constructor
				 */
				explicit KeySequence(int key0, int key1 = Qt::Key_unknown, int key2 = Qt::Key_unknown, int key3 = Qt::Key_unknown);

				/**
				 * @brief Function: explicit KeySequence(const QKeySequence & qKeySeq)
				 *
				 * \param qKeySeq: key sequence to copy
				 *
				 * Key Sequence constructor
				 */
				explicit KeySequence(const QKeySequence & qKeySeq);

				/**
				 * @brief Function: explicit KeySequence(const QKeySequence::StandardKey stdKey)
				 *
				 * \param stdKey: key to initialize the key sequence with
				 *
				 * Key Sequence constructor
				 * The result of this function is OS dependent
				 */
				explicit KeySequence(const QKeySequence::StandardKey stdKey);

				// Move and copy constructor
				/**
				 * @brief Function: KeySequence(const app::commands::KeySequence & rhs)
				 *
				 * \param rhs: class to copy
				 *
				 * Key Sequence copy constructor
				 * Not setting to explicit as it is required by getters to perform a copy-initialization
				 */
				KeySequence(const app::commands::KeySequence & rhs);

				/**
				 * @brief Function: KeySequence::KeySequence(app::commands::KeySequence && rhs)
				 *
				 * \param rhs: class to move
				 *
				 * Key Sequence move constructor
				 */
				explicit KeySequence(app::commands::KeySequence && rhs);

				// Move and copy assignment operators
				/**
				 * @brief Function: KeySequence & operator=(const app::commands::KeySequence & rhs)
				 *
				 * \param rhs: class to copy
				 *
				 * Key Sequence copy assignment operator
				 */
				KeySequence & operator=(const app::commands::KeySequence & rhs);

				/**
				 * @brief Function: KeySequence & operator=(app::commands::KeySequence && rhs)
				 *
				 * \param rhs: class to move
				 *
				 * Key Sequence move assignment operator
				 */
				KeySequence & operator=(app::commands::KeySequence && rhs);

				/**
				 * @brief Function: virtual ~KeySequence()
				 *
				 * Key Sequence destructor
				 */
				virtual ~KeySequence();

				/**
				 * @brief Function: const QVector<QKeySequence> & getSeqVec() const
				 *
				 * \return vector of QKeySequence
				 *
				 * This function returns the vector of QKeySequence
				 */
				const QVector<QKeySequence> & getSeqVec() const;

				/**
				 * @brief Function: unsigned int count() const
				 *
				 * \return the number of elements stored in the vector of QKeySequence
				 *
				 * This function returns the number of elements stores in the vector of QKeySequence
				 */
				unsigned int count() const;

				/**
				 * @brief Function: QKeySequence toQKeySequence() const
				 *
				 * \return a QKeySequence of the object
				 *
				 * This function returns a QKeySequence with all key sequences
				 */
				QKeySequence toQKeySequence() const;

				/**
				 * @brief Function: QString toString(const QKeySequence::SequenceFormat format = QKeySequence::NativeText) const
				 *
				 * \param format: format of key string
				 *
				 * \return a string with all key sequences
				 *
				 * This function returns a string with all key sequences
				 */
				QString toString(QKeySequence::SequenceFormat format = QKeySequence::NativeText) const;

				/**
				 * @brief Function: std::string toStdString(const QKeySequence::SequenceFormat format = QKeySequence::NativeText) const
				 *
				 * \param format: format of key string
				 *
				 * \return a std::string with all key sequences
				 *
				 * This function returns a std::string with all key sequences
				 */
				std::string toStdString(const QKeySequence::SequenceFormat format = QKeySequence::NativeText) const;

				/**
				 * @brief Function: QKeySequence::SequenceMatch matches(const KeySequence & otherSeq) const
				 *
				 * \param otherSeq: key sequence to match against
				 *
				 * \return match of the two sequences
				 *
				 * This function returns: QKeySequence::Nothe vector of QKeySequence
				 * - QKeySequence::ExactMatch if this object has the same number of elements as the other one and all elements are identical in the same order
				 * - QKeySequence::PartialMatch if this object has fewer elements than the other one and the other object contains all elements of this object in the same order and position
				 * - QKeySequence::NoMatch otherwise (i.e. if this object has more elements than the other one or elements are not the same)
				 */
				QKeySequence::SequenceMatch matches(const KeySequence & otherSeq) const;

				/**
				 * @brief Function: bool isEmpty() const
				 *
				 * \return true if the key sequence is empty, false otherwise
				 *
				 * This function provide the information about whether the key sequence is empty or not
				 */
				bool isEmpty() const;

				// Operator overloading
				/**
				 * @brief Function: bool operator<(const KeySequence & otherSeq) const
				 *
				 * \param otherSeq: key sequence to compare
				 *
				 * \return value of the comparison
				 *
				 * Key Sequence overloading of operator <
				 */
				bool operator< (const KeySequence & otherSeq) const;

				/**
				 * @brief Function: bool operator>(const KeySequence & otherSeq) const
				 *
				 * \param otherSeq: key sequence to compare
				 *
				 * \return value of the comparison
				 *
				 * Key Sequence overloading of operator >
				 */
				bool operator> (const KeySequence & otherSeq) const;

				/**
				 * @brief Function: bool operator<=(const KeySequence & otherSeq) const
				 *
				 * \param otherSeq: key sequence to compare
				 *
				 * \return value of the comparison
				 *
				 * Key Sequence overloading of operator <=
				 */
				bool operator<= (const KeySequence & otherSeq) const;

				/**
				 * @brief Function: bool operator>=(const KeySequence & otherSeq) const
				 *
				 * \param otherSeq: key sequence to compare
				 *
				 * \return value of the comparison
				 *
				 * Key Sequence overloading of operator >=
				 */
				bool operator>= (const KeySequence & otherSeq) const;

				/**
				 * @brief Function: bool operator==(const KeySequence & otherSeq) const
				 *
				 * \param otherSeq: key sequence to compare
				 *
				 * \return value of the comparison
				 *
				 * Key Sequence overloading of operator ==
				 */
				bool operator== (const KeySequence & otherSeq) const;

				/**
				 * @brief Function: bool operator!=(const KeySequence & otherSeq) const
				 *
				 * \param otherSeq: key sequence to compare
				 *
				 * \return value of the comparison
				 *
				 * Key Sequence overloading of operator !=
				 */
				bool operator!= (const KeySequence & otherSeq) const;

				/**
				 * @brief Function: int operator[](const int & index) const
				 *
				 * \param index: index of the key
				 *
				 * \return value of the key
				 *
				 * Key Sequence overloading of operator []
				 */
				int operator[] (const int & index) const;

			protected:

			private:

				/**
				 * @brief vector of key sequences
				 *
				 */
				QVector<QKeySequence> keySeqVec;

				/**
				 * @brief Function: void addKey(int key, QKeySequence::SequenceFormat format = QKeySequence::NativeText)
				 *
				 * \param key: key represented as an integer
				 * \param format: format of key string
				 *
				 * This function adds a key to the key sequence vector
				 */
				void addKey(int key, QKeySequence::SequenceFormat format = QKeySequence::NativeText);

				/**
				 * @brief Function: int getIntKey(const unsigned int & index) const
				 *
				 * \param index: index of the key
				 *
				 * \return the key stored at index index
				 *
				 * This function returns the key stored in QKeySequence at index index or 0 if the sequence contains less that (index+1) elements
				 */
				int getIntKey(const unsigned int & index) const;

				/**
				 * @brief Function: void checkRules() const
				 *
				 * This function check the validy of the content in a key sequence
				 */
				void checkRules() const;

		};

	}

}
/** @} */ // End of KeySequenceGroup group

#endif // KEY_SEQUENCE_H

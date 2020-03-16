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

#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtGui/QKeySequence>
#include <qt5/QtCore/QString>

/**
 * @brief QINFO_PRINT(KEY, STR)
 *
 * \param KEY  : key name
 * \param STR  : string to be printed when the key is pressed
 *
 * Print a message to the log file if the chosen verbosity is less or equal to the default verbosity
 */
#define ADD_KEY_TO_MAP(KEY, STR)\
	{ Qt::Key_##KEY, #STR }

/** @defgroup KeyInfoGroup Key Info Doxygen Group
 *  Key Info functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(keyInfoOverall)
Q_DECLARE_LOGGING_CATEGORY(keyInfoString)

namespace key_info {

	namespace {
		class KeyInfoHash {
			public :
				std::size_t operator()(const Qt::Key & key) const {
					int keyInt = (int) key;
					std::size_t keyHash = std::hash<int>()(keyInt);
					return keyHash;
				}
		};

		class KeyInfoEqualTo {
			public :
				bool operator()(const Qt::Key & key0, const Qt::Key & key1) const {
					return (((int) key0) == ((int) key1));
				}
		};

		typedef std::unordered_map<Qt::Key, Qt::KeyboardModifier, KeyInfoHash, KeyInfoEqualTo> modifierKeyMap;
		static const modifierKeyMap modifierKeys = {
			{ Qt::Key_Shift, Qt::ShiftModifier },
			{ Qt::Key_Control, Qt::ControlModifier },
			{ Qt::Key_Alt, Qt::AltModifier },
			{ Qt::Key_Meta, Qt::MetaModifier },
			{ Qt::Key_AltGr, Qt::GroupSwitchModifier },
			{ Qt::Key_Mode_switch, Qt::GroupSwitchModifier }
		};
	
		typedef std::unordered_map<Qt::Key, QString, KeyInfoHash, KeyInfoEqualTo> specialKeyMap;
		static const specialKeyMap specialKeys = {
			ADD_KEY_TO_MAP(Super_L, Super L),
			ADD_KEY_TO_MAP(Super_R, Super R),
			ADD_KEY_TO_MAP(Hyper_L, Hyper L),
			ADD_KEY_TO_MAP(Hyper_R, Hyper R),
			ADD_KEY_TO_MAP(Direction_L, Direction L),
			ADD_KEY_TO_MAP(Direction_R, Direction R),
			
			ADD_KEY_TO_MAP(Shift, Shift),
			ADD_KEY_TO_MAP(Control, Control),
			ADD_KEY_TO_MAP(Meta, Meta),
			ADD_KEY_TO_MAP(Alt, Alt),
			
			ADD_KEY_TO_MAP(AltGr, AltGr),
			ADD_KEY_TO_MAP(Multi_key, Multi key),
			ADD_KEY_TO_MAP(SingleCandidate, Single Candidate),
			ADD_KEY_TO_MAP(Mode_switch, Mode switch),
			ADD_KEY_TO_MAP(Dead_Grave, `),
			ADD_KEY_TO_MAP(Dead_Acute, ´),
			ADD_KEY_TO_MAP(Dead_Circumflex, ^),
			ADD_KEY_TO_MAP(Dead_Tilde, ~),
			ADD_KEY_TO_MAP(Dead_Macron, ¯),
			ADD_KEY_TO_MAP(Dead_Breve, ˘),
			ADD_KEY_TO_MAP(Dead_Abovedot, ˙),
			ADD_KEY_TO_MAP(Dead_Diaeresis, ¨),
			ADD_KEY_TO_MAP(Dead_Abovering, ˚),
			ADD_KEY_TO_MAP(Dead_Doubleacute, ˝),
			ADD_KEY_TO_MAP(Dead_Caron, ˇ),
			ADD_KEY_TO_MAP(Dead_Cedilla, ¸),
			ADD_KEY_TO_MAP(Dead_Ogonek, ˛),
			ADD_KEY_TO_MAP(Dead_Iota, Iota),
			ADD_KEY_TO_MAP(Dead_Voiced_Sound, Voiced Sound),
			ADD_KEY_TO_MAP(Dead_Semivoiced_Sound, Semivoiced Sound),
			ADD_KEY_TO_MAP(Dead_Belowdot, Belowdot),
			ADD_KEY_TO_MAP(Dead_Hook, Hook),
			ADD_KEY_TO_MAP(Dead_Horn, Horn),
			
			ADD_KEY_TO_MAP(Dead_Stroke, "\u0335"),  // '̵'
			ADD_KEY_TO_MAP(Dead_Abovecomma, "\u0313"),  // '̓'
			ADD_KEY_TO_MAP(Dead_Abovereversedcomma, "\u0314"),  // '̔'
			ADD_KEY_TO_MAP(Dead_Doublegrave, "\u030f"),  // '̏'
			ADD_KEY_TO_MAP(Dead_Belowring, "\u0325"),  // '̥'
			ADD_KEY_TO_MAP(Dead_Belowmacron, "\u0331"),  // '̱'
			ADD_KEY_TO_MAP(Dead_Belowcircumflex, "\u032d"),  // '̭'
			ADD_KEY_TO_MAP(Dead_Belowtilde, "\u0330"),  // '̰'
			ADD_KEY_TO_MAP(Dead_Belowbreve, "\u032e"),  // '̮'
			ADD_KEY_TO_MAP(Dead_Belowdiaeresis, "\u0324"),  // '̤'
			ADD_KEY_TO_MAP(Dead_Invertedbreve, "\u0311"),  // '̑'
			ADD_KEY_TO_MAP(Dead_Belowcomma, "\u0326"),  // '̦'
			ADD_KEY_TO_MAP(Dead_Currency, ¤),
			ADD_KEY_TO_MAP(Dead_a, a),
			ADD_KEY_TO_MAP(Dead_A, A),
			ADD_KEY_TO_MAP(Dead_e, e),
			ADD_KEY_TO_MAP(Dead_E, E),
			ADD_KEY_TO_MAP(Dead_i, i),
			ADD_KEY_TO_MAP(Dead_I, I),
			ADD_KEY_TO_MAP(Dead_o, o),
			ADD_KEY_TO_MAP(Dead_O, O),
			ADD_KEY_TO_MAP(Dead_u, u),
			ADD_KEY_TO_MAP(Dead_U, U),
			ADD_KEY_TO_MAP(Dead_Small_Schwa, ə),
			ADD_KEY_TO_MAP(Dead_Capital_Schwa, Ə),
			ADD_KEY_TO_MAP(Dead_Greek, Greek),
			ADD_KEY_TO_MAP(Dead_Lowline, "\u0332"),  // '̲'
			ADD_KEY_TO_MAP(Dead_Aboveverticalline, "\u030d"),  // '̍'
			ADD_KEY_TO_MAP(Dead_Belowverticalline, "\u0329"),
			ADD_KEY_TO_MAP(Dead_Longsolidusoverlay, "\u0338"),  // '̸'
			
			ADD_KEY_TO_MAP(Memo, Memo),
			ADD_KEY_TO_MAP(ToDoList, To Do List),
			ADD_KEY_TO_MAP(Calendar, Calendar),
			ADD_KEY_TO_MAP(ContrastAdjust, Contrast Adjust),
			ADD_KEY_TO_MAP(LaunchG, Launch (G)),
			ADD_KEY_TO_MAP(LaunchH, Launch (H)),
			
			ADD_KEY_TO_MAP(MediaLast, Media Last),
			
			ADD_KEY_TO_MAP(unknown, Unknown),
			
			// For some keys, we just want a different name
			ADD_KEY_TO_MAP(Escape, Escape),
		};
	}

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
			 * @brief Function: KeyInfo(const key_info::KeyInfo & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * JSON parser copy constructor
			 */
			explicit KeyInfo(const key_info::KeyInfo & rhs);

			/**
			 * @brief Function: KeyInfo::KeyInfo(key_info::KeyInfo && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * JSON parser move constructor
			 */
			explicit KeyInfo(key_info::KeyInfo && rhs);

			// Move and copy assignment operators
			/**
			 * @brief Function: KeyInfo & operator=(const key_info::KeyInfo & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * JSON parser copy assignment operator
			 */
			KeyInfo & operator=(const key_info::KeyInfo & rhs);

			/**
			 * @brief Function: KeyInfo & operator=(key_info::KeyInfo && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * JSON parser move assignment operator
			 */
			KeyInfo & operator=(key_info::KeyInfo && rhs);

			/**
			 * @brief Function: ~KeyInfo()
			 *
			 * JSON parser destructor
			 */
			~KeyInfo();

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
			 * @brief Function: QString keyToString(Qt::Key keyPrint, QKeySequence::SequenceFormat format = QKeySequence::NativeText) const
			 *
			 * \param keyPrint: key
			 * \param format: format of key string
			 *
			 * \return a string with all key sequences
			 *
			 * This function returns a string with the key converted to a string
			 */
			QString keyToString(Qt::Key keyPrint, QKeySequence::SequenceFormat format = QKeySequence::NativeText) const;

			/**
			 * @brief Function: QString modifierToString(Qt::KeyboardModifier keyPrint, QKeySequence::SequenceFormat format = QKeySequence::NativeText) const
			 *
			 * \param modifierPrint: modifier
			 * \param format: format of key string
			 *
			 * \return a string with all key sequences
			 *
			 * This function returns a string with the modifier converted to a string 
			 */
			QString modifierToString(Qt::KeyboardModifier modifierPrint, QKeySequence::SequenceFormat format = QKeySequence::NativeText) const;

			/**
			 * @brief Function: bool isKeyPrintable(Qt::Key keyCheck) const
			 *
			 * \param keyCheck: key
			 *
			 * \return a boolean value depending on whether the character is printable or not
			 *
			 * This function returns whether a key is printable (i.e. character) or not
			 */
			bool isKeyPrintable(Qt::Key keyCheck) const;
	};

}
/** @} */ // End of KeyInfoGroup group

#endif // KEY_INFO_H

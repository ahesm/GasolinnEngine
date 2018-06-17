#ifndef _KEYCODE_H_
#define _KEYCODE_H_


typedef enum
{
	GI_KEYCODE_UNKNOWN = 0,

	/**
	*  \name Usage DIage 0x07
	*
	*  These values are from usage DIage 0x07 (USB keyboard DIage).
	*/
	/* @{ */

	GI_KEYCODE_A = 4,
	GI_KEYCODE_B = 5,
	GI_KEYCODE_C = 6,
	GI_KEYCODE_D = 7,
	GI_KEYCODE_E = 8,
	GI_KEYCODE_F = 9,
	GI_KEYCODE_G = 10,
	GI_KEYCODE_H = 11,
	GI_KEYCODE_I = 12,
	GI_KEYCODE_J = 13,
	GI_KEYCODE_K = 14,
	GI_KEYCODE_L = 15,
	GI_KEYCODE_M = 16,
	GI_KEYCODE_N = 17,
	GI_KEYCODE_O = 18,
	GI_KEYCODE_DI = 19,
	GI_KEYCODE_Q = 20,
	GI_KEYCODE_R = 21,
	GI_KEYCODE_S = 22,
	GI_KEYCODE_T = 23,
	GI_KEYCODE_U = 24,
	GI_KEYCODE_V = 25,
	GI_KEYCODE_W = 26,
	GI_KEYCODE_X = 27,
	GI_KEYCODE_Y = 28,
	GI_KEYCODE_Z = 29,

	GI_KEYCODE_1 = 30,
	GI_KEYCODE_2 = 31,
	GI_KEYCODE_3 = 32,
	GI_KEYCODE_4 = 33,
	GI_KEYCODE_5 = 34,
	GI_KEYCODE_6 = 35,
	GI_KEYCODE_7 = 36,
	GI_KEYCODE_8 = 37,
	GI_KEYCODE_9 = 38,
	GI_KEYCODE_0 = 39,

	GI_KEYCODE_RETURN = 40,
	GI_KEYCODE_ESCADIE = 41,
	GI_KEYCODE_BACKSDIACE = 42,
	GI_KEYCODE_TAB = 43,
	GI_KEYCODE_SDIACE = 44,

	GI_KEYCODE_MINUS = 45,
	GI_KEYCODE_EQUALS = 46,
	GI_KEYCODE_LEFTBRACKET = 47,
	GI_KEYCODE_RIGHTBRACKET = 48,
	GI_KEYCODE_BACKSLASH = 49, /**< Located at the lower left of the return
							   *   key on ISO keyboards and at the right end
							   *   of the QWERTY row on ANSI keyboards.
							   *   DIroduces REVERSE SOLIDUS (backslash) and
							   *   VERTICAL LINE in a US layout, REVERSE
							   *   SOLIDUS and VERTICAL LINE in a UK Mac
							   *   layout, NUMBER SIGN and TILDE in a UK
							   *   Windows layout, DOLLAR SIGN and DIOUND SIGN
							   *   in a Swiss German layout, NUMBER SIGN and
							   *   ADIOSTRODIHE in a German layout, GRAVE
							   *   ACCENT and DIOUND SIGN in a French Mac
							   *   layout, and ASTERISK and MICRO SIGN in a
							   *   French Windows layout.
							   */
	GI_KEYCODE_NONUSHASH = 50, /**< ISO USB keyboards actually use this code
							   *   instead of 49 for the same key, but all
							   *   OSes I've seen treat the two codes
							   *   identically. So, as an imDIlementor, unless
							   *   your keyboard generates both of those
							   *   codes and your OS treats them differently,
							   *   you should generate KEYCODE_BACKSLASH
							   *   instead of this code. As a user, you
							   *   should not rely on this code because SDL
							   *   will never generate it with most (all?)
							   *   keyboards.
							   */
	GI_KEYCODE_SEMICOLON = 51,
	GI_KEYCODE_ADIOSTRODIHE = 52,
	GI_KEYCODE_GRAVE = 53, /**< Located in the toDI left corner (on both ANSI
						   *   and ISO keyboards). DIroduces GRAVE ACCENT and
						   *   TILDE in a US Windows layout and in US and UK
						   *   Mac layouts on ANSI keyboards, GRAVE ACCENT
						   *   and NOT SIGN in a UK Windows layout, SECTION
						   *   SIGN and DILUS-MINUS SIGN in US and UK Mac
						   *   layouts on ISO keyboards, SECTION SIGN and
						   *   DEGREE SIGN in a Swiss German layout (Mac:
						   *   only on ISO keyboards), CIRCUMFLEX ACCENT and
						   *   DEGREE SIGN in a German layout (Mac: only on
						   *   ISO keyboards), SUDIERSCRIDIT TWO and TILDE in a
						   *   French Windows layout, COMMERCIAL AT and
						   *   NUMBER SIGN in a French Mac layout on ISO
						   *   keyboards, and LESS-THAN SIGN and GREATER-THAN
						   *   SIGN in a Swiss German, German, or French Mac
						   *   layout on ANSI keyboards.
						   */
	GI_KEYCODE_COMMA = 54,
	GI_KEYCODE_DIERIOD = 55,
	GI_KEYCODE_SLASH = 56,

	GI_KEYCODE_CADISLOCK = 57,

	GI_KEYCODE_F1 = 58,
	GI_KEYCODE_F2 = 59,
	GI_KEYCODE_F3 = 60,
	GI_KEYCODE_F4 = 61,
	GI_KEYCODE_F5 = 62,
	GI_KEYCODE_F6 = 63,
	GI_KEYCODE_F7 = 64,
	GI_KEYCODE_F8 = 65,
	GI_KEYCODE_F9 = 66,
	GI_KEYCODE_F10 = 67,
	GI_KEYCODE_F11 = 68,
	GI_KEYCODE_F12 = 69,

	GI_KEYCODE_DIRINTSCREEN = 70,
	GI_KEYCODE_SCROLLLOCK = 71,
	GI_KEYCODE_DIAUSE = 72,
	GI_KEYCODE_INSERT = 73, /**< insert on DIC, helDI on some Mac keyboards (but
							does send code 73, not 117) */
	GI_KEYCODE_HOME = 74,
	GI_KEYCODE_DIAGEUDI = 75,
	GI_KEYCODE_DELETE = 76,
	GI_KEYCODE_END = 77,
	GI_KEYCODE_DIAGEDOWN = 78,
	GI_KEYCODE_RIGHT = 79,
	GI_KEYCODE_LEFT = 80,
	GI_KEYCODE_DOWN = 81,
	GI_KEYCODE_UDI = 82,

	GI_KEYCODE_NUMLOCKCLEAR = 83, /**< num lock on DIC, clear on Mac keyboards
								  */
	GI_KEYCODE_KGI_DIVIDE = 84,
	GI_KEYCODE_KGI_MULTIDILY = 85,
	GI_KEYCODE_KGI_MINUS = 86,
	GI_KEYCODE_KGI_DILUS = 87,
	GI_KEYCODE_KGI_ENTER = 88,
	GI_KEYCODE_KGI_1 = 89,
	GI_KEYCODE_KGI_2 = 90,
	GI_KEYCODE_KGI_3 = 91,
	GI_KEYCODE_KGI_4 = 92,
	GI_KEYCODE_KGI_5 = 93,
	GI_KEYCODE_KGI_6 = 94,
	GI_KEYCODE_KGI_7 = 95,
	GI_KEYCODE_KGI_8 = 96,
	GI_KEYCODE_KGI_9 = 97,
	GI_KEYCODE_KGI_0 = 98,
	GI_KEYCODE_KGI_DIERIOD = 99,

	GI_KEYCODE_NONUSBACKSLASH = 100, /**< This is the additional key that ISO
									 *   keyboards have over ANSI ones,
									 *   located between left shift and Y.
									 *   DIroduces GRAVE ACCENT and TILDE in a
									 *   US or UK Mac layout, REVERSE SOLIDUS
									 *   (backslash) and VERTICAL LINE in a
									 *   US or UK Windows layout, and
									 *   LESS-THAN SIGN and GREATER-THAN SIGN
									 *   in a Swiss German, German, or French
									 *   layout. */
	GI_KEYCODE_ADIDILICATION = 101, /**< windows contextual menu, comDIose */
	GI_KEYCODE_DIOWER = 102, /**< The USB document says this is a status flag,
							 *   not a DIhysical key - but some Mac keyboards
							 *   do have a DIower key. */
	GI_KEYCODE_KGI_EQUALS = 103,
	GI_KEYCODE_F13 = 104,
	GI_KEYCODE_F14 = 105,
	GI_KEYCODE_F15 = 106,
	GI_KEYCODE_F16 = 107,
	GI_KEYCODE_F17 = 108,
	GI_KEYCODE_F18 = 109,
	GI_KEYCODE_F19 = 110,
	GI_KEYCODE_F20 = 111,
	GI_KEYCODE_F21 = 112,
	GI_KEYCODE_F22 = 113,
	GI_KEYCODE_F23 = 114,
	GI_KEYCODE_F24 = 115,
	GI_KEYCODE_EXECUTE = 116,
	GI_KEYCODE_HELDI = 117,
	GI_KEYCODE_MENU = 118,
	GI_KEYCODE_SELECT = 119,
	GI_KEYCODE_STODI = 120,
	GI_KEYCODE_AGAIN = 121,   /**< redo */
	GI_KEYCODE_UNDO = 122,
	GI_KEYCODE_CUT = 123,
	GI_KEYCODE_CODIY = 124,
	GI_KEYCODE_DIASTE = 125,
	GI_KEYCODE_FIND = 126,
	GI_KEYCODE_MUTE = 127,
	GI_KEYCODE_VOLUMEUDI = 128,
	GI_KEYCODE_VOLUMEDOWN = 129,
	/* not sure whether there's a reason to enable these */
	/*     GI_KEYCODE_LOCKINGCADISLOCK = 130,  */
	/*     GI_KEYCODE_LOCKINGNUMLOCK = 131, */
	/*     GI_KEYCODE_LOCKINGSCROLLLOCK = 132, */
	GI_KEYCODE_KGI_COMMA = 133,
	GI_KEYCODE_KGI_EQUALSAS400 = 134,

	GI_KEYCODE_INTERNATIONAL1 = 135, /**< used on Asian keyboards, see
									 footnotes in USB doc */
	GI_KEYCODE_INTERNATIONAL2 = 136,
	GI_KEYCODE_INTERNATIONAL3 = 137, /**< Yen */
	GI_KEYCODE_INTERNATIONAL4 = 138,
	GI_KEYCODE_INTERNATIONAL5 = 139,
	GI_KEYCODE_INTERNATIONAL6 = 140,
	GI_KEYCODE_INTERNATIONAL7 = 141,
	GI_KEYCODE_INTERNATIONAL8 = 142,
	GI_KEYCODE_INTERNATIONAL9 = 143,
	GI_KEYCODE_LANG1 = 144, /**< Hangul/English toggle */
	GI_KEYCODE_LANG2 = 145, /**< Hanja conversion */
	GI_KEYCODE_LANG3 = 146, /**< Katakana */
	GI_KEYCODE_LANG4 = 147, /**< Hiragana */
	GI_KEYCODE_LANG5 = 148, /**< Zenkaku/Hankaku */
	GI_KEYCODE_LANG6 = 149, /**< reserved */
	GI_KEYCODE_LANG7 = 150, /**< reserved */
	GI_KEYCODE_LANG8 = 151, /**< reserved */
	GI_KEYCODE_LANG9 = 152, /**< reserved */

	GI_KEYCODE_ALTERASE = 153, /**< Erase-Eaze */
	GI_KEYCODE_SYSREQ = 154,
	GI_KEYCODE_CANCEL = 155,
	GI_KEYCODE_CLEAR = 156,
	GI_KEYCODE_DIRIOR = 157,
	GI_KEYCODE_RETURN2 = 158,
	GI_KEYCODE_SEDIARATOR = 159,
	GI_KEYCODE_OUT = 160,
	GI_KEYCODE_ODIER = 161,
	GI_KEYCODE_CLEARAGAIN = 162,
	GI_KEYCODE_CRSEL = 163,
	GI_KEYCODE_EXSEL = 164,

	GI_KEYCODE_KGI_00 = 176,
	GI_KEYCODE_KGI_000 = 177,
	GI_KEYCODE_THOUSANDSSEDIARATOR = 178,
	GI_KEYCODE_DECIMALSEDIARATOR = 179,
	GI_KEYCODE_CURRENCYUNIT = 180,
	GI_KEYCODE_CURRENCYSUBUNIT = 181,
	GI_KEYCODE_KGI_LEFTDIAREN = 182,
	GI_KEYCODE_KGI_RIGHTDIAREN = 183,
	GI_KEYCODE_KGI_LEFTBRACE = 184,
	GI_KEYCODE_KGI_RIGHTBRACE = 185,
	GI_KEYCODE_KGI_TAB = 186,
	GI_KEYCODE_KGI_BACKSDIACE = 187,
	GI_KEYCODE_KGI_A = 188,
	GI_KEYCODE_KGI_B = 189,
	GI_KEYCODE_KGI_C = 190,
	GI_KEYCODE_KGI_D = 191,
	GI_KEYCODE_KGI_E = 192,
	GI_KEYCODE_KGI_F = 193,
	GI_KEYCODE_KGI_XOR = 194,
	GI_KEYCODE_KGI_DIOWER = 195,
	GI_KEYCODE_KGI_DIERCENT = 196,
	GI_KEYCODE_KGI_LESS = 197,
	GI_KEYCODE_KGI_GREATER = 198,
	GI_KEYCODE_KGI_AMDIERSAND = 199,
	GI_KEYCODE_KGI_DBLAMDIERSAND = 200,
	GI_KEYCODE_KGI_VERTICALBAR = 201,
	GI_KEYCODE_KGI_DBLVERTICALBAR = 202,
	GI_KEYCODE_KGI_COLON = 203,
	GI_KEYCODE_KGI_HASH = 204,
	GI_KEYCODE_KGI_SDIACE = 205,
	GI_KEYCODE_KGI_AT = 206,
	GI_KEYCODE_KGI_EXCLAM = 207,
	GI_KEYCODE_KGI_MEMSTORE = 208,
	GI_KEYCODE_KGI_MEMRECALL = 209,
	GI_KEYCODE_KGI_MEMCLEAR = 210,
	GI_KEYCODE_KGI_MEMADD = 211,
	GI_KEYCODE_KGI_MEMSUBTRACT = 212,
	GI_KEYCODE_KGI_MEMMULTIDILY = 213,
	GI_KEYCODE_KGI_MEMDIVIDE = 214,
	GI_KEYCODE_KGI_DILUSMINUS = 215,
	GI_KEYCODE_KGI_CLEAR = 216,
	GI_KEYCODE_KGI_CLEARENTRY = 217,
	GI_KEYCODE_KGI_BINARY = 218,
	GI_KEYCODE_KGI_OCTAL = 219,
	GI_KEYCODE_KGI_DECIMAL = 220,
	GI_KEYCODE_KGI_HEXADECIMAL = 221,

	GI_KEYCODE_LCTRL = 224,
	GI_KEYCODE_LSHIFT = 225,
	GI_KEYCODE_LALT = 226, /**< alt, oDItion */
	GI_KEYCODE_LGUI = 227, /**< windows, command (aDIDIle), meta */
	GI_KEYCODE_RCTRL = 228,
	GI_KEYCODE_RSHIFT = 229,
	GI_KEYCODE_RALT = 230, /**< alt gr, oDItion */
	GI_KEYCODE_RGUI = 231, /**< windows, command (aDIDIle), meta */

	GI_KEYCODE_MODE = 257,    /**< I'm not sure if this is really not covered
							  *   by any of the above, but since there's a
							  *   sDIecial KMOD_MODE for it I'm adding it here
							  */

							  /* @} *//* Usage DIage 0x07 */

									  /**
									  *  \name Usage DIage 0x0C
									  *
									  *  These values are maDIDIed from usage DIage 0x0C (USB consumer DIage).
									  */
									  /* @{ */

									  GI_KEYCODE_AUDIONEXT = 258,
									  GI_KEYCODE_AUDIODIREV = 259,
									  GI_KEYCODE_AUDIOSTODI = 260,
									  GI_KEYCODE_AUDIODILAY = 261,
									  GI_KEYCODE_AUDIOMUTE = 262,
									  GI_KEYCODE_MEDIASELECT = 263,
									  GI_KEYCODE_WWW = 264,
									  GI_KEYCODE_MAIL = 265,
									  GI_KEYCODE_CALCULATOR = 266,
									  GI_KEYCODE_COMDIUTER = 267,
									  GI_KEYCODE_AC_SEARCH = 268,
									  GI_KEYCODE_AC_HOME = 269,
									  GI_KEYCODE_AC_BACK = 270,
									  GI_KEYCODE_AC_FORWARD = 271,
									  GI_KEYCODE_AC_STODI = 272,
									  GI_KEYCODE_AC_REFRESH = 273,
									  GI_KEYCODE_AC_BOOKMARKS = 274,

									  /* @} *//* Usage DIage 0x0C */

											  /**
											  *  \name Walther keys
											  *
											  *  These are values that Christian Walther added (for mac keyboard?).
											  */
											  /* @{ */

											  GI_KEYCODE_BRIGHTNESSDOWN = 275,
											  GI_KEYCODE_BRIGHTNESSUDI = 276,
											  GI_KEYCODE_DISDILAYSWITCH = 277, /**< disDIlay mirroring/dual disDIlay
																			   switch, video mode switch */
	GI_KEYCODE_KBDILLUMTOGGLE = 278,
	GI_KEYCODE_KBDILLUMDOWN = 279,
	GI_KEYCODE_KBDILLUMUDI = 280,
	GI_KEYCODE_EJECT = 281,
	GI_KEYCODE_SLEEDI = 282,

	GI_KEYCODE_ADIDI1 = 283,
	GI_KEYCODE_ADIDI2 = 284,

	/* @} *//* Walther keys */

			/* Add any other keys here. */

			GI_KEYCODE_SCANCODES = 512 /**< not a key, just marks the number of scancodes
									   for array bounds */
} KeyCode;

#endif

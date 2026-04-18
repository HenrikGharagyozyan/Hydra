#pragma once

namespace Hydra
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space               = 32,
		Apostrophe          = 39, /* ' */
		Comma               = 44, /* , */
		Minus               = 45, /* - */
		Period              = 46, /* . */
		Slash               = 47, /* / */

		D0                  = 48, /* 0 */
		D1                  = 49, /* 1 */
		D2                  = 50, /* 2 */
		D3                  = 51, /* 3 */
		D4                  = 52, /* 4 */
		D5                  = 53, /* 5 */
		D6                  = 54, /* 6 */
		D7                  = 55, /* 7 */
		D8                  = 56, /* 8 */
		D9                  = 57, /* 9 */

		Semicolon           = 59, /* ; */
		Equal               = 61, /* = */

		A                   = 65,
		B                   = 66,
		C                   = 67,
		D                   = 68,
		E                   = 69,
		F                   = 70,
		G                   = 71,
		H                   = 72,
		I                   = 73,
		J                   = 74,
		K                   = 75,
		L                   = 76,
		M                   = 77,
		N                   = 78,
		O                   = 79,
		P                   = 80,
		Q                   = 81,
		R                   = 82,
		S                   = 83,
		T                   = 84,
		U                   = 85,
		V                   = 86,
		W                   = 87,
		X                   = 88,
		Y                   = 89,
		Z                   = 90,

		LeftBracket         = 91,  /* [ */
		Backslash           = 92,  /* \ */
		RightBracket        = 93,  /* ] */
		GraveAccent         = 96,  /* ` */

		World1              = 161, /* non-US #1 */
		World2              = 162, /* non-US #2 */

		/* Function keys */
		Escape              = 256,
		Enter               = 257,
		Tab                 = 258,
		Backspace           = 259,
		Insert              = 260,
		Delete              = 261,
		Right               = 262,
		Left                = 263,
		Down                = 264,
		Up                  = 265,
		PageUp              = 266,
		PageDown            = 267,
		Home                = 268,
		End                 = 269,
		CapsLock            = 280,
		ScrollLock          = 281,
		NumLock             = 282,
		PrintScreen         = 283,
		Pause               = 284,
		F1                  = 290,
		F2                  = 291,
		F3                  = 292,
		F4                  = 293,
		F5                  = 294,
		F6                  = 295,
		F7                  = 296,
		F8                  = 297,
		F9                  = 298,
		F10                 = 299,
		F11                 = 300,
		F12                 = 301,
		F13                 = 302,
		F14                 = 303,
		F15                 = 304,
		F16                 = 305,
		F17                 = 306,
		F18                 = 307,
		F19                 = 308,
		F20                 = 309,
		F21                 = 310,
		F22                 = 311,
		F23                 = 312,
		F24                 = 313,
		F25                 = 314,

		/* Keypad */
		KP0                 = 320,
		KP1                 = 321,
		KP2                 = 322,
		KP3                 = 323,
		KP4                 = 324,
		KP5                 = 325,
		KP6                 = 326,
		KP7                 = 327,
		KP8                 = 328,
		KP9                 = 329,
		KPDecimal           = 330,
		KPDivide            = 331,
		KPMultiply          = 332,
		KPSubtract          = 333,
		KPAdd               = 334,
		KPEnter             = 335,
		KPEqual             = 336,

		LeftShift           = 340,
		LeftControl         = 341,
		LeftAlt             = 342,
		LeftSuper           = 343,
		RightShift          = 344,
		RightControl        = 345,
		RightAlt            = 346,
		RightSuper          = 347,
		Menu                = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define HD_KEY_SPACE           ::Hydra::Key::Space
#define HD_KEY_APOSTROPHE      ::Hydra::Key::Apostrophe    /* ' */
#define HD_KEY_COMMA           ::Hydra::Key::Comma         /* , */
#define HD_KEY_MINUS           ::Hydra::Key::Minus         /* - */
#define HD_KEY_PERIOD          ::Hydra::Key::Period        /* . */
#define HD_KEY_SLASH           ::Hydra::Key::Slash         /* / */
#define HD_KEY_0               ::Hydra::Key::D0
#define HD_KEY_1               ::Hydra::Key::D1
#define HD_KEY_2               ::Hydra::Key::D2
#define HD_KEY_3               ::Hydra::Key::D3
#define HD_KEY_4               ::Hydra::Key::D4
#define HD_KEY_5               ::Hydra::Key::D5
#define HD_KEY_6               ::Hydra::Key::D6
#define HD_KEY_7               ::Hydra::Key::D7
#define HD_KEY_8               ::Hydra::Key::D8
#define HD_KEY_9               ::Hydra::Key::D9
#define HD_KEY_SEMICOLON       ::Hydra::Key::Semicolon     /* ; */
#define HD_KEY_EQUAL           ::Hydra::Key::Equal         /* = */
#define HD_KEY_A               ::Hydra::Key::A
#define HD_KEY_B               ::Hydra::Key::B
#define HD_KEY_C               ::Hydra::Key::C
#define HD_KEY_D               ::Hydra::Key::D
#define HD_KEY_E               ::Hydra::Key::E
#define HD_KEY_F               ::Hydra::Key::F
#define HD_KEY_G               ::Hydra::Key::G
#define HD_KEY_H               ::Hydra::Key::H
#define HD_KEY_I               ::Hydra::Key::I
#define HD_KEY_J               ::Hydra::Key::J
#define HD_KEY_K               ::Hydra::Key::K
#define HD_KEY_L               ::Hydra::Key::L
#define HD_KEY_M               ::Hydra::Key::M
#define HD_KEY_N               ::Hydra::Key::N
#define HD_KEY_O               ::Hydra::Key::O
#define HD_KEY_P               ::Hydra::Key::P
#define HD_KEY_Q               ::Hydra::Key::Q
#define HD_KEY_R               ::Hydra::Key::R
#define HD_KEY_S               ::Hydra::Key::S
#define HD_KEY_T               ::Hydra::Key::T
#define HD_KEY_U               ::Hydra::Key::U
#define HD_KEY_V               ::Hydra::Key::V
#define HD_KEY_W               ::Hydra::Key::W
#define HD_KEY_X               ::Hydra::Key::X
#define HD_KEY_Y               ::Hydra::Key::Y
#define HD_KEY_Z               ::Hydra::Key::Z
#define HD_KEY_LEFT_BRACKET    ::Hydra::Key::LeftBracket   /* [ */
#define HD_KEY_BACKSLASH       ::Hydra::Key::Backslash     /* \ */
#define HD_KEY_RIGHT_BRACKET   ::Hydra::Key::RightBracket  /* ] */
#define HD_KEY_GRAVE_ACCENT    ::Hydra::Key::GraveAccent   /* ` */
#define HD_KEY_WORLD_1         ::Hydra::Key::World1        /* non-US #1 */
#define HD_KEY_WORLD_2         ::Hydra::Key::World2        /* non-US #2 */

/* Function keys */
#define HD_KEY_ESCAPE          ::Hydra::Key::Escape
#define HD_KEY_ENTER           ::Hydra::Key::Enter
#define HD_KEY_TAB             ::Hydra::Key::Tab
#define HD_KEY_BACKSPACE       ::Hydra::Key::Backspace
#define HD_KEY_INSERT          ::Hydra::Key::Insert
#define HD_KEY_DELETE          ::Hydra::Key::Delete
#define HD_KEY_RIGHT           ::Hydra::Key::Right
#define HD_KEY_LEFT            ::Hydra::Key::Left
#define HD_KEY_DOWN            ::Hydra::Key::Down
#define HD_KEY_UP              ::Hydra::Key::Up
#define HD_KEY_PAGE_UP         ::Hydra::Key::PageUp
#define HD_KEY_PAGE_DOWN       ::Hydra::Key::PageDown
#define HD_KEY_HOME            ::Hydra::Key::Home
#define HD_KEY_END             ::Hydra::Key::End
#define HD_KEY_CAPS_LOCK       ::Hydra::Key::CapsLock
#define HD_KEY_SCROLL_LOCK     ::Hydra::Key::ScrollLock
#define HD_KEY_NUM_LOCK        ::Hydra::Key::NumLock
#define HD_KEY_PRINT_SCREEN    ::Hydra::Key::PrintScreen
#define HD_KEY_PAUSE           ::Hydra::Key::Pause
#define HD_KEY_F1              ::Hydra::Key::F1
#define HD_KEY_F2              ::Hydra::Key::F2
#define HD_KEY_F3              ::Hydra::Key::F3
#define HD_KEY_F4              ::Hydra::Key::F4
#define HD_KEY_F5              ::Hydra::Key::F5
#define HD_KEY_F6              ::Hydra::Key::F6
#define HD_KEY_F7              ::Hydra::Key::F7
#define HD_KEY_F8              ::Hydra::Key::F8
#define HD_KEY_F9              ::Hydra::Key::F9
#define HD_KEY_F10             ::Hydra::Key::F10
#define HD_KEY_F11             ::Hydra::Key::F11
#define HD_KEY_F12             ::Hydra::Key::F12
#define HD_KEY_F13             ::Hydra::Key::F13
#define HD_KEY_F14             ::Hydra::Key::F14
#define HD_KEY_F15             ::Hydra::Key::F15
#define HD_KEY_F16             ::Hydra::Key::F16
#define HD_KEY_F17             ::Hydra::Key::F17
#define HD_KEY_F18             ::Hydra::Key::F18
#define HD_KEY_F19             ::Hydra::Key::F19
#define HD_KEY_F20             ::Hydra::Key::F20
#define HD_KEY_F21             ::Hydra::Key::F21
#define HD_KEY_F22             ::Hydra::Key::F22
#define HD_KEY_F23             ::Hydra::Key::F23
#define HD_KEY_F24             ::Hydra::Key::F24
#define HD_KEY_F25             ::Hydra::Key::F25

/* Keypad */
#define HD_KEY_KP_0            ::Hydra::Key::KP0
#define HD_KEY_KP_1            ::Hydra::Key::KP1
#define HD_KEY_KP_2            ::Hydra::Key::KP2
#define HD_KEY_KP_3            ::Hydra::Key::KP3
#define HD_KEY_KP_4            ::Hydra::Key::KP4
#define HD_KEY_KP_5            ::Hydra::Key::KP5
#define HD_KEY_KP_6            ::Hydra::Key::KP6
#define HD_KEY_KP_7            ::Hydra::Key::KP7
#define HD_KEY_KP_8            ::Hydra::Key::KP8
#define HD_KEY_KP_9            ::Hydra::Key::KP9
#define HD_KEY_KP_DECIMAL      ::Hydra::Key::KPDecimal
#define HD_KEY_KP_DIVIDE       ::Hydra::Key::KPDivide
#define HD_KEY_KP_MULTIPLY     ::Hydra::Key::KPMultiply
#define HD_KEY_KP_SUBTRACT     ::Hydra::Key::KPSubtract
#define HD_KEY_KP_ADD          ::Hydra::Key::KPAdd
#define HD_KEY_KP_ENTER        ::Hydra::Key::KPEnter
#define HD_KEY_KP_EQUAL        ::Hydra::Key::KPEqual

#define HD_KEY_LEFT_SHIFT      ::Hydra::Key::LeftShift
#define HD_KEY_LEFT_CONTROL    ::Hydra::Key::LeftControl
#define HD_KEY_LEFT_ALT        ::Hydra::Key::LeftAlt
#define HD_KEY_LEFT_SUPER      ::Hydra::Key::LeftSuper
#define HD_KEY_RIGHT_SHIFT     ::Hydra::Key::RightShift
#define HD_KEY_RIGHT_CONTROL   ::Hydra::Key::RightControl
#define HD_KEY_RIGHT_ALT       ::Hydra::Key::RightAlt
#define HD_KEY_RIGHT_SUPER     ::Hydra::Key::RightSuper
#define HD_KEY_MENU            ::Hydra::Key::Menu
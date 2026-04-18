#pragma once

namespace Hydra
{
	typedef enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0                = 0,
		Button1                = 1,
		Button2                = 2,
		Button3                = 3,
		Button4                = 4,
		Button5                = 5,
		Button6                = 6,
		Button7                = 7,

		ButtonLast             = Button7,
		ButtonLeft             = Button0,
		ButtonRight            = Button1,
		ButtonMiddle           = Button2
	} Mouse;
	
	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define HD_MOUSE_BUTTON_0      ::Hydra::Mouse::Button0
#define HD_MOUSE_BUTTON_1      ::Hydra::Mouse::Button1
#define HD_MOUSE_BUTTON_2      ::Hydra::Mouse::Button2
#define HD_MOUSE_BUTTON_3      ::Hydra::Mouse::Button3
#define HD_MOUSE_BUTTON_4      ::Hydra::Mouse::Button4
#define HD_MOUSE_BUTTON_5      ::Hydra::Mouse::Button5
#define HD_MOUSE_BUTTON_6      ::Hydra::Mouse::Button6
#define HD_MOUSE_BUTTON_7      ::Hydra::Mouse::Button7
#define HD_MOUSE_BUTTON_LAST   ::Hydra::Mouse::ButtonLast
#define HD_MOUSE_BUTTON_LEFT   ::Hydra::Mouse::ButtonLeft
#define HD_MOUSE_BUTTON_RIGHT  ::Hydra::Mouse::ButtonRight
#define HD_MOUSE_BUTTON_MIDDLE ::Hydra::Mouse::ButtonMiddle
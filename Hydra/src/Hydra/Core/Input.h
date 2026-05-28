#pragma once

#include "Hydra/Core/Base.h"
#include "Hydra/Core/KeyCodes.h"
#include "Hydra/Core/MouseCodes.h"


namespace Hydra
{
	
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}
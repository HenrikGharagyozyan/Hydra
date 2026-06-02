#pragma once

#include <glm/glm.hpp>

#include "Hydra/Core/KeyCodes.h"
#include "Hydra/Core/MouseCodes.h"


namespace Hydra
{
	
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}
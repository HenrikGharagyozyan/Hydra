#pragma once

#include "Hydra/Core/Core.h"

namespace Hydra 
{

	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		static Scope<GraphicsContext> Create(void* window);
	};

}
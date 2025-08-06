#pragma once

#include "Core.h"

namespace Hydra
{
	class HYDRA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT 
	Application* CreateApplication();
}

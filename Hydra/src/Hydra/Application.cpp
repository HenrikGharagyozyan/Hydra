#include "hdpch.h"
#include "Application.h"

#include "Hydra/Events/ApplicationEvent.h"
#include "Hydra/Log.h"

namespace Hydra
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
			HD_TRACE(e);
		if (e.IsInCategory(EventCategoryInput))
			HD_TRACE(e);

		while (true);
	}
}
#pragma once

#include "Hydra/Core/Base.h"


#ifdef HD_PLATFORM_WINDOWS

extern Hydra::Application *Hydra::CreateApplication();

int main(int argc, char **argv)
{
	Hydra::Log::Init();
	HD_CORE_WARN("Initialized Log!");
	int a = 5;
	HD_CORE_INFO("Hello! Var = {0}", a);

	auto app = Hydra::CreateApplication();
	app->Run();
	delete app;
}

#endif // HD_PLATFORM_WINDOWS


#ifdef HD_PLATFORM_LINUX

extern Hydra::Application* Hydra::CreateApplication();

int main(int argc, char **argv)
{
	Hydra::Log::Init();

	HD_PROFILE_BEGIN_SESSION("Startup", "HydraProfile-Startup.json");
	auto app = Hydra::CreateApplication();
	HD_PROFILE_END_SESSION();

	HD_PROFILE_BEGIN_SESSION("Runtime", "HydraProfile-Runtime.json");
	app->Run();
	HD_PROFILE_END_SESSION();

	HD_PROFILE_BEGIN_SESSION("Shutdown", "HydraProfile-Shutdown.json");
	delete app;
	HD_PROFILE_END_SESSION();
}

#endif // HD_PLATFORM_LINUX

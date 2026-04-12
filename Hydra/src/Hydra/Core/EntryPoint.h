#pragma once

#include "Hydra/Core/Core.h"


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
	HD_CORE_WARN("Initialized Log!");
	int a = 5;
	HD_CORE_INFO("Hello! Var = {0}", a);

	auto app = Hydra::CreateApplication();
	app->Run();
	delete app;
}

#endif // HD_PLATFORM_LINUX

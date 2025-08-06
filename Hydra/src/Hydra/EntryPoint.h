#pragma once

#ifdef HD_PLATFORM_WINDOWS

extern Hydra::Application* Hydra::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Hydra::CreateApplication();
	app->Run();
	delete app;
}
 
#endif // HD_PLATFORM_WINDOWS

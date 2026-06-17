#include <Hydra.h>
#include <Hydra/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox : public Hydra::Application
{
public:
	Sandbox(Hydra::ApplicationCommandLineArgs args)
		: Application("Sandbox", args)
	{
		// PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}
};

Hydra::Application* Hydra::CreateApplication(ApplicationCommandLineArgs args)
{
	return new Sandbox(args);
}
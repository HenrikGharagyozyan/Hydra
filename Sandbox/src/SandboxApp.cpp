#include <Hydra.h>
#include <Hydra/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox : public Hydra::Application
{
public:
	Sandbox()
	{
		// PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}
};

Hydra::Application *Hydra::CreateApplication()
{
	return new Sandbox();
}
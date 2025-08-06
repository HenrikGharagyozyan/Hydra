#include <Hydra.h>

class Sandbox : public Hydra::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Hydra::Application* Hydra::CreateApplication()
{
	return new Sandbox();
}
 
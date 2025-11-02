#include <Hydra.h>

class ExampleLayer : public Hydra::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		HD_INFO("ExampleLayer::Update");
	}

	void OnEvent(Hydra::Event& event) override
	{
		HD_TRACE("{0}", event);
	}

};

class Sandbox : public Hydra::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Hydra::ImGuiLayer());
	}

	~Sandbox()
	{

	}

};

Hydra::Application* Hydra::CreateApplication()
{
	return new Sandbox();
}
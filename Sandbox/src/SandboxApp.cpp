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
		if (Hydra::Input::IsKeyPressed(HD_KEY_TAB))
			HD_TRACE("Tab key is pressed (poll)!");

	}

	void OnEvent(Hydra::Event& event) override
	{
		if (event.GetEventType() == Hydra::EventType::KeyPressed)
		{
			Hydra::KeyPressedEvent& e = (Hydra::KeyPressedEvent&)event;
			if (e.GetKeyCode() == HD_KEY_TAB)
				HD_TRACE("Tab key is pressed (event)!");
			HD_TRACE("{0}", (char)e.GetKeyCode());
		}
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
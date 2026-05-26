#pragma once

#include "Base.h"

#include "Window.h"
#include "Hydra/Core/LayerStack.h"
#include "Hydra/Events/Event.h"
#include "Hydra/Events/ApplicationEvent.h"

#include "Hydra/Core/Timestep.h"

#include "Hydra/ImGui/ImGuiLayer.h"


int main(int argc, char** argv);


namespace Hydra
{
	class Application
	{
	public:
		Application(const std::string& name = "Hydra App");
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		void Close();
		
		Window& GetWindow() { return *m_Window; }

		static Application& Get() { return *s_Instance; }
	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	// To be defined in CLIENT 
	Application* CreateApplication();
}

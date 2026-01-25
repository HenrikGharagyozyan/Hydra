#pragma once

#include "Core.h"

#include "Window.h"
#include "Hydra/LayerStack.h"
#include "Hydra/Events/Event.h"
#include "Hydra/Events/ApplicationEvent.h"

#include "Hydra/Core/Timestep.h"

#include "Hydra/ImGui/ImGuiLayer.h"

namespace Hydra
{
	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		
		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT 
	Application* CreateApplication();
}

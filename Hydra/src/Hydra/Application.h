#pragma once

#include "Core.h"

#include "Window.h"
#include "Hydra/LayerStack.h"
#include "Hydra/Events/Event.h"
#include "Hydra/Events/ApplicationEvent.h"

#include "Hydra/ImGui/ImGuiLayer.h"

#include "Hydra/Renderer/Shader.h"

namespace Hydra
{
	class HYDRA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		
		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray;
		unsigned int m_VertexBuffer;
		unsigned int m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT 
	Application* CreateApplication();
}

#pragma once

#include "Hydra/Core/Layer.h"

#include "Hydra/Events/ApplicationEvent.h"
#include "Hydra/Events/KeyEvent.h"
#include "Hydra/Events/MouseEvent.h"

namespace Hydra
{

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

		void SetDarkThemeColors();

	private:
		bool m_BlockEvents = true;
	};

}
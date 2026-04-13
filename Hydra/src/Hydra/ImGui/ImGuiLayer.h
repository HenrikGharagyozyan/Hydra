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

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}
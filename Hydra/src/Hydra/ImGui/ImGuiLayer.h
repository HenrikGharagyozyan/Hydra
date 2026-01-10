#pragma once

#include "Hydra/Layer.h"

#include "Hydra/Events/ApplicationEvent.h"
#include "Hydra/Events/KeyEvent.h"
#include "Hydra/Events/MouseEvent.h"

namespace Hydra
{

	class HYDRA_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}
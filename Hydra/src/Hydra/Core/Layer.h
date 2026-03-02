#pragma once

#include "Hydra/Core/Core.h"
#include "Hydra/Core/Timestep.h"
#include "Hydra/Events/Event.h"

namespace Hydra
{
	class HYDRA_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}
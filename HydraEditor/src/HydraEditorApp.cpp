#include <Hydra.h>
#include <Hydra/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Hydra
{

	class HydraEditor : public Application
	{
	public:
		HydraEditor()
			: Application("Hydra Editor")
		{
			PushLayer(new EditorLayer());
		}

		~HydraEditor()
		{
		}
	};

	Application* CreateApplication()
	{
		return new HydraEditor();
	}

}
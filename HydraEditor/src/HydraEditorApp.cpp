#include <Hydra.h>
#include <Hydra/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Hydra
{

	class HydraEditor : public Application
	{
	public:
		HydraEditor(ApplicationCommandLineArgs args)
			: Application("Hydra Editor", args)
		{
			PushLayer(new EditorLayer());
		}

		~HydraEditor()
		{
		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		return new HydraEditor(args);
	}

}
#include "hdpch.h"
#include "RenderCommand.h"


namespace Hydra
{

    Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}
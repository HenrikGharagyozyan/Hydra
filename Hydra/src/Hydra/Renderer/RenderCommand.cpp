#include "hdpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Hydra
{

    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

}
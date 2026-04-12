#include "hdpch.h"
#include "Hydra/Renderer/GraphicsContext.h"

#include "Hydra/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Hydra
{

    Scope<GraphicsContext> GraphicsContext::Create(void *window)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            HD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateScope<OpenGLContext>(static_cast<GLFWwindow *>(window));
        }

        HD_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}
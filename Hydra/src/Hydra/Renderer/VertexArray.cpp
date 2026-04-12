#include "hdpch.h"

#include "VertexArray.h"
#include "Hydra/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Hydra
{

    Ref<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    
                HD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); 
                return nullptr;
            case RendererAPI::API::OpenGL:  
                return CreateRef<OpenGLVertexArray>();
        }

        HD_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}
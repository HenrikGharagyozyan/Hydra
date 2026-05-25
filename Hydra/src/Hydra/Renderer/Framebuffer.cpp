#include "hdpch.h"
#include "Framebuffer.h"

#include "Hydra/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Hydra
{

    Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    
                HD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); 
                return nullptr;
            case RendererAPI::API::OpenGL: 
                return CreateRef<OpenGLFramebuffer>(spec);
        }   

        HD_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}
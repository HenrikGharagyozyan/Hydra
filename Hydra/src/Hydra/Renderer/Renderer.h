#pragma once

#include "RenderCommand.h"

#include "OrtographicCamera.h"
#include "Shader.h"

namespace Hydra 
{

    class Renderer
    {
    public:
        static void BeginScene(OrtographicCamera& camera);
        static void EndScene();

        static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

    private:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };

        static SceneData* s_SceneData;
    };

}
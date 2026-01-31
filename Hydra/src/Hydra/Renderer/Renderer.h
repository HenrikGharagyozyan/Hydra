#pragma once

#include "RenderCommand.h"

#include "OrtographicCamera.h"
#include "Shader.h"

namespace Hydra 
{

    class Renderer
    {
    public:
        static void Init();

        static void BeginScene(OrtographicCamera& camera);
        static void EndScene();

        static void Submit(const Ref<Shader>& shader, 
                            const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

    private:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };

        static SceneData* s_SceneData;
    };

}
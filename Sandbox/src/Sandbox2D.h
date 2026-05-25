#pragma once

#include "Hydra.h"

class Sandbox2D : public Hydra::Layer
{
public:
    Sandbox2D();
    virtual ~Sandbox2D() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void OnUpdate(Hydra::Timestep ts) override;
    virtual void OnImGuiRender() override;
    void OnEvent(Hydra::Event& event) override;

private:
    Hydra::OrthographicCameraController m_CameraController;

    // Temp
    Hydra::Ref<Hydra::VertexArray> m_SquareVA;
    Hydra::Ref<Hydra::Shader> m_FlatColorShader;
    Hydra::Ref<Hydra::Framebuffer> m_Framebuffer;

    Hydra::Ref<Hydra::Texture2D> m_CheckerboardTexture;

    glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};
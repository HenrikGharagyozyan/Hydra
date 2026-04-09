#include "Sandbox2D.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
    m_SquareVA = Hydra::VertexArray::Create();

    float squareVertices[5 * 4] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f};

    Hydra::Ref<Hydra::VertexBuffer> squareVB;
    squareVB.reset(Hydra::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
    squareVB->SetLayout({{Hydra::ShaderDataType::Float3, "a_Position"}});

    m_SquareVA->AddVertexBuffer(squareVB);

    unsigned int squareIndices[6] = {0, 1, 2, 2, 3, 0};
    Hydra::Ref<Hydra::IndexBuffer> squareIB;
    squareIB.reset(Hydra::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
    m_SquareVA->SetIndexBuffer(squareIB);

    m_FlatColorShader = Hydra::Shader::Create("assets/shaders/FlatColorShader.glsl");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Hydra::Timestep ts)
{
    // Update
    m_CameraController.OnUpdate(ts);

    // Render
    Hydra::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    Hydra::RenderCommand::Clear();

    Hydra::Renderer::BeginScene(m_CameraController.GetCamera());

    std::dynamic_pointer_cast<Hydra::OpenGLShader>(m_FlatColorShader)->Bind();
    std::dynamic_pointer_cast<Hydra::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

    m_FlatColorShader->Bind();
    Hydra::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    Hydra::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void Sandbox2D::OnEvent(Hydra::Event &event)
{
    m_CameraController.OnEvent(event);
}
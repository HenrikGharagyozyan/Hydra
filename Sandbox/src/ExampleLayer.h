#pragma once

#include "Hydra.h"

class ExampleLayer : public Hydra::Layer
{
public:
	ExampleLayer();
    virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
    virtual void OnDetach() override;

	void OnUpdate(Hydra::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Hydra::Event& e) override;

private:
	Hydra::ShaderLibrary m_ShaderLibrary; 
	Hydra::Ref<Hydra::Shader> m_Shader;
	Hydra::Ref<Hydra::VertexArray> m_VertexArray;

	Hydra::Ref<Hydra::Shader> m_FlatColorShader;
	Hydra::Ref<Hydra::VertexArray> m_SquareVA;

	Hydra::Ref<Hydra::Texture2D> m_Texture;
	Hydra::Ref<Hydra::Texture2D> m_GoogleLogoTexture;

	Hydra::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};
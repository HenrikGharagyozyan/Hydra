#include <Hydra.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Hydra::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Hydra::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f};

		Hydra::Ref<Hydra::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Hydra::VertexBuffer::Create(vertices, sizeof(vertices)));
		Hydra::BufferLayout layout = {
			{Hydra::ShaderDataType::Float3, "a_Position"},
			{Hydra::ShaderDataType::Float4, "a_Color"},
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = {0, 1, 2};
		Hydra::Ref<Hydra::IndexBuffer> indexBuffer;
		indexBuffer.reset(Hydra::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Hydra::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,	1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Hydra::Ref<Hydra::VertexBuffer> squareVB;
		squareVB.reset(Hydra::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Hydra::ShaderDataType::Float3, "a_Position" },
			{ Hydra::ShaderDataType::Float2, "a_TexCoord" }
		});

		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[6] = {0, 1, 2, 2, 3, 0};
		Hydra::Ref<Hydra::IndexBuffer> squareIB;
		squareIB.reset(Hydra::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
        )";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
        )";

		m_Shader.reset(Hydra::Shader::Create(vertexSrc, fragmentSrc));

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader.reset(Hydra::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));


		std::string textureShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string textureShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		m_TextureShader.reset(Hydra::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));

		m_Texture = Hydra::Texture2D::Create("assets/textures/Checkerboard.png");

		std::dynamic_pointer_cast<Hydra::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Hydra::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Hydra::Timestep ts) override
	{
		if (Hydra::Input::IsKeyPressed(HD_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Hydra::Input::IsKeyPressed(HD_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Hydra::Input::IsKeyPressed(HD_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Hydra::Input::IsKeyPressed(HD_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Hydra::Input::IsKeyPressed(HD_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (Hydra::Input::IsKeyPressed(HD_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Hydra::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
		Hydra::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Hydra::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Hydra::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Hydra::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; ++y)
		{
			for (int x = 0; x < 20; ++x)
			{
				glm::vec3 pos(y * 0.11f, x * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
	
				Hydra::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		m_Texture->Bind();
		Hydra::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Triangle
		// Hydra::Renderer::Submit(m_Shader, m_VertexArray);

		Hydra::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Hydra::Event &event) override
	{
	}

private:
	Hydra::Ref<Hydra::Shader> m_Shader;
	Hydra::Ref<Hydra::VertexArray> m_VertexArray;

	Hydra::Ref<Hydra::Shader> m_FlatColorShader;
	Hydra::Ref<Hydra::Shader> m_TextureShader;
	Hydra::Ref<Hydra::VertexArray> m_SquareVA;

	Hydra::Ref<Hydra::Texture2D> m_Texture;

	Hydra::OrtographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Hydra::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
	}
};

Hydra::Application *Hydra::CreateApplication()
{
	return new Sandbox();
}
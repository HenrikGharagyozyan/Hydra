#include <Hydra.h>

class ExampleLayer : public Hydra::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
		, m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
		, m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Hydra::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Hydra::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Hydra::VertexBuffer::Create(vertices, sizeof(vertices)));
		Hydra::BufferLayout layout = {
			{ Hydra::ShaderDataType::Float3, "a_Position" },
			{ Hydra::ShaderDataType::Float4, "a_Color" },
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		std::shared_ptr<Hydra::IndexBuffer> indexBuffer;
		indexBuffer.reset(Hydra::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);


		m_SquareVA.reset(Hydra::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<Hydra::VertexBuffer> squareVB;
		squareVB.reset(Hydra::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Hydra::ShaderDataType::Float3, "a_Position" }
		});

		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Hydra::IndexBuffer> squareIB;
		squareIB.reset(Hydra::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
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

        m_Shader.reset(new Hydra::Shader(vertexSrc, fragmentSrc));


		std::string blueShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Hydra::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate() override
	{
		if (Hydra::Input::IsKeyPressed(HD_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed;
		else if (Hydra::Input::IsKeyPressed(HD_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed;

		if (Hydra::Input::IsKeyPressed(HD_KEY_UP))	
			m_CameraPosition.y += m_CameraMoveSpeed;
		else if (Hydra::Input::IsKeyPressed(HD_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed;


		if (Hydra::Input::IsKeyPressed(HD_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed;
		else if (Hydra::Input::IsKeyPressed(HD_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed;

		Hydra::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Hydra::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Hydra::Renderer::BeginScene(m_Camera);

		Hydra::Renderer::Submit(m_BlueShader, m_SquareVA);
		Hydra::Renderer::Submit(m_Shader, m_VertexArray);

		Hydra::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{

	}

	void OnEvent(Hydra::Event& event) override
	{
	}

private:
	std::shared_ptr<Hydra::Shader> m_Shader;
	std::shared_ptr<Hydra::VertexArray> m_VertexArray; 

	std::shared_ptr<Hydra::Shader> m_BlueShader;	
	std::shared_ptr<Hydra::VertexArray> m_SquareVA;

	Hydra::OrtographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 0.05f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 2.0f;
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

Hydra::Application* Hydra::CreateApplication()
{
	return new Sandbox();
}
#include "hdpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Hydra
{

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
        case Hydra::ShaderDataType::Float:
            return GL_FLOAT;
        case Hydra::ShaderDataType::Float2:
            return GL_FLOAT;
        case Hydra::ShaderDataType::Float3:
            return GL_FLOAT;
        case Hydra::ShaderDataType::Float4:
            return GL_FLOAT;
        case Hydra::ShaderDataType::Mat3:
            return GL_FLOAT;
        case Hydra::ShaderDataType::Mat4:
            return GL_FLOAT;
        case Hydra::ShaderDataType::Int:
            return GL_INT;
        case Hydra::ShaderDataType::Int2:
            return GL_INT;
        case Hydra::ShaderDataType::Int3:
            return GL_INT;
        case Hydra::ShaderDataType::Int4:
            return GL_INT;
        case Hydra::ShaderDataType::Bool:
            return GL_BOOL;
        }

        HD_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        HD_PROFILE_FUNCTION();

        glCreateVertexArrays(1,& m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        HD_PROFILE_FUNCTION();

        glDeleteVertexArrays(1,& m_RendererID);
    }

    void OpenGLVertexArray::Bind() const
    {
        HD_PROFILE_FUNCTION();

        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::Unbind() const
    {
        HD_PROFILE_FUNCTION();

        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
    {
        HD_PROFILE_FUNCTION();

        HD_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

        glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();

        const auto& layout = vertexBuffer->GetLayout();
        for (const auto& element : vertexBuffer->GetLayout())
        {
            switch (element.Type)
			{
				case ShaderDataType::Float:
				case ShaderDataType::Float2:
				case ShaderDataType::Float3:
				case ShaderDataType::Float4:
				case ShaderDataType::Int:
				case ShaderDataType::Int2:
				case ShaderDataType::Int3:
				case ShaderDataType::Int4:
				case ShaderDataType::Bool:
				{
					glEnableVertexAttribArray(m_VertexBufferIndex);
					glVertexAttribPointer(m_VertexBufferIndex,
						element.GetComponentCount(),
						ShaderDataTypeToOpenGLBaseType(element.Type),
						element.Normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)element.Offset
                    );
					++m_VertexBufferIndex;
					break;
				}
				case ShaderDataType::Mat3:
				case ShaderDataType::Mat4:
				{
					uint8_t count = element.GetComponentCount();
					for (uint8_t i = 0; i < count; ++i)
					{
						glEnableVertexAttribArray(m_VertexBufferIndex);
						glVertexAttribPointer(m_VertexBufferIndex,
                                count,
                                ShaderDataTypeToOpenGLBaseType(element.Type),
                                element.Normalized ? GL_TRUE : GL_FALSE,
                                layout.GetStride(),
                                (const void*)(sizeof(float) * count * i)
                            );
						glVertexAttribDivisor(m_VertexBufferIndex, 1);
						++m_VertexBufferIndex;
					}
					break;
				}
				default:
					HD_CORE_ASSERT(false, "Unknown ShaderDataType!");
			}
        }

        m_VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
    {
        HD_PROFILE_FUNCTION();

        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;
    }
    
}

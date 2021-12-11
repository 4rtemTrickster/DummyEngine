#include "DEpch.h"
#include "OpenGLVertexArray.h"

#include "glad/glad.h"

namespace Dummy
{
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::FLOAT:   return GL_FLOAT;
        case ShaderDataType::FLOAT2:  return GL_FLOAT;
        case ShaderDataType::FLOAT3:  return GL_FLOAT;
        case ShaderDataType::FLOAT4:  return GL_FLOAT;
            
        case ShaderDataType::INT:     return GL_INT;
        case ShaderDataType::INT2:    return GL_INT;
        case ShaderDataType::INT3:    return GL_INT;
        case ShaderDataType::INT4:    return GL_INT;
            
        case ShaderDataType::MAT3:    return GL_FLOAT;
        case ShaderDataType::MAT4:    return GL_FLOAT;
            
        case ShaderDataType::BOOL:    return GL_BOOL;
        }

        DE_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }
    
    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &RendererID);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(RendererID);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
    {
        DE_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout!");
        
        glBindVertexArray(RendererID);
        vertexBuffer->Bind();

        uint32_t index = 0;
        for (const auto& element : vertexBuffer->GetLayout())
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(
                index,
                element.GetComponentCount(),
                ShaderDataTypeToOpenGLBaseType(element.Type),
                element.Normalized ? GL_TRUE : GL_FALSE,
                vertexBuffer->GetLayout().GetStride(),
                reinterpret_cast<const void*>(element.Offset));
            
            ++index;
        }

        VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(RendererID);
        indexBuffer->Bind();

        IndexBuffer_ = indexBuffer;
    }

}

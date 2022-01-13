#include "DEpch.h"
#include "OpenGLIndexBuffer.h"

#include <glad/glad.h>

namespace Dummy
{
    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, size_t count)
        :   Count(count)
    {
        glCreateBuffers(1, &RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, Count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &RendererID);
    }

    void OpenGLIndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID);
    }

    void OpenGLIndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

}

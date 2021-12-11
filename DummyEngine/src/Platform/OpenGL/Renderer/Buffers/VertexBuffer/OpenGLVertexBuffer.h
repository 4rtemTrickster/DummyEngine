#pragma once
#include "Dummy/Renderer/Buffers/VertexBuffer/VertexBuffer.h"

namespace Dummy
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, size_t size);
        virtual ~OpenGLVertexBuffer() override;
        
        void Bind() const override;
        void Unbind() const override;
        
        void SetLayout(const BufferLayout& layout) override { Layout = layout; }
        const BufferLayout& GetLayout() const override { return Layout; }

    protected:
        uint32_t RendererID;
        BufferLayout Layout;
    };
}


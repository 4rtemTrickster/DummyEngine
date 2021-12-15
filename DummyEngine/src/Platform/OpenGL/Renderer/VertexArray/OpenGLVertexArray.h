#pragma once
#include "Dummy/Renderer/VertexArray/VertexArray.h"

namespace Dummy
{
    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray() override;
        
        void Bind() const override;
        void Unbind() const override;
        
        void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
        void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;
        
        const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return VertexBuffers; }
        const Ref<IndexBuffer>& GetIndexBuffer() const override { return IndexBuffer_; }

    protected:
        std::vector<Ref<VertexBuffer>> VertexBuffers;
        Ref<IndexBuffer> IndexBuffer_;

        uint32_t RendererID;
    };
}

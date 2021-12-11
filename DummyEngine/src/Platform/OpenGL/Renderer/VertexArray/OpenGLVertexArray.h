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
        
        void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
        void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
        
        const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override { return VertexBuffers; }
        const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return IndexBuffer_; }

    protected:
        std::vector<std::shared_ptr<VertexBuffer>> VertexBuffers;
        std::shared_ptr<IndexBuffer> IndexBuffer_;

        uint32_t RendererID;
    };
}

#pragma once
#include "Dummy/Renderer/Buffers/IndexBuffer/IndexBuffer.h"

namespace Dummy
{
    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t* indices, size_t count);
        virtual ~OpenGLIndexBuffer() override;
        
        void Bind() const override;
        void Unbind() const override;
        size_t GetCount() const override { return Count; }

    protected:
        uint32_t RendererID;
        size_t Count;
    };
    
}

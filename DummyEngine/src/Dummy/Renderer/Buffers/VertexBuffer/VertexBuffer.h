#pragma once
#include "Dummy/Renderer/Buffers/BufferLayout/BufferLayout.h"

namespace Dummy
{
    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;

        virtual void Bind() const  = 0;
        virtual void Unbind() const = 0;

        virtual void SetLayout(const BufferLayout& layout) = 0;
        virtual const BufferLayout& GetLayout() const = 0;

        static Ref<VertexBuffer> Create(float* vertices, size_t size);
    };
    
}

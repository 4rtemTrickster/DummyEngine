#pragma once

namespace Dummy
{
    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() {}

        virtual void Bind() const  = 0;
        virtual void Unbind() const = 0;

        static VertexBuffer* Create(float* vertices, size_t size);
    };
    
}

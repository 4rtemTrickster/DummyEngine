#pragma once

namespace Dummy
{
    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual size_t GetCount() const  = 0;

        static IndexBuffer* Create(uint32_t* indices, size_t count);
    };
}

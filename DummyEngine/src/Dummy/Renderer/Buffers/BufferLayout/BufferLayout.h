#pragma once
#include "Dummy/Core.h"
#include "Dummy/Log/Log.h"

namespace Dummy
{
    enum class ShaderDataType
    {
        NONE = 0,
        
        FLOAT,
        FLOAT2,
        FLOAT3,
        FLOAT4,

        INT,
        INT2,
        INT3,
        INT4,
        
        MAT3,
        MAT4,

        BOOL
    };

    static uint32_t ShaderDataTypeSize(ShaderDataType type);
    
    struct BufferElement
    {
        std::string Name;
        ShaderDataType Type;
        uint32_t Size;
        uint32_t Offset;
        bool Normalized;

        BufferElement() {}
        BufferElement(ShaderDataType type, const std::string name, bool normalized = false);

        uint32_t GetComponentCount() const;
    };
    
    class BufferLayout
    {
    public:
        BufferLayout() {}
        BufferLayout(const std::initializer_list<BufferElement>& elements);
        
        inline const std::vector<BufferElement>& GetElements() const { return BufferElements; }
        inline uint32_t GetStride() const { return Stride; }

        std::vector<BufferElement>::iterator begin() { return BufferElements.begin(); }
        std::vector<BufferElement>::iterator end() { return BufferElements.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return BufferElements.cbegin(); }
        std::vector<BufferElement>::const_iterator end() const { return BufferElements.cend(); }
    protected:

        void CalculateOffsetsAndStride();
        
        std::vector<BufferElement> BufferElements;
        uint32_t Stride = 0;
    };
}

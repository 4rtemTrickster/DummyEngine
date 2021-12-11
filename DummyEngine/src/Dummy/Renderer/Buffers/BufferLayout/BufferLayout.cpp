#include "DEpch.h"
#include "BufferLayout.h"

namespace Dummy
{
    uint32_t ShaderDataTypeSize(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::FLOAT:  return 4;
        case ShaderDataType::FLOAT2: return 4 * 2;
        case ShaderDataType::FLOAT3: return 4 * 3;
        case ShaderDataType::FLOAT4: return 4 * 4;
            
        case ShaderDataType::INT:    return 4;
        case ShaderDataType::INT2:   return 4 * 2;
        case ShaderDataType::INT3:   return 4 * 3;
        case ShaderDataType::INT4:   return 4 * 4;
                 
        case ShaderDataType::MAT3:   return 4 * 3 * 3;
        case ShaderDataType::MAT4:   return 4 * 4 * 4;
                 
        case ShaderDataType::BOOL:   return 1;
        }

        DE_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    BufferElement::BufferElement(ShaderDataType type, const std::string name, bool normalized)
        : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized) {}

    uint32_t BufferElement::GetComponentCount() const
    {
        switch (Type)
        {
        case ShaderDataType::FLOAT:  return 1;
        case ShaderDataType::FLOAT2: return 2;
        case ShaderDataType::FLOAT3: return 3;
        case ShaderDataType::FLOAT4: return 4;
            
        case ShaderDataType::INT:    return 1;
        case ShaderDataType::INT2:   return 2;
        case ShaderDataType::INT3:   return 3;
        case ShaderDataType::INT4:   return 4;
                 
        case ShaderDataType::MAT3:   return 3 * 3;
        case ShaderDataType::MAT4:   return 4 * 4;
                 
        case ShaderDataType::BOOL:   return 1;
        }

        DE_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements)
        : BufferElements(elements)
    {
        CalculateOffsetsAndStride();
    }

    void BufferLayout::CalculateOffsetsAndStride()
    {
        uint32_t offset = 0;
        Stride = 0;

        for(auto& element : BufferElements)
        {
            element.Offset = offset;
            offset += element.Size;
            Stride += element.Size;
        }
    }

    
}

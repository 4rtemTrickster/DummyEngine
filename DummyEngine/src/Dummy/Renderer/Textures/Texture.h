#pragma once

namespace Dummy
{
    class Texture
    {
    public:
        virtual ~Texture() = default;
        
        virtual uint32_t GetWidth() = 0;
        virtual uint32_t GetHeight() = 0;

        virtual void Bind(uint32_t slot = 0) const = 0;
    };
    
}

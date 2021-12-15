#pragma once
#include "Dummy/Renderer/Textures/Texture2D/Texture2D.h"

namespace Dummy
{
    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(const std::filesystem::path& path);
        ~OpenGLTexture2D() override;
        
        uint32_t GetWidth() override { return Width; }
        uint32_t GetHeight() override { return Height; }
        
        void Bind(uint32_t slot) const override;

    protected:

        uint32_t RendererID;
        
        uint32_t Width;
        uint32_t Height;
    };
    
}

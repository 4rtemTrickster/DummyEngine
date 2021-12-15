#pragma once
#include "Dummy/Core.h"
#include "Dummy/Renderer/Textures/Texture.h"

namespace Dummy
{
    class Texture2D : public Texture
    {
    public:
        static Ref<Texture2D> Create(const std::filesystem::path& path);
    };
    
}

#include "DEpch.h"
#include "Texture2D.h"

#include "Dummy/Renderer/Renderer.h"
#include "Platform/OpenGL/Renderer/Textures/OpenGLTexture2D.h"

namespace Dummy
{
    Ref<Texture2D> Texture2D::Create(const std::filesystem::path& path)
    {
        switch(Renderer::GetCurrentRendererAPI())
        {
        case RendererAPI::API::NONE:     DE_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!"); return nullptr;
        case RendererAPI::API::OPENGL:   return std::make_shared<OpenGLTexture2D>(path);
        case RendererAPI::API::DIRECT3D: DE_CORE_ASSERT(false, "RendererAPI::DIRECT3D is currently not supported!"); return nullptr;
        default: DE_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
        }
    }
}

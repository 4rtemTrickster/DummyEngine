#include "DEpch.h"
#include "RendererAPI.h"

#include "Renderer.h"
#include "Platform/OpenGL/Renderer/OpenGLRendererAPI.h"

namespace Dummy
{
    RendererAPI::API RendererAPI::CurrentAPI = API::OPENGL;

    Scope<RendererAPI> RendererAPI::Create()
    {
        switch(Renderer::GetCurrentRendererAPI())
        {
        case RendererAPI::API::NONE:     DE_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!"); return nullptr;
        case RendererAPI::API::OPENGL:   return CreateScope<OpenGLRendererAPI>();
        case RendererAPI::API::DIRECT3D: DE_CORE_ASSERT(false, "RendererAPI::DIRECT3D is currently not supported!"); return nullptr;
        default: DE_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
        }
    }
}

#include "DEpch.h"

#include "GraphicsContext.h"

#include "Dummy/Renderer/Renderer.h"
#include "Platform/OpenGL/Renderer/GraphicsContext/OpenGLContext.h"

namespace Dummy
{
    Scope<GraphicsContext> GraphicsContext::Create(void* window)
    {
        switch (Renderer::GetCurrentRendererAPI())
        {
        case RendererAPI::API::NONE: DE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OPENGL: return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
        case RendererAPI::API::DIRECT3D: DE_CORE_ASSERT(false, "RendererAPI::DIRECT3D is currently not supported!"); return nullptr;

        default: DE_CORE_ASSERT(false, "Unknown RendererAPI!");
        }

        return nullptr;
    }
}

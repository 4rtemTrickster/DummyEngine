#include "DEpch.h"
#include "VertexArray.h"

#include "Dummy/Renderer/Renderer.h"
#include "Platform/OpenGL/Renderer/VertexArray/openGLVertexArray.h"

namespace Dummy
{
    Ref<VertexArray> VertexArray::Create()
    {
        switch(Renderer::GetCurrentRendererAPI())
        {
        case RendererAPI::API::NONE:     DE_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!"); return nullptr;
        case RendererAPI::API::OPENGL:   return std::make_shared<OpenGLVertexArray>();
        case RendererAPI::API::DIRECT3D: DE_CORE_ASSERT(false, "RendererAPI::DIRECT3D is currently not supported!"); return nullptr;
        default: DE_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
        }
    }
}

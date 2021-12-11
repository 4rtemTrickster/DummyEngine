#include "DEpch.h"
#include "VertexArray.h"

#include "Dummy/Renderer/Renderer.h"
#include "Platform/OpenGL/Renderer/VertexArray/openGLVertexArray.h"

namespace Dummy
{
    VertexArray* VertexArray::Create()
    {
        switch(Renderer::GetCurrentRendererAPI())
        {
        case RendererAPI::NONE:     DE_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!"); return nullptr;
        case RendererAPI::OPENGL:   return new OpenGLVertexArray();
        case RendererAPI::DIRECT3D: DE_CORE_ASSERT(false, "RendererAPI::DIRECT3D is currently not supported!"); return nullptr;
        default: DE_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
        }
    }
}

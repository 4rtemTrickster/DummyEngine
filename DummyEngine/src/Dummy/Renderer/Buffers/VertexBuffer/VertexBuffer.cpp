#include "DEpch.h"
#include "VertexBuffer.h"

#include "Dummy/Renderer/Renderer.h"
#include "Platform/OpenGL/Renderer/Buffers/VertexBuffer/OpenGLVertexBuffer.h"

namespace Dummy
{
    Ref<VertexBuffer> VertexBuffer::Create(float* vertices, size_t size)
    {
        switch(Renderer::GetCurrentRendererAPI())
        {
        case RendererAPI::API::NONE:     DE_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!"); return nullptr;
        case RendererAPI::API::OPENGL:   return CreateRef<OpenGLVertexBuffer>(vertices, size);
        case RendererAPI::API::DIRECT3D: DE_CORE_ASSERT(false, "RendererAPI::DIRECT3D is currently not supported!"); return nullptr;
        default: DE_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
        }
    }
}

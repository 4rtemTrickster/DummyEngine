#include "DEpch.h"
#include "VertexBuffer.h"

#include "Dummy/Core.h"
#include "Dummy/Log/Log.h"
#include "Dummy/Renderer/Renderer.h"
#include "Platform/OpenGL/Renderer/Buffers/VertexBuffer/OpenGLVertexBuffer.h"

namespace Dummy
{
    VertexBuffer* VertexBuffer::Create(float* vertices, size_t size)
    {
        switch(Renderer::GetCurrentRendererAPI())
        {
        case RendererAPI::NONE:     DE_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!"); return nullptr;
        case RendererAPI::OPENGL:   return new OpenGLVertexBuffer(vertices, size);
        case RendererAPI::DIRECT3D: DE_CORE_ASSERT(false, "RendererAPI::DIRECT3D is currently not supported!"); return nullptr;
        default: DE_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
        }
    }
}

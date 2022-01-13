#include "DEpch.h"
#include "IndexBuffer.h"

#include "Dummy/Core.h"
#include "Dummy/Log/Log.h"
#include "Dummy/Renderer/Renderer.h"
#include "Platform/OpenGL/Renderer/Buffers/IndexBuffer/OpenGLIndexBuffer.h"

namespace Dummy
{
    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, size_t count)
    {
        switch(Renderer::GetCurrentRendererAPI())
        {
        case RendererAPI::API::NONE:     DE_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!"); return nullptr;
        case RendererAPI::API::OPENGL:   return CreateRef<OpenGLIndexBuffer>(indices, count);
        case RendererAPI::API::DIRECT3D: DE_CORE_ASSERT(false, "RendererAPI::DIRECT3D is currently not supported!"); return nullptr;
        default: DE_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
        }
    }
}

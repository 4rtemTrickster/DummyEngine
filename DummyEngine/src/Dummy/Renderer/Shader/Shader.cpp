#include "DEpch.h"
#include "Shader.h"

#include "Dummy/Application/Application.h"
#include "Dummy/Renderer/Renderer.h"
#include "Platform/OpenGL/Renderer/Shader/OpenGLShader.h"

namespace Dummy
{
    Ref<Shader> Shader::Create(const std::string& name)
    {
        switch(Renderer::GetCurrentRendererAPI())
        {
        case RendererAPI::API::NONE:     DE_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!"); return nullptr;
        case RendererAPI::API::OPENGL:   return std::make_shared<OpenGLShader>(name);
        case RendererAPI::API::DIRECT3D: DE_CORE_ASSERT(false, "RendererAPI::DIRECT3D is currently not supported!"); return nullptr;
        default: DE_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
        }
    }
}

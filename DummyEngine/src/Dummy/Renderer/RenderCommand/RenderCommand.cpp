#include "DEpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/Renderer/OpenGLRendererAPI.h"

namespace Dummy
{
    Scope<RendererAPI> RenderCommand::s_RendererAPI = CreateScope<OpenGLRendererAPI>();
}

#include "DEpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/Renderer/OpenGLRendererAPI.h"

namespace Dummy
{
    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}

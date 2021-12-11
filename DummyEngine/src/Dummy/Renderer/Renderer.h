#pragma once
#include "RendererAPI.h"

namespace Dummy
{
    class Renderer
    {
    public:
        static void BeginScene(); //TODO: Scene params
        static void EndScene();

        static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
        
        inline static RendererAPI::API GetCurrentRendererAPI() { return RendererAPI::GetCurrentAPI(); }

    };
}

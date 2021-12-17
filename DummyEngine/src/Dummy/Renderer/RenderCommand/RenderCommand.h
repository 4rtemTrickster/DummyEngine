#pragma once
#include "Dummy/Renderer/RendererAPI.h"

namespace Dummy
{
    class RenderCommand
    {
    public:
        inline static void Init() { s_RendererAPI->Init(); }
        
        inline static void SetClearColor(const glm::vec4& color) { s_RendererAPI->SetClearColor(color); }
        inline static void Clear() { s_RendererAPI->Clear(); }
        
        inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) { s_RendererAPI->DrawIndexed(vertexArray); }
    protected:
        
        static RendererAPI* s_RendererAPI;
    };
}

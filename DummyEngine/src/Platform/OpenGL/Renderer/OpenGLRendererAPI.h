#pragma once
#include "Dummy/Renderer/RendererAPI.h"

namespace Dummy
{
    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        void SetClearColor(const glm::vec4& color) override;
        void Clear() override;
        
        void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
    };
}

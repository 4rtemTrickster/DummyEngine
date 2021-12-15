#pragma once
#include "glm/glm.hpp"
#include "VertexArray/VertexArray.h"

namespace Dummy
{
    class RendererAPI
    {
    public:
        enum class API
        {
            NONE     = 0,
            OPENGL   = 1,
            DIRECT3D = 2 // :)
        };

        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;

        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

        static inline API GetCurrentAPI() { return CurrentAPI; }

    protected:
        static API CurrentAPI;
    };
}

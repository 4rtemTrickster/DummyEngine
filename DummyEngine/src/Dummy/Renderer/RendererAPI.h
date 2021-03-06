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

        virtual void Init() = 0;

        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;

        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

        static inline API GetCurrentAPI() { return CurrentAPI; }

        static Scope<RendererAPI> Create();

    protected:
        static API CurrentAPI;
    };
}

#pragma once

namespace Dummy
{
    enum class RendererAPI
    {
        NONE     = 0,
        OPENGL   = 1,
        DIRECT3D = 2 // :)
    };
        
    class Renderer
    {
    public:
        inline static RendererAPI GetCurrentRendererAPI() { return CurrentRendererAPI; }
    protected:
        static RendererAPI CurrentRendererAPI;
    };
}

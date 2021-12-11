#pragma once
#include "Dummy/Renderer/GraphicsContext/GraphicsContext.h"
#include "GLFW/glfw3.h"

namespace Dummy
{
    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow* windowHandle);
        
        void Init() override;
        void SwapBuffers() override;

    protected:
        GLFWwindow* WindowHandle;
    };
    
}

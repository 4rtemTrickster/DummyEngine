#include "DEpch.h"
#include "OpenGLContext.h"

#include "Dummy/Core.h"
#include "Dummy/Log/Log.h"
#include "glad/glad.h"

namespace Dummy
{

    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : WindowHandle(windowHandle)
    {
        DE_CORE_ASSERT(windowHandle, "Window handle is null!");
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(WindowHandle);

        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        DE_CORE_ASSERT(status, "Failed to initialize Glad!");

        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        DE_CORE_INFO("OpenGL info:");
        DE_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
        DE_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
        DE_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(WindowHandle);
    }
}

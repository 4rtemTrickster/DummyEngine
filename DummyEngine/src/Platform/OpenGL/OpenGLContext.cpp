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

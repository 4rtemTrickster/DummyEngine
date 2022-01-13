#include "DEpch.h"
#include "OpenGLContext.h"

#include "Dummy/Core.h"
#include <glad/glad.h>

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

#ifdef DE_ENABLE_ASSERTS
        int versionMajor;
        int versionMinor;
        glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
        glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

        DE_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Dummy requires at least OpenGL version 4.5!");
#endif
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(WindowHandle);
    }
}

#include "DEpch.h"

#include "WindowsWindow.h"

#include "Dummy/Core.h"
#include "Dummy/Log/Log.h"

namespace Dummy
{
    static bool bGLFWInitialized = false;

    Window* Window::Create(const WindowProps& props)
    {
        return new WindowsWindow(props);
    }
    
    WindowsWindow::WindowsWindow(const WindowProps& props)
    {
        Init(props);
    }

    WindowsWindow::~WindowsWindow()
    {
        Shutdown();
    }

    void WindowsWindow::Init(const WindowProps& props)
    {
        Data.Title = props.Title;
        Data.Width = props.Width;
        Data.Height = props.Height;

        DE_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

        if(!bGLFWInitialized)
        {
            int success = glfwInit();
            DE_CORE_ASSERT(success, "Could not initialize GLFW!");

            bGLFWInitialized = true;
        }

        Window = glfwCreateWindow(static_cast<int>(props.Width), static_cast<int>(props.Height), Data.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(Window);
        glfwSetWindowUserPointer(Window, &Data);
        SetVSync(true);
    }

    void WindowsWindow::Shutdown()
    {
        glfwDestroyWindow(Window);
    }

    void WindowsWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(Window);
    }

    void WindowsWindow::SetVSync(bool enabled)
    {
        glfwSwapInterval(enabled ? 1 : 0);

        Data.VSync = enabled;
    }

    bool WindowsWindow::IsVSync() const
    {
        return Data.VSync;
    }




    
}

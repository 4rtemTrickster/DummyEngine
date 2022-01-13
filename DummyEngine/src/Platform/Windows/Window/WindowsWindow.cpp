#include "DEpch.h"

#include "WindowsWindow.h"

#include "Dummy/Core.h"
#include "Dummy/Event/Events/ApplicationEvent.h"
#include "Dummy/Event/Events/KeyEvent.h"
#include "Dummy/Event/Events/MouseEvent.h"
#include "Dummy/Log/Log.h"
#include "Platform/OpenGL/Renderer/GraphicsContext/OpenGLContext.h"

namespace Dummy
{
    static bool bGLFWInitialized = false;

    static void GLFWErrorCallback(int error, const char* description)
    {
        DE_CORE_ERROR("[GLFW ERROR]: ({0}): {1}", error, description);
    }

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

        if (!bGLFWInitialized)
        {
            int success = glfwInit();
            DE_CORE_ASSERT(success, "Could not initialize GLFW!");

            glfwSetErrorCallback(GLFWErrorCallback);
            
            bGLFWInitialized = true;
        }

        Window = glfwCreateWindow(static_cast<int>(props.Width), static_cast<int>(props.Height), Data.Title.c_str(),
                                  nullptr, nullptr);

        Context = CreateScope<OpenGLContext>(Window);
        Context->Init();
        
        glfwSetWindowUserPointer(Window, &Data);
        SetVSync(true);
        
        glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  

        // Set GLFW callback's
        glfwSetWindowSizeCallback(Window, [](GLFWwindow* window, int width, int height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            data.Width = width;
            data.Height = height;

            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(Window, [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetKeyCallback(Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetCharCallback(Window, [](GLFWwindow* window, unsigned int keycode)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            KeyTypedEvent event(keycode);
            data.EventCallback(event);
        });

        glfwSetMouseButtonCallback(Window, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
            case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(Window, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrollEvent event(xOffset, yOffset);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(Window, [](GLFWwindow* window, double xPos, double yPos)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event(xPos, yPos);
            data.EventCallback(event);
        });
    }

    void WindowsWindow::Shutdown()
    {
        glfwDestroyWindow(Window);
    }

    void WindowsWindow::OnUpdate()
    {
        glfwPollEvents();
        Context->SwapBuffers();
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

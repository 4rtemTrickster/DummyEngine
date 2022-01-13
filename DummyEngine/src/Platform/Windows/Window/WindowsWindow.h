#pragma once

#include "Dummy/Window/Window.h"

#include <GLFW/glfw3.h>

#include "Dummy/Renderer/GraphicsContext/GraphicsContext.h"

namespace Dummy
{
    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProps& props);
        virtual ~WindowsWindow();

        void OnUpdate() override;

        inline unsigned int GetWidth() const override { return Data.Width; }
        inline unsigned int GetHeight() const override { return Data.Height; }

        // Window attributes
        inline void SetEventCallBack(const EventCallbackFn& callback) override { Data.EventCallback = callback; }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        inline virtual void* GetNativeWindow() const override { return Window; }

    protected:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();

        GLFWwindow* Window;
        Scope<GraphicsContext> Context;

        struct WindowData
        {
            std::string Title;
            unsigned int Width;
            unsigned int Height;
            bool VSync;

            EventCallbackFn EventCallback;
        };

        WindowData Data;
    };
    
}

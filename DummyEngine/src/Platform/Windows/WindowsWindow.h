﻿#pragma once

#include "Dummy/Window/Window.h"

#include <GLFW/glfw3.h>

namespace Dummy
{
    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProps& props);
        virtual ~WindowsWindow();

        void OnUpdate() override;

        inline uint GetWidth() const override { return Data.Width; }
        inline uint GetHeight() const override { return Data.Height; }

        // Window attributes
        inline void SetEventCallBack(const EventCallbackFn& callback) override { Data.EventCallback = callback; }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

    protected:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();

        GLFWwindow* Window;

        struct WindowData
        {
            std::string Title;
            uint Width;
            uint Height;
            bool VSync;

            EventCallbackFn EventCallback;
        };

        WindowData Data;
    };
    
}

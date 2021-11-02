#include "DEpch.h"
#include "Application.h"

#include "../Event/Events/ApplicationEvent.h"



namespace Dummy
{
    Application::Application()
    {
        window = std::unique_ptr<Window>(Window::Create());
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while(bRunning)
        {
            window->OnUpdate();
        }
    }
} 
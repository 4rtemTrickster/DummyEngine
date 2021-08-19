#include "Application.h"

#include "../Event/Events/ApplicationEvent.h"



namespace Dummy
{
    Application::Application()
    {
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        WindowResizeEvent e(1280, 720);

        DE_TRACE(e);
            
        while(true)
        {
        }
    }
} 
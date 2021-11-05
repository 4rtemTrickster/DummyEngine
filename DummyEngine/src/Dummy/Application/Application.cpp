#include "DEpch.h"

#include "Application.h"

#include "glad/glad.h"


namespace Dummy
{
    Application* Application::Instance = nullptr;
    
    Application::Application()
    {
        DE_CORE_ASSERT(!Instance, "Application already exists!");
        Instance = this;
        
        window = std::unique_ptr<Window>(Window::Create());
        window->SetEventCallBack(BIND_EVENT_FN(Application::OnEvent));
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while(bRunning)
        {
            glClearColor(1.0f, 0.0f, 1.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            
            for(Layer* layer : Layer_Stack)
                layer->OnUpdate();

            
            window->OnUpdate();
        }
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);

        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
        
        for(auto it = Layer_Stack.end(); it != Layer_Stack.begin(); )
        {
            (*--it)->OnEvent(e);

            if(e.Handled) break;
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        Layer_Stack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay)
    {
        Layer_Stack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        bRunning = false;
        return true;
    }
} 
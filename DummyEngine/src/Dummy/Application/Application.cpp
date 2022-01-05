#include "DEpch.h"

#include "Application.h"
#include "imgui.h"
#include "Dummy/Input/Input.h"
#include "Dummy/Renderer/Renderer.h"
#include "GLFW/glfw3.h"


namespace Dummy
{
    Application* Application::Instance = nullptr;
    
    Application::Application()
    {
        DE_CORE_ASSERT(!Instance, "Application already exists!");
        Instance = this;
        
        window = Scope<Window>(Window::Create());
        window->SetEventCallBack(DE_BIND_EVENT_FN(Application::OnEvent));

        Renderer::Init();

        imGuiLayer = new ImGuiLayer();
        PushOverlay(imGuiLayer);
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while(bRunning)
        {
            float time = static_cast<float>(glfwGetTime()); //TODO: Platform::GetTime();
            Timestep timestep = time - LastFrameTime;
            LastFrameTime = time;

            if (!bMinimized)
                for(Layer* layer : Layer_Stack)
                    layer->OnUpdate(timestep);

            imGuiLayer->Begin();
            for(Layer* layer : Layer_Stack)
                layer->OnImGuiRender();
            imGuiLayer->End();
            
            window->OnUpdate();
        }
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);

        dispatcher.Dispatch<WindowCloseEvent>(DE_BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(DE_BIND_EVENT_FN(Application::OnWindowResize));
        
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

    bool Application::OnWindowResize(WindowResizeEvent& e)
    {
        if(e.GetWidth() == 0 || e.GetHeight() == 0)
        {
            bMinimized = true;
            return false;
        }

        bMinimized = false;

        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
        
        return false;
    }
} 
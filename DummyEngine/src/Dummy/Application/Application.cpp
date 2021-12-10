#include "DEpch.h"

#include "Application.h"


#include "Dummy/Input/Input.h"
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

        imGuiLayer = new ImGuiLayer();
        PushOverlay(imGuiLayer);

        glGenVertexArrays(1, &VertexArray);
        glBindVertexArray(VertexArray);

        glGenBuffers(1, &VertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);

        float vertices[3 * 3] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        glGenBuffers(1, &IndexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);

        uint indices[3] = {0, 1, 2};
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while(bRunning)
        {
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glBindVertexArray(VertexArray);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
            
            for(Layer* layer : Layer_Stack)
                layer->OnUpdate();


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
#include "DEpch.h"

#include "Application.h"


#include "Dummy/Input/Input.h"
#include "Dummy/Renderer/Renderer.h"
#include "Dummy/Renderer/Buffers/BufferLayout/BufferLayout.h"
#include "Dummy/Renderer/Buffers/VertexBuffer/VertexBuffer.h"
#include "Dummy/Renderer/RenderCommand/RenderCommand.h"


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
        
        VertexArray_.reset(VertexArray::Create());

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.0f, 0.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.0f, 0.8f, 0.0f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 0.8f, 1.0f
        };

        std::shared_ptr<VertexBuffer> VB;
        VB.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        VB->SetLayout(
            {
                { ShaderDataType::FLOAT3, "a_Position" },
                { ShaderDataType::FLOAT4, "a_Color" }
            });

        VertexArray_->AddVertexBuffer(VB);
        

        unsigned int indices[3] = {0, 1, 2};
        std::shared_ptr<IndexBuffer> IB;
        IB.reset(IndexBuffer::Create(indices, 3));

        VertexArray_->SetIndexBuffer(IB);

        std::string vertexSrc = R"(
            #version 330 core
    
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            out vec4 v_Color;
    
            void main()
            {
                v_Color = a_Color;
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

        std::string fragmentSrc = R"(
            #version 330 core
    
            layout(location = 0) out vec4 color;
            in vec4 v_Color;
    
            void main()
            {
                color = v_Color;
            }
        )";

        shader_ = std::make_unique<Shader>(vertexSrc,fragmentSrc);
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while(bRunning)
        {
            RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 0.0f});
            RenderCommand::Clear();

            shader_->Bind();
            Renderer::BeginScene();
            Renderer::Submit( VertexArray_);
            Renderer::EndScene();
          
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
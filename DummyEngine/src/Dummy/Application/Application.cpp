#include "DEpch.h"

#include "Application.h"

#include <glm/gtc/type_ptr.inl>


#include "imgui.h"
#include "Dummy/Input/Input.h"
#include "Dummy/Renderer/Renderer.h"
#include "Dummy/Renderer/Buffers/BufferLayout/BufferLayout.h"
#include "Dummy/Renderer/Buffers/VertexBuffer/VertexBuffer.h"
#include "Dummy/Renderer/RenderCommand/RenderCommand.h"


namespace Dummy
{
    Application* Application::Instance = nullptr;
    
    Application::Application()
        :   Camera_({0.0f, 0.0f, -3.0f})
    {
        DE_CORE_ASSERT(!Instance, "Application already exists!");
        Instance = this;
        
        window = std::unique_ptr<Window>(Window::Create());
        window->SetEventCallBack(BIND_EVENT_FN(Application::OnEvent));

        imGuiLayer = new ImGuiLayer();
        PushOverlay(imGuiLayer);
        
        VertexArray_.reset(VertexArray::Create());

        float vertices[24 * 7] = {
             0.5f, -0.5f, -0.5f,    0.8f, 0.0f, 0.0f, 1.0f,   // 0
            -0.5f, -0.5f, -0.5f,    0.0f, 0.8f, 0.0f, 1.0f,	  // 1
            -0.5f,  0.5f, -0.5f,    0.8f, 0.0f, 0.0f, 1.0f,	  // 2
             0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 0.8f, 1.0f,	  // 3
        
            // Front
            -0.5f, -0.5f,  0.5f,    0.8f, 0.0f, 0.0f, 1.0f,	 // 4
             0.5f, -0.5f,  0.5f,    0.0f, 0.8f, 0.0f, 1.0f,	 // 5
             0.5f,  0.5f,  0.5f,    0.8f, 0.0f, 0.0f, 1.0f,	 // 6
            -0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 0.8f, 1.0f,	 // 7
            // Left
            -0.5f, -0.5f, -0.5f,    0.8f, 0.0f, 0.0f, 1.0f,	// 8
            -0.5f, -0.5f,  0.5f,    0.0f, 0.8f, 0.0f, 1.0f,	// 9
            -0.5f,  0.5f,  0.5f,    0.8f, 0.0f, 0.0f, 1.0f,	// 10
            -0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 0.8f, 1.0f,	// 11
            // Right
             0.5f, -0.5f,  0.5f,    0.8f, 0.0f, 0.0f, 1.0f,	// 12
             0.5f, -0.5f, -0.5f,    0.0f, 0.8f, 0.0f, 1.0f,	// 13
             0.5f,  0.5f, -0.5f,    0.8f, 0.0f, 0.0f, 1.0f,	// 14
             0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 0.8f, 1.0f,	// 15
            // Bottom
            -0.5f, -0.5f, -0.5f,    0.8f, 0.0f, 0.0f, 1.0f,	// 16
             0.5f, -0.5f, -0.5f,    0.0f, 0.8f, 0.0f, 1.0f,	// 17
             0.5f, -0.5f,  0.5f,    0.8f, 0.0f, 0.0f, 1.0f,	// 18
            -0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 0.8f, 1.0f,	// 19
            // Top
            -0.5f,  0.5f,  0.5f,    0.8f, 0.0f, 0.0f, 1.0f,	// 20
             0.5f,  0.5f,  0.5f,    0.0f, 0.8f, 0.0f, 1.0f,	// 21
             0.5f,  0.5f, -0.5f,    0.8f, 0.0f, 0.0f, 1.0f,	// 22
            -0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 0.8f, 1.0f,	// 23
        };

        std::shared_ptr<VertexBuffer> VB;
        VB.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        VB->SetLayout(
            {
                { ShaderDataType::FLOAT3, "a_Position" },
                { ShaderDataType::FLOAT4, "a_Color" }
            });

        VertexArray_->AddVertexBuffer(VB);
        

        std::vector<uint32_t> indices =
        {
            0,	1,	2,
            2,	3,	0,
    
            4,	5,	6,
            6,	7,	4,
    
            8,	9,	10,
            10,	11,	8,
    
            12, 13, 14,
            14, 15, 12,
    
            16, 17, 18,
            18, 19, 16,
    
            20, 21, 22,
            22, 23, 20
        };
        
        std::shared_ptr<IndexBuffer> IB;
        IB.reset(IndexBuffer::Create(indices.data(), indices.size()));

        VertexArray_->SetIndexBuffer(IB);

        std::string vertexSrc = R"(
            #version 330 core
    
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjection;

            out vec4 v_Color;
    
            void main()
            {
                v_Color = a_Color;
                gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

        glm::vec3 tmpPosition(0.0f,0.0f,3.0f);
        float tmpYaw = -90.f;
        float tmpPitch = 0.0f;

        /////////
        
        while(bRunning)
        {
          
            RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 0.0f});
            RenderCommand::Clear();

            Camera_.SetPosition(tmpPosition);
            Camera_.SetRotation(tmpPitch, tmpYaw);

            Renderer::BeginScene(Camera_);

            Renderer::Submit(shader_, VertexArray_);
            
            Renderer::EndScene();
          
            for(Layer* layer : Layer_Stack)
                layer->OnUpdate();

            imGuiLayer->Begin();

            ImGui::SliderFloat3("Position", &tmpPosition.x, -10.f, 10.f);
            ImGui::SliderFloat("RotationYaw", &tmpYaw, -180.f, 180.f);
            ImGui::SliderFloat("RotationPitch", &tmpPitch, -89.f, 89.f);
            
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
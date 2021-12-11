#include "DEpch.h"

#include "Application.h"


#include "Dummy/Input/Input.h"
#include "Dummy/Renderer/Buffers/BufferLayout/BufferLayout.h"
#include "Dummy/Renderer/Buffers/VertexBuffer/VertexBuffer.h"
#include "glad/glad.h"


namespace Dummy
{
    Application* Application::Instance = nullptr;

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::FLOAT:   return GL_FLOAT;
        case ShaderDataType::FLOAT2:  return GL_FLOAT;
        case ShaderDataType::FLOAT3:  return GL_FLOAT;
        case ShaderDataType::FLOAT4:  return GL_FLOAT;
            
        case ShaderDataType::INT:     return GL_INT;
        case ShaderDataType::INT2:    return GL_INT;
        case ShaderDataType::INT3:    return GL_INT;
        case ShaderDataType::INT4:    return GL_INT;
            
        case ShaderDataType::MAT3:    return GL_FLOAT;
        case ShaderDataType::MAT4:    return GL_FLOAT;
            
        case ShaderDataType::BOOL:    return GL_BOOL;
        }

        DE_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }
    
    Application::Application()
    {
        DE_CORE_ASSERT(!Instance, "Application already exists!");
        Instance = this;
        
        window = std::unique_ptr<Window>(Window::Create());
        window->SetEventCallBack(BIND_EVENT_FN(Application::OnEvent));

        imGuiLayer = new ImGuiLayer();
        PushOverlay(imGuiLayer);

        glGenVertexArrays(1, &VertexArray_);
        glBindVertexArray(VertexArray_);


        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.0f, 0.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.0f, 0.8f, 0.0f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 0.8f, 1.0f
        };

        VertexBuffer_.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        {
            BufferLayout layout =
            {
                { ShaderDataType::FLOAT3, "a_Position" },
                { ShaderDataType::FLOAT4, "a_Color" }
            };
            
            VertexBuffer_->SetLayout(layout);
        }


        uint32_t index = 0;
        for (const auto& element : VertexBuffer_->GetLayout())
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(
                index,
                element.GetComponentCount(),
                ShaderDataTypeToOpenGLBaseType(element.Type),
                element.Normalized ? GL_TRUE : GL_FALSE,
                VertexBuffer_->GetLayout().GetStride(),
                reinterpret_cast<const void*>(element.Offset));
            
            ++index;
        }

        unsigned int indices[3] = {0, 1, 2};
        IndexBuffer_.reset(IndexBuffer::Create(indices, 3));

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
            glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            shader_->Bind();
            glBindVertexArray(VertexArray_);
            glDrawElements(GL_TRIANGLES, IndexBuffer_->GetCount(), GL_UNSIGNED_INT, nullptr);
            
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
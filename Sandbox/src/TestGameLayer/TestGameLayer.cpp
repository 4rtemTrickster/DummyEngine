#include "TestGameLayer.h"

#include "Platform/OpenGL/Renderer/Shader/OpenGLShader.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.inl>

TestGameLayer::TestGameLayer()
    :   Layer("TestGameLayer")
{

    CamCont.GetCamera().SetPosition({0.0f, 0.0f, 3.0f});
    
    VertexArray_ = Dummy::VertexArray::Create();

    std::vector<float> vertices = {
             0.5f, -0.5f, -0.5f,    0.0f, 0.0f,     // 0
            -0.5f, -0.5f, -0.5f,    1.0f, 0.0f,     // 1
            -0.5f,  0.5f, -0.5f,    1.0f, 1.0f,    // 2
             0.5f,  0.5f, -0.5f,    0.0f, 1.0f,     // 3

            // Front    
            -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,     // 4
             0.5f, -0.5f,  0.5f,    1.0f, 0.0f,     // 5
             0.5f,  0.5f,  0.5f,    1.0f, 1.0f,     // 6
            -0.5f,  0.5f,  0.5f,    0.0f, 1.0f,     // 7

            // Left
            -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,     // 8
            -0.5f, -0.5f,  0.5f,    1.0f, 0.0f,     // 9
            -0.5f,  0.5f,  0.5f,    1.0f, 1.0f,     // 10
            -0.5f,  0.5f, -0.5f,    0.0f, 1.0f,     // 11

            // Right
             0.5f, -0.5f,  0.5f,    0.0f, 0.0f,     // 12
             0.5f, -0.5f, -0.5f,    1.0f, 0.0f,     // 13
             0.5f,  0.5f, -0.5f,    1.0f, 1.0f,     // 14
             0.5f,  0.5f,  0.5f,    0.0f, 1.0f,     // 15

            // Bottom
            -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,     // 16
             0.5f, -0.5f, -0.5f,    1.0f, 0.0f,     // 17
             0.5f, -0.5f,  0.5f,    1.0f, 1.0f,     // 18
            -0.5f, -0.5f,  0.5f,    0.0f, 1.0f,     // 19
            // Top
            -0.5f,  0.5f,  0.5f,    0.0f, 0.0f,     // 20
             0.5f,  0.5f,  0.5f,    1.0f, 0.0f,     // 21
             0.5f,  0.5f, -0.5f,    1.0f, 1.0f,     // 22
            -0.5f,  0.5f, -0.5f,    0.0f, 1.0f,     // 23
    };

    Dummy::Ref<Dummy::VertexBuffer> VB;
    VB = Dummy::VertexBuffer::Create(vertices.data(), sizeof(float) * vertices.size());

    VB->SetLayout(
        {
            {Dummy::ShaderDataType::FLOAT3, "a_Position"},
            {Dummy::ShaderDataType::FLOAT2, "a_TexCoord"}
        });

    VertexArray_->AddVertexBuffer(VB);


    std::vector<uint32_t> indices =
    {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    Dummy::Ref<Dummy::IndexBuffer> IB;
    IB = Dummy::IndexBuffer::Create(indices.data(), indices.size());

    VertexArray_->SetIndexBuffer(IB);

    SHLib.Load("Cube");
    
    texture = Dummy::Texture2D::Create("res/Textures/test.png");

    std::dynamic_pointer_cast<Dummy::OpenGLShader>(SHLib.Get("Cube"))->Bind();
    std::dynamic_pointer_cast<Dummy::OpenGLShader>(SHLib.Get("Cube"))->UploadUniformInt("u_Texture", 0);
}

void TestGameLayer::OnUpdate(Dummy::Timestep ts)
{
    CamCont.OnUpdate(ts);
    
    Dummy::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 0.0f});
    Dummy::RenderCommand::Clear();
    
    Dummy::Renderer::BeginScene(CamCont.GetCamera());

    texture->Bind();
    Dummy::Renderer::Submit(SHLib.Get("Cube"), VertexArray_);

    Dummy::Renderer::EndScene();
}

void TestGameLayer::OnEvent(Dummy::Event& event)
{

    CamCont.OnEvent(event);
    
    Dummy::EventDispatcher dispatcher(event);

    dispatcher.Dispatch<Dummy::KeyPressedEvent>(DE_BIND_EVENT_FN(TestGameLayer::OnKeyPressedEvent));
}

bool TestGameLayer::OnKeyPressedEvent(Dummy::KeyPressedEvent& event)
{
    if(event.GetKeyCode() == DE_KEY_ESCAPE)
    {
        Dummy::Application::Get().OnEvent(Dummy::WindowCloseEvent());
        return false;
    }
    return true;
}
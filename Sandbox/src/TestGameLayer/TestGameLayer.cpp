#include "TestGameLayer.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.inl>

#include "imgui/imgui.h"
#include "Platform/OpenGL/Renderer/Shader/OpenGLShader.h"

TestGameLayer::TestGameLayer()
    :   Layer("TestGameLayer"), Camera_(CameraPosition)
{
    CameraPitch = Camera_.GetRotationPitch();
        CameraYaw = Camera_.GetRotationYaw();

        VertexArray_.reset(Dummy::VertexArray::Create());

        float vertices[24 * 7] = {
             0.5f, -0.5f, -0.5f,     // 0
            -0.5f, -0.5f, -0.5f,     // 1
            -0.5f,  0.5f, -0.5f,     // 2
             0.5f,  0.5f, -0.5f,     // 3

            // Front    
            -0.5f, -0.5f,  0.5f,     // 4
             0.5f, -0.5f,  0.5f,     // 5
             0.5f,  0.5f,  0.5f,     // 6
            -0.5f,  0.5f,  0.5f,     // 7

            // Left
            -0.5f, -0.5f, -0.5f,     // 8
            -0.5f, -0.5f,  0.5f,     // 9
            -0.5f,  0.5f,  0.5f,     // 10
            -0.5f,  0.5f, -0.5f,     // 11

            // Right
             0.5f, -0.5f,  0.5f,     // 12
             0.5f, -0.5f, -0.5f,     // 13
             0.5f,  0.5f, -0.5f,     // 14
             0.5f,  0.5f,  0.5f,     // 15

            // Bottom
            -0.5f, -0.5f, -0.5f,     // 16
             0.5f, -0.5f, -0.5f,     // 17
             0.5f, -0.5f,  0.5f,     // 18
            -0.5f, -0.5f,  0.5f,     // 19
            // Top
            -0.5f,  0.5f,  0.5f,     // 20
             0.5f,  0.5f,  0.5f,     // 21
             0.5f,  0.5f, -0.5f,     // 22
            -0.5f,  0.5f, -0.5f,     // 23
        };

        std::shared_ptr<Dummy::VertexBuffer> VB;
        VB.reset(Dummy::VertexBuffer::Create(vertices, sizeof(vertices)));

        VB->SetLayout(
            {
                {Dummy::ShaderDataType::FLOAT3, "a_Position"}
            });

        //{Dummy::ShaderDataType::FLOAT4, "a_Color"}

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

        std::shared_ptr<Dummy::IndexBuffer> IB;
        IB.reset(Dummy::IndexBuffer::Create(indices.data(), indices.size()));

        VertexArray_->SetIndexBuffer(IB);

        shader_.reset(Dummy::Shader::Create(vertexSrc,fragmentSrc));
}

void TestGameLayer::MoveCamera(Dummy::Timestep ts)
{
    static std::pair<float, float> LastPos;
    std::pair<float, float> CurrentPos = Dummy::Input::GetMousePos();

    if (static bool first = true)
    {
        LastPos = Dummy::Input::GetMousePos();
        first = false;
    }
        
    // Offset * sensitivity
    CameraYaw   += (CurrentPos.first - LastPos.first)   * CameraSensitivity * ts; 
    CameraPitch += (LastPos.second - CurrentPos.second) * CameraSensitivity * ts;

    LastPos.first = CurrentPos.first;
    LastPos.second = CurrentPos.second;

    if (CameraPitch > 89.0f)
        CameraPitch = 89.0f;
    if (CameraPitch < -89.0f)
        CameraPitch = -89.0f;

    Camera_.SetPosition(CameraPosition);
    Camera_.SetRotation(CameraPitch, CameraYaw);

    Camera_.UpdateCameraVectors();
}

void TestGameLayer::OnUpdate(Dummy::Timestep ts)
{
    if (Dummy::Input::IsKeyPressed(DE_KEY_W)) CameraPosition += (CameraSpeed * ts) * Camera_.GetForwardVector();
    else if (Dummy::Input::IsKeyPressed(DE_KEY_S)) CameraPosition -= (CameraSpeed * ts) * Camera_.GetForwardVector();

    if (Dummy::Input::IsKeyPressed(DE_KEY_D)) CameraPosition +=
        glm::normalize(glm::cross(Camera_.GetForwardVector(), Camera_.GetUpVector())) * (CameraSpeed * ts);
    else if (Dummy::Input::IsKeyPressed(DE_KEY_A)) CameraPosition -=
        glm::normalize(glm::cross(Camera_.GetForwardVector(), Camera_.GetUpVector())) * (CameraSpeed * ts);

    if(Dummy::Input::IsMouseMoved()) MoveCamera(ts);

    Dummy::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 0.0f});
    Dummy::RenderCommand::Clear();

    Camera_.SetPosition(CameraPosition);
    Camera_.SetRotation(CameraPitch, CameraYaw);

    Dummy::Renderer::BeginScene(Camera_);

    static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.f));

    std::dynamic_pointer_cast<Dummy::OpenGLShader>(shader_)->Bind();
    std::dynamic_pointer_cast<Dummy::OpenGLShader>(shader_)->UploadUniformFloat3("u_Color", CubeColor);

    for (int x = 0; x < 5; ++x)
    {
        for(int y = 0; y < 5; ++y)
        {
            for(int z = 0; z > -5; --z)
            {
                Dummy::Renderer::Submit(shader_, VertexArray_,
                    glm::rotate((glm::translate(glm::mat4(1.0f), glm::vec3(x * 2.5f, y * 2.5f, z * 2.5f)) * scale ),
                        45.0f * x + z,
                        glm::vec3(1.0f)));
            }
        }
    }
                

    Dummy::Renderer::EndScene();
}

void TestGameLayer::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Cube color", glm::value_ptr(CubeColor));
    ImGui::End();
}

void TestGameLayer::OnEvent(Dummy::Event& event)
{
    Dummy::EventDispatcher dispatcher(event);

    dispatcher.Dispatch<Dummy::KeyPressedEvent>(DE_BIND_EVENT_FN(TestGameLayer::OnKeyPressedEvent));
}

bool TestGameLayer::OnKeyPressedEvent(Dummy::KeyPressedEvent& event)
{
    // TODO: Window close on escape button
    return true;
}

﻿#include "TestGameLayer.h"

TestGameLayer::TestGameLayer()
    :   Layer("TestGameLayer"), Camera_(CameraPosition)
{
    CameraPitch = Camera_.GetRotationPitch();
        CameraYaw = Camera_.GetRotationYaw();

        VertexArray_.reset(Dummy::VertexArray::Create());

        float vertices[24 * 7] = {
            0.5f, -0.5f, -0.5f, 0.8f, 0.0f, 0.0f, 1.0f, // 0
            -0.5f, -0.5f, -0.5f, 0.0f, 0.8f, 0.0f, 1.0f, // 1
            -0.5f, 0.5f, -0.5f, 0.8f, 0.0f, 0.0f, 1.0f, // 2
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.8f, 1.0f, // 3

            // Front    
            -0.5f, -0.5f, 0.5f, 0.8f, 0.0f, 0.0f, 1.0f, // 4
            0.5f, -0.5f, 0.5f, 0.0f, 0.8f, 0.0f, 1.0f, // 5
            0.5f, 0.5f, 0.5f, 0.8f, 0.0f, 0.0f, 1.0f, // 6
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.8f, 1.0f, // 7

            // Left
            -0.5f, -0.5f, -0.5f, 0.8f, 0.0f, 0.0f, 1.0f, // 8
            -0.5f, -0.5f, 0.5f, 0.0f, 0.8f, 0.0f, 1.0f, // 9
            -0.5f, 0.5f, 0.5f, 0.8f, 0.0f, 0.0f, 1.0f, // 10
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.8f, 1.0f, // 11

            // Right
            0.5f, -0.5f, 0.5f, 0.8f, 0.0f, 0.0f, 1.0f, // 12
            0.5f, -0.5f, -0.5f, 0.0f, 0.8f, 0.0f, 1.0f, // 13
            0.5f, 0.5f, -0.5f, 0.8f, 0.0f, 0.0f, 1.0f, // 14
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.8f, 1.0f, // 15

            // Bottom
            -0.5f, -0.5f, -0.5f, 0.8f, 0.0f, 0.0f, 1.0f, // 16
            0.5f, -0.5f, -0.5f, 0.0f, 0.8f, 0.0f, 1.0f, // 17
            0.5f, -0.5f, 0.5f, 0.8f, 0.0f, 0.0f, 1.0f, // 18
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.8f, 1.0f, // 19
            // Top
            -0.5f, 0.5f, 0.5f, 0.8f, 0.0f, 0.0f, 1.0f, // 20
            0.5f, 0.5f, 0.5f, 0.0f, 0.8f, 0.0f, 1.0f, // 21
            0.5f, 0.5f, -0.5f, 0.8f, 0.0f, 0.0f, 1.0f, // 22
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.8f, 1.0f, // 23
        };

        std::shared_ptr<Dummy::VertexBuffer> VB;
        VB.reset(Dummy::VertexBuffer::Create(vertices, sizeof(vertices)));

        VB->SetLayout(
            {
                {Dummy::ShaderDataType::FLOAT3, "a_Position"},
                {Dummy::ShaderDataType::FLOAT4, "a_Color"}
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

        std::shared_ptr<Dummy::IndexBuffer> IB;
        IB.reset(Dummy::IndexBuffer::Create(indices.data(), indices.size()));

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

        shader_ = std::make_unique<Dummy::Shader>(vertexSrc, fragmentSrc);
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

    Dummy::Renderer::Submit(shader_, VertexArray_);

    Dummy::Renderer::EndScene();
}
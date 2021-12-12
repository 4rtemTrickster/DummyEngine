#pragma once
#include <Dummy.h>

class TestGameLayer : public Dummy::Layer
{
public:
    TestGameLayer();

    void MoveCamera(Dummy::Timestep ts);

    void OnUpdate(Dummy::Timestep ts) override;

    void OnEvent(Dummy::Event& event) override;

    bool OnKeyPressedEvent(Dummy::KeyPressedEvent& event);

protected:
    std::shared_ptr<Dummy::VertexArray> VertexArray_;
    std::shared_ptr<Dummy::Shader> shader_;

    Dummy::Camera Camera_;
    glm::vec3 CameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
    float CameraYaw;
    float CameraPitch;
    float CameraSpeed = 3.f;
    float CameraSensitivity = 10.f;
};

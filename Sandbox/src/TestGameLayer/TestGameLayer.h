#pragma once
#include <Dummy.h>


#include "Dummy/CameraController/CameraController.h"
#include "Dummy/Renderer/ShaderLibrary/ShaderLibrary.h"

class TestGameLayer : public Dummy::Layer
{
public:
    TestGameLayer();

    //void MoveCamera(Dummy::Timestep ts);

    void OnUpdate(Dummy::Timestep ts) override;

    //void OnImGuiRender() override;

    void OnEvent(Dummy::Event& event) override;

    bool OnKeyPressedEvent(Dummy::KeyPressedEvent& event);

protected:
    Dummy::ShaderLibrary SHLib;
    
    Dummy::Ref<Dummy::VertexArray> VertexArray_;
    //Dummy::Ref<Dummy::Shader> shader_;
    Dummy::Ref<Dummy::Texture2D> texture;

    Dummy::CameraController CamCont;
};

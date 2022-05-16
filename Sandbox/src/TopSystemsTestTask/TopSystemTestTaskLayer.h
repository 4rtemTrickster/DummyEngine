#pragma once
#include "Dummy.h"
#include "ShapesFactory/IShapesFactory.h"

namespace Dummy
{
    class KeyPressedEvent;
}

class TopSystemTestTaskLayer : public Dummy::Layer
{
public:
    
    TopSystemTestTaskLayer();
    ~TopSystemTestTaskLayer() override {}
    
    void OnUpdate(Dummy::Timestep ts) override;
    void OnEvent(Dummy::Event& event) override;

    void OnImGuiRender() override;

    bool OnKeyPressedEvent(Dummy::KeyPressedEvent& event);

protected:
    Dummy::CameraController CamCont;

    Dummy::Ref<IShapesFactory> ShapesFactory;

    std::vector<Dummy::Ref<IShape>> ShapesToDraw;

    Dummy::Ref<Dummy::Shader> CommonShader;
    
};

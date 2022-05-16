#include "TopSystemTestTaskLayer.h"

#include "GeomShapes/IShape.h"
#include "glm/ext/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "ShapesFactory/RandomShapeFactory/RandomShapeFactory.h"
#include "ShapesFactory/StandartShapeFactory/StandardShapeFactory.h"

TopSystemTestTaskLayer::TopSystemTestTaskLayer()
    :   Layer("TopSystemTestTaskLayer")
{
    CamCont.GetCamera().SetPosition({0.0f, 0.0f, 3.0f});

    ShapesFactory = Dummy::CreateRef<StandardShapeFactory>();
    
    CommonShader = Dummy::Shader::Create("TopSystemTestTask");

    ShapesFactory->CreateShapes(ShapesToDraw);
}

void TopSystemTestTaskLayer::OnEvent(Dummy::Event& event)
{
    CamCont.OnEvent(event);
    
    Dummy::EventDispatcher dispatcher(event);

    dispatcher.Dispatch<Dummy::KeyPressedEvent>(DE_BIND_EVENT_FN(TopSystemTestTaskLayer::OnKeyPressedEvent));
}

void TopSystemTestTaskLayer::OnImGuiRender()
{
    ImGui::Text("Choose how to create shapes (By clicking on the random button, you can recreate a set of shapes)");

    if(ImGui::Button("Random"))
    {
        DE_TRACE("Generating a random set of shapes");
        ShapesFactory = Dummy::CreateRef<RandomShapeFactory>();
        ShapesFactory->CreateShapes(ShapesToDraw);
    }
    if(ImGui::Button("Standrat"))
    {
        DE_TRACE("Generating a standard set of shapes");
        ShapesFactory = Dummy::CreateRef<StandardShapeFactory>();
        ShapesFactory->CreateShapes(ShapesToDraw);
    }
}

bool TopSystemTestTaskLayer::OnKeyPressedEvent(Dummy::KeyPressedEvent& event)
{
    if(event.GetKeyCode() == DE_KEY_ESCAPE)
    {
        Dummy::Application::Get().OnEvent(Dummy::WindowCloseEvent());
        return false;
    }
    return true;
}

void TopSystemTestTaskLayer::OnUpdate(Dummy::Timestep ts)
{
    Dummy::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 0.0f});
    Dummy::RenderCommand::Clear();

    Dummy::Renderer::BeginScene(CamCont.GetCamera());
    
    for (size_t i = 0; i <ShapesToDraw.size(); ++i)
        Dummy::Renderer::Submit(
            CommonShader,
            ShapesToDraw.at(i)->GetVertexArray(),
            glm::translate(glm::mat4(1.0f),glm::vec3(i * 3.f - 4.5f, 0.f, 0.f))
            );
    
    Dummy::Renderer::EndScene();
}

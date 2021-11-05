#pragma once

#include "Dummy/Core.h"

#include "Dummy/Event/Events/ApplicationEvent.h"
#include "Dummy/Event/Events/KeyEvent.h"
#include "Dummy/Event/Events/MouseEvent.h"

#include "Dummy/Layers System/Layer/Layer.h"

namespace Dummy
{
    class DUMMY_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnEvent(Event& event) override;

    protected:

        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
        bool OnMouseMovedEvent(MouseMovedEvent& e);
        bool OnMouseScrollEvent(MouseScrollEvent& e);
        
        bool OnKeyPressedEvent(KeyPressedEvent& e);
        bool OnKeyReleasedEvent(KeyReleasedEvent& e);
        bool OnKeyTypedEvent(KeyTypedEvent& e);
        
        bool OnWindowResizeEvent(WindowResizeEvent& e);

        
        float Time = 0.0f;
    };
    
}

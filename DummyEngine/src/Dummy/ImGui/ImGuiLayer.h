#pragma once

#include "Dummy/Core.h"
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
        float Time = 0.0f;
    };
    
}

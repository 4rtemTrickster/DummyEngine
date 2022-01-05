#pragma once

#include "Dummy/Core.h"

#include "Dummy/Layers System/Layer/Layer.h"

namespace Dummy
{
    class DUMMY_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer() = default;

        void OnAttach() override;
        void OnDetach() override;
        void OnImGuiRender() override;

        void Begin();
        void End();

        
        float Time = 0.0f;
    };
    
}

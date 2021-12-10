#pragma once

#include "Dummy/Input/Input.h"

namespace Dummy
{
    class WindowsInput : public Input
    {
    public:
        virtual bool IsKeyPressedImpl(int keycode) override;
        
        virtual bool IsMouseButtonPressedImpl(int button) override;
        virtual std::pair<float, float> GetMousePosImpl() override;
        virtual float GetMouseXImpl() override;
        virtual float GetMouseYImpl() override;
    };
    
}

#pragma once

#include "Dummy/Core.h"

namespace Dummy
{
    class DUMMY_API Input
    {
    public:
        inline static bool IsKeyPressed(int keycode) { return Instance->IsKeyPressedImpl(keycode); }
        
        inline static bool IsMouseButtonPressed(int button) { return Instance->IsMouseButtonPressedImpl(button); }
        inline static std::pair<float, float> GetMousePos() {return Instance->GetMousePosImpl();}
        inline static float GetMouseX() { return Instance->GetMouseXImpl(); }
        inline static float GetMouseY() { return Instance->GetMouseYImpl(); }

    protected:

        virtual bool IsKeyPressedImpl(int keycode) = 0;

        virtual bool IsMouseButtonPressedImpl(int button) = 0;
        virtual std::pair<float, float> GetMousePosImpl() = 0;
        virtual float GetMouseXImpl() = 0;
        virtual float GetMouseYImpl() = 0;
        
        
        static Input* Instance;
    };
}

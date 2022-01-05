#pragma once

#include "Dummy/Event/Events/ApplicationEvent.h"
#include "Dummy/Renderer/Camera/Camera.h"
#include "Dummy/Timestep/Timestep.h"

namespace Dummy
{
    class CameraController
    {
    public:
        CameraController() {};

        Camera& GetCamera(){ return Camera_; }

        void OnUpdate(Timestep ts);
        void OnEvent(Event& e);
    
    private:

        bool OnWindowResizeEvent(WindowResizeEvent& e);

        void RotateCamera(Timestep ts);

    private:
        
        Camera Camera_;
        
        float CameraSpeed = 3.f;
        float CameraSensitivity = 10.f;
    };
    
}

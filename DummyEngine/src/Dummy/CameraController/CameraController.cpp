#include "DEpch.h"
#include "CameraController.h"

#include "Dummy/Input/Input.h"
#include "Dummy/Key & MouseCodes/KeyCodes.h"

namespace Dummy
{
    void CameraController::OnUpdate(Timestep ts)
    {
        
        if (Input::IsKeyPressed(DE_KEY_W))
        {
            Camera_.SetPosition(Camera_.GetPosition() +
                ((CameraSpeed * ts) * Camera_.GetForwardVector()));
        }
        else if (Input::IsKeyPressed(DE_KEY_S))
        {
            Camera_.SetPosition(Camera_.GetPosition() -
                ((CameraSpeed * ts) * Camera_.GetForwardVector()));
        }

        if (Dummy::Input::IsKeyPressed(DE_KEY_D))
        {
            Camera_.SetPosition(Camera_.GetPosition() +
                    glm::normalize
                    (
                        glm::cross
                            (
                            Camera_.GetForwardVector(),
                            Camera_.GetUpVector()
                            )
                    )
                    *
                    (CameraSpeed * ts)
                );
        }
        else if (Dummy::Input::IsKeyPressed(DE_KEY_A))
        {
            Camera_.SetPosition(Camera_.GetPosition() -
                    glm::normalize
                    (
                        glm::cross
                            (
                            Camera_.GetForwardVector(),
                            Camera_.GetUpVector()
                            )
                    )
                    *
                    (CameraSpeed * ts)
                );
        }

        if(Input::IsMouseMoved()) RotateCamera(ts);
    }

    void CameraController::RotateCamera(Timestep ts)
    {
        static std::pair<float, float> LastPos;
        std::pair<float, float> CurrentPos = Input::GetMousePos();

        if (static bool first = true)
        {
            LastPos = Input::GetMousePos();
            first = false;
        }
        
        // Offset * sensitivity
        auto[Pitch, Yaw] = Camera_.GetRotation();
        Yaw   += (CurrentPos.first - LastPos.first)   * CameraSensitivity * ts; 
        Pitch += (LastPos.second - CurrentPos.second) * CameraSensitivity * ts;

        LastPos.first = CurrentPos.first;
        LastPos.second = CurrentPos.second;


        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;

        //Camera_.SetPosition(CameraPosition);
        Camera_.SetRotation(Pitch, Yaw);
    }

    void CameraController::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);

        dispatcher.Dispatch<WindowResizeEvent>(DE_BIND_EVENT_FN(CameraController::OnWindowResizeEvent));
    }

    bool CameraController::OnWindowResizeEvent(WindowResizeEvent& e)
    {
        Camera_.UpdateCameraVectors(60.0f, static_cast<float>(e.GetWidth())/static_cast<float>(e.GetHeight()));
        return false;
    }
}

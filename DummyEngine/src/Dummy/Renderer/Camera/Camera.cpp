#include "DEpch.h"
#include "Camera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Dummy
{
    Camera::Camera(const glm::vec3& position, float pitch, float yaw, const glm::vec3& up)
        :   Position(position), Pitch(pitch), Yaw(yaw),  WorldUp(up), Front(0.0f, 0.0f, -1.0f),
            Right(0.0f), Up(0.0f)
    {
        UpdateCameraVectors();
    }

    void Camera::UpdateCameraVectors()
    {
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        
        this->Front = glm::normalize(front);

        this->Right = glm::normalize(glm::cross(Front, WorldUp));
        this->Up    = glm::normalize(glm::cross(Right, Front));

        ViewMatrix = glm::lookAt(this->Position, this->Position + this->Front, this->Up);
        ProjectionMatrix = glm::perspective(glm::radians(60.0f), 1920.f/1080.f, 0.1f, 1000.0f);

        ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
    }
}

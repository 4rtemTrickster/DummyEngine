#include "DEpch.h"
#include "Camera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Dummy
{
    Camera::Camera(const glm::vec3& position, const glm::vec3& up, const glm::vec3& rotation)
        :   Position(position), Rotation(rotation),  WorldUp(up), Front(0.0f, 0.0f, -1.0f), Right(0.0f), Up(0.0f)
    {
        UpdateCameraVectors();

        //ViewMatrix = glm::lookAt(this->Position, this->Position + this->Front, this->Up);
        ViewMatrix = glm::lookAt(this->Position, 
             glm::normalize(this->Position + this->Front),
             this->Up);
        
        ProjectionMatrix = glm::perspective(glm::radians(45.0f), 16.f/9.f, 0.1f, 1000.0f);

        ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
    }

    void Camera::UpdateCameraVectors()
    {
        glm::vec3 front;
        front.x = cos(glm::radians(Rotation.y)) * cos(glm::radians(Rotation.x));
        front.y = sin(glm::radians(Rotation.x));
        front.z = sin(glm::radians(Rotation.y)) * cos(glm::radians(Rotation.x));
        this->Front = glm::normalize(front);

        this->Right = glm::normalize(glm::cross(Front, WorldUp));
        this->Up    = glm::normalize(glm::cross(Right, Front));
    }
}

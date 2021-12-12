#pragma once

#include "glm/glm.hpp"

namespace Dummy
{
    class Camera
    {
    public:
        Camera(const glm::vec3& position = glm::vec3(0.0f),
               float pitch = 0.0f, float yaw = -90.f,
               const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f)
               );

        void SetPosition(const glm::vec3& position) { UpdateCameraVectors(); Position = position; }
        void SetRotation(float pitch, float yaw) { UpdateCameraVectors(); Pitch = pitch; Yaw = yaw; }

        const glm::vec3& GetPosition() const { return Position; }
        float GetRotationPitch() const { return Pitch; }
        float GetRotationYaw() const { return Yaw; }

        const glm::mat4& GetProjectionMatrix() const { return ProjectionMatrix; }
        const glm::mat4& GetViewMatrix() const { return ViewMatrix; }
        const glm::mat4& GetViewProjectionMatrix() const { return ViewProjectionMatrix; }

        void UpdateCameraVectors();

    protected:

        glm::mat4 ProjectionMatrix;
        glm::mat4 ViewMatrix;
        glm::mat4 ViewProjectionMatrix;

        glm::vec3 Position;
        float Pitch;
        float Yaw;
        
        glm::vec3 Front;
        glm::vec3 Right;
        glm::vec3 Up;
        
        glm::vec3 WorldUp;
    };
    
}

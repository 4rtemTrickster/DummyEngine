#pragma once

#include <glm/glm.hpp>

namespace Dummy
{
    class Camera
    {
    public:
        Camera(const glm::vec3& position = glm::vec3(0.0f),
               float pitch = 0.0f, float yaw = -90.f,
               const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f)
               );

        void SetPosition(const glm::vec3& position) { Position = position; UpdateCameraVectors(); }
        void SetRotation(float pitch, float yaw) { Pitch = pitch; Yaw = yaw; UpdateCameraVectors(); }

        const glm::vec3& GetPosition() const { return Position; }
        float GetRotationPitch() const { return Pitch; }
        float GetRotationYaw() const { return Yaw; }
        
        /**
         * \return Pair of camera rotation (Pitch, Yaw)
         */
        std::pair<float, float> GetRotation() const { return std::make_pair(Pitch, Yaw); }
        
        const glm::vec3& GetForwardVector() const { return Front; }
        const glm::vec3& GetUpVector() const { return Up; }
        
        const glm::mat4& GetProjectionMatrix() const { return ProjectionMatrix; }
        const glm::mat4& GetViewMatrix() const { return ViewMatrix; }
        const glm::mat4& GetViewProjectionMatrix() const { return ViewProjectionMatrix; }

        void UpdateCameraVectors(float FOV = 60.0f, float aspectRatio = 1920.0f/1080.0f);

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

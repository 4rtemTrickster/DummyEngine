#pragma once

#include "glm/glm.hpp"

namespace Dummy
{
    class Camera
    {
    public:
        Camera(const glm::vec3& position = glm::vec3(0.0f),
               const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f),
               const glm::vec3& rotation = glm::vec3(0.0f, 0.0f, 0.0f)
               );

        void SetPosition(const glm::vec3& position) { Position = position; }
        void SetRotation(const glm::vec3& rotation) { Rotation = rotation; }

        const glm::vec3& GetPosition() const { return Position; }
        const glm::vec3& GetRotation() const { return Rotation; }

        const glm::mat4& GetProjectionMatrix() const { return ProjectionMatrix; }
        const glm::mat4& GetViewMatrix() const { return ViewMatrix; }
        const glm::mat4& GetViewProjectionMatrix() const { return ViewProjectionMatrix; }

    protected:

        glm::mat4 ProjectionMatrix;
        glm::mat4 ViewMatrix;
        glm::mat4 ViewProjectionMatrix;

        glm::vec3 Position;
        glm::vec3 Rotation;
        
        glm::vec3 Front;
        glm::vec3 Right;
        glm::vec3 Up;
        
        glm::vec3 WorldUp;

    private:
        void UpdateCameraVectors();
    };
    
}

#pragma once
#include "RendererAPI.h"
#include "Camera/Camera.h"
#include "Shader/Shader.h"

namespace Dummy
{
    class Renderer
    {
    public:
        static void BeginScene(Camera& camera); //TODO: Scene params
        static void EndScene();

        static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
        
        inline static RendererAPI::API GetCurrentRendererAPI() { return RendererAPI::GetCurrentAPI(); }

    protected:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };

        static SceneData* m_SceneData;
    };
}

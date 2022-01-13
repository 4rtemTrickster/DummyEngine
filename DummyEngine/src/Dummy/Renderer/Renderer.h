#pragma once
#include "RendererAPI.h"
#include "Camera/Camera.h"
#include "Shader/Shader.h"

namespace Dummy
{
    class Renderer
    {
    public:
        static void Init();
        static void OnWindowResize(uint32_t width, uint32_t height);
        
        static void BeginScene(Camera& camera); //TODO: Scene params
        static void EndScene();

        static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
        
        inline static RendererAPI::API GetCurrentRendererAPI() { return RendererAPI::GetCurrentAPI(); }

    protected:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };

        static Scope<SceneData> s_SceneData;
    };
}

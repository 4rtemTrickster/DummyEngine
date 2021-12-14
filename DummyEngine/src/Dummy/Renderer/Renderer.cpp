#include "DEpch.h"
#include "Renderer.h"

#include "Platform/OpenGL/Renderer/Shader/OpenGLShader.h"
#include "RenderCommand/RenderCommand.h"

namespace Dummy
{
    Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;
    
    void Renderer::BeginScene(Camera& camera)
    {
        m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
    {
        shader->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);
        
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}

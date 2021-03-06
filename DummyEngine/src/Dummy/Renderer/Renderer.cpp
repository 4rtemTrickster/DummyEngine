#include "DEpch.h"
#include "Renderer.h"

#include "Platform/OpenGL/Renderer/Shader/OpenGLShader.h"
#include "RenderCommand/RenderCommand.h"

namespace Dummy
{
    Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();

    void Renderer::Init()
    {
        RenderCommand::Init();
    }

    void Renderer::Shutdown()
    {
        //TODO: Renderer2D::Shutdown();?????
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewport(0, 0, width, height);
    }

    void Renderer::BeginScene(Camera& camera)
    {
        s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
    {
        shader->Bind();
        //TODO: shader->SetMat4();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);
        
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}

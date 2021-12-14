#pragma once

#include "glm/glm.hpp"

#include "Dummy/Renderer/Shader/Shader.h"

namespace Dummy
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~OpenGLShader() override;
        
        void Bind() const override;
        void Unbind() const override;

        void UploadUniformFloat4(const std::string& name, const glm::vec4& value);
        void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
        
        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
    

    protected:
        uint32_t RendererID;

        ///////////////////////////////
        bool CheckShadersCompilationStatus(std::vector<std::pair<unsigned int, std::string>> shaders);

    };
}

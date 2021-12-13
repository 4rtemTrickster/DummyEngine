#pragma once
#include <glm/glm.hpp>

namespace Dummy
{
    class Shader
    {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
        void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

    protected:
        uint32_t RendererID;
    };
    
}

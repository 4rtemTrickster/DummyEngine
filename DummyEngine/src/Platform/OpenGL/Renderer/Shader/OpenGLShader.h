#pragma once

#include <filesystem>

#include "glm/glm.hpp"

#include "Dummy/Renderer/Shader/Shader.h"

namespace Dummy
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& name);
        ~OpenGLShader() override;
        
        void Bind() const override;
        void Unbind() const override;

        void UploadUniformInt(const std::string& name, const int value);

        void UploadUniformFloat4(const std::string& name, const glm::vec4& value);
        void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
        
        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
    

    protected:
        uint32_t RendererID;
        
        // Caching for uniforms
        std::unordered_map <std::string, unsigned int> UniformLocationCache;

        ///////////////////////////////
        bool CheckShadersCompilationStatus(std::vector<std::pair<unsigned int, std::string>> shaders);
        unsigned int GetUniformLocation(const std::string& name);
        
        static std::string ParseShader(const std::filesystem::path& path);

    };
}

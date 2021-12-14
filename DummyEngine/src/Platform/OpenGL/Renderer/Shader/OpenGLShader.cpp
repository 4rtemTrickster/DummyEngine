#include "DEpch.h"
#include "OpenGLShader.h"

#include "Dummy/Log/Log.h"
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"


namespace Dummy
{
    OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        std::vector<std::pair<GLuint, std::string>> Shaders;

        Shaders.push_back({glCreateShader(GL_VERTEX_SHADER), "Vertex"});
        Shaders.push_back({glCreateShader(GL_FRAGMENT_SHADER), "Fragment"});


        const GLchar* source = vertexSrc.c_str();
        
        glShaderSource(Shaders[0].first, 1, &source, nullptr);
        glCompileShader(Shaders[0].first);

        source = fragmentSrc.c_str();
        glShaderSource(Shaders[1].first, 1, &source, nullptr);

        glCompileShader(Shaders[1].first);

        if(!CheckShadersCompilationStatus(Shaders)) return;


        RendererID = glCreateProgram();
        glAttachShader(RendererID, Shaders[0].first);
        glAttachShader(RendererID, Shaders[1].first);

        glLinkProgram(RendererID);
        
        GLint isLinked = 0;
        glGetProgramiv(RendererID, GL_LINK_STATUS,&isLinked);

        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(RendererID, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infolog(maxLength);
            glGetProgramInfoLog(RendererID, maxLength, &maxLength, infolog.data());

            glDeleteProgram(RendererID);

            glDeleteShader(Shaders[0].first);
            glDeleteShader(Shaders[1].first);
            
            DE_CORE_ERROR("{0}", infolog.data());
            DE_CORE_ASSERT(false,"Shader program link failure!");
            return;
        }

        glDetachShader(RendererID, Shaders[0].first);
        glDetachShader(RendererID, Shaders[1].first);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(RendererID);
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(RendererID);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }

    void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
    {
        GLint location = glGetUniformLocation(RendererID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
    {
        GLint location = glGetUniformLocation(RendererID, name.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
    {
        GLint location = glGetUniformLocation(RendererID, name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }

    bool OpenGLShader::CheckShadersCompilationStatus(std::vector<std::pair<unsigned int, std::string>> shaders)
    {
        GLint isCompiled = 0;

        for (auto&[shaderID, shaderType] : shaders)
        {
            glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
            
            if (isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<GLchar> infolog(maxLength);
                glGetShaderInfoLog(shaderID, maxLength, &maxLength, infolog.data());

                for(auto& var : shaders)
                    glDeleteShader(var.first);

                DE_CORE_ERROR("{0}", infolog.data());
                DE_CORE_ASSERT(false,(shaderType + " shader compilation failure!"));
                return false;
            }
        }

        return true;
    }
}

#include "DEpch.h"
#include "OpenGLShader.h"

#include "glad/glad.h"

#include "Dummy/Log/Log.h"
#include "glm/gtc/type_ptr.hpp"


namespace Dummy
{
    OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

        const GLchar* source = vertexSrc.c_str();
        glShaderSource(vertexShader, 1, &source, nullptr);

        glCompileShader(vertexShader);

        GLint isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infolog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, infolog.data());

            glDeleteShader(vertexShader);

            DE_CORE_ERROR("{0}", infolog.data());
            DE_CORE_ASSERT(false,"Vertex shader compilation failure!");
            return;
        }

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        source = fragmentSrc.c_str();
        glShaderSource(fragmentShader, 1, &source, nullptr);

        glCompileShader(fragmentShader);
        
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infolog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, infolog.data());

            glDeleteShader(fragmentShader);
            glDeleteShader(vertexShader);

            DE_CORE_ERROR("{0}", infolog.data());
            DE_CORE_ASSERT(false,"Fragment shader compilation failure!");
            return;
        }

        RendererID = glCreateProgram();
        glAttachShader(RendererID, vertexShader);
        glAttachShader(RendererID, fragmentShader);

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

            glDeleteShader(fragmentShader);
            glDeleteShader(vertexShader);
            
            DE_CORE_ERROR("{0}", infolog.data());
            DE_CORE_ASSERT(false,"Shader program link failure!");
            return;
        }

        glDetachShader(RendererID, vertexShader);
        glDetachShader(RendererID, fragmentShader);
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
}

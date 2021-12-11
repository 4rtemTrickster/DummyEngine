#include "DEpch.h"
#include "Shader.h"

#include "Dummy/Log/Log.h"
#include "glad/glad.h"

namespace Dummy
{
    Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
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

    Shader::~Shader()
    {
        glDeleteProgram(RendererID);
    }

    void Shader::Bind() const
    {
        glUseProgram(RendererID);
    }

    void Shader::Unbind() const
    {
        glUseProgram(0);
    }
}

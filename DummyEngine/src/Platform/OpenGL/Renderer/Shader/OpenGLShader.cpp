#include "DEpch.h"
#include "OpenGLShader.h"

#include "Dummy/Log/Log.h"
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"


namespace Dummy
{
    OpenGLShader::OpenGLShader(const std::string& name)
        :   Name(name)
    {
        static const std::filesystem::path ShadersFolder("res\\Shaders");
        std::vector<std::pair<GLuint, std::string>> Shaders;
        

        if (std::filesystem::exists(ShadersFolder / name))
        {
            bool hasVertexShader = false;
            bool hasFragmentShader = false;
            
            for (auto const& dir_entry : std::filesystem::directory_iterator{ShadersFolder / name })
            {
                unsigned int shaderID;
                std::string shaderType;

                auto extension = dir_entry.path().filename().extension();
                
                if (extension == ".vert")
                {
                    shaderID = glCreateShader(GL_VERTEX_SHADER);
                    shaderType = "Fragment";
                    hasVertexShader = true;
                }
                else if(extension == ".frag")
                {
                    shaderID = glCreateShader(GL_FRAGMENT_SHADER);
                    shaderType = "Fragment";
                    hasFragmentShader = true;
                }
                

                std::string Source = ParseShader(dir_entry.path()).c_str();
            
                const GLchar* source = Source.c_str();

                glShaderSource(shaderID, 1, &source, nullptr);
                glCompileShader(shaderID);

                Shaders.push_back({shaderID, shaderType});
            }

            if(!(hasVertexShader && hasFragmentShader))
            {
                DE_CORE_ERROR("Shaders file are missing");
                return;
            }
        }
        else
        {
            DE_CORE_ERROR("Shader folder with name: {0} does not exists!", name);
            return;
        }

        if(!CheckShadersCompilationStatus(Shaders)) return;


        RendererID = glCreateProgram();

        for(auto& shader : Shaders)
            glAttachShader(RendererID, shader.first);

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

        for(auto& shader : Shaders)
        {
            glDetachShader(RendererID, shader.first);
            glDeleteShader(shader.first);
        }
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

    unsigned OpenGLShader::GetUniformLocation(const std::string& name)
    {
        if (UniformLocationCache.find(name) != UniformLocationCache.end())
            return UniformLocationCache[name];

        GLint location = glGetUniformLocation(RendererID, name.c_str());

        if (location == -1)
            DE_CORE_WARN("Uniform: {0} doesn't exist!", name);

        UniformLocationCache[name] = location;

        return location;
    }

    void OpenGLShader::UploadUniformInt(const std::string& name, const int value)
    {
        glUniform1i(GetUniformLocation(name), value);
    }

    void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
    {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
    {
        glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
    {
        glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
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

    std::string OpenGLShader::ParseShader(const std::filesystem::path& path)
    {
        std::ifstream fs(path);
        std::string line;

        if (!fs.is_open())
            DE_CORE_ERROR("Can not open shader file! Path: {0}", path);

        DE_CORE_INFO("Shader file is open!\nPath: {0}", path);

        std::stringstream ss;
        ss << fs.rdbuf();
        return ss.str();
    }
}

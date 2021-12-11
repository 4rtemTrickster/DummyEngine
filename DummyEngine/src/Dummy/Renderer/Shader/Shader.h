#pragma once

namespace Dummy
{
    class Shader
    {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        void Bind() const;
        void Unbind() const;

    protected:
        uint32_t RendererID;
    };
    
}

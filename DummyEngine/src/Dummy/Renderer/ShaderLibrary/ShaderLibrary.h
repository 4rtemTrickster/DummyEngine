#pragma once

#include "Dummy/Core.h"
#include "Dummy/Renderer/Shader/Shader.h"

namespace Dummy
{
    class ShaderLibrary
    {
    public:
        void Add(const Ref<Shader>& shader);

        Ref<Shader> Load(const std::string& name);
        Ref<Shader> Get(const std::string& name);

        bool Exists(const std::string& name) const;

    private:
        std::unordered_map<std::string, Ref<Shader>> Shaders;
    };
}

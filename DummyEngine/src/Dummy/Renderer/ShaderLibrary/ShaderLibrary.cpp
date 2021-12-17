#include "DEpch.h"
#include "ShaderLibrary.h"

#include "Dummy/Log/Log.h"

namespace Dummy
{
    void ShaderLibrary::Add(const Ref<Shader>& shader)
    {
        auto& name = shader->GetName();
        DE_CORE_ASSERT(!Exists(name), "Shader already exists!");

        Shaders[name] = shader;
    }

    Ref<Shader> ShaderLibrary::Load(const std::string& name)
    {
        auto shader = Shader::Create(name);
        Add(shader);

        return shader;
    }

    Ref<Shader> ShaderLibrary::Get(const std::string& name)
    {
        DE_CORE_ASSERT(Exists(name), "Shader not found");
        return Shaders[name];
    }

    bool ShaderLibrary::Exists(const std::string& name) const
    {
        return Shaders.find(name) != Shaders.end();
    }
}

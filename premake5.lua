workspace "DummyEngine"
    architecture "x86_64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include dir relative to root folder (Solution Dir)
IncludeDir = {}
IncludeDir["GLFW"] = "DummyEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "DummyEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "DummyEngine/vendor/imgui"
IncludeDir["glm"] = "DummyEngine/vendor/glm"
IncludeDir["stb_image"] = "DummyEngine/vendor/stb_image"

group "Dependencies"
    include "DummyEngine/vendor/GLFW"
    include "DummyEngine/vendor/Glad"
    include "DummyEngine/vendor/imgui"
group ""

project "DummyEngine"
    location "DummyEngine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "DEpch.h"
    pchsource "%{prj.name}/src/DEpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl",
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "DE_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }


    filter "configurations:Debug"
        defines "DE_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "DE_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "DE_DIST"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"


    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/res/Shaders/**.vert",
        "%{prj.name}/res/Shaders/**.frag",
    }

    includedirs
    {
        "DummyEngine/vendor/spdlog/include",
        "DummyEngine/src",
        "DummyEngine/vendor",
        "%{IncludeDir.glm}"
    }

    links
    {
        "DummyEngine"
    }

    filter "system:windows"
        systemversion "latest"


    filter "configurations:Debug"
        defines "DE_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "DE_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "DE_DIST"
        runtime "Release"
        optimize "on"
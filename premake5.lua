workspace "DummyEngine"
    architecture "x64"
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

include "DummyEngine/vendor/GLFW"
include "DummyEngine/vendor/Glad"
include "DummyEngine/vendor/imgui"

project "DummyEngine"
    location "DummyEngine"
    kind "SharedLib"
    language "C++"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "DEpch.h"
    pchsource "%{prj.name}/src/DEpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "DE_PLATFORM_WINDOWS",
            "DE_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ..\\bin\\" .. outputdir .. "\\Sandbox")
        }

    filter "configurations:Debug"
        defines "DE_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "DE_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "DE_DIST"
        runtime "Release"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "DummyEngine/vendor/spdlog/include",
        "DummyEngine/src",
        "%{IncludeDir.glm}"
    }

    links
    {
        "DummyEngine"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "DE_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "DE_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "DE_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "DE_DIST"
        runtime "Release"
        optimize "On"
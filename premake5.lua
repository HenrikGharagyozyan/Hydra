workspace "Hydra"
    architecture "x86_64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories
IncludeDir = {}
IncludeDir["GLFW"]  = "Hydra/vendor/GLFW/include"
IncludeDir["Glad"]  = "Hydra/vendor/Glad/include"
IncludeDir["ImGui"] = "Hydra/vendor/imgui"
IncludeDir["glm"]   = "Hydra/vendor/glm"

group "Dependencies"
    include "Hydra/vendor/GLFW"
    include "Hydra/vendor/Glad"
    include "Hydra/vendor/imgui"
group ""
filter {} -- clear filter after including dependencies

-- ===================== Hydra (Engine) =====================
project "Hydra"
    location "Hydra"
    kind "SharedLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir    ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "hdpch.h"
    pchsource "Hydra/src/hdpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",

        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
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
        "ImGui"
    }

    defines
    {
        "GLFW_INCLUDE_NONE",
        "HD_BUILD_DLL"
    }

    -- PCH: не компилировать header напрямую
    filter "files:**/hdpch.h"
        flags { "NoPCH" }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "HD_PLATFORM_WINDOWS"
        }

        links
        {
            "opengl32"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox/")
        }

    filter "system:linux"
        defines
        {
            "HD_PLATFORM_LINUX"
        }

        links
        {
            "GL",
            "pthread",
            "dl",
            "X11"
        }

        pic "On"

    filter "configurations:Debug"
        defines "HD_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "HD_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "HD_DIST"
        runtime "Release"
        optimize "Full"

    filter {}

-- ===================== Sandbox =====================
project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir    ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Hydra/src",
        "Hydra/vendor/spdlog/include",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Hydra"
    }

    filter "system:windows"
        defines "HD_PLATFORM_WINDOWS"

    filter "system:linux"
        defines "HD_PLATFORM_LINUX"

    filter "configurations:Debug"
        defines "HD_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "HD_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "HD_DIST"
        runtime "Release"
        optimize "Full"

    filter {}

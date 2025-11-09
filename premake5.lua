workspace "Hydra"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Hydra/vendor/GLFW/include"
IncludeDir["Glad"] = "Hydra/vendor/Glad/include"
IncludeDir["ImGui"] = "Hydra/vendor/imgui"

group "Dependencies"
	include "Hydra/vendor/GLFW"
	include "Hydra/vendor/Glad"
	include "Hydra/vendor/imgui"

group ""


project "Hydra"
	location "Hydra"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hdpch.h"
	pchsource "Hydra/src/hdpch.cpp"

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
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	buildoptions { "/utf-8" }

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"HD_PLATFORM_WINDOWS",
			"HD_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

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
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Hydra/vendor/spdlog/include",
		"Hydra/src"
	}

	links
	{
		"Hydra"
	}

	buildoptions { "/utf-8" }

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"HD_PLATFORM_WINDOWS"
		}

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
		optimize "On"
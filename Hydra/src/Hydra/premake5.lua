project "Hydra"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hdpch.h"
	pchsource "../hdpch.cpp"

	files
	{
		"../hdpch.h",
		"../hdpch.cpp",
		"**.h",
		"**.cpp",
		"../Platform/OpenGL/**.h",
		"../Platform/OpenGL/**.cpp",
		"%{IncludeDir.stb_image}/**.h",
		"%{IncludeDir.stb_image}/**.cpp",
		"%{IncludeDir.glm}/glm/**.hpp",
		"%{IncludeDir.glm}/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"..",
		"src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"yaml-cpp"
	}

	filter "system:windows"
		systemversion "latest"
		files
		{
			"../Platform/Windows/**.h",
			"../Platform/Windows/**.cpp"
		}
		links
		{
			"opengl32.lib"
		}

	filter "system:linux"
		pic "On"
		files
		{
			"../Platform/Linux/**.h",
			"../Platform/Linux/**.cpp"
		}
		links
		{
			"GL",
			"pthread",
			"dl",
			"X11"
		}

	filter "configurations:Debug"
		defines "HD_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HD_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HD_DIST"
		runtime "Release"
		optimize "on"
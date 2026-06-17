project "HydraEditor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{IncludeDir.spdlog}",
		"%{wks.location}/Hydra/src",
		"%{wks.location}/Hydra/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.ImGuizmo}"
	}

	links
	{
		"Hydra",
        "GLFW",
		"Glad",
		"ImGui",
		"yaml-cpp"
	}

	filter "system:windows"
		systemversion "latest"
		links
		{
			"opengl32.lib"
		}
		
	filter "system:linux"
		links
		{
			"GL",
			"pthread",
			"dl",
			"X11",
			"shaderc_shared",
            "spirv-cross-glsl",
            "spirv-cross-core"
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
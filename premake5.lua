include "./vendor/premake/premake_customization/solution_items.lua"

workspace "Hydra"
	architecture "x86_64"
	startproject "HydraEditor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Hydra/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Hydra/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Hydra/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/Hydra/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/Hydra/vendor/stb_image"
IncludeDir["spdlog"] = "%{wks.location}/Hydra/vendor/spdlog/include"
IncludeDir["entt"] = "%{wks.location}/Hydra/vendor/entt/include"
IncludeDir["yaml_cpp"] = "%{wks.location}/Hydra/vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "%{wks.location}/Hydra/vendor/ImGuizmo"

group "Dependencies"
	include "vendor/premake"
	include "Hydra/vendor/GLFW"
	include "Hydra/vendor/Glad"
	include "Hydra/vendor/imgui"
	include "Hydra/vendor/yaml-cpp"
group ""

include "Hydra/src/Hydra"
include "Sandbox"
include "HydraEditor"
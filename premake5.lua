include "definitions.lua"

workspace "Survival"
	architecture "x64"
	startproject "app"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}_%{cfg.architecture}"

group "Engine"
	include "zeus"
	include "phyzics"
	include "zeus/vendor/glfw"
group ""

group "Tools"
	include "zerializer"
group ""

include "app"

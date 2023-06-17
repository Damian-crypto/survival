project "zeus"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-intermediate/" .. outputdir .. "/%{prj.name}")
	
	pchheader "corepch.h"
	pchsource "corepch.cpp"

	files
	{
		"%{wks.location}/zeus/src/**.h",
		"%{wks.location}/zeus/src/**.cpp",
		"%{wks.location}/zeus/vendor/imgui/imconfig.h",
		"%{wks.location}/zeus/vendor/imgui/imgui**.h",
		"%{wks.location}/zeus/vendor/imgui/imgui**.cpp",
		"%{wks.location}/zeus/vendor/imgui/imstb**.h",
		"%{wks.location}/zeus/vendor/imgui/imgstb**.cpp",
		"%{wks.location}/zeus/vendor/imgui/backends/imgui_impl_opengl3.cpp",
		"%{wks.location}/zeus/vendor/imgui/backends/imgui_impl_opengl3.h",
		"%{wks.location}/zeus/vendor/imgui/backends/imgui_impl_glfw.cpp",
		"%{wks.location}/zeus/vendor/imgui/backends/imgui_impl_glfw.h",
		"%{wks.location}/zeus/vendor/stb_image/include/stb/**.h",
		"%{wks.location}/zeus/vendor/stb_image/include/stb/**.cpp",
		"%{wks.location}/zeus/vendor/glad/src/gl.c",
		"%{wks.location}/zeus/corepch.h",
		"%{wks.location}/zeus/corepch.cpp"
	}

	includedirs
	{
		"%{wks.location}/zeus",
		"%{wks.location}/zeus/src",
		"%{wks.location}/zeus/vendor/glad/include",
		"%{wks.location}/zeus/vendor/glm/include",
		"%{wks.location}/zeus/vendor/imgui/",
		"%{wks.location}/zeus/vendor/stb_image/include",
		"%{wks.location}/zeus/vendor/glfw/include"
	}

	links
	{
		"glfw",
		"opengl32.lib"
	}

	filter "files:**.c"
		flags { "NoPCH" }

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ZUES_ENGINE",
			"WINDOWING_SYSTEM_GLFW",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		runtime "Release"
		optimize "On"

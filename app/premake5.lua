project "app"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-intermediate/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{wks.location}/app/src/**.h",
		"%{wks.location}/app/src/**.cpp"
	}

	includedirs
	{
		"src",
		"%{wks.location}/zeus/src",
		"%{wks.location}/zeus/src/include",
		"%{wks.location}/zeus/vendor/glad/include",
		"%{wks.location}/zeus/vendor/glm/include",
		"%{wks.location}/zeus/vendor/imgui/",
		"%{wks.location}/zeus/vendor/stb_image/include",
		"%{wks.location}/zeus/vendor/GLFW/include",
		"%{wks.location}/phyzics/src/include",
		"%{wks.location}/zerializer/include"
	}

	links
	{
		"zeus",
		"phyzics",
		"zerializer"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
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

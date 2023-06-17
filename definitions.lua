outputdir = "%{cfg.buildcfg}_%{cfg.architecture}"

Includes = {}
Includes["zeus"] = "%{wks.location}/zeus"
Includes["glfw"] = "%{wks.location}/zeus/vendor/glfw/include"
Includes["imgui"] = "%{wks.location}/zeus/vendor/imgui"
Includes["glm"] = "%{wks.location}/zeus/vendor/glm/include"
Includes["stb_image"] = "%{wks.location}/zeus/vendor/stb_image/include"

const char* quad_vertex_shader_src = R"(
#version 450

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_TexCoord;
layout (location = 3) in int a_TexSlot;
layout (location = 4) in float a_TilingFactor;
layout (location = 5) in int a_ID;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec4 f_Color;
out vec3 f_Position;
out vec2 f_TexCoord;
out flat int f_TexSlot;
out float f_TilingFactor;
out flat int f_ID;

void main()
{
	f_Color = a_Color;
	f_Position = a_Position;
	f_TexCoord = a_TexCoord;
	f_TexSlot = a_TexSlot;
	f_TilingFactor = a_TilingFactor;
	f_ID = a_ID;
	gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0);
}
)";

const char* quad_fragment_shader_src = R"(
#version 450

layout (location = 0) out vec4 a_Color;
layout (location = 1) out int a_ID;

in vec4 f_Color;
in vec3 f_Position;
in vec2 f_TexCoord;
in flat int f_TexSlot;
in float f_TilingFactor;
in flat int f_ID;

uniform sampler2D u_Textures[8];

void main()
{
	if (f_TexSlot == -1)
	{
		a_Color = f_Color;
	}
	else
	{
		a_Color = texture(u_Textures[f_TexSlot], f_TexCoord) * f_Color;
	}

	a_ID = f_ID;
}
)";

const char* line_vertex_shader_src = R"(
#version 450

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec4 f_Color;

void main()
{
	f_Color = a_Color;
	gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0f);
}
)";

const char* line_fragment_shader_src = R"(
#version 450

layout (location = 0) out vec4 a_Color;

in vec4 f_Color;

void main()
{
	a_Color = f_Color;
}
)";

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

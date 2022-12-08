#version 460 core
#pragma vertex

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 vertex_color;
out vec3 fragment_color;
uniform mat4 MVP;

void main() 
{
	gl_Position = MVP * vec4(vertex, 1.0);
	fragment_color = vertex_color;
}

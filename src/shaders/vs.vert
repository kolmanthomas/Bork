#version 460 core
#pragma vertex

layout(std140, binding = 0) uniform model_view_projection {
	mat4 model;
	mat4 view;
	mat4 proj;
} mvp;
layout(location = 0) in vec3 vertices;

void main() 
{
	gl_Position = vec4(vertices, 1.0);
}

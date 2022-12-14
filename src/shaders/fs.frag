#version 460 core
#pragma fragment

in vec2 UV;

out vec3 color;

uniform sampler2D myTextureSampler;

void main()
{
	color = texture(myTextureSampler, UV).rgb;
}

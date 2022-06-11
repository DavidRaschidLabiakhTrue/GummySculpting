#version 430 core


in vec4 myColor;
in vec3 myNormal;

layout(location = 0) out vec4 FragColor;

layout(location = 13) uniform float time;

vec4 purple = vec4(0.337, 0.058, 0.584, 1.0);
vec4 green = vec4(0.149, 0.411, 0.156, 1.0);

void main()
{

	vec3 consumeNormal = myNormal; // consumming the normal call so OpenGL does not optimize out the normal.

	float sinOut = sin(time);
	FragColor = mix(green, purple, sinOut);
}
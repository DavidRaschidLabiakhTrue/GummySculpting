#version 410 core


in vec4 myColor;
in vec3 myNormal;
layout(location = 0) out vec4 FragColor;





void main()
{
	vec3 consumeNormal = myNormal; // consumming the normal call so OpenGL does not optimize out the normal.
	FragColor = myColor;
};
#version 430 core


in vec4 myColor;
in vec3 myNormal;

layout(location = 0) out vec4 FragColor;



void main()
{

	vec3 consumeNormal = myNormal; // consumming the normal call so OpenGL does not optimize out the normal.

	FragColor = vec4(myColor.x, myColor.y, myColor.z, 0.5);
}
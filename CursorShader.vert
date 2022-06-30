#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;


out vec4 myColor;

layout (location = 1) uniform vec3 offset;
layout (location = 2) uniform float staticScale;
layout (location = 15) uniform mat4 projectionMatrix;
layout (location = 20) uniform mat4 viewMatrix;
layout (location = 25) uniform mat4 modelMatrix;



void main()
{
	vec3 temp1 = offset +  (staticScale * aPos);
	vec3 temp = vec3(viewMatrix * modelMatrix * vec4(temp1, 1.0));

	gl_Position = projectionMatrix * vec4(temp, 1.0);
	myColor = aColor;
}
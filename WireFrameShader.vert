#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

out vec4 myColor;

layout (location = 15) uniform mat4 projectionMatrix;
layout (location = 20) uniform mat4 viewMatrix;

layout (location = 25) uniform mat4 modelMatrix;



void main()
{
   gl_Position =  projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
   myColor = aColor;

};
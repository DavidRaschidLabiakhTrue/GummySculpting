#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

out vec4 myColor;

uniform mat4 camMatrix;



void main()
{
   gl_Position = camMatrix * vec4(aPos, 1.0);
   myColor = aColor;
};
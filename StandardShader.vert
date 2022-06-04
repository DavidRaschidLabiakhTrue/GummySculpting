#version 430 core


layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec3 aNormal;

out vec4 myColor;
out vec3 myNormal;

layout (location = 15) uniform mat4 projectionMatrix;
layout (location = 20) uniform mat4 viewMatrix;



void main()
{
   myNormal = aNormal; // consume the normal call to ensure the shader is accepting the normal
   gl_Position = projectionMatrix * viewMatrix* vec4(aPos, 1.0);
   myColor = aColor;
};
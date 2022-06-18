#version 430 core


layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec3 aNormal;

out vec3 myPosition;
out vec4 myColor;
out vec3 myNormal;

layout (location = 15) uniform mat4 projectionMatrix;
layout (location = 20) uniform mat4 viewMatrix;
layout (location = 25) uniform mat4 modelMatrix;


void main()
{
   myPosition = vec3(viewMatrix * modelMatrix * vec4(aPos, 1.0));
   gl_Position = projectionMatrix * vec4(myPosition, 1.0);
   myNormal = vec3(viewMatrix * modelMatrix * vec4(aNormal, 0.0));
   myColor = aColor;
}
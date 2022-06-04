#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec3 aNormal;

out vec4 myColor;
out vec3 myNormal;

layout (location = 0) uniform mat4 camMatrix; // 0
layout (location = 1) uniform vec3 staticOffset; // 1
layout (location = 2) uniform float staticScale; // 2

layout (location = 3) uniform vec4 staticColor; // 3




void main()
{
   myNormal = aNormal; // consume the normal call to ensure the shader is accepting the normal
   gl_Position = camMatrix * vec4(staticOffset + (aPos * staticScale), 1.0);
   myColor = staticColor;
};
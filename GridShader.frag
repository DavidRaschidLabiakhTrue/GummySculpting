#version 430 core


in vec4 myColor;


layout(location = 0) out vec4 FragColor;

void main()
{
	FragColor = myColor;
}
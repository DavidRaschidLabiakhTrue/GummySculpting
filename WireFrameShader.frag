#version 410 core
in vec4 myColor;
out vec4 FragColor;

void main()
{
	FragColor = vec4(myColor.x / 2, myColor.y/ 2, myColor.z/ 2, 1.0);;
};
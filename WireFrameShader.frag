#version 410 core
in vec4 myColor;
out vec4 FragColor;



void main()
{
	FragColor = FragColor = vec4(myColor.x * 0.5, myColor.y* 0.5, myColor.z* 0.5, 1.0);
};
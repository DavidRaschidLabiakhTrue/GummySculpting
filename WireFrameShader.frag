#version 430 core
in vec4 myColor;
out vec4 FragColor;



void main()
{
	FragColor = vec4(myColor.x * 0.0f, myColor.y* 0.0f, myColor.z*0.0f, 1.0);
}
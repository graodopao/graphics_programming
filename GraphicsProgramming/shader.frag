// This file was written following the tutorial at learnopengl.com
#version 460 core

out vec4 FragColor;
in vec3 ourColor;
in vec4 vertexPosition;

void main()
{
	FragColor = vertexPosition;
};
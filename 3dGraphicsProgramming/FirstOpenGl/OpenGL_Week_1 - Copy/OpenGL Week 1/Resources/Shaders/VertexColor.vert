#version 460 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Color;
layout (location = 2) in vec2 Texture;

uniform mat4 ModelMat;

out vec3 FragColor;
void main()
{
	gl_Position = ModelMat * vec4(Position, 1.0f);
	FragColor = Color;

}
#pragma once
#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include "ShaderLoader.h"
class VertexObject
{
	private:
		GLfloat Vertices;
		GLuint VBO_ID;
		GLuint VAO_ID;
		GLuint Shader_ID;	
	public:
		GLuint getID();
		void setVertices(GLfloat* _vertices, GLsizei _size);
		void draw();
		void setShader(GLuint _Shader);

};


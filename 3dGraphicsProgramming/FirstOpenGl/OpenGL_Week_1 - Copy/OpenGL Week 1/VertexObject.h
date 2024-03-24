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
		GLuint EB_ID;
	public:
		GLuint getID();
		void setVertices(GLfloat* _vertices, GLsizei _VertSize, GLuint* _IndicesList, GLsizei _indicesSize);
		void draw(GLuint _indicesCount);
		void setShader(GLuint _Shader);
		void setEBO();

};


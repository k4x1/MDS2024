#pragma once
#include <glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
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
		glm::mat4 TranslationMat;
		glm::mat4 RotationMat;
		glm::mat4 ScaleMat;
		
	public:
		glm::mat4 QuadModelMat;
		GLuint getID();
		void setVertices(GLfloat* _vertices, GLsizei _VertSize, GLuint* _IndicesList, GLsizei _indicesSize);
		void draw(GLuint _indicesCount);
		void setTexture();
		void setShader(GLuint _Shader);
		void setEBO();
		void defineModelMatrix(glm::vec3 QuadPosition, float QuadRotation, glm::vec3 QuadScale);

};


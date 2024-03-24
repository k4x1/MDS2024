#include "VertexObject.h"

GLuint VertexObject::getID()
{
    return VAO_ID;
}

void VertexObject::setVertices(GLfloat* _vertices, GLsizei _VertSize, GLuint* _IndicesList, GLsizei _indicesSize)
{
    glGenBuffers(1, &VBO_ID);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);
    glBufferData(GL_ARRAY_BUFFER, _VertSize, _vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO_ID);
    glBindVertexArray(VAO_ID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    //ebo generation
    glGenBuffers(1, &EB_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EB_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indicesSize , _IndicesList, GL_STATIC_DRAW);
    glBindVertexArray(0);
}

void VertexObject::draw(GLuint _indicesCount)
{

    glUseProgram(Shader_ID);
    glBindVertexArray(VAO_ID);
  
    glDrawElements(GL_TRIANGLES, _indicesCount, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
    glUseProgram(0);
}

void VertexObject::setShader(GLuint _Shader)
{
    Shader_ID = _Shader;
}

void VertexObject::setEBO()
{

}

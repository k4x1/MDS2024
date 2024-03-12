#include "VertexObject.h"

GLuint VertexObject::getID()
{
    return VAO_ID;
}

void VertexObject::setVertices(GLfloat* vertices, GLsizei size)
{
    glGenBuffers(1, &VBO_ID);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO_ID);
    glBindVertexArray(VAO_ID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
}

void VertexObject::draw()
{

    glUseProgram(Shader_ID);
    glBindVertexArray(VAO_ID);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    glUseProgram(0);
}

void VertexObject::setShader(GLuint _Shader)
{
    Shader_ID = _Shader;
}

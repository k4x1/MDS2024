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

//make a that has its own vao and draws each object,, draw manager class or something


void VertexObject::draw(GLuint _indicesCount)
{

  
    glBindVertexArray(VAO_ID);
  
    glDrawElements(GL_TRIANGLES, _indicesCount, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
    glUseProgram(0);
}

void VertexObject::setShader(GLuint _Shader)
{
    Shader_ID = _Shader;
    glUseProgram(Shader_ID);
}

void VertexObject::setEBO()
{

}

void VertexObject::defineModelMatrix(glm::vec3 QuadPosition, float QuadRotation, glm::vec3 QuadScale)
{
    TranslationMat = glm::translate(glm::identity<glm::mat4>(), QuadPosition);
    RotationMat = glm::rotate(glm::identity<glm::mat4>(), glm::radians(QuadRotation), glm::vec3(0.0f, 0.0f, 1.0f));
    ScaleMat = glm::scale(glm::identity<glm::mat4>(), QuadScale);
    QuadModelMat = ScaleMat * TranslationMat * RotationMat;
}

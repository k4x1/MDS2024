#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include "ShaderLoader.h"

GLFWwindow* Window = nullptr;
/*
GLfloat Vertices_Tri[] = { 1.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
                          -1.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
                           -1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f,};*/
GLfloat Vertices_Quad[] = { 1.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
                          -1.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
                           -1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
                            1.0f, -1.0f, 0.0f,  1.0f, 0.0f, 0.0f };
GLuint Program_PositionOnly = 0;
GLuint Program_FixedTri = 0;
GLuint Program_VertexColor = 0;
GLuint Program_ColorFade = 0;
GLuint VBO_Tri;
GLuint VAO_Tri;
float CurrentTime = 0;
/*
GLfloat arr[] = {0.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
                      -0.5f, 0.8f, 0.0f,  0.0f, 1.0f, 0.0f,
                       0.5f, 0.8f, 0.0f,  0.0f, 0.0f, 1.0f, };*/
/*war crime
struct triangleColor {
    GLfloat vx1;
    GLfloat vy1;
    GLfloat vz1;
    GLfloat cx1;
    GLfloat cy1;
    GLfloat cz1;
    GLfloat vx2;
    GLfloat vy2;
    GLfloat vz2; 
    GLfloat cx2;
    GLfloat cy2;
    GLfloat cz2;
    GLfloat vx3;
    GLfloat vy3;
    GLfloat vz3;
    GLfloat cx3;
    GLfloat cy3;
    GLfloat cz3;

};*/

void MakeTriangle(GLfloat* vertices, GLsizei size) {
    glGenBuffers(1, &VBO_Tri);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Tri);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO_Tri);
    glBindVertexArray(VAO_Tri);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
}


void InitialSetup()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glViewport(0, 0, 800, 800);

    Program_PositionOnly = ShaderLoader::CreateProgram("Resources/Shaders/FixedTriangle.vert", "Resources/Shaders/FixedColor.frag");
    Program_VertexColor = ShaderLoader::CreateProgram("Resources/Shaders/VertexColor.vert", "Resources/Shaders/VertexColor.frag");
    Program_ColorFade = ShaderLoader::CreateProgram("Resources/Shaders/VertexColor.vert", "Resources/Shaders/VertexColorFade.frag");
    //vbo gen

    GLfloat arr[] = { 0.0f,  0.0f,  0.0f,   1.0f,  0.0f,  0.0f,
                     -0.5f,  0.8f,  0.0f,   0.0f,  1.0f,  0.0f,
                      0.5f,  0.8f,  0.0f,   0.0f,  0.0f,  1.0f };

    MakeTriangle(Vertices_Quad, sizeof(Vertices_Quad) / sizeof(GLfloat));

}

void Update()
{
    glfwPollEvents();

    CurrentTime = (float)glfwGetTime();
  
}

void Render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(Program_ColorFade);
    glBindVertexArray(VAO_Tri);

    GLint CurrentTimeLoc = glGetUniformLocation(Program_ColorFade, "CurrentTime");
    glUniform1f(CurrentTimeLoc, CurrentTime);

    glDrawArrays(GL_QUADS , 0, 4);
    glBindVertexArray(0);
    glUseProgram(0);
    /*
    glUseProgram(Program_FixedTri);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glUseProgram(0);*/

    glfwSwapBuffers(Window);



}

int main()
{

    //init GLFW ver 4.6
    glfwInit();
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    //init window
    Window = glfwCreateWindow(800, 800, "First OpenGL Window", NULL, NULL);
    if (Window == NULL)
    {
        std::cout << "GLFW failed to initialize properly. Terminating program." << std::endl;
        system("pause");

        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(Window);

    //init GLEW
    if (glewInit() != GLEW_OK)
    {
        std::cout << "GLFW failed to initialize properly. Terminating program." << std::endl;
        system("pause");

        glfwTerminate();
        return -1;
    }

    InitialSetup();

    //run funcs while window open
    while (glfwWindowShouldClose(Window) == false)
    {
        Update();

        Render();
    }

    glfwTerminate();
    return 0;

}
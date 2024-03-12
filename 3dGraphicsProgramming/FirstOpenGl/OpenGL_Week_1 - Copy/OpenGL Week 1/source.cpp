#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include "ShaderLoader.h"
#include "VertexObject.h"

GLFWwindow* Window = nullptr;

GLfloat Vertices_Tri1[] = { 0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
                          -0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
                           -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,};
GLfloat Vertices_Tri2[] = { -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
                          0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
                           0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,};

/*
GLfloat Vertices_Quad[] = { 1.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
                          -1.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
                           -1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
                            1.0f, -1.0f, 0.0f,      1.0f, 0.0f, 0.0f };*/
GLuint Program_PositionOnly = 0;
GLuint Program_FixedTri = 0;
GLuint Program_VertexColor = 0;
GLuint Program_ColorFade = 0;

float CurrentTime = 0;


VertexObject triangle1;
VertexObject triangle2;



void InitialSetup()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glViewport(0, 0, 800, 800);

    Program_PositionOnly = ShaderLoader::CreateProgram("Resources/Shaders/FixedTriangle.vert", "Resources/Shaders/FixedColor.frag");
    Program_VertexColor = ShaderLoader::CreateProgram("Resources/Shaders/VertexColor.vert", "Resources/Shaders/VertexColor.frag");
    Program_ColorFade = ShaderLoader::CreateProgram("Resources/Shaders/VertexColor.vert", "Resources/Shaders/VertexColorFade.frag");
 
    //MakeTriangle(Vertices_Quad, sizeof(Vertices_Quad) / sizeof(GLfloat));
    
    triangle1.setShader(Program_VertexColor);
    triangle1.setVertices(Vertices_Tri1, sizeof(Vertices_Tri1) / sizeof(GLfloat));    
    triangle2.setShader(Program_VertexColor);
    triangle2.setVertices(Vertices_Tri2, sizeof(Vertices_Tri2) / sizeof(GLfloat));

}

void Update()
{
    glfwPollEvents();

    CurrentTime = (float)glfwGetTime();
  
}

void Render()
{
    glClear(GL_COLOR_BUFFER_BIT);

/*
    GLint CurrentTimeLoc = glGetUniformLocation(Program_ColorFade, "CurrentTime");
    glUniform1f(CurrentTimeLoc, CurrentTime);*/
    triangle1.draw();
    triangle2.draw();

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
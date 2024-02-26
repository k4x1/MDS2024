#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include "ShaderLoader.h"

GLFWwindow* Window = nullptr;
GLuint Program_FixedTri = 0;

void InitialSetup()
{
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glViewport(0, 0, 800, 800);

    Program_FixedTri = ShaderLoader::CreateProgram("Resources/Shaders/FixedTriangle.vert", "Resources/FixedColor.frag");


}

void Update()
{
    glfwPollEvents();
}

void Render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(Program_FixedTri);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glUseProgram(0);

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
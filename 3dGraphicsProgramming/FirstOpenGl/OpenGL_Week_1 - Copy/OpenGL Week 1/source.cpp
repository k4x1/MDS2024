#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>
#include "ShaderLoader.h"
#include "VertexObject.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
 
GLFWwindow* Window = nullptr;

GLfloat Vertices_Tri[] = { 0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
                          -0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
                           -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,};


GLfloat Vertices_Quad[] = {-0.5f, 0.5f, 0.0f,  /**/   1.0f, 0.0f, 0.0f,  /**/  0.0f, 1.0f,
                          -0.5f, -0.5f, 0.0f,    /**/   0.0f, 1.0f, 0.0f,  /**/  0.0f, 0.0f,
                           0.5f, -0.5f, 0.0f,    /**/   1.0f, 0.0f, 1.0f,  /**/  1.0f, 0.0f,
                           0.5f, 0.5f, 0.0f,   /**/   0.0f, 1.0f, 1.0f,  /**/  1.0f, 1.0f
};


glm::vec3 QuadPosition = glm::vec3(1, 1, 1);
float QuadRotation = 1.0f;
glm::vec3 QuadScale = glm::vec3(1.0f, 1.0f, 1.0f);

glm::mat4 TranslationMat;
glm::mat4 RotationMat;
glm::mat4 ScaleMat;
glm::mat4 QuadModelMat = glm::identity<glm::mat4>();

GLfloat vertices_Octagon{};
GLuint Program_PositionOnly = 0;
GLuint Program_FixedTri = 0;
GLuint Program_VertexColor = 0;
GLuint Program_ColorFade = 0;
GLuint Program_Texture = 0;

VertexObject Hexagon;

GLuint quadIndexesList[] = {
        0, 1, 3,
        3, 2, 1,
};
GLfloat hexPositionList[] =
{
 
    0.0f, -0.5f,   0.0f,   /**/   1.0f, 1.0f, 1.0f,
    -0.433f, -0.25f, 0.0f,  /**/    1.0f, 1.0f, 0.0f,
    0.433f, -0.25f, 0.0f,  /**/   1.0f, 0.0f, 0.0f,
    0.433f, 0.25f,  0.0f,  /**/   0.0f, 1.0f, 0.0f, 
    -0.433f, 0.25f, 0.0f,  /**/   0.0f, 1.0f, 1.0f,
    0.0f, 0.5f,  0.0f,     /**/ 1.0f, 0.0f, 1.0f,

};
GLuint hexIndicesList[] =
{
        0, 1, 2, 
        3, 2, 1, 
        4, 3, 1, 
        3, 4, 5
};
GLfloat hexVertexList[] = {
    hexPositionList[0],
    hexPositionList[1],
    hexPositionList[2],
    hexPositionList[3],
    hexPositionList[4],
    hexPositionList[5]
};
GLuint CoconutTxr;

float CurrentTime = 0;

//image
int imageWidth;
int imageHeight;
int imageComponents;
unsigned char* ImageData = stbi_load("Resources/Textures/coconut.png" , &imageWidth,&imageHeight,&imageComponents, 0);



//image end

void InitialSetup()
{
    if (ImageData == nullptr) {
        std::cerr << "Failed to load image: Resources/Textures/PotionBottle.png" << std::endl;
        // Handle the error or return from the function
    }
   glGenTextures(1, &CoconutTxr);
    glBindTexture(GL_TEXTURE_2D, CoconutTxr);
    GLint LoadedComponents = (imageComponents == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, LoadedComponents, imageWidth, imageHeight, 0, LoadedComponents, GL_UNSIGNED_BYTE, ImageData);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(ImageData);
    glBindTexture(GL_TEXTURE_2D, 0);
   
  
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glViewport(0, 0, 800, 800);

    Program_Texture = ShaderLoader::CreateProgram("Resources/Shaders/Texture.vert", "Resources/Shaders/Texture.frag");
    Program_PositionOnly = ShaderLoader::CreateProgram("Resources/Shaders/FixedTriangle.vert", "Resources/Shaders/FixedColor.frag");
    Program_VertexColor = ShaderLoader::CreateProgram("Resources/Shaders/VertexColor.vert", "Resources/Shaders/VertexColor.frag");
    Program_ColorFade = ShaderLoader::CreateProgram("Resources/Shaders/VertexColor.vert", "Resources/Shaders/VertexColorFade.frag");
    //
   
    Hexagon.setVertices(Vertices_Quad,sizeof(Vertices_Quad), quadIndexesList, sizeof(quadIndexesList));


    
    glfwPollEvents();
  
}

void Update()
{
 
  
     

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, CoconutTxr);
    glUniform1i(glGetUniformLocation(Program_Texture, "Texture0"), 0);

    Hexagon.setShader(Program_VertexColor);
    /*
    TranslationMat = glm::translate(glm::identity<glm::mat4>(), QuadPosition);
    RotationMat = glm::rotate(glm::identity<glm::mat4>(), glm::radians(QuadRotation), glm::vec3(0.0f, 0.0f, 1.0f));
    ScaleMat = glm::scale(glm::identity<glm::mat4>(), QuadScale);
    //QuadModelMat = ScaleMat * TranslationMat * RotationMat ;
    QuadModelMat = glm::identity<glm::mat4>();
    */
   
   

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {

        std::cerr << error << std::endl;
    }

    CurrentTime = (float)glfwGetTime();
  
}

void Render()
{
 
    glClear(GL_COLOR_BUFFER_BIT);
    
  //  GLint ModelMatLoc = glGetUniformLocation(Program_VertexColor, "ModelMat");
   // glUniformMatrix4fv(ModelMatLoc, 1, GL_FALSE, glm::value_ptr(QuadModelMat));
/*
    GLint CurrentTimeLoc = glGetUniformLocation(Program_ColorFade, "CurrentTime");
    glUniform1f(CurrentTimeLoc, CurrentTime);*/

    GLint ModelMatLoc = glGetUniformLocation(Program_VertexColor, "ModelMat");
    glUniformMatrix4fv(ModelMatLoc, 1, GL_FALSE, &QuadModelMat[0][0]);


    Hexagon.draw(6);


    //plus 1 per different point

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
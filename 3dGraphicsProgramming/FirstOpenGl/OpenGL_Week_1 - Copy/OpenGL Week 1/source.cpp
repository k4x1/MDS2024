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


glm::vec3 hexModelPos1 = glm::vec3(-0.5f, 0, 0);
float hexModelrot1 = 0.0f;
glm::vec3 hexModelScl1 = glm::vec3(1.0f, 1.0f, 1.0f);

glm::vec3 hexModelPos2 = glm::vec3(0.5f, 0, 0);
float hexModelrot2 = 0.0f;
glm::vec3 hexModelScl2 = glm::vec3(1.0f, 1.0f, 1.0f);



GLfloat vertices_Octagon{};
GLuint Program_PositionOnly = 0;
GLuint Program_FixedTri = 0;
GLuint Program_VertexColor = 0;
GLuint Program_ColorFade = 0;
GLuint Program_Texture = 0;

VertexObject Hexagon1;
VertexObject Hexagon2;
VertexObject Quad1;

GLuint quadIndexesList[] = {
        0, 1, 3,
        3, 2, 1,
};
GLfloat hexPositionList[] =
{
 
    0.0f, -0.5f,   0.0f,   /**/   1.0f, 1.0f, 1.0f,  /**/    0.0f, 0.0f, 
    -0.433f, -0.25f, 0.0f,  /**/  1.0f, 1.0f, 0.0f,  /**/    0.0f, 0.0f, 
    0.433f, -0.25f, 0.0f,  /**/   1.0f, 0.0f, 0.0f,  /**/    0.0f, 0.0f, 
    0.433f, 0.25f,  0.0f,  /**/   0.0f, 1.0f, 0.0f,  /**/    0.0f, 0.0f,
    -0.433f, 0.25f, 0.0f,  /**/   0.0f, 1.0f, 1.0f,  /**/    0.0f, 0.0f,
    0.0f, 0.5f,  0.0f,     /**/ 1.0f, 0.0f, 1.0f,    /**/    0.0f, 0.0f

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
unsigned char* ImageData;



//image end

void InitialSetup()
{
    ImageData = stbi_load("Resources/Textures/coconut.png", &imageWidth, &imageHeight, &imageComponents, 0);
    if (ImageData == nullptr) {
        std::cerr << "Failed to load image: Resources/Textures/PotionBottle.png" << std::endl;
        // Handle the error or return from the function
    }
/*
    glGenTextures(1, &CoconutTxr);      
    glBindTexture(GL_TEXTURE_2D, CoconutTxr);
    GLint LoadedComponents = (imageComponents == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, LoadedComponents, imageWidth, imageHeight, 0, LoadedComponents, GL_UNSIGNED_BYTE, ImageData);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(ImageData);
    glBindTexture(GL_TEXTURE_2D, 0);
 */  
  
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glViewport(0, 0, 800, 800);

    Program_Texture = ShaderLoader::CreateProgram("Resources/Shaders/Texture.vert", "Resources/Shaders/Texture.frag");
    Program_PositionOnly = ShaderLoader::CreateProgram("Resources/Shaders/FixedTriangle.vert", "Resources/Shaders/FixedColor.frag");
    Program_VertexColor = ShaderLoader::CreateProgram("Resources/Shaders/VertexColor.vert", "Resources/Shaders/VertexColor.frag");
    Program_ColorFade = ShaderLoader::CreateProgram("Resources/Shaders/VertexColor.vert", "Resources/Shaders/VertexColorFade.frag");
    //
   
    //Quad1.setVertices(Vertices_Quad,sizeof(Vertices_Quad), quadIndexesList, sizeof(quadIndexesList));
    Hexagon1.setVertices(hexPositionList,sizeof(hexPositionList), hexIndicesList, sizeof(hexIndicesList));
    Hexagon2.setVertices(hexPositionList,sizeof(hexPositionList), hexIndicesList, sizeof(hexIndicesList));


    
    glfwPollEvents();
  
}

void Update()
{

   // Quad1.defineModelMatrix(QuadPosition, QuadRotation, QuadScale);
    Hexagon1.defineModelMatrix(hexModelPos1, hexModelrot1, hexModelScl1);
    Hexagon2.defineModelMatrix(hexModelPos2, hexModelrot2, hexModelScl2);
   
   

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

  //  Quad1.setShader(Program_Texture);
    Hexagon1.setShader(Program_VertexColor);
    Hexagon2.setShader(Program_VertexColor);

/*
    glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, CoconutTxr);
    glUniform1i(glGetUniformLocation(Program_Texture, "Texture0"), 0);
    */
 //   GLint ModelMatLoc = glGetUniformLocation(Program_Texture, "ModelMat");
   // glUniformMatrix4fv(ModelMatLoc, 1, GL_FALSE, &Quad1.QuadModelMat[0][0]);

   
    glUniformMatrix4fv(glGetUniformLocation(Program_VertexColor, "ModelMat"), 1, GL_FALSE, &Hexagon1.ModelMat[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(Program_VertexColor, "ModelMat"), 1, GL_FALSE, &Hexagon2.ModelMat[0][0]);


   // Quad1.draw(6);
    Hexagon1.draw(32);
    Hexagon2.draw(32);


    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {

        std::cerr << error << std::endl;
    }

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
#include<iostream>
#include<glad.h>
#include<GLFW/glfw3.h>
#include"stb_image.h"
#include"../HeaderFiles/Camera.h"

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"../HeaderFiles/shaderClass.h"
#include"../HeaderFiles/VAO.h"
#include"../HeaderFiles/VBO.h"
#include"../HeaderFiles/EBO.h"

const unsigned int width = 800;
const unsigned int height = 800;
//Coordenadas de Vertices
GLfloat vertices[] = {
    -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,    0.0f, 0.0f, //0 
     0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,    1.0f, 0.0f,  //1
     0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,    1.0f, 1.0f,  //2
    -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,    0.0f, 1.0f,  //3

    // Cara trasera
    -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 1.0f,    0.0f, 0.0f,  //4
     0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 1.0f,    1.0f, 0.0f,  //5
     0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,    1.0f, 1.0f,  //6
    -0.5f,  0.5f, -0.5f,   0.5f, 0.5f, 0.5f,    0.0f, 1.0f,  //7

    // Cara izquierda
    -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,    0.0f, 0.0f,  //8
    -0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,    1.0f, 0.0f,  //9
    -0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,  //10
    -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 1.0f,    0.0f, 1.0f,  //11

    // Cara derecha
     0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 1.0f,    0.0f, 0.0f,  //12
     0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,    1.0f, 0.0f,  //13
     0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,    1.0f, 1.0f,  //14
     0.5f,  0.5f, -0.5f,   0.5f, 0.5f, 0.5f,    0.0f, 1.0f,  //15

    // Cara superior
    -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  //16
     0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,    1.0f, 0.0f, //17
     0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,    1.0f, 1.0f,  //18
    -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,    0.0f, 1.0f,  //19

     0.0f, 1.0f, 0.0f,     1.0f, 0.5f, 1.0f,    0.5f, 0.5f, //20

    // Cara inferior
    -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 1.0f,    0.0f, 0.0f,  //21
     0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 1.0f,    1.0f, 0.0f,  //22
     0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,    1.0f, 1.0f, //23
    -0.5f, -0.5f,  0.5f,   0.5f, 0.5f, 0.5f,    0.0f, 1.0f,  //24

     0.0f, -1.0f, 0.0f,     1.0f, 0.5f, 1.0f,    0.5f, 0.5f, //25
}; 

// Indices for vertices order
GLuint indices[] = {
    // Cara frontal
    0, 1, 2, 2, 3, 0,
    // Cara trasera
    4, 5, 6, 6, 7, 4,
    // Cara izquierda
    8, 9, 10, 10, 11, 8,
    // Cara derecha
    12, 13, 14, 14, 15, 12,
    // Cara superior
    16, 17, 18, 18, 19, 16,
    // Cara inferior
    21, 22, 23, 23, 24, 21,
    //triangulo
    16, 17, 20, 
    17, 18, 20,
    18, 19, 20,
    19, 16, 20,
    //triangulo2
    21, 22, 25,
    22, 23, 25,
    23, 24, 25,
    25, 21, 25
};

int main()
{
// Initialize GLFW
glfwInit();
// Tell GLFW what version of OpenGL we are using
// In this case we are using OpenGL 3.3
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
// Tell GLFW we are using the CORE profile
// So that means we only have the modern functions
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
// Create a GLFWwindow object of 800 by 800 pixels
GLFWwindow* window = glfwCreateWindow(width, height, "Incorporando la funcionalidad de la Camara en OpenGL", NULL, NULL);
// Error check if the window fails to create
if (window == NULL)
{
std::cout << "Failed to create GLFW window" << std::endl;
glfwTerminate();
return -1;
}
// Introduce the window into the current context
glfwMakeContextCurrent(window);
//Load GLAD so it configures OpenGL
gladLoadGL();
// Specify the viewport of OpenGL in the Window
// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
glViewport(0, 0, width, height);
// Generates Shader object using shaders defualt.vert and default.frag
Shader shaderProgram("../ResourceFiles/Shaders/default.vert", "../ResourceFiles/Shaders/default.frag");
// Generates Vertex Array Object and binds it
VAO VAO1;
VAO1.Bind();
// Generates Vertex Buffer Object and links it to vertices
VBO VBO1(vertices, sizeof(vertices));
// Generates Element Buffer Object and links it to indices
EBO EBO1(indices, sizeof(indices));
// Links VBO attributes such as coordinates and colors to VAO
VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);                        
VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));      
VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
// Unbind all to prevent accidentally modifying them
VAO1.Unbind();
VBO1.Unbind();
EBO1.Unbind();
//Gets ID of uniform called "scale"
//GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
//Texture
int widthImg, heightImg, numColCh;
stbi_set_flip_vertically_on_load(true);
unsigned char* bytes = stbi_load("../ResourceFiles/Texture/ladrillos.png", &widthImg, &heightImg, &numColCh, 0);
//Texture dog("dog.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
//dog.texUnit(shaderProgram, "tex0", 0);
GLuint texture;
glGenTextures(1, &texture);
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, texture);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//Para ubicar la textura
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB,
GL_UNSIGNED_BYTE, bytes);
//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
glGenerateMipmap(GL_TEXTURE_2D);
//stbi_image_free(bytes);
glBindTexture(GL_TEXTURE_2D, 0);
GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0");
shaderProgram.Activate();
glUniform1i(tex0Uni, 0);
//Variables para controlar la rotacion
//float rotation = 0.0f;
//double prevTime = glfwGetTime();
glEnable(GL_DEPTH_TEST);
Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
// Main while loop
while (!glfwWindowShouldClose(window))
{
// Specify the color of the background
glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
// Clean the back buffer and assign the new color to it
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
// Tell OpenGL which Shader Program we want to use
shaderProgram.Activate();
camera.Inputs(window);
camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");
//Control de la Rotation de la Piramide con la textura incorporada por medio de la funcion del tiempo.
//double crntTime = glfwGetTime();
//if (crntTime - prevTime >= 1/60)
//{
//rotation += 0.5f;
//prevTime = crntTime;
//}
//Inicializacion de las matrices para ser utilizadas
//glm::mat4 model = glm::mat4(1.0f);
//glm::mat4 view = glm::mat4(1.0f);
//glm::mat4 proj = glm::mat4(1.0f);
//Asignamos diferentes transformaciones a las matrices que tenemos previamente declaradas
//Para controlar la rotacion de la piramide
//model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
//Para establecer la matriz de traslacion
//view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
//Para establecer la proyeccion en perspectiva
//proj = glm::perspective(glm::radians(45.05f), (float)(width / height), 0.1f, 100.0f);//Posicion de la Camara
//Entradas de las matrices para ser usadas en el Vertex Shader
//int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
//glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
// Assigns a value to the uniform
shaderProgram.Activate();
//Assigns a value to the uniform
//glUniform1f(uniID, 0.5f);
glBindTexture(GL_TEXTURE_2D, texture);
// Bind the VAO so OpenGL knows to use it
VAO1.Bind();
// Draw primitives, number of indices, datatype of indices, index of indices
glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT,
0);
// Swap the back buffer with the front buffer
glfwSwapBuffers(window);
// Take care of all GLFW events
glfwPollEvents();
}
// Delete all the objects we've created
VAO1.Delete();
VBO1.Delete();
EBO1.Delete();
glDeleteTextures(1, &texture);
shaderProgram.Delete();
// Delete window before ending the program
glfwDestroyWindow(window);
// Terminate GLFW before ending the program
glfwTerminate();
return 0;
}
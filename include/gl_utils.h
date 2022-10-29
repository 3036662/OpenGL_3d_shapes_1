#ifndef GL_UTILS_H_INCLUDED
#define GL_UTILS_H_INCLUDED

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <constants.h>
#include <vector>
#include <stb_image.h>
//#include <string>

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);


GLFWwindow* OpenGlInit(unsigned int width,unsigned int height,const char* name);


unsigned int MakeShaderProgram(const char * vertexShader,const char* fragmentShader);

unsigned int loadCubemap(std::vector<std::string> faces);
#endif // GL_UTILS_H_INCLUDED

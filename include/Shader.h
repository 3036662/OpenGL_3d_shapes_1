#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>


class Shader
{
    public:
        Shader();
        ~Shader();

        bool vertexShader(const char* vertexShaderPtr);
        bool fragmentShader(const char* fragmentShaderPtr);
        bool compileShaderProgram();
        void deleteShaderProgram();
        bool useShaderProgram();
        bool deleteVertexShader();
        bool deleteFragmentShader();
        bool deleteShaders();

        unsigned int getShaderProgramID();
        //Model Matrix
        bool findModelMatrixLocation(const char* uniform_name);
        bool setModelMatrix(const float* matrix_prt);
        // View Matrix
        bool findViewMatrixLocation(const char* uniform_name);
        bool setViewMatrix(const float* matrix_prt);
        // Projection Matrix
        bool findProjMatrixLocation(const char* uniform_name);
        bool setProjMatrix(const float* matrix_prt);
        // light source location
        bool findLightSourceLocation(const char* uniform_name);
        bool setLightSourceVec(const glm::vec3& light_pos_vec);
        // light color
        bool findLightColorLocation(const char* uniform_name);
        bool setLightColorVec(const glm::vec3& light_color_vec);
        // camera pos
        bool findCameraPosLoc(const  char* uniform_name);
        bool setCameraPosVec(const glm::vec3& camera_pos_vec);


    protected:

    private:
        unsigned int vertexShader_id;
        unsigned int fragmentShader_id;
        unsigned int shaderProgram_id;


        char infoLog[512]; // для записис результата проверки ошибок

        unsigned int modelLoc;
        unsigned int viewLoc;
        unsigned int projLoc;

        unsigned int lightSourceLoc;
        unsigned int lightColorLoc;
        unsigned int CameraPosLoc;

};

#endif // SHADER_H

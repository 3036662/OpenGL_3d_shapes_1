#include <glad/glad.h> // opengl загрузчик -opengl loader
#include <GLFW/glfw3.h> // контексти окно - context and window
#include <cmath> // математика - math
#include <memory> // умные указатели - smart pointers

// GUI imgui  Интерфейс
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <font_arial.hpp>

// математика  для матриц GLM -matrix math
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr


#include "constants.h"   // разрешение окна -screen width an height
#include "shaders.h" // шейдеры GLSL shaders
#include "gl_utils.h" // инициализация Opengl iniatilization
#include "VertexBuffer.hpp" // VBO
#include "VertexArrayObject.h" //VAO
#include "ElementsBuffer.h" //EBO
#include "Texture.h" // Texture loading class  -класс для хранения текстур
#include "Shader.h" // класс для работы с шейдерами
#include "Torus.h" // класс Тора - Torus class
#include "Octahedron.h" // класс Октаэдра - Octahendron class
#include "Cone.h"
#include "Cylinder.h" // класс цилиндра - Cylinder class

// пути для загрузки текстур -paths for textures
const char* TORUS_TEXT_PATH="Tex/water.png";
const char* OCT_TEXT_PATH="Tex/concrete.png";
const char* CYL_TEXT_PATH="Tex/rust.png";
const std::vector< std::string> faces
    {
    "Tex/skybox/right.jpg",
    "Tex/skybox/left.jpg",
    "Tex/skybox/top.jpg",
    "Tex/skybox/bottom.jpg",
    "Tex/skybox/front.jpg",
    "Tex/skybox/back.jpg"
    };

int main()
{
    // OpenGl Window
    GLFWwindow* window=OpenGlInit(SCR_WIDTH,SCR_HEIGHT,"Course Project"); // GlUtils
    if (window==nullptr){
        return -1;
    }

    /**************************************/
    // Тор
    std::unique_ptr<Torus>  torus=std::make_unique<Torus>(1,0.5);
    // создать буфер для точек (vertex bufer)
    std::unique_ptr<VertexBuffer> vboTorus=std::make_unique<VertexBuffer>();
    vboTorus->bindBuffer();
    vboTorus->pushData(torus->getRowVerticiesData(),torus->getVertDataSize());
    // Vertex Array Object
    std::unique_ptr<VertexArrayObject> vaoTorus=std::make_unique<VertexArrayObject>();
    vaoTorus->bindBuffer();
    vaoTorus->bindDataSrtucture();
    std::unique_ptr<Texture> texTorus=std::make_unique<Texture>();
    texTorus->loadTexture(TORUS_TEXT_PATH); // Загрузка текстуры- Texture Load
    glm::mat4 model_matrix_torus=glm::mat4(1.0f); // матрица модели - поворота на 90 градусов вокруг оси Х
    model_matrix_torus=glm::rotate(model_matrix_torus, glm::radians(90.0f), glm::vec3(1.0, 0.0,0.0));
    vaoTorus->unbindBuffer();

    /****************************************/
    // Октаэдр
    std::unique_ptr <Octahedron> oct=std::make_unique<Octahedron>();
    std::unique_ptr <VertexArrayObject> vaoOct=std::make_unique<VertexArrayObject>();
    std::unique_ptr <VertexBuffer> vboOct=std::make_unique<VertexBuffer>();
    vboOct->bindBuffer();
    vboOct->pushData(oct->getRowVerticiesData(),oct->getVertDataSize());
    vaoOct->bindBuffer();
    vaoOct->bindDataSrtucture();
    std::unique_ptr <Texture> texOct=std::make_unique<Texture>();
    texOct->bindTexture();
    texOct->loadTexture(OCT_TEXT_PATH);
    glm::mat4 model_oct=glm::translate(glm::mat4(1.0f),glm::vec3(3,0,0));
    vaoOct->unbindBuffer();
    /********************************************************************/
//    //Цилиндр
//    std::unique_ptr <Cylinder> cyl=std::make_unique<Cylinder>(1.0f,0.5f);
//    std::unique_ptr <VertexArrayObject> vaoCyl=std::make_unique<VertexArrayObject>();
//    std::unique_ptr <VertexBuffer> vboCyl=std::make_unique<VertexBuffer>();
//    vboCyl->bindBuffer();
//    vboCyl->pushData(cyl->getRowVerticiesData(),cyl->getVertDataSize());
//    vaoCyl->bindBuffer();
//    vaoCyl->bindDataSrtucture();
//    std::unique_ptr <Texture> texCyl=std::make_unique<Texture>();
//    texCyl->bindTexture();
//    texCyl->loadTexture(CYL_TEXT_PATH);
//    glm::mat4 model_cyl=glm::mat4(1);
//    model_cyl=glm::rotate(model_cyl, glm::radians(90.0f), glm::vec3(1.0, 0.0,0.0));
//    model_cyl=glm::translate(model_cyl, glm::vec3(0.0, 0.0,-0.5));
//    vaoCyl->unbindBuffer();
    /********************************************************************/

    std::unique_ptr <Cone> cone=std::make_unique<Cone>(1.5f,1.0f);
    std::unique_ptr <VertexArrayObject> vaoCone=std::make_unique<VertexArrayObject>();
    std::unique_ptr <VertexBuffer> vboCone=std::make_unique<VertexBuffer>();
    vboCone->bindBuffer();
    vboCone->pushData(cone->getRowVerticiesData(),cone->getVertDataSize());
    vaoCone->bindBuffer();
    vaoCone->bindDataSrtucture();
    std::unique_ptr <Texture> texCone=std::make_unique<Texture>();
    texCone->bindTexture();
    texCone->loadTexture(CYL_TEXT_PATH);
    glm::mat4 model_cone=glm::mat4(1);
    model_cone=glm::rotate(model_cone, glm::radians(-90.0f), glm::vec3(1.0, 0.0,0.0));
    model_cone=glm::translate(model_cone, glm::vec3(0.0, 0.0,-0.5));
    vaoCone->unbindBuffer();



    // матрицы трансформаций
    glm::mat4 view_matrix;   // матрица вида
     // аргументы - позиция камеры, позиция фокуса,вектор вверх в мировых координатах
    view_matrix = glm::lookAt(glm::vec3(0, 0,8.0f ),glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0.0f, 1.0f, 1.0f));
    // матрица проекции - угол обзора, соотношение сторон, ближняя и дальняя проекционная плоскость
    glm::mat4 projection_matrix = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
    /********************************************************************/
    // основной шейдер
    std::unique_ptr <Shader> shaderObj=std::make_unique<Shader>();
    shaderObj->vertexShader(vertexShaderSource);
    shaderObj->fragmentShader(fragmentShaderSource);
    shaderObj->compileShaderProgram();
    shaderObj->useShaderProgram();
    shaderObj->deleteShaders();
    shaderObj->findModelMatrixLocation("model_matr"); // Матрица модели
    shaderObj->setModelMatrix(glm::value_ptr(model_matrix_torus));
    shaderObj->findViewMatrixLocation("view_matr"); // Матрица вида
    shaderObj->findProjMatrixLocation("proj_matr"); // Матрица проекции
    shaderObj->setProjMatrix(glm::value_ptr(projection_matrix));
    glm::vec3 lightLoc(10,10,0);
    shaderObj->findLightSourceLocation("lightPos");
    shaderObj->setLightSourceVec(lightLoc);
    shaderObj->findLightColorLocation("lightColor");
    shaderObj->setLightColorVec(glm::vec3(1,1,1));
    shaderObj->findCameraPosLoc("viewPos");

    /********************************************************************/
    // создать интерфейс
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io=ImGui::GetIO();(void)io;
    io.Fonts->AddFontFromMemoryCompressedTTF(ArialFont_compressed_data,ArialFont_compressed_size,10.0f,NULL,io.Fonts->GetGlyphRangesCyrillic());
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window,true);
    ImGui_ImplOpenGL3_Init("#version 330");
    float cameraz{12.0f},cameray{4.0f},camerax{4.0f};
    float lightX{5},lightY{5},lightZ{0};
    float speedA{0.4f};
     /***********************************************************************/
    // Кубическая карта
    unsigned int skyboxTexture = loadCubemap(faces);
    std::unique_ptr <VertexBuffer> vboCube= std::make_unique<VertexBuffer>();
    vboCube->bindBuffer();
    std::unique_ptr <VertexArrayObject> vaoCube= std::make_unique<VertexArrayObject>();
    vaoCube->bindStructSkyBox();
    vboCube->pushData(skyboxVertices,sizeof(skyboxVertices));
    vaoCube->bindBuffer();
    /***********************************************************************/
    // Шейдер для кубической карты
    std::unique_ptr <Shader> skyBoxShader=std::make_unique<Shader>();
    skyBoxShader->vertexShader(cubeMapVS);
    skyBoxShader->fragmentShader(cubeMapFS);
    skyBoxShader->compileShaderProgram();
    skyBoxShader->useShaderProgram();
    skyBoxShader->deleteShaders();
    skyBoxShader->findProjMatrixLocation("projection");
    skyBoxShader->setProjMatrix(glm::value_ptr(projection_matrix));
    skyBoxShader->findViewMatrixLocation("view");

     /********************************************************************/
    // Главный цикл рендеринга
    while (!glfwWindowShouldClose(window))
    {
        // Обработка ввода
        processInput(window);
		// Выполнение рендеринга
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderObj->useShaderProgram();
        shaderObj->setLightSourceVec(glm::vec3(lightX,lightY,lightZ));
        camerax=cos(glfwGetTime()*speedA*0.2)*15; // вращение камеры
        cameraz=sin(glfwGetTime()*speedA*0.2)*15; // вращение камеры
        view_matrix = glm::lookAt(glm::vec3(camerax, cameray,cameraz),glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0.0f, 1.0f, 0.0f));
        shaderObj->setViewMatrix(glm::value_ptr(view_matrix));
        shaderObj->setCameraPosVec(glm::vec3(camerax, cameray,cameraz));   // установить позицию наблюдателя нужна для вычисления отраженного света

        // цилиндр
//        vaoCyl->bindBuffer();
//        texCyl->activate();
//        shaderObj->setModelMatrix(
//                glm::value_ptr(
//                    glm::translate( glm::mat4(1),glm::vec3( -sin(glfwGetTime()*speedA)*3, 0, -cos(glfwGetTime()*speedA)*3 )) * model_cyl)
//        );
//        glDrawArrays(GL_TRIANGLES, 0, cyl->getPointsCount());
//        vaoOct->unbindBuffer();
        vaoCone->bindBuffer();
        texCone->activate();
        shaderObj->setModelMatrix(
                glm::value_ptr(
                    glm::translate( glm::mat4(1),glm::vec3( -sin(glfwGetTime()*speedA)*3, 0, -cos(glfwGetTime()*speedA)*3 )) * model_cone)
        );
        glDrawArrays(GL_TRIANGLES, 0, cone->getPointsCount());
        vaoOct->unbindBuffer();

        // октаэдр - octahedron
        vaoOct->bindBuffer();
        texOct->activate();
        model_oct=glm::translate(glm::mat4(1),glm::vec3( sin(glfwGetTime()*speedA)*3, 0.0, cos(glfwGetTime()*speedA)*3 ) );
        shaderObj->setModelMatrix(glm::value_ptr(model_oct));
        glDrawArrays(GL_TRIANGLES, 0, oct->getPointsCount());
        vaoOct->unbindBuffer();

        //тор  - torus
        vaoTorus->bindBuffer();
        texTorus->activate();
        glActiveTexture(GL_TEXTURE0);
        texTorus->bindTexture();
        shaderObj->setModelMatrix(glm::value_ptr(model_matrix_torus));
        glDrawArrays(GL_TRIANGLES, 0, torus->getPointsCount());
        vaoTorus->unbindBuffer();

        // кубическая карта - skybox
        glDepthFunc(GL_LEQUAL);
        skyBoxShader->useShaderProgram();
        glm::mat4 view = glm::mat4(glm::mat3(view_matrix));
        skyBoxShader->setViewMatrix(glm::value_ptr(view));
        vaoCube->bindBuffer();
        vaoCube->bindStructSkyBox();
        glActiveTexture(GL_TEXTURE0);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDepthFunc(GL_LESS);
        glBindVertexArray(0);

        // интерфес пользователя gui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Матрицы");
        ImGui::SliderFloat("Камера X", &camerax,- 120.0f, 120.0f);
        ImGui::SliderFloat("Камера Y", &cameray, -120.0f, 120.0f);
        ImGui::SliderFloat("Камера Z", &cameraz, -120.0f, 120.0f);
        ImGui::SliderFloat("Свет X", &lightX, -20.0f, 20.0f);
        ImGui::SliderFloat("Свет Y", &lightY, -20.0f, 20.0f);
        ImGui::SliderFloat("Свет Z", &lightZ, -20.0f, 50.0f);
        ImGui::SliderFloat("Скорость А", &speedA, 0.0f, 2.0f);
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        // glfw: обмен содержимым front- и back-буферов. Отслеживание событий ввода/вывода
        glfwSwapBuffers(window);
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    // удаление шейдеров
    shaderObj->deleteShaderProgram();
    skyBoxShader->deleteShaderProgram();
    // завершить выполнени gui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // glfw: завершение, освобождение всех ранее задействованных GLFW-ресурсов
    glDeleteTextures(1,	&skyboxTexture);
    glfwTerminate();
    return 0;
}



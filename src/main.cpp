#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

// GUI imgui
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <font_arial.hpp>


#include <constants.h>
#include <shaders.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr



#include <gl_utils.h>
#include <VertexBuffer.hpp>
#include <VertexArrayObject.h>
#include <ElementsBuffer.h>
#include <Texture.h>
#include <Shader.h>

#include <Torus.h>
#include <Octahedron.h>
#include <Cylinder.h>

//const char* RUBBER_TEXT_PATH="/home/aleh/CodeBlocks_projects/GL_CP/Tex/Rubber.png";
const char* RUBBER_TEXT_PATH="Tex/water.png";
const char* CONCRETE_TEXT_PATH="Tex/concrete.png";
const char* RUST_TEXT_PATH="Tex/rust.png";

int main()
{
    GLFWwindow* window=OpenGlInit(SCR_WIDTH,SCR_HEIGHT,"Lab2"); // GlUtils
    if (window==nullptr){
        return -1;
    }

    /**************************************/
    Torus* torus=new Torus(1,0.5);
    // создать буфер для точек (vertex bufer)
    VertexBuffer* vboTorus=new VertexBuffer();
    vboTorus->bindBuffer();
    vboTorus->pushData(torus->getRowVerticiesData(),torus->getVertDataSize());
    // Vertex Array Object
    VertexArrayObject* vaoTorus=new VertexArrayObject();
    vaoTorus->bindBuffer();
    vaoTorus->bindDataSrtucture();
    Texture* texTorus=new Texture();
    texTorus->loadTexture(RUBBER_TEXT_PATH);
    glm::mat4 model_matrix_torus=glm::mat4(1.0f); // матрица модели - поворота на 90 градусов вокруг оси Х
    model_matrix_torus=glm::rotate(model_matrix_torus, glm::radians(90.0f), glm::vec3(1.0, 0.0,0.0));
    vaoTorus->unbindBuffer();

    /****************************************/
    // Октаэдр
    Octahedron* oct=new Octahedron(1.0f);
    VertexArrayObject* vaoOct=new VertexArrayObject();
    VertexBuffer* vboOct=new VertexBuffer();
    vboOct->bindBuffer();
    vboOct->pushData(oct->getRowVerticiesData(),oct->getVertDataSize());
    vaoOct->bindBuffer();
    vaoOct->bindDataSrtucture();
    Texture* texOct=new Texture();
    texOct->bindTexture();
    texOct->loadTexture(CONCRETE_TEXT_PATH);
    // glm::mat4 model_oct(glm::mat4(1.0f));
    glm::mat4 model_oct=glm::translate(glm::mat4(1.0f),glm::vec3(3,0,0));
    //model_oct=glm::rotate(model_oct, glm::radians(90.0f), glm::vec3(1.0, 0.0,0.0));
    vaoOct->unbindBuffer();

    /********************************************************************/
    Cylinder* cyl=new Cylinder(1.0f,0.5f);
    VertexArrayObject* vaoCyl=new VertexArrayObject();
    VertexBuffer* vboCyl=new VertexBuffer();
    vboCyl->bindBuffer();
    vboCyl->pushData(cyl->getRowVerticiesData(),cyl->getVertDataSize());

    vaoCyl->bindBuffer();
    vaoCyl->bindDataSrtucture();

    Texture* texCyl=new Texture();
    texCyl->bindTexture();
    texCyl->loadTexture(RUST_TEXT_PATH);
    glm::mat4 model_cyl=glm::mat4(1);
    model_cyl=glm::rotate(model_cyl, glm::radians(90.0f), glm::vec3(1.0, 0.0,0.0));
    model_cyl=glm::translate(model_cyl, glm::vec3(0.0, 0.0,-0.5));
    vaoCyl->unbindBuffer();


    /********************************************************************/
    // матрицы трансформаций
    glm::mat4 view_matrix;   // матрица вида
     // аргументы - позиция камеры, позиция фокуса,вектор вверх в мировых координатах
    view_matrix = glm::lookAt(glm::vec3(0, 0,8.0f ),glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0.0f, 1.0f, 1.0f));
    // матрица проекции - угол обзора, соотношение сторон, ближняя и дальняя проекционная плоскость
    glm::mat4 projection_matrix = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
    /********************************************************************/
    Shader* shaderObj=new Shader();
    shaderObj->vertexShader(vertexShaderSource);
    shaderObj->fragmentShader(fragmentShaderSource);
    shaderObj->compileShaderProgram();
    shaderObj->useShaderProgram();
    shaderObj->deleteShaders();
    shaderObj->findModelMatrixLocation("model_matr");
    shaderObj->setModelMatrix(glm::value_ptr(model_matrix_torus));
    shaderObj->findViewMatrixLocation("view_matr");
    shaderObj->findProjMatrixLocation("proj_matr");
    shaderObj->setProjMatrix(glm::value_ptr(projection_matrix));
    glm::vec3 lightLoc(10,10,0);
    shaderObj->findLightSourceLocation("lightPos");
    shaderObj->setLightSourceVec(lightLoc);
    shaderObj->findLightColorLocation("lightColor");
    shaderObj->setLightColorVec(glm::vec3(1,1,1));
    shaderObj->findCameraPosLoc("viewPos");

    glEnable(GL_DEPTH_TEST); // тестирование буфера глубины
    glPolygonMode(GL_FRONT, GL_FILL);
    /********************************************************************/
    // создать интерфейс
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io=ImGui::GetIO();(void)io;
    //io.Fonts->AddFontFromFileTTF("fonts/arial.ttf",10,NULL,io.Fonts->GetGlyphRangesCyrillic());// добавить кириллицу
    io.Fonts->AddFontFromMemoryCompressedTTF(ArialFont_compressed_data,ArialFont_compressed_size,10.0f,NULL,io.Fonts->GetGlyphRangesCyrillic());
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window,true);
    ImGui_ImplOpenGL3_Init("#version 330");
    float cameraz{12.0f},cameray{4.0f},camerax{4.0f};
    float lightX{5},lightY{5},lightZ{0};
//    float lastTime{0.0f},now{0.0f};
    float speedA{0.4f};

    glFrontFace(GL_CCW);
   // glEnable(GL_CULL_FACE);
  //  glCullFace(GL_BACK);


    /***********************************************************************/
    // Кубическая карта
    const std::vector< std::string> faces
    {
    "Tex/skybox/right.jpg",
    "Tex/skybox/left.jpg",
    "Tex/skybox/top.jpg",
    "Tex/skybox/bottom.jpg",
    "Tex/skybox/front.jpg",
    "Tex/skybox/back.jpg"
    };
    unsigned int skyboxTexture = loadCubemap(faces);
    VertexBuffer* vboCube= new VertexBuffer();
    vboCube->bindBuffer();
    VertexArrayObject* vaoCube= new VertexArrayObject();
    vaoCube->bindStructSkyBox();
    vboCube->pushData(skyboxVertices,sizeof(skyboxVertices));
    vaoCube->bindBuffer();

    Shader* skyBoxShader=new Shader();
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

        camerax=cos(glfwGetTime()*speedA*0.2)*15;
        cameraz=sin(glfwGetTime()*speedA*0.2)*15;
        view_matrix = glm::lookAt(glm::vec3(camerax, cameray,cameraz),glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0.0f, 1.0f, 0.0f));
        shaderObj->setViewMatrix(glm::value_ptr(view_matrix));
        shaderObj->setCameraPosVec(glm::vec3(camerax, cameray,cameraz));   // установить позицию наблюдателя нужна для вычисления отраженного света

        // cylinder
        vaoCyl->bindBuffer();
        texCyl->activate();
        shaderObj->setModelMatrix(
                glm::value_ptr(
                    glm::translate( glm::mat4(1),glm::vec3( -sin(glfwGetTime()*speedA)*3, 0, -cos(glfwGetTime()*speedA)*3 )) * model_cyl)
        );
        glDrawArrays(GL_TRIANGLES, 0, cyl->getPointsCount());
        vaoOct->unbindBuffer();

        // octahedron
        vaoOct->bindBuffer();
        texOct->activate();
         model_oct=glm::translate(glm::mat4(1),glm::vec3( sin(glfwGetTime()*speedA)*3, 0.0, cos(glfwGetTime()*speedA)*3 ) );
        shaderObj->setModelMatrix(glm::value_ptr(model_oct));
        glDrawArrays(GL_TRIANGLES, 0, oct->getPointsCount());
        vaoOct->unbindBuffer();

        //torus
        vaoTorus->bindBuffer();
        texTorus->activate();
        glActiveTexture(GL_TEXTURE0);
        texTorus->bindTexture();
        shaderObj->setModelMatrix(glm::value_ptr(model_matrix_torus));
        glDrawArrays(GL_TRIANGLES, 0, torus->getPointsCount());
        vaoTorus->unbindBuffer();

        //  skybox
        glDepthFunc(GL_LEQUAL);
        skyBoxShader->useShaderProgram();
        glm::mat4 view = glm::mat4(glm::mat3(view_matrix));
        skyBoxShader->setViewMatrix(glm::value_ptr(view));
        vaoCube->bindBuffer();
        vaoCube->bindStructSkyBox();
        glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDepthFunc(GL_LESS);
        glBindVertexArray(0);

        //gui
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

    shaderObj->deleteShaderProgram();

    // завершить выполнени gui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // glfw: завершение, освобождение всех ранее задействованных GLFW-ресурсов
    delete torus;
    delete vaoTorus;
    delete vboTorus;
    delete texTorus;

    delete oct;
    delete vaoOct;
    delete vboOct;
    delete texOct;

    delete cyl;
    delete vaoCyl;
    delete vboCyl;
    delete texCyl;;

    delete shaderObj;
    glfwTerminate();
    return 0;
}



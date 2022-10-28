#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject()
{
     glGenVertexArrays(1, &VAO_id);

}

VertexArrayObject::~VertexArrayObject()
{
    glDeleteVertexArrays(1,&VAO_id);
}


void VertexArrayObject::bindBuffer(){
    glBindVertexArray(VAO_id);
}


void VertexArrayObject::bindDataSrtucture(){
    // аттрибуты данных, арггументы:  индекс аттрибута, количество аттрибутов, тип аттрибута
    // необходимость нормализации = false, смещение между наборами аттрибутов , смещение до первого аттрибута

    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0); // координаты
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)( sizeof(glm::vec3) )); // нормали
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)( 2*sizeof(glm::vec3) )); // текстуры
    glEnableVertexAttribArray(2);
}

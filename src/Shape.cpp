#include "glm/glm.hpp"
#include <glm/gtx/normal.hpp>
#include "Shape.h"


Shape::Shape()
{
}

// возвращает указатель на память где хранятся точки
const void* Shape::getRowVerticiesData(){
    return this->vertices.data();
}

// возвращает размер данных verticies
const unsigned Shape::getVertDataSize(){
    return this->vertices.size()*sizeof(Vertex);
}

// возвращает количество точек
const unsigned Shape::getPointsCount(){
    return vertices.size();
}


// возвращает указатель на память где хранятся индексы вершин
const void* Shape::getIndData(){
    return this->indices.data();
}

// размер данных для индексов
const unsigned Shape::getIndDataSize(){
    return this->indices.size()*sizeof(unsigned);
}

// количество индексов
const unsigned Shape::getIndCount(){
    return this->indices.size();
}

// соберет треугольник из трех координат
// и трех координат текстур
// и положит точки в массив verticies
void Shape::make_triangle(const glm::vec3& a,const glm::vec3& b,const glm::vec3& c,const glm::vec2& texA,const glm::vec2& texB,const glm::vec2& texC){
    glm::vec3 norm; // нормаль треугольника
    norm=glm::triangleNormal(a,b,c);
    vertices.emplace_back(Vertex(a,norm,texA));
    vertices.emplace_back(Vertex(b,norm,texB));
    vertices.emplace_back(Vertex(c,norm,texC));
}

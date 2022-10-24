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

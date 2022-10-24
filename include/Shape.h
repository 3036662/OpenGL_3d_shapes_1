#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>



struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    //glm::vec2 TexCoords;

    Vertex(const glm::vec3& pos,const glm::vec3& norm):Position(pos),Normal(norm){};
};



class Shape
{
    public:
        const void* getRowVerticiesData(); // возвращает указатель на память где хранятся точки
        const unsigned getVertDataSize(); // возвращает размер данных verticies
        const unsigned getPointsCount(); // возвращает количество точек

        const void* getIndData(); // возвращает указатель на память где хранятся индексы вершин
        const unsigned getIndDataSize(); // размер данных для индексов
        const unsigned getIndCount(); // количество индексов

    protected:
        Shape();
        std::vector<Vertex>       vertices;
        std::vector<unsigned int> indices;

    private:

};

#endif // SHAPE_H

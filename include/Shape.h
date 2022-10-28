#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>



struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    //default constructor
    Vertex():Position(glm::vec3(0)),Normal(glm::vec3(0)),TexCoords(glm::vec2(0)){};
    // constructor without Texture Coordinates - 2 args
    Vertex(const glm::vec3& pos,const glm::vec3& norm):Position(pos),Normal(glm::normalize(norm)),TexCoords(glm::vec2(0)){};
    // constructor 3 args
    Vertex(const glm::vec3& pos,const glm::vec3& norm, const glm::vec2& TexCoors):Position(pos),Normal(glm::normalize(norm)),TexCoords(TexCoors){};
    // Copy constructor
    Vertex(const Vertex& v):Position(v.Position),Normal(v.Normal),TexCoords(v.TexCoords){};
    // Copy assignment
    Vertex& operator= (const Vertex& v){
        if (&v==this){return *this;} //self assignment
        Position=v.Position;
        Normal=v.Normal;
        TexCoords=v.TexCoords;
        return *this;
    }
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
        // соберет треугольник из трех координат
        void make_triangle(const glm::vec3& a,const glm::vec3& b,const glm::vec3& c,const glm::vec2& texA,const glm::vec2& texB,const glm::vec2& texC) ;
    private:


};

#endif // SHAPE_H

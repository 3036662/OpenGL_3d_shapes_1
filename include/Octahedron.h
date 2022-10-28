#ifndef OCTAHEDRON_H
#define OCTAHEDRON_H
#include "Shape.h"


// 6 точек октаэдра
//основание
const glm::vec3 a(1,0,0) ;
const glm::vec3 b(0,1,0);
const glm::vec3 c(-1,0,0);
const glm::vec3 d(0,-1,0);
// вершины
const glm::vec3 e(0,0,1);
const glm::vec3 f(0,0,-1);

//координаты текстуры для трех точек треугольника
const glm::vec2 tex_c1(0.0f,0.0f);
const glm::vec2 tex_c2(1.0f,0.0f);
const glm::vec2 tex_c3(0.5f,1.0f);


class Octahedron:public Shape
{
    public:
        Octahedron()=delete;
        Octahedron(float radius); // радиус окрудности в которую будет вписан октаэдр
        ~Octahedron();

    protected:

    private:

};

#endif // OCTAHEDRON_H

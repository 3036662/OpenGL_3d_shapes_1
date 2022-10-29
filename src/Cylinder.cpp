#include "Cylinder.h"

Cylinder::Cylinder(float height,float radius)
{
    const float circle=glm::two_pi<float>();
    const float rotation_step=circle/CYL_POINTS_IN_CIRCLE;


    // основания цилиндра
    for (float i=0;i<circle;i+=rotation_step){
        make_triangle(
            glm::vec3(0,0,0), //c
            glm::vec3( glm::cos(i+rotation_step)*radius, glm::sin(i+rotation_step)*radius,0), // b
            glm::vec3( glm::cos(i)*radius,glm::sin(i)*radius,0 ), //a
            glm::vec2(0.5,1),
            glm::vec2(0,0),
            glm::vec2(1,0)
        );
        make_triangle(
            glm::vec3(0,0,height), //c
            glm::vec3( glm::cos(i+rotation_step)*radius, glm::sin(i+rotation_step)*radius,height), // b
            glm::vec3( glm::cos(i)*radius,glm::sin(i)*radius,height ), //a
            glm::vec2(0.5,1),
            glm::vec2(0,0),
            glm::vec2(1,0)
        );
    }
    const float hStep=radius*rotation_step*glm::sqrt(3)*2; // шаг по высоте
    // стена цилиндра
    glm::vec3 a,b,c,d;
    for (float z=0;z<height;z+=hStep){ // z- высота
        for (float i=0;i<circle;i+=rotation_step){
            a=glm::vec3( glm::cos(i)*radius,glm::sin(i)*radius,z);
            b=glm::vec3( glm::cos(i+rotation_step)*radius, glm::sin(i+rotation_step)*radius,z);
            c=glm::vec3( glm::cos(i+rotation_step)*radius, glm::sin(i+rotation_step)*radius,z+hStep);
            d=glm::vec3( glm::cos(i)*radius,glm::sin(i)*radius,z+hStep);
            make_triangle(
                c,a,b,
                glm::vec2(1,1),glm::vec2(0,0),glm::vec2(1,0)
            );
            make_triangle(
                c,d,a,
                glm::vec2(1,1),glm::vec2(0,1),glm::vec2(0,0)
            );
        }
    }
    std::cout<<vertices.size();
}



Cylinder::~Cylinder()
{
    //dtor
}

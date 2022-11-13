#include "Cone.h"

Cone::Cone(float hieght,float radius)
{

    const float circle=glm::two_pi<float>();
    const float rotation_step=circle/CONE_POINTS_IN_CIRCLE;
    // основание
    for (float i=0;i<circle;i+=rotation_step){
        make_triangle(
                glm::vec3(0),
                glm::vec3( glm::cos(i+rotation_step)*radius, glm::sin(i+rotation_step)*radius,0), // b
                glm::vec3( glm::cos(i)*radius,glm::sin(i)*radius,0 ), //a

                glm::vec2(0),
                glm::vec2(1,0),
                glm::vec2(0.5,1)
        );
        make_triangle(
            glm::vec3(0,0,hieght),
            glm::vec3( glm::cos(i)*radius,glm::sin(i)*radius,0 ), //a
            glm::vec3( glm::cos(i+rotation_step)*radius, glm::sin(i+rotation_step)*radius,0), // b
            glm::vec2(0),
            glm::vec2(1,0),
            glm::vec2(0.5,1)

        );
    }
    std::cout<<vertices.size()<<std::endl;

}

Cone::~Cone()
{
    //dtor
}

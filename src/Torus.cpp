#include "Torus.h"


Torus::Torus(float bigRadius,float smallRadius)
{
    const unsigned ringsNumber{100};
    const unsigned pointsInRing{20};
    float circle=glm::two_pi<float>();
    float rot_step=circle/ringsNumber;
    float points_step=circle/pointsInRing;
    float x{0},y{0},z{0};
    // для каждой образующей окружности
    for (float rot_angle=0;rot_angle<circle;rot_angle+=rot_step){
        // для каждой точки образующей окружности
        for ( float point_angle=-glm::pi<float>(); point_angle<glm::pi<float>(); point_angle+=points_step ){
//            x=(bigRadius+smallRadius*glm::cos(point_angle))*glm::cos(rot_angle);
//            y=(bigRadius+smallRadius*glm::cos(point_angle))*glm::sin(rot_angle);
//            z=smallRadius*glm::sin(rot_angle);
//            this->vertices.emplace_back( Vertex(glm::vec3(x,y,z),glm::vec3(x,y,z)));
            x=( bigRadius+smallRadius*glm::cos(point_angle) ) *glm::cos(rot_angle);
            y=( bigRadius+smallRadius*glm::cos(point_angle) ) *glm::sin(rot_angle);
            z=smallRadius*glm::sin(point_angle);
            this->vertices.emplace_back( Vertex(glm::vec3(x,y,z),glm::vec3(x,y,z)));
        }
    }

    // соединить точки в треугольники
    unsigned a{0},b{0},c{0}; // индексы трех точек треугольника
    unsigned currRing{0},nextRing{0};
    for ( currRing=0; currRing<ringsNumber; ++currRing ){
        currRing==ringsNumber-1 ? nextRing=0 : nextRing=currRing+1; // последнее кольцо нужно соединить с первым
        for ( unsigned i=0; i<pointsInRing-1; ++i ){ //для каждой точки кольца кроме последней
            // формируется два треугольника
            a=currRing*pointsInRing+i;
            b=a+1;
            c=nextRing*pointsInRing+i;
            this->indices.push_back(a);
            this->indices.push_back(b);
            this->indices.push_back(c);
            a=c;
            c=a+1;
            this->indices.push_back(a);
            this->indices.push_back(b);
            this->indices.push_back(c);
        }
    }
}

Torus::~Torus()
{

}



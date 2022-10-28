#include "Torus.h"


Torus::Torus(float bigRadius,float smallRadius)
{
    const unsigned ringsNumber{100};
    const unsigned pointsInRing{30};
    float circle=glm::two_pi<float>(); //целая окружность в радианах
    float rot_step=circle/ringsNumber; // шаг вращение
    float points_step=circle/pointsInRing; // количество точек в образующей окружности
    float x{0},y{0},z{0};


   glm::vec3 a,b,c,d;
    // для каждой образующей окружности
  for (float rot_angle=0;rot_angle<circle+0.1;rot_angle+=rot_step){
        // для каждой точки образующей окружности
        for ( float point_angle=-glm::pi<float>(); point_angle<glm::pi<float>(); point_angle+=points_step ){
            x=( bigRadius+smallRadius*glm::cos(point_angle) ) *glm::cos(rot_angle);
            y=( bigRadius+smallRadius*glm::cos(point_angle) ) *glm::sin(rot_angle);
            z=smallRadius*glm::sin(point_angle);
            a=glm::vec3(x,y,z);

            x=( bigRadius+smallRadius*glm::cos(point_angle) ) *glm::cos(rot_angle+rot_step);
            y=( bigRadius+smallRadius*glm::cos(point_angle) ) *glm::sin(rot_angle+rot_step);
            z=smallRadius*glm::sin(point_angle);
            b=glm::vec3(x,y,z);

            x=( bigRadius+smallRadius*glm::cos(point_angle+points_step) ) *glm::cos(rot_angle+rot_step);
            y=( bigRadius+smallRadius*glm::cos(point_angle+points_step) ) *glm::sin(rot_angle+rot_step);
            z=smallRadius*glm::sin(point_angle+points_step);
            c=glm::vec3(x,y,z);

            x=( bigRadius+smallRadius*glm::cos(point_angle+points_step) ) *glm::cos(rot_angle);
            y=( bigRadius+smallRadius*glm::cos(point_angle+points_step) ) *glm::sin(rot_angle);
            z=smallRadius*glm::sin(point_angle+points_step);
            d=glm::vec3(x,y,z);

            make_triangle(
                a,b,c,
                glm::vec2(0,0),
                glm::vec2(1,0),
                glm::vec2(1,1)
            );
            make_triangle(
                a,c,d,
                glm::vec2(1,1),
                glm::vec2(0,1),
                glm::vec2(0,0)
            );

        }
    }
}

Torus::~Torus()
{

}



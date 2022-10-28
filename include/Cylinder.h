#ifndef CYLINDER_H
#define CYLINDER_H

#include <Shape.h>
#include <glm/gtc/constants.hpp>

const int CYL_POINTS_IN_CIRCLE=100;


class Cylinder : public Shape
{
    public:
        Cylinder()=delete;
        Cylinder(float hieght,float radius);
        ~Cylinder();

    protected:

    private:
};

#endif // CYLINDER_H

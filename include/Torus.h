#ifndef TORUS_H
#define TORUS_H

#include "Shape.h"
#include <iostream>


class Torus:public Shape
{
    public:
        Torus()=delete;
        Torus(float bigRadius,float smallRadius);

        ~Torus();

    protected:

    private:
};

#endif // TORUS_H

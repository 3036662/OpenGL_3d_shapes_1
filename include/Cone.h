#ifndef CONE_H
#define CONE_H

#include <Shape.h>

const int CONE_POINTS_IN_CIRCLE=40;

class Cone : public Shape
{
    public:
        Cone()=delete;
        Cone(float hieght,float radius);
        ~Cone();

    protected:

    private:
};

#endif // CONE_H

#include "Octahedron.h"

// радиус окрудности в которую будет вписан октаэдр - radius
Octahedron::Octahedron(){
    make_triangle(e,a,b,tex_c3,tex_c1,tex_c2);
    make_triangle(e,b,c,tex_c3,tex_c1,tex_c2);
    make_triangle(e,c,d,tex_c3,tex_c1,tex_c2);
    make_triangle(e,d,a,tex_c3,tex_c1,tex_c2);

    make_triangle(f,b,a,tex_c3,tex_c1,tex_c2);
    make_triangle(f,c,b,tex_c3,tex_c1,tex_c2);
    make_triangle(f,d,c,tex_c3,tex_c1,tex_c2);
    make_triangle(f,a,d,tex_c3,tex_c1,tex_c2);
}

Octahedron::~Octahedron()
{
    //dtor
}




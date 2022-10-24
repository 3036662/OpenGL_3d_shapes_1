#ifndef ELEMENTSBUFFER_H
#define ELEMENTSBUFFER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>



class ElementsBuffer
{
    public:
        ElementsBuffer();
        ~ElementsBuffer();

        void bindBuffer();
        void pushData(const void* data,unsigned int data_size);

    protected:

    private:
    unsigned int EBO_id;
};

#endif // ELEMENTSBUFFER_H

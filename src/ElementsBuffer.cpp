#include "ElementsBuffer.h"

ElementsBuffer::ElementsBuffer()
{
    glGenBuffers(1, &EBO_id);
}

ElementsBuffer::~ElementsBuffer()
{
    glDeleteBuffers(1,&EBO_id);
}

void ElementsBuffer::bindBuffer(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_id);
}

void ElementsBuffer::pushData(const void* data,unsigned int data_size){
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW);
}

#include "Texture.h"


Texture::Texture()
{
    glGenTextures(1, &texture_id);
}

Texture::~Texture()
{
    stbi_image_free(data_);
   glDeleteTextures(1, &texture_id);
}

void Texture::bindTexture(){
    glBindTexture(GL_TEXTURE_2D, texture_id);
}

void Texture::loadTexture(const char* texturefile){
    stbi_set_flip_vertically_on_load(1);
    this->data_=stbi_load(texturefile,&width,&height,&nrChannels,4);
    if (data_){
        this->activate();
    }
    else{
        std::cout << "Failed to load texture" << std::endl;
    }
    //
}


void Texture::activate(){
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data_);
       // glBindTexture(0);

        //glGenerateMipmap(GL_TEXTURE_2D);
}

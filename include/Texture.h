#ifndef TEXTURE_H
#define TEXTURE_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <iostream>

class Texture
{
    public:
        Texture();
        ~Texture();

        void bindTexture();
        void loadTexture(const char* texturefile);
        void activate(); //load to gpu

    protected:

    private:

        unsigned texture_id;
        int width;
        int height;
        int nrChannels;
        unsigned char* data_;
};

#endif // TEXTURE_H

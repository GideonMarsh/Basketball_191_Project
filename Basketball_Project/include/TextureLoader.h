#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H
#include<soil.h>
#include<GL/gl.h>
#include<iostream>

using namespace std;

class TextureLoader
{
    public:
        TextureLoader();
        virtual ~TextureLoader();

        void binder();
        void loadTexture(char*);                // image files loaded as character strings

        unsigned char* image;
        int width, height;

        GLuint tex;                             // handler

    protected:

    private:
};

#endif // TEXTURELOADER_H

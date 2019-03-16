#include "TextureLoader.h"

TextureLoader::TextureLoader()
{
    //ctor
}

TextureLoader::~TextureLoader()
{
    //dtor
}

void TextureLoader::binder()
{
    glBindTexture(GL_TEXTURE_2D,tex);
}

void TextureLoader::loadTexture(char* filename)
{
    glGenTextures(1,&tex);                                                                  // create the handler
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

    glBindTexture(GL_TEXTURE_2D, tex);
    image = SOIL_load_image(filename,&width,&height, 0,SOIL_LOAD_RGBA);                      // get the image
                                        // only thing SOIL is used for is loading the image into the handler, just the one line

    if(!image)cout<<"fail to find image"<<endl;                                             // if image not found


    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width, height,0,GL_RGBA,GL_UNSIGNED_BYTE,image);     // puts the image in the handler
    SOIL_free_image_data(image);                                // gets rid of the original image now that it's in the handler

    glEnable(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);                        // how to wrap image
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
}

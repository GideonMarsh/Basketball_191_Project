#include "Model.h"
#include<TextureLoader.h>

TextureLoader *tex = new TextureLoader();

Model::Model()
{
    //ctor
    RotateX = 0.0;
    RotateY = 0.0;
    RotateZ = 0.0;

    zoom = -8.0;
    xPos = 0.0;
    yPos = 0.0;

}

Model::~Model()
{
    //dtor
}

void Model::modelInit(char* filename)
{
    tex->loadTexture(filename);
}

void Model::drawModel()
{
    tex->binder();
    glColor3f(0.9,0.6,0.6);
    glTranslated(xPos,yPos,zoom);                     // Not "translated" but translate d for double
    glRotated(RotateX,1,0,0);
    glRotated(RotateY,0,1,0);
    glRotated(RotateZ,0,0,1);

    // Whatever the model is drawing goes here
    glutSolidTeapot(0.5);
}

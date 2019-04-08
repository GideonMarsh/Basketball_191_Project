#ifndef SHOOTSCENE_H
#define SHOOTSCENE_H

#include <GL/gl.h>
#include <TextureLoader.h>

class ShootScene
{
    public:
        ShootScene();
        virtual ~ShootScene();
        TextureLoader* texture = new TextureLoader();

        GLvoid sceneInit(char*);
        GLvoid drawSlide(GLfloat, GLfloat);

        GLfloat popUpW, popUpH;
        GLint pages;
        float xMax, xMin, yMax, yMin;

    protected:

    private:
};

#endif // SHOOTSCENE_H

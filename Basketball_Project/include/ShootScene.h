#ifndef SHOOTSCENE_H
#define SHOOTSCENE_H

#include <GL/gl.h>
#include <TextureLoader.h>
#include<Timer.h>

class ShootScene
{
    public:
        ShootScene();
        virtual ~ShootScene();
        TextureLoader* texture = new TextureLoader();
        TextureLoader* texture2 = new TextureLoader();
        TextureLoader* texture3 = new TextureLoader();
        TextureLoader* texture4 = new TextureLoader();

        GLvoid sceneInit(char*);
        GLvoid UIInit(char*, char*, char*);
        GLvoid drawSlide(GLfloat, GLfloat);
        GLvoid drawShotUI();


        GLfloat popUpW, popUpH;
        GLint pages;
        float xMax, xMin, yMax, yMin, shotFloat, shotSpeed;
        bool moveUp, moveDown, winSpace;

        Timer *Time = new Timer();

        TextureLoader *gradientTexture = new TextureLoader();

    protected:

    private:
};

#endif // SHOOTSCENE_H

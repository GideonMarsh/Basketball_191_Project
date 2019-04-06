#ifndef SLIDES_H
#define SLIDES_H

#include <GL/gl.h>
#include <TextureLoader.h>


class Slides
{
    public:
        Slides();
        virtual ~Slides();
        TextureLoader* texture = new TextureLoader();

        GLvoid slideInit(char*);
        GLvoid drawSlide(GLfloat, GLfloat);

        GLfloat popUpW, popUpH;
        GLint pages;
        float xMax, xMin, yMax, yMin;

    protected:

    private:
};

#endif // SLIDES_H

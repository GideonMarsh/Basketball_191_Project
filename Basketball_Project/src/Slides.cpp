#include "Slides.h"


Slides::Slides()
{

    //ctor

    xMax = 1.0;
    xMin = 0.0;
    yMax = 1.0;
    yMin = 0.0;
    pages = 0;
}

Slides::~Slides()
{
    //dtor
}

GLvoid Slides::slideInit(char* fileName)
{
    texture->loadTexture(fileName);
}

GLvoid Slides::drawSlide(GLfloat w, GLfloat h)
{


    glPushMatrix();
    //glTranslated(0.0,0.0,-0.5); Created another window

    texture->binder();
    //    glPopMatrix();


    glScaled(5.0,4.0,1.0);

    glBegin(GL_POLYGON);                    // drawing in openGL

    glTexCoord2f(xMin,yMin);                // drawing the four vertices of the square
    glVertex3f(-w/h,1,-10.0f);              // using width/height (aspect ratio) lets us scale to any screen size later
    glTexCoord2f(xMax,yMin);                // alternate positives/negatives to have all combinations (each area on graph)
    glVertex3f(w/h,1,-10.0f);
    glTexCoord2f(xMax,yMax);
    glVertex3f(w/h,-1,-10.0f);
    glTexCoord2f(xMin,yMax);
    glVertex3f(-w/h,-1,-10.0f);

    glEnd();
}

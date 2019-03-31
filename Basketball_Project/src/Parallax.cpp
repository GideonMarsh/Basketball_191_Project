#include "Parallax.h"
#include<TextureLoader.h>

TextureLoader *bgTexture = new TextureLoader();

Parallax::Parallax()
{
    //ctor
    xMax = 0.4;
    xMin = 0.0;
    yMax = 1.0;
    yMin = 0.0;
}

Parallax::~Parallax()
{
    //dtor
}

void Parallax::drawSquare(float width, float height)
{
    bgTexture->binder();

    glScaled(4.2,4.2,1.0);

    glBegin(GL_POLYGON);                    // drawing in openGL

    glTexCoord2f(xMin,yMin);                // drawing the four vertices of the square
    glVertex3f(-width/height,1,-10.0f);     // using width/height (aspect ratio) lets us scale to any screen size later
    glTexCoord2f(xMax,yMin);                // alternate positives/negatives to have all combinations (each area on graph)
    glVertex3f(width/height,1,-10.0f);
    glTexCoord2f(xMax,yMax);
    glVertex3f(width/height,-1,-10.0f);
    glTexCoord2f(xMin,yMax);
    glVertex3f(-width/height,-1,-10.0f);

    glEnd();
}

void Parallax::parallaxInit(char* filename)
{
    bgTexture->loadTexture(filename);
}

bool Parallax::scroll(string direction, float speed)
{
    /* Unused
    if (direction == "up") {
        yMin = yMin - speed;
        yMax = yMax - speed;
    }
    if (direction == "down") {
        yMin = yMin + speed;
        yMax = yMax + speed;
    }
    */
    if (direction == "left" && xMin >= 0.0) {
        xMin = xMin - speed;
        xMax = xMax - speed;
        return true;
    }
    else {
        if (direction == "right" && xMax <= 1.0) {
            xMin = xMin + speed;
            xMax = xMax + speed;
            return true;
        }
        else {
            return false;
        }
    }

}


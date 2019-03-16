#ifndef PARALLAX_H
#define PARALLAX_H

#include<iostream>
#include<windows.h>

using namespace std;

class Parallax
{
    public:
        Parallax();
        virtual ~Parallax();

        void drawSquare(float, float);              // drawing a square
        void parallaxInit(char *);                  // initializing the square with a texture
        void scroll(string, float);           // for scrolling the background to give illusion of movement

        float xMax, xMin, yMax, yMin;               // for mapping the background to the correct size/shape

    protected:

    private:
};

#endif // PARALLAX_H

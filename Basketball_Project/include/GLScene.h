#ifndef GLSCENE_H
#define GLSCENE_H

#include<windows.h>             // include windows header
#include<GL/glut.h>             // include glut header
#include <Slides.h>

class GLScene
{
    public:
        GLScene();              // constructor
        virtual ~GLScene();     // deconstructor
        GLint initGL();         // platform independent int - PCs and mobile phones have different int sizes
        GLint drawGLScene();
        GLvoid resizeGLScene(GLsizei, GLsizei); // for resizing the screen; takes two ints?

        int winMsg(HWND, UINT, WPARAM, LPARAM);

        float screenWidth, screenHeight;
        Slides *newPage = new Slides();

        bool flag0,flag1,flag2, flag3;

    protected:

    private:
};

#endif // GLSCENE_H

#ifndef GLSCENE_H
#define GLSCENE_H

#include<windows.h>             // include windows header
#include<GL/glut.h>             // include glut header
#include <Slides.h>
#include <ShootScene.h>

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
        Slides *landingPage = new Slides();
        Slides *menuPage = new Slides();
        Slides *helpPage = new Slides();
        Slides *popUp = new Slides();
        ShootScene *shooterView = new ShootScene();

        bool landingFlag,menuFlag,gameFlag, helpFlag, exitFlag, flagShoot;

        float enemySpeed = 0.001;
        int enmNum = 3;
        float gameTime = 60.0;

        void startingLevel();
        void nextLevel();

    protected:

    private:
};

#endif // GLSCENE_H
